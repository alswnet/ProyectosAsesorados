#include <SoftwareSerial.h>//Se puede emular mas de un puerto serial
#include <EEPROM.h>

SoftwareSerial BTSerial(9, 8); // RX | TX Poner los pines que usas
int Temperatura = 0;
int EstadoAc = 0;
int TemperaturaNueva = 0;
int Direccion = 0;
int DireccionEstado = 1;

int PinesControl[4] = {
  2,// 0- Apagar/Encender
  4,// 1- Bajar
  3,// 2- Subir
  5// 3- Modo
};

void setup()
{
  Serial.begin(9600);
  Serial.println("Iniciando:");
  BTSerial.begin(9600);
  Temperatura = EEPROM.read(Direccion);
  EstadoAc = EEPROM.read(DireccionEstado);
  if (Temperatura < 17) Temperatura = 17;
  else if (Temperatura > 30) Temperatura = 30;
  if ( EstadoAc < 0) EstadoAc = 0;
  else if (EstadoAc > 1) EstadoAc = 1;
  for (int i = 0; i < 4; i++) {
    pinMode(PinesControl[i], OUTPUT);
  }
  Serial.print("Temperatura actual ");
  Serial.println(Temperatura);
  Serial.print("Estado actual AC");
  Serial.println(EstadoAc);
  //Inicializando los puerto seria de ambos lados
}

void loop()
{
  // Leer el puerto HC-05 y lo escrive en el puerto serial de Arduino
  if (BTSerial.available()) {
    char Mensaje = BTSerial.read();
    EnviarMensaje(Mensaje);
  }

  if (Serial.available()) {
    char Mensaje = Serial.read();
    EnviarMensaje(Mensaje);
  }
}

void EnviarMensaje(char Mensaje) {
  if (Mensaje == 'A' || Mensaje == 'a') {
    Serial.println("Apagar");
    digitalWrite(PinesControl[0], 0);
    delay(500);
    digitalWrite(PinesControl[0], 1);
    delay(500);
    digitalWrite(PinesControl[0], 0);
    delay(500);
    EstadoAc = EstadoAc == 1 ? 0 : 1;
    EEPROM.write(DireccionEstado, EstadoAc);
    //Codigo de Apagar
  }
  else if (Mensaje == 'g' || Mensaje == 'G') {
    BTSerial.println(EstadoAc);
    Serial.println("Preguntando Estado");
  }
  else if (Mensaje >= '0' && Mensaje <= '9') {
    TemperaturaNueva  = TemperaturaNueva  * 10 +  int (Mensaje - '0');
  }
  else if (Mensaje == '\n' && TemperaturaNueva > 0) {
    Serial.print("La Temperatura es ");
    Serial.println(Temperatura);
    if (TemperaturaNueva < 17) TemperaturaNueva = 17;
    if (TemperaturaNueva > 30) TemperaturaNueva = 30;
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
      delay(800);
      digitalWrite(PinesControl[1], 0);
      delay(800);
      Serial.println("Bajando");
    }
    Temperatura = 17;
    EstadoAc = 1;
    EEPROM.write(DireccionEstado, EstadoAc);
    EEPROM.write(Direccion, Temperatura);
  }
}
