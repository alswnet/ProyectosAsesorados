#include <Servo.h>

//Creando nombres Reservador
#define Izquieda 0
#define Centro 1
#define Derecha 2
#define Adelante 1
#define Atras 0
#define MotorIzquierdo 0
#define MotorDerecha 1

Servo myservo;

int PinDelantero[2] = {8, 5};
int PinTracero[2] = {2, 6};
int PinVelocidad[2] = {9, 11};

int Velocidad[2] = {0, 0};
int PinSensor[3] = {A0, A2, A4};

int ValorSensor[3] = {0, 0, 0};
boolean EstadoSensor[3] = {false, false, false};
int PasadoSensor[3] = {0, 0, 0};
int MaximoSensor[3] = {0, 0, 0};
int MinimoSensor[3] = {1024, 1024, 1024};

void setup() {

  for (int i = 0; i < 3; i++) {
    pinMode(PinSensor[i], INPUT);
  }

  for (int i = 0; i < 2; i++) {
    pinMode( PinDelantero[i], OUTPUT);
    pinMode( PinTracero[i], OUTPUT);
    pinMode( PinVelocidad[i], OUTPUT);
  }

  myservo.attach(7);
  Serial.begin(9600);
}

void loop() {
  ActualizarEntradas();
   Caminar(Atras,25, MotorIzquierdo);
  Caminar(Adelante, 25, MotorDerecha);
}


void Caminar(int Direccion, int Velocidad, int Motor) {
  if (Direccion == Adelante) {
    digitalWrite(PinDelantero[Motor], 1);
    digitalWrite(PinTracero[Motor], 0);
    analogWrite(PinVelocidad[Motor], Velocidad);
  }
  else if (Direccion == Atras) {
    digitalWrite(PinDelantero[Motor], 0);
    digitalWrite(PinTracero[Motor], 1);
    analogWrite(PinVelocidad[Motor], Velocidad);
  }
}

void ActualizarEntradas() {
  for (int i = 0; i < 3; i++) {
    ValorSensor[i] = analogRead(PinSensor[i]);
    if (ValorSensor[i] > MaximoSensor[i]) {
      MaximoSensor[i] = ValorSensor[i];
    }
    if (ValorSensor[i] < MinimoSensor[i]) {
      MinimoSensor[i] = ValorSensor[i];
    }
    if (ValorSensor[i] > (MaximoSensor[i] + MinimoSensor[i]) / 2) {
      EstadoSensor[i] = true;
    }
    else {
      EstadoSensor[i] = false;
    }
    Serial.print("| S");
    Serial.print(i);
    Serial.print(" V:");
    Serial.print(ValorSensor[i]);
    Serial.print(" E:");
    Serial.print(EstadoSensor[i]);
  }
  Serial.println();
}
