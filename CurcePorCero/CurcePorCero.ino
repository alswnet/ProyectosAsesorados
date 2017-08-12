#include <LiquidCrystal.h>

LiquidCrystal lcd(11, 12, 5, 4, 3, 8);

const float Dispara = 8.33;
const float Encendido = 2;

int Salida1 = 7;
int Salida2 = 6;

int veces = 0;
int Interupcion = 0;//Pin 2
int Potenciometro = A0;
float Retardo = 0;
float Tiempo = 0;

void setup() {
  delay(300);
  lcd.begin(16, 2);
  lcd.clear();

  Serial.println("Iniciando");
  pinMode(Salida1, OUTPUT);
  pinMode(Salida2, OUTPUT);
  pinMode(Potenciometro, INPUT);
  attachInterrupt(Interupcion, MandarPulso, RISING );
}

void loop() {
  Retardo = map(analogRead(Potenciometro), 0, 1023, Dispara, 0);
  int Angulo = map(Retardo, 0, Dispara, 0, 360);
  lcd.setCursor(0, 0);
  lcd.print("Angulo ");
  lcd.print(Angulo);
}


void MandarPulso() {
  digitalWrite(Salida1, 0);
  digitalWrite(Salida2, 0);
  delay(Retardo);
  digitalWrite(Salida1, 1);
  digitalWrite(Salida2, 1);
  delay(Encendido);
  digitalWrite(Salida1, 0);
  digitalWrite(Salida2, 0);
}
