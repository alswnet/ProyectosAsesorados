#include <Servo.h>
Servo PuertaCochera;

int Sala = 4;
int Patio = 5;
int Cuarto = 6;
int Comedor = 7;
int Cochera = 8;

int Lectura = 0;

void setup() {
  pinMode(Sala, OUTPUT);
  pinMode(Patio, OUTPUT);
  pinMode(Cuarto, OUTPUT);
  pinMode(Comedor, OUTPUT);
  pinMode(Cochera, OUTPUT);
  PuertaCochera.attach(9);
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {
    Lectura = Serial.read();
    if (Lectura == 'A') {
      digitalWrite(Sala, HIGH);
    }
    else if (Lectura == 'B') {
      digitalWrite(Sala, LOW);
    }
    else if (Lectura == 'H') {
      digitalWrite(Patio, HIGH);
    }
    else if (Lectura == 'R') {
      digitalWrite(Patio, LOW);
    }
    else if (Lectura == 'V') {
      digitalWrite(Cuarto, HIGH);
    }

    else if (Lectura == 'W') {
      digitalWrite(Cuarto, LOW);
    }
    else if (Lectura == 'P') {
      digitalWrite(Comedor, HIGH);
    }
    else if (Lectura == 'm') {
      digitalWrite(Comedor, LOW);
    }
    else if (Lectura == 'L') {
      digitalWrite(Cochera, HIGH);
    }
    else if (Lectura == 'g') {
      digitalWrite(Cochera, LOW);
    }
    else if (Lectura == 'C') {
      PuertaCochera.write(0);
    }
    else if (Lectura == 'Y') {
      PuertaCochera.write(90);
    }
  }
}
