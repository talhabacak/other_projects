import time
from selenium import webdriver
from selenium.webdriver import ActionChains
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.common.keys import Keys
#from bs4 import BeautifulSoup as BS
from selenium.webdriver.support import expected_conditions as EC
from selenium.webdriver.common.by import By
from openpyxl import load_workbook
from openpyxl import Workbook


class CrawlBook:
    def __init__(self,url="https://www.amazon.com.tr/s?bbn=12466380031&rh=n%3A12466380031%2Cp_85%3A21345931031&dc&qid=1631131188&rnid=21345902031&ref=lp_12466381031_nr_p_85_1"):
        self.login_url = "https://www.amazon.com.tr/ap/signin?openid.pape.max_auth_age=0&openid.return_to=https%3A%2F%2Fwww.amazon.com.tr%2Fb%3Fnode%3D12466380031%26ref_%3Dnav_ya_signin&openid.identity=http%3A%2F%2Fspecs.openid.net%2Fauth%2F2.0%2Fidentifier_select&openid.assoc_handle=trflex&openid.mode=checkid_setup&openid.claimed_id=http%3A%2F%2Fspecs.openid.net%2Fauth%2F2.0%2Fidentifier_select&openid.ns=http%3A%2F%2Fspecs.openid.net%2Fauth%2F2.0&"
        self.url = url 
        self.username = "*************"
        self.password = "*************"
        self.driver = self.get_driver()
        self.driver.maximize_window()
        self.booksName = []
        self.pageBefore = []
        self.pageBefore.append(["item_sku", "isbn_13", "author", "product_description", "manufacturer", "item_name", "language_value1", "img_link","price"])
        self.is_continue = True
        self.book_num = 0
        self.mod = "2"

    def get_driver(self):
        options = webdriver.ChromeOptions()
        print("Driver has created")
        return webdriver.Chrome(r'chromedriver.exe')

    def login(self):
         self.driver.get(self.login_url)
         self.put_email()
         self.put_password()
         #otp = input("OTP kodunu giriniz:\n")
         #self.put_otp(otp)
         self.driver.get(self.url)

    def put_email(self):
        WebDriverWait(self.driver, 3).until(EC.presence_of_element_located((By.CSS_SELECTOR, "label[class='a-form-label']")))
        textarea_username = self.driver.find_element(By.CSS_SELECTOR,"label[class='a-form-label']")
        ActionChains(self.driver).move_to_element(textarea_username).click().send_keys(self.username).perform()
        self.driver.find_element(By.CSS_SELECTOR,"span[class='a-button-inner']").click()

    def put_password(self):
        WebDriverWait(self.driver, 3).until(EC.presence_of_element_located((By.CSS_SELECTOR, "input[id='ap_password']")))
        textarea_password = self.driver.find_element(By.CSS_SELECTOR,"input[id='ap_password']")
        ActionChains(self.driver).move_to_element(textarea_password).click().send_keys(self.password).perform()
        self.driver.find_element(By.CSS_SELECTOR,"span[class='a-button-inner']").click()

    def put_otp(self,otp):
        WebDriverWait(self.driver, 3).until(EC.presence_of_element_located((By.CSS_SELECTOR, "label[class='a-form-label']")))
        textarea_otp = self.driver.find_element(By.CSS_SELECTOR,"label[class='a-form-label']")
        ActionChains(self.driver).move_to_element(textarea_otp).click().send_keys(otp).perform()
        self.driver.find_element(By.CSS_SELECTOR,"span[class='a-button-inner']").click()

    def sku_generator(self):
        name = self.name.lower()
        name = name.replace('ç', 'c')
        name = name.replace('ı', 'i')
        name = name.replace('ö', 'o')
        name = name.replace('ü', 'u')
        name = name.replace('ş', 's')
        name = name.replace('ğ', 'g')
        name = name.replace(' ', '_')

        sku_name = name + str(self.book_num).zfill(5)
        return sku_name
    
    def getMode(self):
        while not self.mod == "1" and not self.mod == "0":
            self.mod = input("Bütün kategoriler için 1, bulunduğunuz kategori için 0 giriniz:\n")
                
    def start(self):
        WebDriverWait(self.driver, 20).until(EC.presence_of_element_located((By.XPATH, "//*[@id='s-refinements']/div[6]/ul/li/span/a")))
        nextpage_obj = self.driver.find_element(By.XPATH,"//*[@id='s-refinements']/div[6]/ul/li/span/a")
        nextpage = nextpage_obj.get_attribute("href")
        self.driver.get(nextpage)
        WebDriverWait(self.driver, 20).until(EC.presence_of_element_located((By.XPATH, "//*[@id='p_n_fulfilled_by_amazon/21345978031']/span/a")))
        nextpage_obj = self.driver.find_element(By.XPATH,"//*[@id='p_n_fulfilled_by_amazon/21345978031']/span/a")
        nextpage = nextpage_obj.get_attribute("href")
        self.driver.get(nextpage)
        WebDriverWait(self.driver, 20).until(EC.presence_of_element_located((By.XPATH, "//*[@id='p_n_fulfilled_by_amazon/21345978031']/span/a")))
        nextpage_obj = self.driver.find_element(By.XPATH,"//*[@id='p_n_availability/13136583031']/span/a/div")
        nextpage = nextpage_obj.get_attribute("href")
        self.driver.get(nextpage)
        
    def end(self):
        wb = Workbook()
        page = wb.active
        count = 1
        for i in self.pageBefore:
            try:
                page.append(i)
            except:
                print(count +" . satır yazılamadı")
            count += 1
            
        try:
            wb.save(filename=self.name + ".xlsx")
            wb.close()
        except Exception as e:
            print(e)
            print("dosya yazılamadı")

        try:
            self.driver.close()
        except Exception as e:
            print(e)

        
    def pagination(self):
        if self.mod == "1":
            self.allCategory()
        else:
            self.thisCategory()
        
    def allCategory(self):
        try:
            count = 0
            main_category_list = self.get_main_categories()
            for mainCategory in main_category_list:
                WebDriverWait(self.driver, 20)
                self.driver.get(mainCategory)
                try:
                    sub_category_list = self.get_main_categories()
                    sub_category_list.pop(0)
                    for subCategory in sub_category_list:
                        WebDriverWait(self.driver, 20)
                        self.driver.get(subCategory)
                        lastpage = subCategory
                        self.is_continue = True
                        while(self.is_continue):
                            WebDriverWait(self.driver, 20)
                            self.get_books()
                            WebDriverWait(self.driver, 20)
                            self.driver.get(lastpage)
                            try:
                                nextpage_obj = self.driver.find_element(By.XPATH,"//*[@id='search']/div[1]/div[1]/div/span[3]/div[2]/div[17]/div/div/span/a[last()]")
                                nextpage = nextpage_obj.get_attribute("href")
                                lastpage = nextpage
                                WebDriverWait(self.driver, 20)
                                self.driver.get(nextpage)
                            except:
                                self.is_continue = False
                except:
                    print("alt kategori yok ya da atlandı")
                count += 1
        except Exception as e:
            print("Hata: " +str(e))
        print("Bitti")
        
    def thisCategory(self):
        try:
            count = 0
            lastpage = self.driver.current_url
            while(self.is_continue):
                self.get_books()
                WebDriverWait(self.driver, 20)
                self.driver.get(lastpage)
                try:
                    nextpage_obj = self.driver.find_element(By.XPATH,"//*[@id='search']/div[1]/div[1]/div/span[3]/div[2]/div[17]/div/div/span/a[last()]")
                    nextpage = nextpage_obj.get_attribute("href")
                    lastpage = nextpage
                    WebDriverWait(self.driver, 20)
                    self.driver.get(nextpage)
                except:
                    self.is_continue = False
                count += 1
        except Exception as e:
            print("Hata: " +str(e))
        print("Bitti")
        
    def get_main_categories(self):
        categories = self.driver.find_elements(By.XPATH,"//*[@id='departments']/ul/li/span/a")
        category_list = []
        for category in categories:
            category_url = category.get_attribute("href")
            category_list.append(category_url)
        print("(ana/alt) kategori sayısı:" ,len(category_list))
        return category_list

    def get_books(self):
        books = self.driver.find_elements(By.XPATH,"//*[@id='search']/div[1]/div[1]/div/span[3]/div[2]/div/div/div/div/div/div/div[2]/div/div/div[1]/h2/a")
        book_list = []
        for book in books:
            book_url = book.get_attribute("href")
            book_list.append(book_url)
        print("kitap sayısı:" ,len(books))
        self.get_book_info(book_list)

    def get_book_info(self,book_list):
        for book in book_list:
            WebDriverWait(self.driver, 20)
            try:
                sku = "sku"
                product_description = "product_description"
                manifacturer = "manifacturer"
                item_name = "item_name"
                language_value1 = "language_value1"
                img_link = "img_link"
                price = "price"
                isbn_13 ="isbn_13"
                name = "name"
                author = "author"
                self.driver.get(book)
                
                name = self.driver.find_element(By.XPATH,"//span[@id='productTitle']").text
            except Exception as e:
                print(e)
                
            try:
                price = self.driver.find_element(By.XPATH,"//span[@id='price']").text.split()[0]
            except Exception as e:
                print(e)
                #print(name + " price")

            try:
                product_description = self.driver.find_element(By.XPATH,"//div[@class='a-section a-spacing-small a-padding-small']").text
            except Exception as e:
                print(e)
                #print(name + " product_description")

            try:
                author = self.driver.find_element(By.XPATH,"//span[@class='author notFaded']/a").text
            except Exception as e:
                   print(e)
                   #print(name +" author")
    
            try:
                item_name = self.driver.find_element(By.XPATH,"//span[@id='productTitle']").text
            except Exception as e:
                print(e)
                #print(name +" item_name")
                
            try:
                img_link = self.driver.find_element(By.XPATH,"//div[@id='img-canvas']/img").get_attribute("src")
            except Exception as e:
                print(e)
                #print(name + " img_link")
                
            try:
                WebDriverWait(self.driver, 10)
                uls = self.driver.find_elements(By.XPATH,"//*[@id='detailBullets_feature_div']/ul/li")
            except Exception as e:
                 print(e)
                 #print(name + " uls")    
                 
            for ul in uls:
                try:
                    name = ul.find_element(By.XPATH,"span/span[1]").text
                except Exception as e:
                     print(e)
                     #print(name + " name")
                     name="Dil : "
                if name=="Yayıncı :":
                    try:
                        manifacturer_ = ul.find_element(By.XPATH,"span/span[2]").text
                        manifacturer = manifacturer_.split(";")[0]
                        
                        manifacturer = manifacturer.replace('ç', 'c')
                        manifacturer = manifacturer.replace('ı', 'i')
                        manifacturer = manifacturer.replace('ö', 'o')
                        manifacturer = manifacturer.replace('ü', 'u')
                        manifacturer = manifacturer.replace('ş', 's')
                        manifacturer = manifacturer.replace('ğ', 'g')
                    except:
                        manifacturer = "manifacturer"
                    
                elif name=="Dil :":
                    try:
                        language_value1 = ul.find_element(By.XPATH,"span/span[2]").text
                    except Exception as e:
                         print(e)
                         #print(name + " name")
                         language_value1="gelmedi"
                
                elif name=="ISBN-13 :":               
                    try:
                        isbn_13 = ul.find_element(By.XPATH,"span/span[2]").text
                        isbn_13 = isbn_13.replace("-", "")
                    except Exception as e:
                        print(e)
                        #print(name + " name")
                        isbn_13 =" "
                        
            try:
                flag = 0
                for i in self.booksName:
                    if i == item_name or item_name == "item_name":
                        flag = 1
                        
                if flag == 0:
                    sku = self.sku_generator()
                    self.booksName.append(item_name)
                    self.pageBefore.append([sku, isbn_13, author, product_description, manifacturer, item_name, language_value1, img_link, price])
                    self.book_num += 1
            except Exception as e:
                print(e)

if __name__ == "__main__":
    obj = CrawlBook()
    obj.login()
    obj.start()
    obj.name = input("SKU ön ekini giriniz:\n")
    obj.getMode()
    obj.pagination()
    obj.end()