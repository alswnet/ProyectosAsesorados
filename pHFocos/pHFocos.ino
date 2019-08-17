#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x27, 16, 2);


float calibration = 20.47; //change this value to calibrate
const int analogInPin = A0;
int sensorValue = 0;
unsigned long int avgValue;
float b;
int buf[10], temp;

int ph[15] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, A1, A2, A3};

void setup() {

  for (int i = 0; i < 15; i++) {
    pinMode(ph[i], OUTPUT);
  }

  // Inicializar el LCD
  lcd.init();

  //Encender la luz de fondo.
  lcd.backlight();

  lcd.setCursor(3, 0);
  lcd.print("Iniciando");
  delay(2000);
  lcd.setCursor(2, 1);
  lcd.print("Programacion");

  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 10; i++)
  {
    buf[i] = analogRead(analogInPin);
    delay(30);
  }
  for (int i = 0; i < 9; i++)
  {
    for (int j = i + 1; j < 10; j++)
    {
      if (buf[i] > buf[j])
      {
        temp = buf[i];
        buf[i] = buf[j];
        buf[j] = temp;
      }
    }
  }
  avgValue = 0;
  for (int i = 2; i < 8; i++)
    avgValue += buf[i];
  float pHVol = (float)avgValue * 5.0 / 1024 / 6;
  float phValue = -5.70 * pHVol + calibration;
  Serial.print("sensor = ");
  Serial.println(phValue);

  delay(500);

  if (0 <= phValue && phValue < 7)
  {

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Acido");

    lcd.setCursor(8, 0);
    lcd.print("Refresco");

    lcd.setCursor(3, 1);
    lcd.print("pH = ");
    lcd.setCursor(9, 1);
    lcd.print(phValue);

  }

  if ( phValue >= 7 && phValue < 8)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Neutro");

    lcd.setCursor(9, 0);
    lcd.print("Agua");


    lcd.setCursor(3, 1);
    lcd.print("pH = ");
    lcd.setCursor(9, 1);
    lcd.print(phValue);

  }

  if (8 <= phValue)
  {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Alcalino");

    lcd.setCursor(9, 0);
    lcd.print("Huevo");


    lcd.setCursor(3, 1);
    lcd.print("pH = ");
    lcd.setCursor(9, 1);
    lcd.print(phValue);

  }

  for (int i = 0; i < 15; i++) {
    if (phValue < i ) {
      digitalWrite(ph[i], 1);
      
    }
    else {
      digitalWrite(ph[i], 0);
      
    }
  }
}
