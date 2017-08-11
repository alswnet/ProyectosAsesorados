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
float posicionpasosX = 0;
float posicionpasosY = 0;
float posicionpasosZ = 0;
int mmpasoX = 50;
int mmpasoY = 50;
int mmpasoZ = 50;
int movimiento = 1;


void setup() {




  MotorX.setSpeed(60);
  MotorY.setSpeed(60);
  MotorZ.setSpeed(60);
  // inicializa el puerto serial
  Serial.begin(9600);
}

void loop() {
  buscarcomandos();
  MoverMotores();
}

void buscarcomandos() {
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

      continue;
    }
    else if (Letra == 'X' || Letra == 'x') {
      EstadoBusqueda = 1;
      PasosX= 0;
    }
    else if (Letra == 'Y' || Letra == 'y') {
      EstadoBusqueda = 2;
      PasosY= 0;
    }
    else if (Letra == 'Z' || Letra == 'z') {
      EstadoBusqueda = 3;
      PasosZ= 0;
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
  boolean seguirmoviendose = true;
  float objetivoX = PasosX * mmpasoX;
  float objetivoY = PasosY * mmpasoY;
  float objetivoZ = PasosZ * mmpasoZ;


  Serial.print("Datos ");
  Serial.print(" Pasos X: ");
  Serial.print(PasosX);
  Serial.print(" Pasos Y: ");
  Serial.print(PasosY);
  Serial.print(" Pasos Z: ");
  Serial.print(PasosZ);
  Serial.print(" Movimiento: ");
  Serial.println(MovimientoG);


  while (seguirmoviendose) {
    if (objetivoX == posicionpasosX && objetivoY == posicionpasosY && objetivoZ == posicionpasosZ )
    {
      seguirmoviendose = false;
    }

    if (objetivoX > posicionpasosX)
    {
      posicionpasosX =  posicionpasosX + movimiento;
      MotorX.step ( movimiento);
    }
    else if (objetivoX < posicionpasosX)
    {
      posicionpasosX =  posicionpasosX - movimiento;
      MotorX.step ( -movimiento);
    }

    if (objetivoY > posicionpasosY)
    {
      posicionpasosY =  posicionpasosY + movimiento;
      MotorY.step ( movimiento);
    }
    else if (objetivoY < posicionpasosY)
    {
      posicionpasosY =  posicionpasosY - movimiento;
      MotorY.step ( -movimiento);
    }

    if (objetivoZ > posicionpasosZ)
    {
      posicionpasosZ =  posicionpasosZ + movimiento;
      MotorZ.step ( movimiento);
    }
    else if (objetivoZ < posicionpasosZ)
    {
      posicionpasosZ =  posicionpasosZ - movimiento;
      MotorZ.step ( -movimiento);
    }

    Serial.print (posicionpasosX);
    Serial.print (" ");
    Serial.print (posicionpasosY);
    Serial.print (" ");
    Serial.println (posicionpasosZ);

  }


  /* PasosX = 0;
    PasosY = 0;
    PasosZ = 0;
  */
  MovimientoG = 0;
  EstadoBusqueda = 0;
}


