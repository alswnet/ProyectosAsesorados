#include <Adafruit_GFX.h> // Libreria de graficos
#include <Adafruit_TFTLCD.h> // Libreria de LCD
#include <TouchScreen.h> // Libreria del panel tactil

#define YP A1 // Pin analogico A1 para ADC
#define XM A2 // Pin analogico A2 para ADC
#define YM 7
#define XP 6

// Para mejor precision de la presion realizada, es necesario
// medir la resistencia entre los pines X+ y X-.
// En Shield TFT 2.4" LCD se mide entre los pines A2 y 6
// Instancia del panel tactil (Pin XP, YP, XM, YM, Resistencia del panel)
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 364);

short TS_MINX = 150; // Coordenadas del panel tactil para delimitar
short TS_MINY = 120; // el tamaño de la zona donde podemos presionar
short TS_MAXX = 850; // y que coincida con el tamaño del LCD
short TS_MAXY = 891;

#define LCD_CS A3 // Definimos los pines del LCD
#define LCD_CD A2 // para poder visualizar elementos graficos
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

// Definimos la presion máxima y minima que podemos realizar sobre el panel
#define MINPRESSURE 1
#define MAXPRESSURE 1000

#define BLACK 0x0000 // Definimos los colores
#define BLUE 0x001F // que utilizaremos para
#define RED 0xF800 // el texto y los elementos graficos
#define GREEN 0x07E0
#define CYAN 0x07FF
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF

Adafruit_TFTLCD Pantalla(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET); // Instancia LCD

int PX[9]  = {60, 120, 180, 60, 120, 180, 60, 120, 180};
int PY[9] = {90, 90, 90, 180, 180, 180,  270, 270, 270};
int Puntos[9] = {0, 0, 0, 0, 0, 0, 0 , 0, 0};
int IndicePuntos = 0;
int PuntosCorrectos[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};

int X ;
int Y;
int Z;
void setup() {
  Pantalla.begin(0x9325); // Iniciamos el LCD especificando el controlador ILI9341.
  Pantalla.fillScreen(GREEN);
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  ActualizarCirculos();
  ActualizarMouse();
  delay(100);

}

void ActualizarMouse() {
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint(); // Realizamos lectura de las coordenadas
  digitalWrite(13, LOW);

  pinMode(XM, OUTPUT); // La librería utiliza estos pines como entrada y salida
  pinMode(YP, OUTPUT);
  X = map(p.x, TS_MAXX, TS_MINX, Pantalla.width(), 0);
  Y = map(p.y, TS_MAXY, TS_MINY, Pantalla.height(), 0);
  Z = p.z;

  Serial.print("X");
  Serial.print(X);
  Serial.print(" Y");
  Serial.print(Y);
  Serial.print(" z");
  Serial.println(Z);
  for (int i = 0; i < 9; i++) {
    if (Distancia(PX[i], PY[i]) < 25) {
      Puntos[IndicePuntos] = i;
      Serial.println(i);
      IndicePuntos++;

    }
  }
}

void ActualizarCirculos() {
  for (int i = 0; i < 9; i++) {
    Pantalla.fillCircle(PX[i], PY[i], 5, BLACK);
    Pantalla.drawCircle(PX[i], PY[i], 25, BLACK);
  }
}

int Distancia(int x, int y) {
  return  sqrt(pow((x - X), 2) + pow(y - Y, 2));
}
