#include <Wire.h>
#include <ESP8266HTTPClient.h>
#include "FirebaseESP8266.h"

#define FIREBASE_HOST "growbox-52071.firebaseio.com"

#define FIREBASE_AUTH "ODA5KgiodLXzwCcoekNBOhfjPRZTUr745GhtKCCX"

//#define WIFI_SSID "MGTS_GPON_2829"
//#define WIFI_PASSWORD "CHTGK9BF"

#define WIFI_SSID "TubondWifi"
#define WIFI_PASSWORD "qwerty123"


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
  
  Wire.begin(D1, D2); /* задаем i2c мост через контакты SDA=D1 и SCL=D2 на NodeMCU */
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
 
 Wire.requestFrom(8, 26); /* запрашиваем и считываем данные с 8 и 13 адреса slave устройства */
 while(Wire.available()){
    char c = Wire.read();
    buff = buff + c;
 //   Serial.print(c);
 }

 Serial.println(buff);
 Serial.println();
}
