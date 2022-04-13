#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include <ctype.h>

// sonuclarin yazdirilmasi
void resultText(int *sinif, char filePath[], int i){
	
	if(sinif[i] == 1){
		printf("\n%s = Tarih\n", filePath);
	}
	else if(sinif[i] == 2){
		printf("\n%s = Tip\n", filePath);
	}
	else{
		printf("\nHatali Sonuc\n");
	}
	
}

// belirtilen metne en cok benzeyen metni bulan algoritma
int findMax(float **matris, int i){
	int j;
	int maxSim = 0;
	int maxIndex = 0;
	
	for(j=0; j<12; j++){
		if (matris[i][j] > maxSim){
			maxSim = matris[i][j];
			maxIndex = j;
		}
	}
	
	return maxIndex;
}

// benzerlik oranlarina göre siniflandiran algoritma
void design(float **matris, int *sinif){
	int i, j, k, index, tempIndex;;
	int flag = 1;
	int count, max, maxSim,maxI, maxJ;
	
	sinif[10] = 1;
	sinif[11] = 2;
	
	/*
	printf("\n0\t1\t2\t3\t4\t5\t6\t7\t8\t9\t10\t11\n\n");
	for(tempIndex=0; tempIndex<12; tempIndex++){
		printf("%d\t", sinif[tempIndex]);	
	}
	printf("\n");
	*/
	
	count = 0;
	i = 10;
	while(flag == 1){
		index = findMax(matris, i);
		if(sinif[index] != 0 && sinif[i] == 0){
			sinif[i] = sinif[index];
		}
		else{
			count++;
		}
		
		if(count == 14){
			maxSim = 0;
			for(k = 0; k <12; k++){
				for(j=0; j<12; j++){
					if (matris[k][j] > maxSim && sinif[j] == 0 && sinif[k] != 0){
						maxSim = matris[k][j];
						maxJ = j;
						maxI = k;
					}
				}
			}
			if(sinif[maxI] != 0 && sinif[maxJ] == 0){
				sinif[maxJ] = sinif[maxI];
			}
			count = 0;
		}
		
		flag = 0;
		for(j=0; j<12; j++){
			if(sinif[j] == 0){
				flag = 1;
			}
		}
		
		i++;
		i %= 12;
		
		/*
		for(tempIndex=0; tempIndex<12; tempIndex++){
			printf("%d\t", sinif[tempIndex]);	
		}
		printf("\n");
		*/
	}
	
}

// 2 textin karsilastirilarak benzerlik oraninin cikartilmasi
float wordComparison(char *text, char *comparisonText){
	int i = 0, j, k, start;
	int countText, countComparison;
	int countWord = 0, sumWord = 0;
	float result;
	
	while(text[i] != '\0'){
		char textTemp[30];
		countText = 0;
		start = i;
		while(text[i] != '\n' && text[i] != ' ' && text[i] != '\0'){
			textTemp[countText] = text[i];			
			i++;
			countText++;
			sumWord++;
		}
		textTemp[countText] = '\0';
		
		j = 0;
		while(comparisonText[j] != '\0'){
			char comparisonTemp[30];
			countComparison = 0;
			while(comparisonText[j] != '\n' && comparisonText[j] != ' ' && comparisonText[j] != '\0'){
				comparisonTemp[countComparison] = comparisonText[j];			
				j++;
				countComparison++;
			}
			comparisonTemp[countComparison] = '\0';
			
			if(strcmp(textTemp,comparisonTemp) == 0){
				countWord++;
			}
			j++;
		}
		i++;
	}

	result = countWord/(float)sumWord;
	
	return result;
}

// dosyalarin arasindaki benzerlik oranini bulan algoritma
void similarity(char *text0, char *text1, char *text2, char *text3, char *text4, char *text5, char *text6, char *text7
, char *text8, char *text9, char *history, char *med, float **similarityMatrix ){
	int i, j;

	similarityMatrix[0][1] = wordComparison(text0, text1);
	similarityMatrix[0][2] = wordComparison(text0, text2);
	similarityMatrix[0][3] = wordComparison(text0, text3);
	similarityMatrix[0][4] = wordComparison(text0, text4);
	similarityMatrix[0][5] = wordComparison(text0, text5);
	similarityMatrix[0][6] = wordComparison(text0, text6);
	similarityMatrix[0][7] = wordComparison(text0, text7);
	similarityMatrix[0][8] = wordComparison(text0, text8);
	similarityMatrix[0][9] = wordComparison(text0, text9);
	similarityMatrix[0][10] = wordComparison(text0, history);
	similarityMatrix[0][11] = wordComparison(text0, med);

	similarityMatrix[1][2] = wordComparison(text1, text2);
	similarityMatrix[1][3] = wordComparison(text1, text3);
	similarityMatrix[1][4] = wordComparison(text1, text4);
	similarityMatrix[1][5] = wordComparison(text1, text5);
	similarityMatrix[1][6] = wordComparison(text1, text6);
	similarityMatrix[1][7] = wordComparison(text1, text7);
	similarityMatrix[1][8] = wordComparison(text1, text8);
	similarityMatrix[1][9] = wordComparison(text1, text9);
	similarityMatrix[1][10] = wordComparison(text1, history);
	similarityMatrix[1][11] = wordComparison(text1, med);

	similarityMatrix[2][3] = wordComparison(text2, text3);
	similarityMatrix[2][4] = wordComparison(text2, text4);
	similarityMatrix[2][5] = wordComparison(text2, text5);
	similarityMatrix[2][6] = wordComparison(text2, text6);
	similarityMatrix[2][7] = wordComparison(text2, text7);
	similarityMatrix[2][8] = wordComparison(text2, text8);
	similarityMatrix[2][9] = wordComparison(text2, text9);
	similarityMatrix[2][10] = wordComparison(text2, history);
	similarityMatrix[2][11] = wordComparison(text2, med);

	similarityMatrix[3][4] = wordComparison(text3, text4);
	similarityMatrix[3][5] = wordComparison(text3, text5);
	similarityMatrix[3][6] = wordComparison(text3, text6);
	similarityMatrix[3][7] = wordComparison(text3, text7);
	similarityMatrix[3][8] = wordComparison(text3, text8);
	similarityMatrix[3][9] = wordComparison(text3, text9);
	similarityMatrix[3][10] = wordComparison(text3, history);
	similarityMatrix[3][11] = wordComparison(text3, med);

	similarityMatrix[4][5] = wordComparison(text4, text5);
	similarityMatrix[4][6] = wordComparison(text4, text6);
	similarityMatrix[4][7] = wordComparison(text4, text7);
	similarityMatrix[4][8] = wordComparison(text4, text8);
	similarityMatrix[4][9] = wordComparison(text4, text9);
	similarityMatrix[4][10] = wordComparison(text4, history);
	similarityMatrix[4][11] = wordComparison(text4, med);

	similarityMatrix[5][6] = wordComparison(text5, text6);
	similarityMatrix[5][7] = wordComparison(text5, text7);
	similarityMatrix[5][8] = wordComparison(text5, text8);
	similarityMatrix[5][9] = wordComparison(text5, text9);
	similarityMatrix[5][10] = wordComparison(text5, history);
	similarityMatrix[5][11] = wordComparison(text5, med);

	similarityMatrix[6][7] = wordComparison(text6, text7);
	similarityMatrix[6][8] = wordComparison(text6, text8);
	similarityMatrix[6][9] = wordComparison(text6, text9);
	similarityMatrix[6][10] = wordComparison(text6, history);
	similarityMatrix[6][11] = wordComparison(text6, med);

	similarityMatrix[7][8] = wordComparison(text7, text8);
	similarityMatrix[7][9] = wordComparison(text7, text9);
	similarityMatrix[7][10] = wordComparison(text7, history);
	similarityMatrix[7][11] = wordComparison(text7, med);

	similarityMatrix[8][9] = wordComparison(text8, text9);
	similarityMatrix[8][10] = wordComparison(text8, history);
	similarityMatrix[8][11] = wordComparison(text8, med);

	similarityMatrix[9][10] = wordComparison(text9, history);
	similarityMatrix[9][11] = wordComparison(text9, med);
	
	i=0;
	while(i<12){
		j=0;
		while(j<i){
			similarityMatrix[i][j] = similarityMatrix[j][i];
			j++;
		}
		i++;
	}
	
	/*
	printf("\n\t0\t\t1\t\t2\t\t3\t\t4\t\t5\t\t6               7\t\t8\t\t9\t\t10\t\t11\n\n");
	for(i=0; i<12; i++){
		printf("%d", i);
		for(j=0; j<12; j++){
			printf("\t%f", similarityMatrix[i][j]);
		}
		printf("\n\n");
	}
	*/
}

// newline ve tab'larin kaldirilmasi
void preprocessing1(char *text){
	int i = 0;
	while(text[i]!='\0'){
		if(text[i] == '\n' || text[i] == '\t'){
			text[i] = ' ';
		}
		i++;
	}
}

// ekstra whitespacelerin kaldirilmasi
void preprocessing2(char *text){
	int i = 0, j;
	while(text[i]!='\0'){
		if(text[i] == ' ' ){
			j = i+1;
			while(text[j] == ' '){
				memmove(&text[j], &text[j + 1], strlen(text) - j);				
				j;
			}
		}
		i++;
	}
}

// noktalama isaretlerinin kaldirilmasi
void preprocessing3(char *text){
	int i = 0;
	while(text[i]!='\0'){
		if(text[i] == '.' || text[i] == ',' || text[i] == ':' || text[i] == ';' || 
		text[i] == '-' || text[i] == '/' || text[i] == '"' || text[i] == '“' || 
		text[i] == '”' || text[i] == '!' || text[i] == '?' || text[i] == '©'|| 
		text[i] == '<' || text[i] == '>' || text[i] == '(' || text[i] == ')' || 
		text[i] == '+'){
			text[i] = ' ';
		}
		i++;
	}
}

// kucuk harfe cevirilmesi
void preprocessing4(char *text){
	int i;
	for(i = 0; text[i]; i++){
	  text[i] = tolower(text[i]);
	}
}

// stop words'lerin kaldirilmasi
void preprocessing5(char *text, char *stopWords){
	int i = 0, j, k, start;
	int countText, countStopWord;
	
	while(text[i] != '\0'){
		char textTemp[30];
		countText = 0;
		start = i;
		while(text[i] != ' ' && text[i] != '\0'){
			textTemp[countText] = text[i];			
			i++;
			countText++;
		}
		textTemp[countText] = '\0';

		j = 0;
		while(stopWords[j] != '\0'){
			char stopWordsTemp[30];
			countStopWord = 0;
			while(stopWords[j] != '\n' && stopWords[j] != ' ' && stopWords[j] != '\0'){
				stopWordsTemp[countStopWord] = stopWords[j];			
				j++;
				countStopWord++;
			}
			stopWordsTemp[countStopWord] = '\0';
			
			if(strcmp(textTemp,stopWordsTemp) == 0){
				for(k=start; k<start+countText; k++){
					memmove(&text[k], &text[k + 1], strlen(text) - k);					
				}
			}
			j++;
		}
		i++;
	}
}

// text dosyalarinin okunmasi
void input(char filePath[], FILE *fp, char *text){	
	int i= 0;
	fp = fopen(filePath,"r");
	if (fp == NULL) {
		printf("Error opening file %s\n",filePath);
		exit ( 1 );
	}
	while(!feof(fp)){
		text[i] = fgetc(fp);
		i++;
	}
	text[i] = '\0';
}

int main(){
	int i,j;
	
	FILE *fp0, *fp1, *fp2, *fp3, *fp4, *fp5, *fp6, *fp7, *fp8, *fp9;
	char filePath0[] = "datafile-0.txt", filePath1[] = "datafile-1.txt", filePath2[] = "datafile-2.txt", filePath3[] = "datafile-3.txt", filePath4[] = "datafile-4.txt";
	char filePath5[] = "datafile-5.txt", filePath6[] = "datafile-6.txt", filePath7[] = "datafile-7.txt", filePath8[] = "datafile-8.txt", filePath9[] = "datafile-9.txt";
	char *text0, *text1, *text2, *text3, *text4, *text5, *text6, *text7, *text8, *text9; 

	FILE *fpStopWords;
	char filePathStopWords[] = "stop_words_english.txt";
	char *stopWords;

	FILE *fpHistory, *fpMed;
	char filePathHistory[] = "history.txt", filePathMed[] = "medicine.txt";
	char *history, *med;

	float **similarityMatrix;
	int *sinif;
	
	// dinamik string olusturma
	text0 = (char*)malloc( 10000 * sizeof(char) );
	text1 = (char*)malloc( 10000 * sizeof(char) );
	text2 = (char*)malloc( 10000 * sizeof(char) );
	text3 = (char*)malloc( 10000 * sizeof(char) );
	text4 = (char*)malloc( 10000 * sizeof(char) );
	text5 = (char*)malloc( 10000 * sizeof(char) );
	text6 = (char*)malloc( 10000 * sizeof(char) );
	text7 = (char*)malloc( 10000 * sizeof(char) );
	text8 = (char*)malloc( 10000 * sizeof(char) );
	text9 = (char*)malloc( 10000 * sizeof(char) );
	stopWords = (char*)malloc( 20000 * sizeof(char) );
	history = (char*)malloc( 20000 * sizeof(char) );
	med = (char*)malloc( 20000 * sizeof(char) );
	
	// dinamik matris olusturma
	similarityMatrix=(float **)calloc(24, sizeof(float));
	for(i=0;i<12;i++){
		similarityMatrix[i]=(float *)calloc(12, sizeof(float));
	}
	
	// dinamik sinif dizisinin olusturulmasi
	sinif = (int *)calloc(12, sizeof(int));

	// dosyalarin okunmasi
	input(filePath0, fp0,text0);
	input(filePath1, fp1,text1);
	input(filePath2, fp2,text2);
	input(filePath3, fp3,text3);
	input(filePath4, fp4,text4);
	input(filePath5, fp5,text5);
	input(filePath6, fp6,text6);
	input(filePath7, fp7,text7);
	input(filePath8, fp8,text8);
	input(filePath9, fp9,text9);
	input(filePathStopWords, fpStopWords, stopWords);	
	input(filePathHistory, fpHistory, history);	
	input(filePathMed, fpMed, med);	
	
	// newline ve tab'larin kaldirilmasi
	preprocessing1(text0);
	preprocessing1(text1);
	preprocessing1(text2);
	preprocessing1(text3);
	preprocessing1(text4);
	preprocessing1(text5);
	preprocessing1(text6);
	preprocessing1(text7);
	preprocessing1(text8);
	preprocessing1(text9);
	preprocessing1(stopWords);
	preprocessing1(history);
	preprocessing1(med);
	
	// noktalama isaretlerinin kaldirilmasi
	preprocessing3(text0);
	preprocessing3(text1);
	preprocessing3(text2);
	preprocessing3(text3);
	preprocessing3(text4);
	preprocessing3(text5);
	preprocessing3(text6);
	preprocessing3(text7);
	preprocessing3(text8);
	preprocessing3(text9);
	preprocessing3(stopWords);
	preprocessing3(history);
	preprocessing3(med);

	// kucuk harfe cevirilmesi
	preprocessing4(text0);
	preprocessing4(text1);
	preprocessing4(text2);
	preprocessing4(text3);
	preprocessing4(text4);
	preprocessing4(text5);
	preprocessing4(text6);
	preprocessing4(text7);
	preprocessing4(text8);
	preprocessing4(text9);
	preprocessing4(stopWords);
	preprocessing4(history);
	preprocessing4(med);
	
	// stop words'lerin kaldirilmasi
	preprocessing5(text0, stopWords);
	preprocessing5(text1, stopWords);
	preprocessing5(text2, stopWords);
	preprocessing5(text3, stopWords);
	preprocessing5(text4, stopWords);
	preprocessing5(text5, stopWords);
	preprocessing5(text6, stopWords);
	preprocessing5(text7, stopWords);
	preprocessing5(text8, stopWords);
	preprocessing5(text9, stopWords);
	preprocessing5(history, stopWords);
	preprocessing5(med, stopWords);

	// ekstra whitespacelerin kaldirilmasi
	preprocessing2(text0);
	preprocessing2(text1);
	preprocessing2(text2);
	preprocessing2(text3);
	preprocessing2(text4);
	preprocessing2(text5);
	preprocessing2(text6);
	preprocessing2(text7);
	preprocessing2(text8);
	preprocessing2(text9);
	preprocessing2(stopWords);
	preprocessing2(history);
	preprocessing2(med);

	// benzerlik algoritmasi
	similarity(text0, text1, text2, text3, text4, text5, text6, text7, text8, text9, history, med, similarityMatrix);
	
	// siniflandirma algoritmasi
	design(similarityMatrix, sinif);

	// Sonuclarin yazdirilmasi
	resultText(sinif, filePath0, 0);
	resultText(sinif, filePath1, 1);
	resultText(sinif, filePath2, 2);
	resultText(sinif, filePath3, 3);
	resultText(sinif, filePath4, 4);
	resultText(sinif, filePath5, 5);
	resultText(sinif, filePath6, 6);
	resultText(sinif, filePath7, 7);
	resultText(sinif, filePath8, 8);
	resultText(sinif, filePath9, 9);

	// dinamik dizilerin ram'den silinmesi
	free(text0);
	free(text1);
	free(text2);
	free(text3);
	free(text4);
	free(text5);
	free(text6);
	free(text7);
	free(text8);
	free(text9);
	free(stopWords);
	free(history);
	free(med);
	for(i=0; i<12; i++){
		free(similarityMatrix[i]);
	}
	free(similarityMatrix);
	free(sinif);
	
	// acilan dosyalarin kapatilmasi
	fclose(fp0);
	fclose(fp1);
	fclose(fp2);
	fclose(fp3);
	fclose(fp4);
	fclose(fp5);
	fclose(fp6);
	fclose(fp7);
	fclose(fp8);
	fclose(fp9);
	fclose(fpStopWords);
	fclose(fpHistory);
	fclose(fpMed);
	
	return 0;
}
