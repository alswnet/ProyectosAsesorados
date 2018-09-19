#define derecha 1
#define izquierda 0

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(A4, A5);

int ZS = 4;
int ZD = 7;
int YS = 3;
int YD = 6;
int XS = 2;
int XD = 5;
int SD = 13;
int SS = 12;
int EN = 8;

void setup() {
  pinMode(ZS, OUTPUT);
  pinMode(EN, OUTPUT);
  pinMode(ZD, OUTPUT);
  pinMode(YS, OUTPUT);
  pinMode(YD, OUTPUT);
  pinMode(XS, OUTPUT);
  pinMode(XD, OUTPUT);
  pinMode(SS, OUTPUT);
  pinMode(SD, OUTPUT);
  digitalWrite(EN, 0);

  Serial.begin(9600);
  BTSerial.begin(9600);
}

void loop() {
  if (BTSerial.available()) {
    ProcesarBluetooth(BTSerial.read());
  }
  if (Serial.available()) {
    ProcesarBluetooth(Serial.read());
  }
}

void mover(int PDire, int PStep, int direccion ) {
  if (direccion == izquierda) {
    digitalWrite(PDire , 1);
  }
  else if (direccion == derecha) {
    digitalWrite(PDire , 0);
  }
  for (int i = 0; i < 1000; i++) {
    digitalWrite(PStep, 1);
    delay(1);
    digitalWrite(PStep, 0);
    delay(1);
  }
}

void ProcesarBluetooth(char letra) {
  Serial.print("Letra: ");
  Serial.println(letra);
  if ( letra == 'a' || letra == 'A' ) {
    mover (XD, XS , izquierda);
  }
  else if ( letra == 'b' || letra == 'B' ) {
    mover (XD, XS, derecha);
  }
  if ( letra == 'c' || letra == 'C' ) {
    mover (YD, YS , izquierda);
  }
  else if ( letra == 'd' || letra == 'D' ) {
    mover (YD, YS, derecha);
  }
  if ( letra == 'e' || letra == 'E' ) {
    mover (ZD, ZS , izquierda);
    mover (SD, SS, izquierda);
  }
  else if ( letra == 'f' || letra == 'F' ) {
    mover (ZD, ZS, derecha);
    mover (SD, SS , derecha);
  }
}
