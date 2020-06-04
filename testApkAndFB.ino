/*
    For tests we are using relay for lamp (it will be growbox lamp),
    photoresistor, 2 line display (if I2C exists),
    air temperature and humidity sensor, rgb
    
    *************************************************
    *
    using firebase for connection android <-> esp
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "FirebaseESP8266.h"
#include "DHT.h"

#define FIREBASE_HOST "growbox-52071.firebaseio.com"

#define FIREBASE_AUTH "ODA5KgiodLXzwCcoekNBOhfjPRZTUr745GhtKCCX"

//#define WIFI_SSID "MGTS_GPON_2829"
//#define WIFI_PASSWORD "CHTGK9BF"

#define WIFI_SSID "TubondWifi"
#define WIFI_PASSWORD "qwerty123"


// define our sensors
#define LAMP 13 
#define PHOTORESISTOR A0
#define DHTPIN 12
#define RedColor 4
#define GreenColor 0
#define BlueColor 2

int r_color = 0, 
    g_color = 0, 
    b_color = 0; 

WiFiClient client;
FirebaseData firebaseData;
DHT dht(DHTPIN, DHT11);

bool wifiConnection();

void setup() {
  Serial.begin(115200);

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

  pinMode(LAMP, OUTPUT);
  pinMode(PHOTORESISTOR, OUTPUT);
  dht.begin();
}

void loop() {

  int countGets = 0,
      val;
  
  if(wifiConnection());

  while(countGets < 20){
  
    Firebase.getInt(firebaseData,"/Led");
    val = firebaseData.intData();
    digitalWrite(LAMP, val);
    Serial.println(val);

    //red
    Firebase.getInt(firebaseData,"/RedColor");
    r_color = firebaseData.intData();
    analogWrite(RedColor, r_color);
    
    //green
    Firebase.getInt(firebaseData,"/GreenColor");
    g_color = firebaseData.intData();
    analogWrite(GreenColor, g_color);
    
    //blue
    Firebase.getInt(firebaseData,"/BlueColor");
    b_color = firebaseData.intData();
    analogWrite(BlueColor, b_color);
    
    countGets++;
    
  }
// val = analogRead(PHOTORESISTOR);
  val = dht.readTemperature();
  Firebase.set(firebaseData,"/Temperature",val);
  Serial.println(val);
  
  val = dht.readHumidity();
  Firebase.set(firebaseData,"/HumidityAir",val);
  Serial.println(val);
  
  val = analogRead(PHOTORESISTOR);
  Firebase.set(firebaseData,"/Photoresistor",val);
  Serial.println(val);

}

//checks is wifi connected
bool wifiConnection(){

  if (WiFi.status() == WL_CONNECTED)
    return true;
  
  //waiting for connection wifi
  while (WiFi.status() != WL_CONNECTED) {
    delay(250);
    Serial.print(".");
  }
  
  return false;
}

