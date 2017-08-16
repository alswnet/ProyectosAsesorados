int PinElectro[3] = {12, 2, 3};
int PinTriger[3] = {6, 8, 10};
int PinEch[3] = {7, 9, 11};
int PinMotor[2] = {4, 5};

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void Iniciar() {
  for (int i = 0; i < 3; i++) {
    pinMode(PinElectro[i], OUTPUT);
    pinMode(PinTrigger[i], OUTPUT);
    pinMode(PinEcho[i], INPUT);
  }
  for (int i = 0; i < 2; i++) {
    pinMode(PinMotor[i], INPUT);
  }
}

int distancia(int cerca) {
  int tiempo, distancia;
  digitalWrite(PinTrigger[cerca], LOW);
  delayMicroseconds(2);
  digitalWrite(PinTrigger[cerca], HIGH);
  delayMicroseconds(10);
  digitalWrite(PinTrigger[cerca], LOW);
  tiempo = pulseIn(PinEcho[cerca], HIGH);
  distancia = tiempo / 58;
  return distancia
}

