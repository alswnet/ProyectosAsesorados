#include <Keypad.h>

const byte ROWS = 4; //Declaramos el uso de las 4 filas
const byte COLS = 3; //declaramos el uso de las 4 columnas

char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

byte rowPins[ROWS] = {18, 19, 20, 21}; //Declaramos los pines de salida de las filas
byte colPins[COLS] = {22, 23, 24,}; //Declaramos los pines de salida de las columnas

Keypad Teclado = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );// Funciones especificas para el Keypad

int DisplayPin[2][8] = {{2, 3, 4, 5, 6, 7, 8, 9}, {10, 11, 12, 13, 14, 15, 16, 17}};
int Botones[3] = {26, 27, 28};

int Tiempo = 0;
int TiempoResiduo = 0;
bool Contando = false;
float TiempoPasado = millis();

void setup()
{
  for (int x = 0; x < 2; x++) {
    for (int y = 0; y < 8; y++) {
      pinMode(DisplayPin[x][y], OUTPUT);
    }
  }
  for (int i = 0; i < 3; i++) {
    pinMode(Botones[i], INPUT);
  }
  MostrarTiempo(Tiempo);
  Serial.begin(9600);
}

void loop()
{
  for (int i = 0; i < 3; i++) {
    if (digitalRead(Botones[i]) == 1) {
      switch (i) {
        case 0:
          if (!Contando) {
            if (Tiempo != 0) {
              TiempoPasado = millis();
              Contando = true;
              Serial.println("Empezar a contar");
              delay(100);
            }
            else {
              Serial.println("Error Tiempo no Asignado");
            }
          }
          break;
        case 1:
          Contando = false;
          Tiempo = TiempoResiduo;
          Serial.print("Detenido ...");
          Serial.println(Tiempo);
          MostrarTiempo(Tiempo);
          break;
        case 2:
          Contando = false;
          Tiempo = 0;
          Serial.print("Detenido ...");
          MostrarTiempo(Tiempo);
          break;
      }
    }
  }

  if (Contando) {
    if (millis() - TiempoPasado < Tiempo * 1000) {
      int TiempoPantalla =  Tiempo - int(millis() - TiempoPasado) / 1000;
      if (TiempoPantalla != TiempoResiduo) {
        TiempoResiduo = TiempoPantalla;
        MostrarTiempo(TiempoPantalla);
        Serial.println(TiempoPantalla);
      }
    }
    else {
      Contando = false;
      Tiempo = 0;
      Serial.println("Finalizado");
    }
  }
  else {
    ActualizarTeclado();
  }
}

void ActualizarTeclado() {
  char key = Teclado.getKey(); // Usaremos la palabra Key para referirnos a =(keypad.getKey) para ahorrarnos espacio
  if (key) {
    int ValorTemporal = int(key - '0');
    Tiempo = (Tiempo * 10 + ValorTemporal) % 100;
    Serial.println(ValorTemporal);
    Serial.print("Tiempo: ");
    Serial.println(Tiempo);
    MostrarTiempo(Tiempo);
  }
}

void MostrarTiempo(int Tiempo) {
  int Digito0 = Tiempo % 10;
  int Digito1 = (Tiempo - Tiempo % 10) / 10;
  MostrarDigito(Digito0, 0);
  MostrarDigito(Digito1, 1);
}

void MostrarDigito(int Numero, int Posicion) {
  switch (Numero) {
    case 1:
      digitalWrite(DisplayPin[Posicion][0], LOW); //1
      digitalWrite(DisplayPin[Posicion][1], LOW);
      digitalWrite(DisplayPin[Posicion][2], LOW);
      digitalWrite(DisplayPin[Posicion][3], LOW);
      digitalWrite(DisplayPin[Posicion][4], LOW);
      digitalWrite(DisplayPin[Posicion][5], HIGH);
      digitalWrite(DisplayPin[Posicion][6], HIGH);
      digitalWrite(DisplayPin[Posicion][7], LOW);
      break;
    case 2:
      digitalWrite(DisplayPin[Posicion][0], 1); //2
      digitalWrite(DisplayPin[Posicion][1], 1);
      digitalWrite(DisplayPin[Posicion][2], 0);
      digitalWrite(DisplayPin[Posicion][3], 1);
      digitalWrite(DisplayPin[Posicion][4], 1);
      digitalWrite(DisplayPin[Posicion][5], 1);
      digitalWrite(DisplayPin[Posicion][6], 0);
      digitalWrite(DisplayPin[Posicion][7], 0);
      break;
  }
}

