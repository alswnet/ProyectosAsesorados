int trigger = 6;
int echo = 7;
int ArduinoPrimero = 9;
int prueba = 13;
int Bomba = 11;
void setup() {
  pinMode(Bomba,OUTPUT);
  pinMode(ArduinoPrimero, OUTPUT);
  pinMode(prueba, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);

}

void loop() {
  int tiempo, distancia;
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  tiempo = pulseIn(echo, HIGH);
  distancia = tiempo / 58;
  if (distancia <= 10) {
    digitalWrite(ArduinoPrimero, HIGH);
    digitalWrite(prueba, HIGH);
    digitalWrite(Bomba,HIGH);
  }
  else
  {
    digitalWrite(Bomba,LOW);
    digitalWrite(ArduinoPrimero, LOW);
    digitalWrite(prueba, LOW);
  }
  Serial.println(distancia);
  delay(500);
}
