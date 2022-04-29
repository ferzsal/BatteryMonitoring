// LIBRERÍAS
#include <ESP8266WiFi.h>
#include "FirebaseArduino.h"
#include <SoftwareSerial.h>

//------------------------------
// FIREBASE
#define FIREBASE_HOST "" // databaseUrl 
#define FIREBASE_AUTH "" // secreto de la base
//------------------------------


// wifi credenciales
#define WIFI_SSID ""    // nombre de la red wifi
#define WIFI_PASSWORD ""   // contraseña de la red wifi
//  ------------------------------
//VARIABLES
//const int rele1 = D1; 
int i;
float v1=0; //Voltaje bateria 1
float v2=0;//voltaje bateria 2



// ----------SETUP-----------------
  void setup() {

  Serial.begin(115200); //velocidad
  delay(100) ;

   // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  
  while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
  }
  Serial.println();
  Serial.print("conectado !! ");

  Serial.println(WiFi.localIP());
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}



// ----------LOOP-----------------
void loop() {

//----------------------------------------
  if (Firebase.failed()) {
        Serial.print("Error en connexion de firebase:");
        Serial.println(Firebase.error());
        delay(1000);
    }
//----------------------------------------

 // COMUNICACION CON ARDUINO 
  Serial.flush();
  //desde aqui empieza a recibir el string:
  String S = "" ;
  if (Serial.available()){
    char c = Serial.read();
    while ( c != '\n' ){  //Hasta que el caracter sea intro != significa diferente a...
      S = S + c ;
      //delay(25) ;
      c = Serial.read();
    }
  }else {
    return;
  }
  
  delay(500);
  Serial.println("recibe: " + String (S));

  // separa (el separador es ':')
  float bateria1 = getValue(String (S),':',0).toFloat();
  Serial.println(bateria1); 
  delay(1000);
  float bateria2 = getValue(String (S),':',1).toFloat();
  Serial.println(bateria2); 
  
  Serial.flush();
  delay(1000);



//-----------VOLTAJE BATERIAS---------------- 
    Firebase.setFloat("/baterias/bateria1",(float)bateria1); //escribe voltaje de las baterías en la base de datos
    Firebase.setFloat("/baterias/bateria2",(float)bateria2);





  
}


// funcion que separa el string desde el arduino
String getValue(String data, char separator, int index){
  
  int found = 0;
  int strIndex[] = {0, -1};
  int maxIndex = data.length()-1;

  for(int i=0; i<=maxIndex && found<=index; i++){
    if(data.charAt(i)==separator || i==maxIndex){
        found++;
        strIndex[0] = strIndex[1]+1;
        strIndex[1] = (i == maxIndex) ? i+1 : i;
    }
  }

  return found>index ? data.substring(strIndex[0], strIndex[1]) : "";
}
