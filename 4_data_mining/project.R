
# Libraries
library(glmnet)
library(mice)
library(caret)
library(tidyverse)
library(rpart)
library(randomForest)

#####################################################

# import data
data <- read.csv("FinalDataset.csv", sep=";")

######################################################

#preprocessing data
minMaxNorm <- function(x){
  
  return ((x-min(x)) / (max(x) - min(x)))
}

data$X=NULL

data$Global_Sales <- gsub(",", ".", data$Global_Sales)
data$Global_Sales <- as.double(data$Global_Sales)
data$Platform <- as.factor(data$Platform)
data$Genre <- as.factor(data$Genre)
data$Rating <- as.factor(data$Rating)
data$PublisherR <- as.factor(data$PublisherR)

data$Critic_Score <- minMaxNorm(data$Critic_Score)
data$Critic_Count <- minMaxNorm(data$Critic_Count)
data$Global_Sales <- minMaxNorm(data$Global_Sales)

data <- sapply(data, unclass)

#data info
cor(data)
pairs(na.omit(data))
md.pattern(data)

# train data and test data
train <- as.data.frame(data[1:1000,])
test <- as.data.frame(data[1001:nrow(data),])

names(train)
names(test)

#########################################################

#Regression Model
modelRegression <- lm(Global_Sales ~ ., data = train)
# coefficients, adjusted R square and F statistic of Regression the model
summary(modelRegression)

#########################################################

#Regression Prediction and RMSE
predictionsReg <- predict(modelRegression, test)
Reg_RMSE <- RMSE(predictionsReg, test$Global_Sales)
Reg_RMSE
#########################################################

# preprocessing data before Ridge and Lasso
num_cols <- c("Critic_Count","Critic_Score","Global_Sales")
pre_scaled <- preProcess(data[,num_cols], method = c("center","scale"))
dataScaled <- predict(pre_scaled, data)
dataScaled <- as.data.frame(dataScaled)

model.matrix(Global_Sales ~ ., data = dataScaled)

trainRidgeLasso <- as.data.frame(dataScaled[1:1000,])
testRidgeLasso <- as.data.frame(dataScaled[1001:nrow(dataScaled),])

trainRidgeLasso_x <- as.data.frame(trainRidgeLasso[,1:ncol(trainRidgeLasso)-1])
trainRidgeLasso_y <- trainRidgeLasso$Global_Sales
trainRidgeLasso_y <- (trainRidgeLasso_y)

trainRidgeLasso_x <- as.matrix(trainRidgeLasso_x)
trainRidgeLasso_y <- as.matrix(trainRidgeLasso_y)

testRidgeLasso_x <- as.data.frame(testRidgeLasso[,1:ncol(testRidgeLasso)-1])
testRidgeLasso_y <- testRidgeLasso$Global_Sales
testRidgeLasso_y <- (testRidgeLasso_y)

testRidgeLasso_x <- as.matrix(testRidgeLasso_x)
testRidgeLasso_y <- as.matrix(testRidgeLasso_y)

#########################################################

#Determine the lambda parameter using cross-validation
lambdas = 10^seq(3,-2,by=-.01)
modelRidgeCV <- cv.glmnet(trainRidgeLasso_x,trainRidgeLasso_y, alpha = 0, lambda = lambdas, nfolds = 10)
modelRidgeCV$lambda.min

#Ridge Model
modelRidge <- glmnet(trainRidgeLasso_x,trainRidgeLasso_y, alpha = 0, lambda = modelRidgeCV$lambda.min)
summary(modelRidge)

#########################################################

#Determine the lambda parameter using cross-validation
modelLassoCV <- cv.glmnet(trainRidgeLasso_x,trainRidgeLasso_y, alpha = 1, lambda = lambdas, nfolds = 3)
modelLassoCV$lambda.min

#Lasso Model
modelLasso <- glmnet(trainRidgeLasso_x,trainRidgeLasso_y, alpha = 1, lambda = modelLassoCV$lambda.min)
summary(modelLasso)

#########################################################

# Ridge and Lasso Prediction and RMSE
predictionRidge <- predict(modelRidge, testRidgeLasso_x)
predictionLasso <- predict(modelLasso, testRidgeLasso_x)

Ridge_RMSE <- RMSE(predictionRidge, testRidgeLasso_y)
Lasso_RMSE <- RMSE(predictionLasso, testRidgeLasso_y)

Ridge_RMSE
Lasso_RMSE

#########################################################

#Regression Tree Model
modelRegTree <- rpart(Global_Sales ~ ., data=train)

#########################################################

#Regression Tree Prediction and RMSE
predictionRegTree <- predict(modelRegTree, test)
RT_RMSE <- RMSE(predictionRegTree, test$Global_Sales)
RT_RMSE

#########################################################

#Random Forest Model
modelRF <- randomForest(Global_Sales ~ ., data=train, ntree=500)

#########################################################

# Random Forest Prediction and RMSE
predictionRF <- predict(modelRF, test)
RF_RMSE <- RMSE(predictionRF, test$Global_Sales)
RF_RMSE

#########################################################

# All RMSE
Reg_RMSE   #Lineer Regresyon
Ridge_RMSE #Ridge Regresyon
Lasso_RMSE #Lasso Regresyon
RT_RMSE    #Regresyon Tree
RF_RMSE    #Random Forest

# coefficients, adjusted R square and F statistic of Regression the model
summary(modelRegression)



