#include <SoftwareSerial.h>//Se puede emular mas de un puerto serial

SoftwareSerial GSMSerial(8, 9); // RX | TX Poner los pines que usas

int temperatura = 3;

void setup() {
  // put your setup code here, to run once:
  GSMSerial.begin(9600);
  mandarGSM();
}

void loop() {
  // put your main code here, to run repeatedly:

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
