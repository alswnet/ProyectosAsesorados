#include <LiquidCrystal.h>

LiquidCrystal lcd(11, 12, 5, 4, 3, 2);

int PinPir = 6;
int LedPin = 13;
int Buzzer = 10;
int Boton = 7;


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando");
  pinMode(Boton, INPUT);
  pinMode(PinPir, INPUT);
  pinMode(LedPin, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  digitalWrite(PinPir, 0);
  digitalWrite(Buzzer, 0);

}

void loop() {
  if (digitalRead(PinPir) == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Intruso");
    digitalWrite(Buzzer, 1);
    digitalWrite(LedPin, 1);
  }

  if (digitalRead(Boton) == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("xxx");
    digitalWrite(Buzzer, 0);
    digitalWrite(LedPin, 0);
  }
  delay(1000);
}
