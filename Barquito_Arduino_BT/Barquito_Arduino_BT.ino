#include <SoftwareSerial.h>//Se puede emular mas de un puerto serial

SoftwareSerial BTSerial(10, 11); // RX | TX Poner los pines que usas

int MD = 13 ;
int MI = 12 ;

void setup() {
  Serial.begin(9600);
  pinMode(MD, OUTPUT);
  pinMode(MI, OUTPUT);
  digitalWrite( MD, HIGH);
  digitalWrite( MI, HIGH);
  BTSerial.begin(9600);
}

void loop() {
  if (BTSerial.available()) {
    char Mensaje = BTSerial.read();
    Serial.write(Mensaje);
    if (Mensaje == 'I' || Mensaje == 'i' ) {
      digitalWrite( MD, 1);
      digitalWrite( MI, 0);
    } else if (Mensaje == 'D' || Mensaje == 'd' ) {
      digitalWrite(MD,1);
      digitalWrite(MI,1);

    } else if (Mensaje == 'C' || Mensaje == 'c' ) {
      digitalWrite( MD, 0);
      digitalWrite( MI, 1);
    } else if (Mensaje == 'P' || Mensaje == 'p' ) {
      digitalWrite( MD, 0);
      digitalWrite( MI, 0);

    }
  }
  delay(50);
}
