#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BTSerial(3, 2);

Servo ServoHola;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

  ServoHola.attach(9);
}

void loop() {
  if (BTSerial.available()) {
    char Letra = BTSerial.read();
    if (Letra == 'a') {
      ServoHola.write(0);
    }
    else if (Letra == 'b') {
      ServoHola.write(90);
    }

    else if (Letra == 'c') {
      ServoHola.write(180);
    }
  }
}
