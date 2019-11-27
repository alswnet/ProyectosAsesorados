#include <OneWire.h>
#include <DallasTemperature.h>

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

OneWire ourWire(5);                //Se establece el pin 2  como bus OneWire

DallasTemperature sensors(&ourWire); //Se declara una variable u objeto para nuestro sensor

void setup() {
  lcd.init();                      // initialize the lcd
  lcd.backlight();
  delay(1000);
  Serial.begin(9600);
  sensors.begin();   //Se inicia el sensor
}

void loop() {
  sensors.requestTemperatures();   //Se envía el comando para leer la temperatura
  float temp = sensors.getTempCByIndex(0); //Se obtiene la temperatura en ºC

  Serial.print("Temperatura= ");
  Serial.print(temp);
  Serial.println(" C");
  delay(100);

  lcd.clear();
  delay(100);
  lcd.setCursor(0, 0);
  lcd.print("C:");
  lcd.setCursor(2, 0);
  lcd.print(temp);
  
}
