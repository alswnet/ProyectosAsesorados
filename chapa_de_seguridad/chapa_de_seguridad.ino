#include <Keypad.h>

const byte Fila = 4;
const byte Columna = 3;
char llave[Fila][Columna] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte PinesFila[Fila] = {5, 4, 3, 2};
byte PinesColumna[Columna] = {8, 7, 6};
char clave[] = {'1', '2', '3', '4', '5'};
char cerradura[] = {'0', '0', '0', '0', '0'};

int Contador = 0;
int confirmacion = 0;
Keypad keypad = Keypad( makeKeymap(llave), PinesFila, PinesColumna, Fila, Columna );

void setup() {
  Serial.begin(9600);
}

void loop() {
  char key = keypad.getKey();
  if (key != NO_KEY) {
    cerradura[Contador] = key;
    Serial.println(cerradura[Contador]);
    Contador ++;
    delay(300);
  }
  if (Contador == 5)
  {
    Contador = 0;
    for (int i = 0; i < 5; i++)
    {
      if (clave[i] == cerradura[i])
      {
        confirmacion++;
      }
    }
    if (confirmacion == 5)
    {
      Serial.println("clave correcta");
      confirmacion = 0;
    }
    else
    {
      Serial.println("intruso");
      confirmacion = 0;
    }
  }
}
