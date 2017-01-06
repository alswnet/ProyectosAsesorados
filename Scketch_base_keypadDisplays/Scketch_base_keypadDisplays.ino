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

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );// Funciones especificas para el Keypad

// Declararemos las variables para cada pin.
//Display 1
int SILI = 2;  //Segmento inferior lateral izquierdo
int SIH = 3;   //Segmento inferior Horizontal
int SSLI = 4;  //Segmento Superior lateral izquierdo
int SMH = 5;   //Segmento Medio Horizontal
int SSH = 6;   //Segmento Superior Horizontal
int SSLD = 7;  //Segmento Superi-or lateral Derecho
int SILD = 8;  //Segmento inferior lateral Derecho
int PUNTO = 9; //Punto

//Display2
int SILI2 = 10;  //Segmento inferior lateral izquierdo
int SIH2 = 11;   //Segmento inferior Horizontal
int SSLI2 = 12;  //Segmento Superior lateral izquierdo
int SMH2 = 13;   //Segmento Medio Horizontal
int SSH2 = 14;   //Segmento Superior Horizontal
int SSLD2 = 15;  //Segmento Superi-or lateral Derecho
int SILD2 = 16;  //Segmento inferior lateral Derecho
int PUNTO2 = 17; //Punto

void setup()
{
  //Display 1
  pinMode (SILI, OUTPUT);
  pinMode (SIH, OUTPUT);
  pinMode (SSLI, OUTPUT);
  pinMode (SMH, OUTPUT);
  pinMode (SSH, OUTPUT);
  pinMode (SSLD, OUTPUT);
  pinMode (SILD, OUTPUT);
  pinMode (PUNTO, OUTPUT);

  //Display 2
  pinMode (SILI2, OUTPUT);
  pinMode (SIH2, OUTPUT);
  pinMode (SSLI2, OUTPUT);
  pinMode (SMH2, OUTPUT);
  pinMode (SSH2, OUTPUT);
  pinMode (SSLD2, OUTPUT);
  pinMode (SILD2, OUTPUT);
  pinMode (PUNTO2, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  char key = keypad.getKey(); // Usaremos la palabra Key para referirnos a =(keypad.getKey) para ahorrarnos espacio

  switch (keypad.getState()) {                    // Indicaremos que si el boton A se presiona ocurrira que se active una indicacion especifica
    case PRESSED:
      if (key == '1')

      {
        digitalWrite(SILI, LOW); //1
        digitalWrite(SIH, LOW);
        digitalWrite(SSLI, LOW);
        digitalWrite(SMH, LOW);
        digitalWrite(SSH, LOW);
        digitalWrite(SSLD, HIGH);
        digitalWrite(SILD, HIGH);
        digitalWrite(PUNTO, LOW);
        delay(1000);
        digitalWrite(SILI, HIGH);  //00
        digitalWrite(SIH, HIGH);
        digitalWrite(SSLI, HIGH);
        digitalWrite(SMH, LOW);
        digitalWrite(SSH, HIGH);
        digitalWrite(SSLD, HIGH);
        digitalWrite(SILD, HIGH);
        digitalWrite(PUNTO, LOW);
        digitalWrite(SILI, HIGH);
        digitalWrite(SIH, HIGH);
        digitalWrite(SSLI2, HIGH);
        digitalWrite(SMH2, LOW);
        digitalWrite(SSH2, HIGH);
        digitalWrite(SSLD2, HIGH);
        digitalWrite(SILD2, HIGH);
        digitalWrite(PUNTO2, LOW);
        delay(1000);
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
}

