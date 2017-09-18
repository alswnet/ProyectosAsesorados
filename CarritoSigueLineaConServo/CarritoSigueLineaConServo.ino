int Motor1D = 5;
int Motor2D = 6;

int Motor1I = 8;
int Motor2I = 9;

int SensorI = 0;
int SensorD = 0;

int vcc1 = 2;
int vcc2 = 3;
int gnd1 = 11;
int gnd2 = 12;
void setup() {
  pinMode(vcc1, OUTPUT);
  pinMode(vcc2, OUTPUT);
  pinMode(gnd1, OUTPUT);
  pinMode(gnd2, OUTPUT);
  digitalWrite(vcc1, HIGH);
  digitalWrite(vcc2, HIGH);
  digitalWrite(gnd1, LOW);
  digitalWrite(gnd2, LOW);
  pinMode(Motor1D, OUTPUT);
  pinMode(Motor2D, OUTPUT);
  pinMode(Motor1I, OUTPUT);
  pinMode(Motor2I, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  SensorI  = analogRead(A0);
  SensorD = analogRead(A2);
  if (SensorD < 500 && SensorI < 500) {
    alto();
  }
  else if (SensorD > 500 && SensorI > 500) {
    delante();
  }
  else if (SensorD > 500 && SensorI < 500) {
    derecha();
  }
  else if (SensorD < 500 && SensorI > 500) {
    izquierda();
  }
  else {
    alto();
  }
  delay(1);
}

void alto() {
  digitalWrite(Motor2D, LOW);
  digitalWrite(Motor1D, LOW);
  digitalWrite(Motor1I, LOW);
  digitalWrite(Motor2I, LOW);
}

void delante() {
  digitalWrite(Motor2D, HIGH);
  digitalWrite(Motor1D, LOW);
  digitalWrite(Motor1I, HIGH);
  digitalWrite(Motor2I, LOW);
}

void izquierda() {
  digitalWrite(Motor2D, HIGH);
  digitalWrite(Motor1D, LOW);
  digitalWrite(Motor1I, LOW);
  digitalWrite(Motor2I, HIGH);
}

void derecha() {
  digitalWrite(Motor2D, LOW);
  digitalWrite(Motor1D, HIGH);
  digitalWrite(Motor1I, HIGH);
  digitalWrite(Motor2I, LOW);
}
