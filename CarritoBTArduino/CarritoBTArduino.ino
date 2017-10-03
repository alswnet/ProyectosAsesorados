#include <SoftwareSerial.h>//Se puede emular mas de un puerto serial
#include <SparkFun_TB6612.h>

SoftwareSerial BTSerial(12, 11); // RX | TX Poner los pines que usas

#define AIN1 2
#define BIN1 7
#define AIN2 4
#define BIN2 8
#define PWMA 5
#define PWMB 6
#define STBY 9

const int offsetA = 1;
const int offsetB = 1;

Motor MotorDerecha = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor MotorIzquierda = Motor(BIN1, BIN2, PWMB, offsetB, STBY);


int ValorX = 0;
int ValorY = 0;

int ValorDerecha = 0;
int ValorIzquierda = 0;

int EstadoBusqueda = 0;
int ValorNegativo = 1;
int Adelante = 0;

void setup() {
  Serial.begin(9600);
  BTSerial.begin(9600);
  //Inicializando los puerto seria de ambos lados
}

void loop() {
  Serial.print("VX: ");
  Serial.print(ValorX);
  Serial.print(" VY: ");
  Serial.print(ValorY);
  Serial.print(" Adelante: ");
  Serial.print(Adelante);
  Serial.print(" VI ");
  Serial.print(ValorIzquierda);
  Serial.print(" VD ");
  Serial.println( ValorDerecha);
  ActualizarBT();
  ActualizarMotor();

}

void ActualizarMotor() {
  Adelante = map(ValorY, -100, 100, -255, 255);

  ValorDerecha = map(ValorX, 0, 100, Adelante, 0);
  ValorDerecha = constrain(ValorDerecha, -255, 255);
  ValorIzquierda = map(ValorX, -100, 0, 0, Adelante);
  ValorIzquierda = constrain(ValorIzquierda, -255, 255);
  MotorDerecha.drive( ValorDerecha);
  MotorIzquierda.drive(ValorIzquierda);

}

void ActualizarBT() {
  while (BTSerial.available()) {
    char Letra = BTSerial.read();
    if (Letra == 'x' ) {
      EstadoBusqueda = 1;
      ValorX = 0;
      ValorNegativo = 1;
    }
    else if (Letra == 'y') {
      EstadoBusqueda = 2;
      ValorY = 0;
      ValorNegativo = 1;
    }
    else if (Letra == '-') {
      ValorNegativo = -1;
    }
    else if (Letra >= '0' && Letra <= '9') {
      int Valor = int(Letra - '0');
      if (EstadoBusqueda == 1) {
        ValorX = ValorX * 10 + Valor;
      }
      else if (EstadoBusqueda == 2) {
        ValorY = ValorY * 10 + Valor;
      }
    }
    else if (Letra == '\n') {
      if (EstadoBusqueda == 1) {
        ValorX = ValorNegativo * ValorX;
      }
      else if (EstadoBusqueda == 2) {
        ValorY = ValorNegativo * ValorY;
      }
    }
  }
}
