#include <Stepper.h>

const int stepsPerRevolution = 200;  // cambie este valor por el numero de pasos de su motor

// inicializa la libreria 'stepper' en los pines 8 a 11
Stepper MotorX(stepsPerRevolution, 2, 3, 4, 5);

Stepper MotorY(stepsPerRevolution, 7, 8, 9, 10);

Stepper MotorZ(stepsPerRevolution, 14, 15, 16, 17);

int PasosX = 0;
int PasosY = 0;
int PasosZ = 0;
int MovimientoG = 0;
int EstadoBusqueda = 0; // 1 x, 2 y, 3 z
char Letra = 0;


void setup() {




  MotorX.setSpeed(60);
  MotorY.setSpeed(60);
  MotorZ.setSpeed(60);
  // inicializa el puerto serial
  Serial.begin(9600);
}

void loop() {

  //Serial.println("Iniciando Busqueda");
  boolean Iniciar = false;
  while (Serial.available() > 0) {
    Letra = Serial.read();
    Serial.print(Letra);
    if ((Letra == 'G' || Letra == 'g') && !Iniciar) {
      Iniciar = true;
    }
    else if (Letra == '\n') {
      Iniciar = false;
      Serial.println("Motrando");
      MoverMotores();
      continue;
    }
    else if (Letra == 'X' || Letra == 'x') {
      EstadoBusqueda = 1;
    }
    else if (Letra == 'Y' || Letra == 'y') {
      EstadoBusqueda = 2;
    }
    else if (Letra == 'Z' || Letra == 'z') {
      EstadoBusqueda = 3;
    }
    else if (Letra >= '0' && Letra <= '9') {
      int Numero = int(Letra - '0');
      switch (EstadoBusqueda) {
        case 0:
          MovimientoG = MovimientoG  * 10 + Numero;
          break;
        case 1: // X
          PasosX = PasosX * 10 + Numero;
          break;
        case 2: // Y
          PasosY = PasosY * 10 + Numero;
          break;
        case 3: // Z
          PasosZ = PasosZ * 10 + Numero;
          break;
      }
    }
  }
}


void MoverMotores() {

  Serial.print("Datos ");
  Serial.print(" Pasos X: ");
  Serial.print(PasosX);
  Serial.print(" Pasos Y: ");
  Serial.print(PasosY);
  Serial.print(" Pasos Z: ");
  Serial.print(PasosZ);
  Serial.print(" Movimiento: ");
  Serial.println(MovimientoG);
  PasosX = 0;
  PasosY = 0;
  PasosZ = 0;
  MovimientoG = 0;
  EstadoBusqueda = 0;
}



