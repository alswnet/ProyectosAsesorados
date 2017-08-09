#include <Stepper.h>

const int stepsPerRevolution = 200;  // cambie este valor por el numero de pasos de su motor

// inicializa la libreria 'stepper' en los pines 8 a 11
Stepper xStepper(stepsPerRevolution, 2, 3, 4, 5);

Stepper yStepper(stepsPerRevolution, 7, 8, 9, 10);

Stepper zStepper(stepsPerRevolution, 14, 15, 16, 17);

void xpositivo();
void ypositivo();
void zpositivo();
void xnegativo();
void ynegativo();
void znegativo();


int trayectoria = 0;


void setup() {
  // establece la velocidad en 60rpm
  xStepper.setSpeed(60);

  yStepper.setSpeed(60);

  zStepper.setSpeed(60);
  // inicializa el puerto serial
  Serial.begin(9600);
}

void loop() {

  if (Serial.available() > 0) {
    trayectoria = Serial.read();

    if (trayectoria == 'w') {
      ypositivo();
    }
    else if (trayectoria == 'x') {
      ynegativo();
    }
    else if (trayectoria == 'd') {
      xpositivo();
    }
    else if (trayectoria == 'a') {
      xnegativo();
    }
    else if (trayectoria == 'f') {
      zpositivo();
    }
    else if (trayectoria == 'r') {
      znegativo();
    }
  }
}


void xpositivo () {
  xStepper.step(stepsPerRevolution);
  delay(500);
 }

void xnegativo () {
  xStepper.step(-stepsPerRevolution);
  delay(500);
}

void ypositivo () {
  yStepper.step(stepsPerRevolution);
  delay(500);
}

void ynegativo () {
  yStepper.step(-stepsPerRevolution);
  delay(500);
}

void zpositivo () {
  zStepper.step(stepsPerRevolution);
  delay(500);
}

void znegativo () {
  zStepper.step(-stepsPerRevolution);
  delay(500);
}

