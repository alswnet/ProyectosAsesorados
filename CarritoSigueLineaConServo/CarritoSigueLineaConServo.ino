int Motor1D = 5;
int Motor2D = 6;

int Motor1I = 8;
int Motor2I = 9;

int sensor1 = 0;
int sensor2 = 0;
void setup() {
  pinMode(Motor1D,OUTPUT);
  pinMode(Motor2D,OUTPUT);
  pinMode(Motor1I,OUTPUT);
  pinMode(Motor2I,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  delante();
  delay(2000);
  alto();
  delay(2000);
  derecha();
  delay(2000);
  alto();
  delay(2000);
  izquierda();
  delay(2000);
  alto();
  delay(2000);
}

void alto() {
  digitalWrite(Motor2D,LOW);
  digitalWrite(Motor1D,LOW);
  digitalWrite(Motor1I,LOW);
  digitalWrite(Motor2I,LOW);
}

void delante() {
  digitalWrite(Motor2D,HIGH);
  digitalWrite(Motor1D,LOW);
  digitalWrite(Motor1I,HIGH);
  digitalWrite(Motor2I,LOW);
}

void izquierda() {
  digitalWrite(Motor2D,LOW);
  digitalWrite(Motor1D,HIGH);
  digitalWrite(Motor1I,HIGH);
  digitalWrite(Motor2I,LOW);
}

void derecha() {
  digitalWrite(Motor2D,HIGH);
  digitalWrite(Motor1D,LOW);
  digitalWrite(Motor1I,LOW);
  digitalWrite(Motor2I,HIGH);
}
