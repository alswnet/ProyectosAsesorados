int trigger = 6;
int echo = 7;
int ArduinoSegundo = 9;
int ArduinoPrimero = 8;
int prueba = 13;
int Bomba = 11;
int lectura = 0;
void setup() {
  pinMode(ArduinoPrimero,INPUT);
  pinMode(Bomba,OUTPUT);
  pinMode(ArduinoPrimero, OUTPUT);
  pinMode(prueba, OUTPUT);
  pinMode(trigger, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(9600);

}

void loop() {
  lectura = digitalRead(ArduinoPrimero);
  int tiempo, distancia;
  digitalWrite(trigger, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  tiempo = pulseIn(echo, HIGH);
  distancia = tiempo / 58;
  if (distancia <= 10 && lectura  == 1) {
    digitalWrite(ArduinoSegundo, HIGH);
    digitalWrite(prueba, HIGH);
    digitalWrite(Bomba,HIGH);
  }
  else
  {
    digitalWrite(Bomba,LOW);
    digitalWrite(ArduinoSegundo, LOW);
    digitalWrite(prueba, LOW);
  }
  Serial.println(lectura);
  Serial.println(distancia);
  delay(500);
}
