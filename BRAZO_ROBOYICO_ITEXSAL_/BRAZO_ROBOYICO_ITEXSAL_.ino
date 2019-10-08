#include <Servo.h>

int PinServo[5] = {A0, A1, A2, A3, A4};
int Pmax[5] = {180, 180, 180, 180, 180};
int Pmin[5] = {0, 0, 0, 0, 0};
int Pactual[5] = {90, 90, 90, 90, 90};
Servo Dedo[5];

int PinSensor = A5;
int VMaxSensor = 0;
int VminSensor = 1024;
int VactSensor;
int VanteriorSensor = 0;


//Cambiar valor segun fuenta de filtro
//Rango de 0-1
//Valores aproximandose a 0 siguen menos la linea real
//Valores aproximandose a 1 siguien la linea real
float FuerzaFiltro = 0.01;

void setup() {
  pinMode(PinSensor, OUTPUT);
  for (int i = 0; i < 5; i++ ) {
    Dedo[i].attach(PinServo[i]);
  }
  Serial.begin(115200);
}

void loop() {
  VactSensor = analogRead(PinSensor);
  Serial.print(VactSensor);
  Serial.print(",");
  VactSensor = FiltroPasaBajo(VactSensor);
  Serial.println(VactSensor);
  if (VactSensor > VMaxSensor) {
    VMaxSensor = VactSensor;
  }

  if (VactSensor < VminSensor) {
    VminSensor = VactSensor;
  }

  for (int i = 0; i < 5; i++) {
    Pactual[i] = map(VactSensor, VminSensor, VMaxSensor, Pmin[i], Pmax[i]);
  }

  for (int i = 0; i < 5; i++) {
    Dedo[i].write(Pactual[i]);
  }
  delay(15);
}

int FiltroPasaBajo(int Valor) {
  VanteriorSensor = FuerzaFiltro * Valor + (1 - FuerzaFiltro) * VanteriorSensor;
  return VanteriorSensor;
}
