#include <Servo.h>

int PinServo[5] = {A0, A1, A2, A3, A4};
int Pmax[5] = {140, 160, 160, 160, 20};
int Pmin[5] = {40, 0, 0, 20, 160};
int Pactual[5] = {90, 90, 90, 90, 90};
int Ppasado[5] = {90, 90, 90, 90, 90};
Servo Dedo[5];

int VMaxSensor = 0;
int VminSensor = 1024;
int VactSensor = 0;
int ValorSuperar = 500;

//Cambiar valor segun fuenta de filtro
//Rango de 0-1
//Valores aproximandose a 0 siguen menos la linea real
//Valores aproximandose a 1 siguien la linea real
float FuerzaFiltro = 0.05;

void setup() {
  for (int i = 0; i < 5; i++ ) {
    Dedo[i].attach(PinServo[i]);
    Dedo[i].write(Pactual[i]);
  }
  Serial.begin(115200);
  delay(1000);
}

void loop() {

  /* Serial.print(VactSensor);
    Serial.print(",");
    Serial.print(VMaxSensor);
    Serial.print(",");
    Serial.print(VminSensor);
    Serial.print(",");
    Serial.print(Pactual[0]);
    Serial.println();
  */
  DecodificarSerial();

  /*
    if (VactSensor > VMaxSensor) {
      VMaxSensor = FiltroPasaBajo(VactSensor, VMaxSensor);
      // VMaxSensor = VactSensor;
    }

    if (VminSensor > VactSensor) {
      VMaxSensor = FiltroPasaBajo(VactSensor, VminSensor);
      // VminSensor = VactSensor;
    }

    for (int i = 0; i < 5; i++) {
    Pactual[i] = map(VactSensor, VminSensor, VMaxSensor, Pmin[i], Pmax[i]);
    }
  */

  if (VactSensor > ValorSuperar) {
    for (int i = 0; i < 5; i++) {
      Pactual[i] = Pmax[i];
    }
  } else {
    for (int i = 0; i < 5; i++) {
      Pactual[i] = Pmin[i];
    }
  }

  for (int i = 0; i < 5; i++) {
    // if (abs(Ppasado[i] - Pactual[i]) > 5) {
    Dedo[i].write(Pactual[i]);
    //   Ppasado[i] = Pactual[i];
    // }
  }

  delay(15);
}

int FiltroPasaBajo(int Valor , int ValorAnteior) {
  int  VanteriorSensor = FuerzaFiltro * Valor + (1 - FuerzaFiltro) * ValorAnteior;
  return VanteriorSensor;
}

void DecodificarSerial() {
  // Mensaje de la forma M1/30
  // Donde M1 Es motor 1
  // 30 el valor
  String Mensaje = Serial.readStringUntil('\n');
  int PosicionPleca = Mensaje.indexOf(',');
  int PosicionSaltoLinea = Mensaje.length();
  String Dato = Mensaje.substring(0, PosicionPleca);
  int Valor = Mensaje.substring(PosicionPleca + 1, PosicionSaltoLinea).toInt();
  if (Dato.equals("V")) {
    VactSensor = Valor;
    Serial.println(Valor);
  }
}
