int MotorA[3] = {2, 3, 9};
int MotorB[3] = {5, 4, 10};
int FinalCarrera[2] = {12, 13};

#define Inicio 0
#define Final 1

#define Izquierda 0
#define Derecha 1
#define Paro 2

int Velocidad = 150;

void setup() {
  for (int i = 0; i < 3; i++) {
    pinMode(MotorA[i], OUTPUT);
    digitalWrite(MotorA[i], 0);
    pinMode(MotorB[i], OUTPUT);
    digitalWrite(MotorB[i], 0);
  }

  for (int i = 0; i < 2; i++) {
    pinMode(FinalCarrera[i], INPUT);
  }
  Serial.begin(9600);
  Direcion(MotorB, Izquierda, Velocidad);
  Direcion(MotorA, Izquierda, Velocidad);
}

void loop() {

  if (digitalRead(FinalCarrera[Inicio]) == 0 ) {
    Serial.println("Inicio");
    Direcion(MotorB, Derecha, Velocidad);
    Direcion(MotorA, Derecha, Velocidad);
    delay(500);
  } else  if (digitalRead(FinalCarrera[Final]) == 0 ) {
    Serial.println("Final");
    Direcion(MotorB, Izquierda, Velocidad);
    Direcion(MotorA, Izquierda, Velocidad);
    delay(500);
  }
}

void Direcion(int Motor[], int Direcion, int Velocidad) {
  if (Direcion == Izquierda) {
    digitalWrite(Motor[0], 1);
    digitalWrite(Motor[1], 0);
    //Serial.println("Izquieda");
  }
  else if (Direcion == Derecha) {
    digitalWrite(Motor[0], 0);
    digitalWrite(Motor[1], 1);
    //Serial.println("Derecha");
  }
  else if (Direcion == Paro) {
    digitalWrite(Motor[0], 1);
    digitalWrite(Motor[1], 1);
    //  Serial.println("Paro");
  }
  analogWrite(Motor[2], Velocidad);
}
