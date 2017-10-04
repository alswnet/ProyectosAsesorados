#include <Servo.h>

//Creando nombres Reservador
#define Izquieda 0
#define Centro 1
#define Derecha 2
#define Adelante 1
#define Atras 0
#define MotorIzquierdo 0
#define MotorDerecha 1

Servo myservo;

int Estado = 0;
int Cambiar = 0;
int PinLed = 13;
int BotonInicio = 13;

int PinDelantero[2] = {3, 11};
int PinTracero[2] =   {6, 9};
//int PinVelocidad[2] = {6, 5};

int Velocidad[2] = {0, 0};
int PinSensor[3] = {A0, A1, A2};

int CantidadSensores = 3;

int ValorSensor[3] = {0, 0, 0};
boolean EstadoSensor[4] = {false, false, false};
int PasadoSensor[3] = {0, 0, 0};
int MaximoSensor[3] = {0, 0, 0 };
int MinimoSensor[3] = {1024, 1024, 1024};

int VelocidadActual[2] = {40, 40};
int VelocidadMaxima[2] = {100, 100};
int VelocidadMinima[2] = {0, 0};

void setup() {


  Serial.begin(9600);
  Serial.println("Iniciando");

  for (int i = 0; i < 3; i++) {
    pinMode(PinSensor[i], INPUT);
  }

  for (int i = 0; i < 2; i++) {
    pinMode( PinDelantero[i], OUTPUT);
    pinMode( PinTracero[i], OUTPUT);
  }

  pinMode(PinLed , OUTPUT);
  pinMode(BotonInicio, INPUT);

  Serial.println("Esperando Boton");
  while (true) {
    int EstadoBoton = digitalRead(BotonInicio);
    digitalWrite(PinLed, 1);
    delay(300);
    digitalWrite(PinLed, 0);
    delay(300);
    ActualizarEntradas();
    //if (EstadoBoton == 0) {
    // Serial.println("Empezando a Segir Linea");
    // digitalWrite(PinLed, 0);
    //break;
    //}
    break;
  }
}

void loop() {


  switch (Estado) {
    case 0:
      //Reto
      Serial.print("-E0-");
      VelocidadActual[MotorIzquierdo] = Velocidad[MotorIzquierdo];
      VelocidadActual[MotorDerecha] = Velocidad[MotorDerecha];
      if (EstadoSensor[Izquieda]) {
        Estado = 2;
      }
      else if (EstadoSensor[Derecha]) {
        Estado = 1;
      }
      break;
    case 1:
      Serial.print("-E1-");
      //Salida por la derecha, regresar por la izquieda
      VelocidadActual[MotorIzquierdo] = Velocidad[MotorIzquierdo];
      VelocidadActual[MotorDerecha] = Velocidad[MotorDerecha] / 2;
      if (EstadoSensor[Centro]) {
        Estado = 0;
      }
      break;
    case 2:
      Serial.print("-E2-");
      //Salida por la izquierda, regresar por la derecha
      VelocidadActual[MotorIzquierdo] = Velocidad[MotorIzquierdo] / 2;
      VelocidadActual[MotorDerecha] = Velocidad[MotorDerecha] ;
      if (EstadoSensor[Centro]) {
        Estado = 0;
      }
      break;
  }
  ActualizarEntradas();
  BuscarBT();

  for (int i = 0; i < 2; i++) {
    Serial.print(Velocidad[i] );
    Serial.print(" ");
  }

  Caminar( Velocidad[0], MotorIzquierdo);
  Caminar( Velocidad[1], MotorDerecha);
}


void Caminar( int Velocidad, int Motor) {
  if (Velocidad > 0) {
    analogWrite(PinDelantero[Motor], Velocidad);
    analogWrite(PinTracero[Motor], 0);
  }
  else if (Velocidad < 0) {
    analogWrite(PinDelantero[Motor], 0);
    analogWrite(PinTracero[Motor],  Velocidad);
  }
  else  {
    analogWrite(PinDelantero[Motor], 0);
    analogWrite(PinTracero[Motor], 0);
    // analogWrite(PinVelocidad[Motor], Velocidad);
  }
}

void ActualizarEntradas() {
  for (int i = 0; i < 3; i++) {
    ValorSensor[i] = analogRead(PinSensor[i]);
    if (ValorSensor[i] > MaximoSensor[i]) {
      MaximoSensor[i] = ValorSensor[i];
    } else if (ValorSensor[i] < MinimoSensor[i]) {
      MinimoSensor[i] = ValorSensor[i];
    }
    if (ValorSensor[i] >  MinimoSensor[i] + 2 * (MaximoSensor[i] - MinimoSensor[i]) / 3) {
      EstadoSensor[i] = true;
    }
    else {
      EstadoSensor[i] = false;
    }
    Serial.print("|S");
    Serial.print(i);
    Serial.print(" V:");
    Serial.print(ValorSensor[i]);
    Serial.print(" E:");
    Serial.print(boolean(EstadoSensor[i]));
  }
  Serial.println();
}

void BuscarBT() {

  while (Serial.available() > 0 ) {
    char Letra = Serial.read();

    if (Letra == 'v') {
      Serial.println("Reiniciar Valor 0");
      Cambiar = 1;
      Velocidad[0] = 0;
    } else if (Letra == 'V') {
      Serial.println("Reiniciar Valor 1");
      Cambiar = 2;
      Velocidad[1] = 0;
    } else if (Letra == '\n') {
      Cambiar = 0;
    }
    if (Letra >= '0' && Letra <= '9') {
      int Numero = int(Letra - '0');
      switch (Cambiar) {
        case 1:
          Velocidad[0]  = Velocidad[0] * 10 + Numero;
          break;
        case 2:
          Velocidad[1]  = Velocidad[1] * 10 + Numero;
          break;
      }
    }
  }
}
