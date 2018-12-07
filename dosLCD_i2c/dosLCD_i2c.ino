#include <string.h>

#include <Keypad.h> // libreria necesaria para KeyPad
#include <Wire.h>                 // libreria necesaria para bus I2C
#include <DHT.h> //Incluimos librería
#include <LiquidCrystal_I2C.h> //libreria necesaria para display I2C

#define DHTPIN 10 //Definimos el pin digital donde se conecta el sensor
#define DHTTYPE DHT11 //Dependiendo del tipo de sensor

LiquidCrystal_I2C lcd20x4(0x23, 20, 4); // configuramos el LCD en la direccion de bus I2C que es 0x27 y el tamaño columnas x filas 20x4
LiquidCrystal_I2C lcd16x2(0x27, 16, 2);

DHT dht(DHTPIN, DHTTYPE); //Inicializamos el sensor DHT11

bool riegoGoteo = false;
bool rociador = false;
const int sensorPinT = A0;
const int releGoteo = 11;
const int releRocio = 12;
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};
byte rowPins[ROWS] = {5, 4, 3, 2}; //Filas(pines del 5 al 2)
byte colPins[COLS] = {9, 8, 7, 6}; //Columnas (pines del 9 al 6)
int valT, liHs = 34, lsHs = 66;
float h, t, liHa = 0.4, lsHa = 0.6, liTemp, lsTemp;


Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void setup() {
  Serial.begin (9600);

  Wire.begin(); // Unimos este dispositivo al bus I2C

  dht.begin();
  lcd20x4.init(); // initialza el lcd
  lcd20x4.backlight(); // enciende la luz de fondo del display

  lcd16x2.init(); // initialza el lcd
  lcd16x2.backlight(); // enciende la luz de fondo del display

  lcd20x4.setCursor(0, 0);
  lcd20x4.print("MENU");
  lcd20x4.setCursor(0, 1);
  lcd20x4.print("[A] Modificar Stndar");
  lcd20x4.setCursor(0, 2);
  lcd20x4.print("[B] Activar actuador.");
}

void loop() {
  //Capturando datos
  valT = map(analogRead(sensorPinT), 0, 1023, 100, 0); //Trunca un valor del rango de (1023, 0) ajustandolo a los porcentajes de (0 y 100)
  valT = constrain(valT, 0, 100); //Restringe un número a estar dentro del porcentaje de 0 y 100

  float t = dht.readTemperature(); // Leemos la temperatura en grados centígrados (por defecto)
  float h = dht.readHumidity(); // Leemos la humedad relativa

  //Validando lecturas de Temperatura y Humedad Relativa
  if (isnan(h) || isnan(t)) {
    Serial.println("Error obteniendo los datos del sensor DHT11");
    return;
  }

  //Desplegando datos en pantalla y puerto Serial
  lcd16x2.setCursor(0, 0);
  lcd16x2.print("HA: ");
  lcd16x2.print(h);
  lcd16x2.print(" %");
  Serial.print("HA:");
  Serial.print(h);
  Serial.println(" %");

  if (h < liHa) {
    digitalWrite(releRocio, HIGH);
    rociador = true;
    Serial.println("Rociador encendido");
  }
  if (h > lsHa) {
    digitalWrite(releRocio, LOW);
    rociador = false;
    Serial.println("Rociador apagado");
  }
  lcd16x2.setCursor(0, 1);
  lcd16x2.print("Temp: ");
  lcd16x2.print(t);
  lcd16x2.print(" *C");
  delay(2000);
  Serial.print("Temp:");
  Serial.print(t);
  Serial.println(" *C");
  lcd16x2.clear();

  //Desplegando datos de la Humedad en el suelo
  lcd16x2.setCursor(0, 0);
  lcd16x2.print("HS: ");
  lcd16x2.print(valT);
  Serial.print("HS:");
  Serial.print(valT);
  Serial.println(" %");
  if ((valT >= 0) and (valT <= 33)) {
    lcd16x2.setCursor(0, 1);
    lcd16x2.print("Suelo seco");
    Serial.println("Suelo seco");
    digitalWrite(releGoteo, HIGH);
    riegoGoteo = true;

    Serial.println("Riego por goteo encendido");
  } else if ((valT >= liHs) and (valT <= lsHs)) {
    lcd16x2.setCursor(0, 1);
    lcd16x2.print("Suelo humedo");
    Serial.println("Suelo humedo");
  } else {
    lcd16x2.setCursor(0, 1);
    lcd16x2.print("Suelo mojado ");
    Serial.println("Suelo mojado");
    digitalWrite(releGoteo, LOW);
    riegoGoteo = false;
    Serial.println("Riego por goteo apagado");
  }

  delay(2000);
  lcd16x2.clear();

  //Leyendo Keypad
  char key = keypad.getKey();
  if (key != NO_KEY) {
    if (key == 'A') {
      lcd20x4.clear();
      lcd20x4.setCursor(0, 0);
      lcd20x4.print("[1] Modificar Temp");
      lcd20x4.setCursor(0, 1);
      lcd20x4.print("[2] Modificar HS");
      lcd20x4.setCursor(0, 2);
      lcd20x4.print("[3] Modificar HR");
      lcd20x4.setCursor(0, 3);
      lcd20x4.print("[C] Cancelar");

      if (key) {
        switch (key)
        {
          case '1':
            lcd20x4.clear();
            lcd20x4.setCursor(0, 0);
            lcd20x4.print("L imite inferior: ");
            lcd20x4.print(liHa);
            lcd20x4.setCursor(0, 1);
            lcd20x4.print("L imite inferior: ");
            lcd20x4.print(liHs);
            lcd20x4.setCursor(0, 2);
            lcd20x4.print("Nuevo valor: ");
            break;
          case '2':

            break;
          case '3':

            break;
        }
      }
    } if (key == 'B') {
      lcd20x4.clear();
      lcd20x4.setCursor(0, 0);
      lcd20x4.print("[1] Riego por goteo");
      lcd20x4.setCursor(0, 1);
      lcd20x4.print("[2] Rociadores");
      lcd20x4.setCursor(0, 2);
      lcd20x4.print("[C] Cancelar");
      if (key) {
        switch (key)
        {
          case '1':
            if (rociador) {
              lcd20x4.clear();
              lcd20x4.setCursor(0, 0);
              lcd20x4.print("Estado actual: ");
            }
            break;
          case '2':
            break;
        }
      }
    }
    if (key == 'C') {
      lcd20x4.clear();
      lcd20x4.setCursor(0, 0);
      lcd20x4.print("MENU");
      lcd20x4.setCursor(0, 1);
      lcd20x4.print("[A] Modificar Stnd.");
      lcd20x4.setCursor(0, 2);
      lcd20x4.print("[B] Activar actuador.");
    }
  }
}
