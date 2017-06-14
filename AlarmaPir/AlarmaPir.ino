#include <LiquidCrystal.h>
LiquidCrystal lcd(11, 12, 5, 4, 3, 2);

int PinPir = A0;
int LedPin = 13;
int Buzzer = 10;
int Boton = 7;


void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("INICIANDO APLICACION!!");
  pinMode(Boton, INPUT);
  pinMode(PinPir, INPUT);
  pinMode(LedPin, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  digitalWrite(PinPir, 0);
  digitalWrite(Buzzer, 0);

}

void loop() {
  int ValorSensor = analogRead(PinPir);
  int ValorBoton = digitalRead(Boton);
  
  Serial.print("ValorSensor ");
  Serial.print(ValorSensor);
  Serial.print(" ValorBoton ");
  Serial.println(ValorBoton);
  
  if (ValorSensor > 500) {
    Serial.println("Intruso");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("INTRUSO, INTRUSO!!");
    digitalWrite(Buzzer, 1);
    digitalWrite(LedPin, 1);

  }

  if (ValorBoton == 1) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("NO INTRUSO EN EL CECLA!!");
    digitalWrite(Buzzer, 0);
    digitalWrite(LedPin, 0);
    delay(1000);
  }
}

