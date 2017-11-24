#include <SoftwareSerial.h>//Se puede emular mas de un puerto serial

SoftwareSerial GSMSerial(8, 9); // RX | TX Poner los pines que usas

int temperatura = 3;
int temperaturaPasada = 2;
void setup() {
  // put your setup code here, to run once:
  GSMSerial.begin(9600);
  mandarGSM();
}

void loop() {
  // Aqui codigo temperatura///
  if (abs(temperatura - temperaturaPasada) > 5) {
    mandarGSM();
    temperaturaPasada = temperatura;
  }
}

void mandarGSM() {
  GSMSerial.println("AT+CMGF=1");
  delay(200);
  GSMSerial.println("AT+CMGS=\"+50378358918\"");
  delay(200);
  GSMSerial.print("hola mundo la tmp es ");
  GSMSerial.print(temperatura);
  GSMSerial.println(" t°");
  delay(200);
  GSMSerial.println((char)26);
  delay(200);
}
