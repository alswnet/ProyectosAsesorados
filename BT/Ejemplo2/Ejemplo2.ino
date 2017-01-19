#include <SoftwareSerial.h>

SoftwareSerial BTSerial(3, 2);

int PinLed = 13;

void setup() {
  Serial.begin(9600);

  BTSerial.begin(9600);
  pinMode(PinLed, OUTPUT);
}

void loop() {
  if (BTSerial.available()) {
    char Letra = BTSerial.read();
    if (Letra == 'a') {
      digitalWrite(PinLed, 1);
    }
    else {
      digitalWrite(PinLed, 0);
    }
  }
}
