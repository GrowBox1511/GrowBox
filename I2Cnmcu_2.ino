
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <SPI.h>
#include <SD.h>
#include <string>
#include "FirebaseESP8266.h"

#define FIREBASE_HOST "growbox-52071.firebaseio.com"

#define FIREBASE_AUTH "ODA5KgiodLXzwCcoekNBOhfjPRZTUr745GhtKCCX"

//#define WIFI_SSID "MGTS_GPON_2829"
//#define WIFI_PASSWORD "CHTGK9BF"

#define WIFI_SSID "TubondWifi"
#define WIFI_PASSWORD "qwerty123"
#define chipSelect 15
#define PIN_SPI_SS    10
#define PIN_SPI_MOSI  11
#define PIN_SPI_MISO  12
#define PIN_SPI_SCK   13

// define our sensors
int lampPos = 0;

WiFiClient client;
FirebaseData firebaseData;

void setup() {
  Serial.begin(9600);
  
  WiFi.begin (WIFI_SSID, WIFI_PASSWORD);

  //waiting for connection wifi
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }

  Serial.println ("");
  Serial.println ("Connected!");
  Serial.println(WiFi.localIP());



  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);


  //I2C
  Wire.begin(D1, D2);



  Serial.print("Initializing SD card...");

  while (!SD.begin(chipSelect)) {
    Serial.println("Card failed, or not present");
  }
  Serial.println("card initialized.");
}

void loop() {

 String buff = "";

 Firebase.getInt(firebaseData,"/Led");
 lampPos = firebaseData.intData();
 Serial.print("FBout ");
 Serial.print(lampPos);
 Serial.println();
  
 Wire.beginTransmission(8); /* Начинаем передачу на адресе 8 */
 Wire.write("{lamp:");  /* Отправляем "hello Arduino" */
 Wire.write(lampPos);
 Wire.write("}");
 Wire.endTransmission();    /* прекращаем передачу */

 delay(50); //10 pls
 
 Wire.requestFrom(8, 26); //8 adress 26 sym
 
 while(Wire.available()){
    char c = Wire.read();
    buff = buff + c;
 }

 //while(buff[buff.length()-1] == '?') buff.remove(buff.length()-1, 1); 

 File dataFile = SD.open("testLog2.txt", FILE_WRITE);
 if (dataFile) {
    dataFile.println(buff);
    dataFile.close();
    Serial.println(buff);
  }
  else {
    Serial.println("error opening datalog.txt");
  }

 Serial.println();
}
