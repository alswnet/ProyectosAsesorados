#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

SoftwareSerial SerialDedo(8, 9);
Adafruit_Fingerprint Dedo = Adafruit_Fingerprint(&SerialDedo);

int Led = 13;

void setup() {
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Iniciando Programa");
  Dedo.begin(57600);
  Serial.begin(9600);
  pinMode(Led, OUTPUT);

  if (Dedo.verifyPassword()) {
    Serial.println("Sensor Encontrado!");
  } else {
    Serial.println("Erro fatal busca el sensor:(");
    digitalWrite(Led, 1);
    lcd.setCursor(0, 0);
    lcd.print("Error Sensor");
    while (1);
  }
  lcd.setCursor(0, 0);
  lcd.println("Esperando...");
}

void loop() {
  if (BuscandoDedo(16) == 1 ) {
    lcd.setCursor(0, 0);
    lcd.println("Hola, abriendo");
    //Aqui 
  }
  digitalWrite(Led, 1);
  delay(400);
  digitalWrite(Led, 0);
  delay(400);

}

int BuscandoDedo(int ID) {
  uint8_t P = Dedo.getImage();

  if (P != FINGERPRINT_OK) {
    lcd.setCursor(0, 0);
    lcd.println("Error con el dedo");
    return 0;
  }

  P = Dedo.image2Tz();
  if (P != FINGERPRINT_OK) {
    lcd.setCursor(0, 0);
    lcd.println("Error con el dedo");
    return 0;
  }

  P = Dedo.fingerFastSearch();
  if ( P == FINGERPRINT_OK) {
    if ( ID == Dedo.fingerID) {
      return 1;
    }
  }
  lcd.setCursor(0, 0);
  lcd.println("Dedo No correcto");
  return 0;
}
