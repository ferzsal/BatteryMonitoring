#include <SoftwareSerial.h>
SoftwareSerial espSerial(3, 2); // RX | TX recuerda desconectar de pin 3 y RX al programar la placa de Nodemcu por el Arduino IDE
String str;

void setup(){
  Serial.begin(115200);
  espSerial.begin(115200);
}
void loop(){

  float bateria1 = analogRead(A0) / 40.92;
  float bateria2 = analogRead(A1) / 40.92;

  //Serial.println("Bateria 1=" + String(bateria1) + 'V');
  //Serial.println("Bateria 2=" + String(bateria2) + 'V');
  Serial.println(String(bateria1));
  Serial.println(String(bateria2));
  Serial.println("---------------------------------------------------------");
  //str =String("coming from arduino: ")+String("Bateria 1= ")+String(bateria1)+String("Bateria 2= ")+String(bateria2);
  
  str =String(bateria1)+String(":")+String(bateria2);
  espSerial.println(str); // lo envía a la nodemcu por comunicación serial

  //Serial.println(str);

  Serial.flush();
  delay(1000);
}
