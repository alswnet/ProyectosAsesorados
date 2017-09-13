#include <SoftwareSerial.h>//Se puede emular mas de un puerto serial

SoftwareSerial BTSerial(9, 8); // RX | TX Poner los pines que usas
int Temperatura = 0;
void setup()
{
  Serial.begin(9600);
  Serial.println("Iniciando:");
  BTSerial.begin(9600);
  //Inicializando los puerto seria de ambos lados
}

void loop()
{

  // Leer el puerto HC-05 y lo escrive en el puerto serial de Arduino
  if (BTSerial.available()) {
    char Mensaje = BTSerial.read();
    if (Mensaje == 'A' || Mensaje == 'a') {
      Serial.println("Apagar");
      //Codigo de Apagar
    }
    else if (Mensaje == 'E' || Mensaje == 'e') {
      Serial.println("Encender");
      //Codigo de Encerder
    }
    else if (Mensaje >= '0' && Mensaje <= '9') {
      Temperatura = Temperatura * 10 +  int (Mensaje - '0');
    }
    else if (Mensaje == '\n' && Temperatura > 0) {
      Serial.print("La Temperatura es ");
      Serial.println(Temperatura);
      Temperatura = 0;
      //Codigp para temperatura
    }
  }

}
