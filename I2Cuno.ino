#include <Wire.h>

#define LAMP 2


int intBuff = 0;

void setup() {
 
 pinMode(LAMP, OUTPUT);
  
 Wire.begin(8);                /* задаем на шине i2c 8 адрес */
 Wire.onReceive(receiveEvent); /* регистрируем полученное событие */
 Wire.onRequest(requestEvent); /* регистрируем запрошенное событие */
 Serial.begin(9600);           /* открываем серийный порт для дебаггинга */
}

void loop() {
 delay(10);
}

// Функция для извлечения любых принимаемых данных от мастера на шину
void receiveEvent(int howMany) {
 String buffRE = "";
 while (0 <Wire.available()) {
    char c = Wire.read();      /* получаем байт как символ*/
    buffRE = buffRE + c;
    if(buffRE == "{lamp:"){
      intBuff = Wire.read();
      c = Wire.read();
      buffRE = buffRE + intBuff + c;
      Serial.println();
      Serial.println(buffRE); 
      Serial.println(intBuff); 
      Serial.println();
      digitalWrite(LAMP, intBuff);
      break;
    }
   // Serial.print(c);           /* выводим символ в серийный порт */
  }
 Serial.println();             /* переходим на новую строку */
}

// Функция для извлечения любых отправляемых данных от мастера на шину
void requestEvent() {
     char buffer__ = intBuff + 48;
     Wire.write("{lampPosUn:"); 
     Wire.write(buffer__);
     Wire.write("}");  
}
