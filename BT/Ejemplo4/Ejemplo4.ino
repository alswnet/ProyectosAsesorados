#include <SoftwareSerial.h>
#include <Servo.h>

SoftwareSerial BTSerial(3, 2);

Servo ServoHola;
int Grados = 0;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);

  ServoHola.attach(9);
}

void loop() {
  if (BTSerial.available()) {
    char Letra = BTSerial.read();
    if (Letra == 'm') {
      Grados = 0;
      Serial.println("Me llego una M");
    }
    else if (Letra == 'x') {
      ServoHola.write(Grados);
      Grados = 0;
      Serial.println("Me llego una X");
    }
    if (Letra >= '0' && Letra <= '9') {
      int Numero = int(Letra - '0');
      Grados = Grados * 10 + Numero;
      Serial.print("Llego  ");
      Serial.print(Numero);
    }
  }
}
