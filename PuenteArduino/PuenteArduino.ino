int PWMA = 5;
int AIN2 = 2;
int AIN1 = 4;
int STBY = 9;
int BIN1 = 7;
int BIN2 = 8;
int PWMB = 6;

boolean Estado = false;

void setup() {
  Serial.begin(9600);
  pinMode(PWMA, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(STBY, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  digitalWrite(STBY, 1);
}

void loop() {
  if (Serial.available()) {
    char Letra = Serial.read();
    if ((Letra == 'a' || Letra == 'A') && !Estado ) {
      Subir();
      Alto();
      Estado = true;
    }
    else if ((Letra == 'b' || Letra == 'B') && Estado) {
      Bajar();
      Espera();
      Estado = false;
    }
  }
  Alto();
}

void Subir() {
  //Inicio Subir
  digitalWrite(AIN2, 1);
  digitalWrite(AIN1, 0);
  analogWrite(PWMA, 150);//0 - 255

  digitalWrite(BIN2, 1);
  digitalWrite(BIN1, 0);
  analogWrite(PWMB, 150);//0 - 255
  delay(1000);
}

void Alto() {
  //Ariba
  digitalWrite(AIN2, 1);
  digitalWrite(AIN1, 1);
  analogWrite(PWMA, 255);//0 - 255

  digitalWrite(BIN2, 1);
  digitalWrite(BIN1, 1);
  analogWrite(PWMB, 255);//0 -
}

void Bajar() {
  //Bajando
  digitalWrite(AIN2, 0);
  digitalWrite(AIN1, 1);
  analogWrite(PWMA, 40);//0 - 255

  digitalWrite(BIN2, 0);
  digitalWrite(BIN1, 1);
  analogWrite(PWMB, 40);//0 - 255
  delay(1000);
}

void Espera() {
  //Reposo
  digitalWrite(AIN2, 0);
  digitalWrite(AIN1, 0);
  analogWrite(PWMA, 0);//0 - 255

  digitalWrite(BIN2, 0);
  digitalWrite(BIN1, 0);
  analogWrite(PWMB, 0);//0 - 255
}
