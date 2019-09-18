int b1 = 27;
int b2 = 26;

int L1 = 5;
int L2 = 15;

int Valor;
int Valor2;

void setup() {
  pinMode(b1, INPUT);
  pinMode(b2, INPUT);
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  Serial.begin(115200);
  

}

void loop() {

  Valor = digitalRead(b1);
  Valor2 = digitalRead(b2);
  if (Valor == 1)
  {
    digitalWrite(L1, HIGH);
    delay(1000);
    digitalWrite(L1, LOW);

  }
   if (Valor2 == 1)
  {
    digitalWrite(L2, HIGH);
    delay(1000);
    digitalWrite(L2, LOW);

  }

}
