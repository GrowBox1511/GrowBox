#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "FirebaseESP8266.h"

#define FIREBASE_HOST "growbox-52071.firebaseio.com"
#define FIREBASE_AUTH "ODA5KgiodLXzwCcoekNBOhfjPRZTUr745GhtKCCX"
#define WIFI_SSID "kolobok10"
#define WIFI_PASSWORD "19-mihailova-66"

WiFiClient client;
FirebaseData firebaseData;
//LiquidCrystal_I2C lcd(0x27, 16, 2);
int hum = 0;
void setup(){
 Serial.begin(9600);
 WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }
 Serial.println ("");
 Serial.println ("Connected!");
 Serial.println(WiFi.localIP());

 Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

 }
 
void loop(){
  Serial.println(analogRead(hum)); 
  Firebase.set(firebaseData,"/HumiditySoil",analogRead(hum));
  delay(3000);
}
