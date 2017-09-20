#include <SoftwareSerial.h>//Se puede emular mas de un puerto serial
#include <EEPROM.h>

SoftwareSerial BTSerial(9, 8); // RX | TX Poner los pines que usas
int Temperatura = 0;
int TemperaturaNueva = 0;
int Direccion = 0;

int PinesControl[4] = {
  2,// 0- Apagar/Encender
  3,// 1- Bajar
  4,// 2- Subir
  5// 3- Modo
};

void setup()
{
  Serial.begin(9600);
  Serial.println("Iniciando:");
  BTSerial.begin(9600);
  Temperatura = EEPROM.read(Direccion);
  if (Temperatura < 17) Temperatura = 17;
  if (Temperatura > 30) Temperatura = 30;
  for (int i = 0; i < 4; i++) {
    pinMode(PinesControl[i], OUTPUT);
  }
  Serial.print("Temperatura actual ");
  Serial.println(Temperatura);
  //Inicializando los puerto seria de ambos lados
}

void loop()
{
  // Leer el puerto HC-05 y lo escrive en el puerto serial de Arduino
  if (BTSerial.available()) {
    char Mensaje = BTSerial.read();
    if (Mensaje == 'A' || Mensaje == 'a') {
      Serial.println("Apagar");
      digitalWrite(PinesControl[0], 0);
      delay(500);
      digitalWrite(PinesControl[0], 1);
      delay(500);
      digitalWrite(PinesControl[0], 0);
      delay(500);
      //Codigo de Apagar
    }
    else if (Mensaje >= '0' && Mensaje <= '9') {
      TemperaturaNueva  = TemperaturaNueva  * 10 +  int (Mensaje - '0');
    }
    else if (Mensaje == '\n' && TemperaturaNueva > 0) {
      Serial.print("La Temperatura es ");
      Serial.println(Temperatura);
      while (TemperaturaNueva > Temperatura) {
        digitalWrite(PinesControl[2], 0);
        delay(500);
        digitalWrite(PinesControl[2], 1);
        delay(500);
        digitalWrite(PinesControl[2], 0);
        delay(500);
        Serial.print("T ");
        Serial.println(Temperatura);
        Serial.println("Subiendo");
        Temperatura++;
      }
      while (TemperaturaNueva < Temperatura) {
        digitalWrite(PinesControl[1], 0);
        delay(500);
        digitalWrite(PinesControl[1], 1);
        delay(500);
        digitalWrite(PinesControl[1], 0);
        delay(500);
        Serial.print("T ");
        Serial.println(Temperatura);
        Serial.println("Bajando");
        Temperatura--;
      }
      TemperaturaNueva = 0;
      Serial.print("La temperatura es ");
      Serial.println(Temperatura);
      EEPROM.write(Direccion, Temperatura);
      //Codigp para temperatura
    }
    else if (Mensaje == 'L' || Mensaje == 'l') {
      //Camiar modo
      digitalWrite(PinesControl[3], 0);
      delay(500);
      digitalWrite(PinesControl[3], 1);
      delay(500);
      digitalWrite(PinesControl[3], 0);
      delay(500);
      Serial.println("Cambiando Mode");
    }
    else if (Mensaje == 'F' || Mensaje == 'f') {
      //Bajar a la ultima temperatura
      for (int i = 0; i < 17; i++) {
        digitalWrite(PinesControl[1], 1);
        delay(500);
        digitalWrite(PinesControl[1], 0);
        delay(500);
        Serial.println("Bajando");
      }
      Temperatura = 17;
      EEPROM.write(Direccion, Temperatura);
    }
  }
}
