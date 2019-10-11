#include <Servo.h>

int PinServo[5] = {A0, A1, A2, A3, A4};
int Pmax[5] = {180, 180, 180, 180, 180};
int Pmin[5] = {0, 0, 0, 0, 0};
int Pactual[5] = {90, 90, 90, 90, 90};

int PinSensor = A5;
int VMaxSensor = 0;
int VminSensor = 1024;
int VactSensor;
int VanteriorSensor = 0;

//Cambiar valor segun fuenta de filtro
//Rango de 0-1
//Valores aproximandose a 0 siguen menos la linea real
//Valores aproximandose a 1 siguien la linea real
float FuerzaFiltro = 0.05;

void setup() {
  pinMode(PinSensor, INPUT);
  Serial.begin(115200);
  delay(1000);
  VanteriorSensor = analogRead(PinSensor);
}

void loop() {
  VactSensor = analogRead(PinSensor);
  //Serial.print(VactSensor);
  //Serial.print(",");
  VactSensor = FiltroPasaBajo(VactSensor);
  Serial.print("V,");
  Serial.print(VactSensor);
  //Serial.print(",");
  //Serial.print(VMaxSensor);
  //Serial.print(",");
  //Serial.print(VminSensor);
  Serial.println();

  delay(15);
}

int FiltroPasaBajo(int Valor) {
  VanteriorSensor = FuerzaFiltro * Valor + (1 - FuerzaFiltro) * VanteriorSensor;
  return VanteriorSensor;
}
