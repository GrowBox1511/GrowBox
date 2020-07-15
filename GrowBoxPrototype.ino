#include <HX711.h>
#define RelayPin 6
#define Humid 1
#define A3 17
#define A2 16
HX711 scale;
float calib = -3.7;
float un;
float gr;
void setup() {
Serial.begin(9600);
scale.begin(A3, A2);
scale.set_scale();
scale.tare();
scale.set_scale(calib);
pinMode(RelayPin, OUTPUT);
digitalWrite(RelayPin, HIGH);
}

void loop() {
for(int i = 0; i<10; i++)un+=scale.get_units(), 10;
un/10;
gr = un * 0.035274;
Serial.print(gr);
Serial.print("grams");
Serial.println(analogRead(Humid));
while(analogRead(Humid)<700){
   digitalWrite(RelayPin, LOW);
  }
digitalWrite(RelayPin, HIGH);
Serial.println(analogRead(Humid));
delay(3000);
}
