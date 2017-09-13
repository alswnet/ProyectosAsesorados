#include <LiquidCrystal.h>

int PinElectro[3] = {13, A0, A1};
int PinTrigger[3] = {6, 8, 10};
int PinEcho[3] = {7, 9, A4};
int PinMotor[2] = {A2, A3};
int SensorPH = A5;
int PinComunicacion[2] = {0, 1};
int DistanciaMinima[3] = {10, 10, 10};
int DistanciaMaxima[3] = {15, 15, 15};
int ValorAceptablePH = 7;
int Distancia[3];
int ConteoVeces = 0;
int CantidaVeces = 3;
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int Estado = 0;

void setup() {

  Serial.begin(9600);
  lcd.begin(16, 2);
  Iniciar();

}

void loop() {
  ActualizarEntradas();
  switch (Estado) {
    case 0:
      Serial.println("E0:Inicial");
      for (int i = 0; i < 2; i++) {
        digitalWrite(PinMotor[i], LOW);
      }
      Estado = 1;
      break;
    case 1:
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("E1:Esperando llene primer tanque");
      lcd.setCursor(0, 1);
      lcd.print("D0:");
      lcd.print(Distancia[0]);
      Serial.println("E1:Esperando llene primer tanque");
      if (Distancia[0] <  DistanciaMinima[0]) {
        digitalWrite(PinMotor[0], HIGH);
        Estado = 2;
      }
      break;
    case 2: lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("E2:Esperando llene Segundo tanque");
      lcd.setCursor(0, 1);
      lcd.print("D1:");
      lcd.print(Distancia[1]);
      Serial.println("E2:Esperando llene Segundo tanque");
      if (Distancia[1] <  DistanciaMinima[1]) {
        digitalWrite(PinMotor[0], LOW);
        digitalWrite(PinElectro[0], HIGH);
        Estado = 3;
      }
      break;
    case 3:
      lcd.setCursor(0, 0);
      lcd.print("E3:Esperando llene Segundo tanque");
      lcd.setCursor(0, 1);
      lcd.print("D2:");
      lcd.print(Distancia[2]);
      Serial.println("E3:Esperando llene Tercer tanque");
      if (Distancia[2] <  DistanciaMinima[2]) {
        digitalWrite(PinElectro[0], LOW);
        Estado = 4;
      }
      break;
    case 4:
      lcd.setCursor(0, 0);
      lcd.print("E4:Medir PH");
      lcd.setCursor(0, 1);
      lcd.print("PH:");
      lcd.print(ValorPH());
      Serial.println("E4:Medir PH");
      if (ValorPH() <  ValorAceptablePH || ConteoVeces > CantidaVeces) {
        digitalWrite(PinElectro[1], HIGH);
        Estado = 5;
      }
      else {
        digitalWrite(PinElectro[2], HIGH);
        digitalWrite(PinMotor[2], HIGH);
        CantidaVeces = CantidaVeces + 1;
        Estado = 6;
      }
      break;
    case 5:
      lcd.setCursor(0, 0);
      lcd.print("E5:Regar plantas");
      lcd.setCursor(0, 1);
      lcd.print("D2:");
      lcd.print(Distancia[2]);
      Serial.println("E5:Regar plantas");
      if (Distancia[2] >  DistanciaMaxima[2]) {
        digitalWrite(PinElectro[2], HIGH);
        Estado = 0;
      }
    case 6:
      lcd.setCursor(0, 0);
      lcd.print("E6: Llenando otra ves el tanque dos");
      lcd.setCursor(0, 1);
      lcd.print("D1:");
      lcd.print(Distancia[1]);
      Serial.println("E6: Llenando otra ves el tanque dos");
      if (Distancia[1] <  DistanciaMinima[1]) {
        digitalWrite(PinElectro[2], LOW);
        digitalWrite(PinMotor[2], LOW);
        digitalWrite(PinElectro[0], HIGH);
        Estado = 3;
      }
      break;
    default:
      Estado = 0;
      break;
  }
}

float ValorPH() {
  return (1023 - analogRead(SensorPH)) / 55.07;
}//Falta meter PH

void ActualizarEntradas() {
  for (int i = 0; i < 3; i++) {
    Distancia[i] = distancia(i);
    Serial.print(" D");
    Serial.print(i);
    Serial.print(" ");
    Serial.print(Distancia[i]);
  }
  Serial.println();
}

void Iniciar() {
  for (int i = 0; i < 3; i++) {
    pinMode(PinElectro[i], OUTPUT);
    pinMode(PinTrigger[i], OUTPUT);
    pinMode(PinEcho[i], INPUT);
  }
  for (int i = 0; i < 2; i++) {
    pinMode(PinMotor[i], OUTPUT);
  }
  pinMode(PinComunicacion[1], OUTPUT);
  pinMode(PinComunicacion[0], INPUT);
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
  return distancia;
}
