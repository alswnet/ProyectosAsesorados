#include <Keypad.h>
#include "U8glib.h"

const byte Fila = 4;
const byte Columna = 3;
char llave[Fila][Columna] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

U8GLIB_ST7920_128X64_1X u8g(16, 15, 14, 9, 10, 11, 12, 13, 17, 19, 18, 25);

byte PinesFila[Fila] = {23, 22, 3, 2};
byte PinesColumna[Columna] = {8, 7, 6};
char clave[] = {'1', '2', '3', '4', '5'};
char cerradura[] = {'0', '0', '0', '0', '0'};

int display = 0;
int Contador = 0;
int confirmacion = 0;
int chapa = 24;

Keypad keypad = Keypad( makeKeymap(llave), PinesFila, PinesColumna, Fila, Columna );

void setup() {
  pinMode(chapa, OUTPUT);
  Serial.begin(9600);
  if ( u8g.getMode() == U8G_MODE_R3G3B2 )
    u8g.setColorIndex(255);   // white
  else if ( u8g.getMode() == U8G_MODE_GRAY2BIT )
    u8g.setColorIndex(1);     // max intensity
  else if ( u8g.getMode() == U8G_MODE_BW )
    u8g.setColorIndex(1);     // pixel on

  u8g.firstPage();
  do
  {
    u8g.setFont(u8g_font_unifont);
    u8g.drawStr(5 , 15, "digite");
    u8g.drawStr(5 , 35, "clave");
    delay(300);
  }
  while ( u8g.nextPage() );
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

      Serial.println("Clave Correcta");
      confirmacion = 0;
      u8g.firstPage();
      do
      {
        u8g.setFont(u8g_font_unifont);
        u8g.drawStr(5 , 15, "Acceso");
        u8g.drawStr(5 , 35, "Concedido");
        delay(300);
      }
      while ( u8g.nextPage() );
      digitalWrite(chapa, HIGH);
      delay(5000);
      u8g.firstPage();
      do
      {
        u8g.setFont(u8g_font_unifont);
        u8g.drawStr(5 , 15, "digite");
        u8g.drawStr(5 , 35, "clave");
        delay(300);
      }
      while ( u8g.nextPage() );
      digitalWrite(chapa, LOW);
    }
    else
    {
      Serial.println("Clave Incorrecta");
      confirmacion = 0;
      u8g.firstPage();
      do
      {
        u8g.setFont(u8g_font_unifont);
        u8g.drawStr(5 , 15, "Acceso");
        u8g.drawStr(10 , 35, "Denegado");
        delay(300);
      }
      while ( u8g.nextPage() );
      delay(5000);
      u8g.firstPage();
      do
      {
        u8g.setFont(u8g_font_unifont);
        u8g.drawStr(5 , 15, "digite");
        u8g.drawStr(5 , 35, "clave");
        delay(300);
      }
      while ( u8g.nextPage() );
    }
  }
}
