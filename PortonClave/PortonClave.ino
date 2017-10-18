#include <Keypad.h>
#include <LiquidCrystal.h>

const byte Fila = 4;
const byte Columna = 3;
char llave[Fila][Columna] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

int M1D = 16;
int M1I = 17;
int M2D = 18;
int M2I = 19;

byte PinesFila[Fila] = {5, 4, 3, 2};
byte PinesColumna[Columna] = {8, 7, 6};


Keypad keypad = Keypad( makeKeymap(llave), PinesFila, PinesColumna, Fila, Columna );
LiquidCrystal lcd(15, 14, 12, 11, 10, 9);

int clave[5] = {0, 0, 0, 0, 0};
int contra[5] = {7, 2, 3, 4, 1};      //Aqui cambias la clave

int i = 0;
int j = 0;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  pinMode(M1D , OUTPUT);
  pinMode(M1I , OUTPUT);
  pinMode(M2D , OUTPUT);
  pinMode(M2I , OUTPUT);

}

void loop() {
  char key = keypad.getKey();
  if (key != NO_KEY && i < 5 && key != '#' && key != '*') {       //Estructura if para guardar numeros en el vector y escribir en la LCD
    clave[i] = int(key - '0');
    lcd.setCursor(i, 0);
    lcd.print(int(key - '0'));
    i++;
  }

  if (key != NO_KEY && key == '#' && i == 5) {      //Comparar la contraseña con la clave
    for (int k = 0; k < 5; k++) {
      if (clave[k] == contra[k]) {
        j++;
      }
    }
    Serial.println(j);
    if (j == 5) {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("felicidades");
      digitalWrite(M1D, HIGH);
      digitalWrite(M1I, LOW);
      digitalWrite(M2D, HIGH);
      digitalWrite(M2I, LOW);
      delay(5000);
      digitalWrite(M1D, LOW);
      digitalWrite(M1I, LOW);
      digitalWrite(M2D, LOW);
      digitalWrite(M2I, LOW);
      delay(5000);
      digitalWrite(M1D, LOW);
      digitalWrite(M1I, HIGH);
      digitalWrite(M2D, LOW);
      digitalWrite(M2I, HIGH);
      delay(5000);
      digitalWrite(M1D, LOW);
      digitalWrite(M1I, LOW);
      digitalWrite(M2D, LOW);
      digitalWrite(M2I, LOW);
      lcd.clear();
    }
    else {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("La cago");
      digitalWrite(M1D, LOW);
      digitalWrite(M1I, LOW);
      digitalWrite(M2D, LOW);
      digitalWrite(M2I, LOW);
      delay(5000);
      lcd.clear();
    }
    i = 0;
    j = 0;
  }
  delay(200);
}
