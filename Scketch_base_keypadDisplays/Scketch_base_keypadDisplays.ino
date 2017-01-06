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

float Tiempo = 0;

void setup()
{
  for (int x = 0; x < 2; x++) {
    for (int y = 0; y < 8; y++) {
      pinMode(DisplayPin[x][y], OUTPUT);
    }
  }
  MostrarDigito(0, 0);
  MostrarDigito(0, 1);
  Serial.begin(9600);
}

void loop()
{
  char key = Teclado.getKey(); // Usaremos la palabra Key para referirnos a =(keypad.getKey) para ahorrarnos espacio
  if (key) {
    int ValorTemporal = int(key - '0');
    Serial.println(ValorTemporal);
  }
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

/*
  digitalWrite(SILI, HIGH);  //100
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  digitalWrite(SILI2, HIGH);
  digitalWrite(SIH2, HIGH);
  digitalWrite(SSLI2, HIGH);
  digitalWrite(SMH2, LOW);
  digitalWrite(SSH2, HIGH);
  digitalWrite(SSLD2, HIGH);
  digitalWrite(SILD2, HIGH);
  digitalWrite(PUNTO2, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //99
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  digitalWrite(SILI2, LOW);
  digitalWrite(SIH2, HIGH);
  digitalWrite(SSLI2, HIGH);
  digitalWrite(SMH2, HIGH);
  digitalWrite(SSH2, HIGH);
  digitalWrite(SSLD2, HIGH);
  digitalWrite(SILD2, HIGH);
  digitalWrite(PUNTO2, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //8
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //7
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //6
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //5
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //4
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //3
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH); //2
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, LOW);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW); //1
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

    digitalWrite(SILI, HIGH);  //90
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  digitalWrite(SILI2, LOW);
  digitalWrite(SIH2, HIGH);
  digitalWrite(SSLI2, HIGH);
  digitalWrite(SMH2, HIGH);
  digitalWrite(SSH2, HIGH);
  digitalWrite(SSLD2, HIGH);
  digitalWrite(SILD2, HIGH);
  digitalWrite(PUNTO2, LOW);
  delay(1000);

  digitalWrite(SILI2, HIGH);  //89
  digitalWrite(SIH2, HIGH);
  digitalWrite(SSLI2, HIGH);
  digitalWrite(SMH2, HIGH);
  digitalWrite(SSH2, HIGH);
  digitalWrite(SSLD2, HIGH);
  digitalWrite(SILD2, HIGH);
  digitalWrite(PUNTO2, LOW);
  digitalWrite(SILI, LOW);
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //8
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //7
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //6
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //5
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //4
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //3
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH); //2
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, LOW);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW); //1
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

   digitalWrite(SILI, HIGH);  //80
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
    digitalWrite(SILI2, HIGH);
  digitalWrite(SIH2, HIGH);
  digitalWrite(SSLI2, HIGH);
  digitalWrite(SMH2, HIGH);
  digitalWrite(SSH2, HIGH);
  digitalWrite(SSLD2, HIGH);
  digitalWrite(SILD2, HIGH);
  digitalWrite(PUNTO2, LOW);
  delay(1000);

  digitalWrite(SILI2, LOW);  //79
  digitalWrite(SIH2, LOW);
  digitalWrite(SSLI2, LOW);
  digitalWrite(SMH2, LOW);
  digitalWrite(SSH2, HIGH);
  digitalWrite(SSLD2, HIGH);
  digitalWrite(SILD2, HIGH);
  digitalWrite(PUNTO2, LOW);
  digitalWrite(SILI, LOW);
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //8
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //7
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //6
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //5
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //4
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //3
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH); //2
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, LOW);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW); //1
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //70
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  digitalWrite(SILI2, LOW);
  digitalWrite(SIH2, LOW);
  digitalWrite(SSLI2, LOW);
  digitalWrite(SMH2, LOW);
  digitalWrite(SSH2, HIGH);
  digitalWrite(SSLD2, HIGH);
  digitalWrite(SILD2, HIGH);
  digitalWrite(PUNTO2, LOW);
  delay(1000);

  digitalWrite(SILI2, HIGH);  //69
  digitalWrite(SIH2, HIGH);
  digitalWrite(SSLI2, HIGH);
  digitalWrite(SMH2, HIGH);
  digitalWrite(SSH2, HIGH);
  digitalWrite(SSLD2, LOW);
  digitalWrite(SILD2, HIGH);
  digitalWrite(PUNTO2, LOW);
  digitalWrite(SILI, LOW);
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //8
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //7
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //6
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //5
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //4
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //3
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH); //2
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, LOW);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW); //1
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

   digitalWrite(SILI, HIGH);  //60
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  digitalWrite(SILI2, HIGH);
  digitalWrite(SIH2, HIGH);
  digitalWrite(SSLI2, HIGH);
  digitalWrite(SMH2, HIGH);
  digitalWrite(SSH2, HIGH);
  digitalWrite(SSLD2, LOW);
  digitalWrite(SILD2, HIGH);
  digitalWrite(PUNTO2, LOW);
  delay(1000);

  digitalWrite(SILI2, LOW);  //59
  digitalWrite(SIH2, HIGH);
  digitalWrite(SSLI2, HIGH);
  digitalWrite(SMH2, HIGH);
  digitalWrite(SSH2, HIGH);
  digitalWrite(SSLD2, LOW);
  digitalWrite(SILD2, HIGH);
  digitalWrite(PUNTO2, LOW);
  digitalWrite(SILI, LOW);
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //8
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //7
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //6
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //5
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //4
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //3
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH); //2
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, LOW);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW); //1
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

   digitalWrite(SILI, HIGH);  //50
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  digitalWrite(SILI2, LOW);
  digitalWrite(SIH2, HIGH);
  digitalWrite(SSLI2, HIGH);
  digitalWrite(SMH2, HIGH);
  digitalWrite(SSH2, HIGH);
  digitalWrite(SSLD2, LOW);
  digitalWrite(SILD2, HIGH);
  digitalWrite(PUNTO2, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //49
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
   digitalWrite(SILI2, LOW);
  digitalWrite(SIH2, LOW);
  digitalWrite(SSLI2, HIGH);
  digitalWrite(SMH2, HIGH);
  digitalWrite(SSH2, LOW);
  digitalWrite(SSLD2, HIGH);
  digitalWrite(SILD2, HIGH);
  digitalWrite(PUNTO2, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //8
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //7
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //6
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //5
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //4
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //3
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH); //2
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, LOW);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW); //1
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //40
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
   digitalWrite(SILI2, LOW);
  digitalWrite(SIH2, LOW);
  digitalWrite(SSLI2, HIGH);
  digitalWrite(SMH2, HIGH);
  digitalWrite(SSH2, LOW);
  digitalWrite(SSLD2, HIGH);
  digitalWrite(SILD2, HIGH);
  digitalWrite(PUNTO2, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //39
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  digitalWrite(SILI2, LOW);
  digitalWrite(SIH2, HIGH);
  digitalWrite(SSLI2, LOW);
  digitalWrite(SMH2, HIGH);
  digitalWrite(SSH2, HIGH);
  digitalWrite(SSLD2, HIGH);
  digitalWrite(SILD2, HIGH);
  digitalWrite(PUNTO2, LOW);
  delay(1000);

   digitalWrite(SILI, HIGH);  //8
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //7
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //6
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //5
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //4
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //3
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH); //2
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, LOW);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW); //1
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //30
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  digitalWrite(SILI2, LOW);
  digitalWrite(SIH2, HIGH);
  digitalWrite(SSLI2, LOW);
  digitalWrite(SMH2, HIGH);
  digitalWrite(SSH2, HIGH);
  digitalWrite(SSLD2, HIGH);
  digitalWrite(SILD2, HIGH);
  digitalWrite(PUNTO2, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //29
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  digitalWrite(SILI2, HIGH);
  digitalWrite(SIH2, HIGH);
  digitalWrite(SSLI2, LOW);
  digitalWrite(SMH2, HIGH);
  digitalWrite(SSH2, HIGH);
  digitalWrite(SSLD2, HIGH);
  digitalWrite(SILD2, LOW);
  digitalWrite(PUNTO2, LOW);
  delay(1000);

    digitalWrite(SILI, HIGH);  //8
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //7
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //6
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //5
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //4
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //3
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH); //2
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, LOW);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW); //1
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //20
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  digitalWrite(SILI2, HIGH);
  digitalWrite(SIH2, HIGH);
  digitalWrite(SSLI2, LOW);
  digitalWrite(SMH2, HIGH);
  digitalWrite(SSH2, HIGH);
  digitalWrite(SSLD2, HIGH);
  digitalWrite(SILD2, LOW);
  digitalWrite(PUNTO2, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //19
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  digitalWrite(SILI2, LOW);
  digitalWrite(SIH2, LOW);
  digitalWrite(SSLI2, LOW);
  digitalWrite(SMH2, LOW);
  digitalWrite(SSH2, LOW);
  digitalWrite(SSLD2, HIGH);
  digitalWrite(SILD2, HIGH);
  digitalWrite(PUNTO2, LOW);
  delay(1000);

    digitalWrite(SILI, HIGH);  //8
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //7
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //6
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //5
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //4
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //3
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH); //2
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, LOW);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW); //1
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //10
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  digitalWrite(SILI2, LOW);
  digitalWrite(SIH2, LOW);
  digitalWrite(SSLI2, LOW);
  digitalWrite(SMH2, LOW);
  digitalWrite(SSH2, LOW);
  digitalWrite(SSLD2, HIGH);
  digitalWrite(SILD2, HIGH);
  digitalWrite(PUNTO2, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);//9
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, LOW);
  digitalWrite(PUNTO, LOW);
  digitalWrite(SILI, LOW);
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

     digitalWrite(SILI, HIGH);  //8
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //7
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //6
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //5
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, LOW);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //4
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW);  //3
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH); //2
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, HIGH);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, LOW);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, LOW); //1
  digitalWrite(SIH, LOW);
  digitalWrite(SSLI, LOW);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, LOW);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  delay(1000);

  digitalWrite(SILI, HIGH);  //0
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI, HIGH);
  digitalWrite(SMH, LOW);
  digitalWrite(SSH, HIGH);
  digitalWrite(SSLD, HIGH);
  digitalWrite(SILD, HIGH);
  digitalWrite(PUNTO, LOW);
  digitalWrite(SILI, HIGH);  //0
  digitalWrite(SIH, HIGH);
  digitalWrite(SSLI2, HIGH);
  digitalWrite(SMH2, LOW);
  digitalWrite(SSH2, HIGH);
  digitalWrite(SSLD2, HIGH);
  digitalWrite(SILD2, HIGH);
  digitalWrite(PUNTO2, LOW);
  delay(1000); */


