#include <Servo.h>

//6 Garra
//5 Muneca X
//4 Muneca Y
//3
int PinMotor[7] = {3, 12, 4, 5, 6, 7, 11};
int PosicionActual[6] = {90, 90, 90, 90, 90, 90};
int PosicionPasada[6] = {90, 90, 90, 90, 90, 90};
int PosicionMaxima[6] = {180, 180, 180, 180, 180, 180};
int PosicionMinima[6] = {0, 0, 0, 0, 0, 0};
int PosicionInicial[6] = {90, 90, 90, 90, 90, 90};

int CantidadPasos = 7;
int PasoMover = 10;
int Descanso = 100;
int PosicionFresa[7][6] = {
  {180, 90, 60, 42, 30, 15},//Posicion 0
  {0, 0, 0, 0, 0, 0},//Posicion 1
  {0, 0, 0, 0, 0, 0},//Posicion 2
  {0, 0, 0, 0, 0, 0},//Posicion 3
  {0, 0, 0, 0, 0, 0},//Posicion 4
  {0, 0, 0, 0, 0, 0},//Posicion 5
  {0, 0, 0, 0, 0, 0}//Posicion 6
};
int PosicionChicle[7][6] = {
  {0, 0, 0, 0, 0, 0},//Posicion 0
  {0, 0, 0, 0, 0, 0},//Posicion 1
  {0, 0, 0, 0, 0, 0},//Posicion 2
  {0, 0, 0, 0, 0, 0},//Posicion 3
  {0, 0, 0, 0, 0, 0},//Posicion 4
  {0, 0, 0, 0, 0, 0},//Posicion 5
  {0, 0, 0, 0, 0, 0}//Posicion 6
};
int PosicionLimon[7][6] = {
  {0, 0, 0, 0, 0, 0},//Posicion 0
  {0, 0, 0, 0, 0, 0},//Posicion 1
  {0, 0, 0, 0, 0, 0},//Posicion 2
  {0, 0, 0, 0, 0, 0},//Posicion 3
  {0, 0, 0, 0, 0, 0},//Posicion 4
  {0, 0, 0, 0, 0, 0},//Posicion 5
  {0, 0, 0, 0, 0, 0}//Posicion 6
};
int TiposDonas = 3;


Servo brazo[7];
int EstadoFlujograma = 0;
int Ptmp = 0;
int Mtmp = 0;

void setup() {
  for (int i = 0 ; i  < 6  ; i ++) {
    brazo[i].attach(PinMotor[i]);
    brazo[i].write(PosicionActual[i]);
  }
  brazo[6].attach(PinMotor[6]);
  brazo[6].write(PosicionActual[1]);
  Serial.begin(9600);
}

void loop() {
  MostrarPosicion();

  if (Serial.available()) {
    char Letra = Serial.read();
    if (Letra == 'D' || Letra == 'd') {
      DescansarBrazo();
    }
    else if (Letra == 'F' || Letra == 'f') {
      Rutina(PosicionFresa);
    }
    else if (Letra == 'C' || Letra == 'c') {
      Rutina(PosicionChicle);
    }
    else if (Letra == 'L' || Letra == 'l') {
      Rutina(PosicionLimon);
    }
    else {
      ActualizarFlujograma(Letra);
    }
  }
}

void ActualizarFlujograma(char Letra ) {
  // Serial.print("Letra ");
  // Serial.print(Letra);
  // Serial.print(" E ");
  // Serial.println(EstadoFlujograma);
  if (EstadoFlujograma == 0) {
    if (Letra == 'M' || Letra == 'm') {
      EstadoFlujograma = 1;
      Ptmp = 0;
      Mtmp = 0;
    }
  }
  else if (EstadoFlujograma == 1) {
    if (Letra >= '0'  || Letra <= '5') {
      Mtmp = int (Letra - '0');
      //    Serial.print("Mtmp:");
      //    Serial.println(Mtmp);
      EstadoFlujograma = 2;
    } else {
      EstadoFlujograma = 0;
    }
  } else if (EstadoFlujograma == 2) {
    if (Letra == 'P' || Letra == 'p') {
      EstadoFlujograma = 3;
    } else {
      EstadoFlujograma = 0;
    }
  } else if (EstadoFlujograma == 3) {
    if (Letra >= '0' && Letra <= '9') {
      Ptmp = Ptmp * 10 + int(Letra - '0');
    } else if (Letra == 'X' || Letra == 'x') {
      EstadoFlujograma = 4;
      //   Serial.print(" Ptmp:");
      //   Serial.println(Ptmp);
    }
    else {
      EstadoFlujograma = 0;
    }

  } else if (EstadoFlujograma == 4) {
    EstadoFlujograma = 0;
    if (Ptmp >= PosicionMinima[Mtmp] && Ptmp <= PosicionMaxima[Mtmp]) {
      PosicionActual[Mtmp] = Ptmp;
      brazo[Mtmp].write( PosicionActual[Mtmp]);
      if (Mtmp == 1) {
        brazo[6].write( PosicionActual[Mtmp]);
      }
    }
  }
}

void MostrarPosicion() {
  for (int i = 0 ; i  < 6  ; i ++) {
    Serial.print(" M");
    Serial.print(i);
    Serial.print(" ");
    Serial.print(PosicionActual[i]);
  }
  Serial.println();
  //delay(1000);
}

void DescansarBrazo() {
  for (int i = 0 ; i  < 6  ; i ++) {
    brazo[i].write(PosicionInicial[i]);
  }
}


void Rutina(int Pasos[7][6]) {
  //Contar en que paso estamos
  for (int i = 0; i < CantidadPasos; i++) {
    //Contando los motor actualizar la posicion
    bool Finalizamos = false;
    while (!Finalizamos) {// mientra no finaliza segir
      Serial.print("Paso ");
      Serial.print(i);
      Serial.print(" : ");
      Finalizamos = true;
      for (int j = 0; j < 6; j++) {
        if (Pasos[i][j] > PosicionActual[j]) {
          PosicionActual[j] = PosicionActual[j] + PasoMover;
          brazo[j].write(PosicionActual[j]);
        } else if (Pasos[i][j] < PosicionActual[j]) {
          PosicionActual[j] = PosicionActual[j] - PasoMover;
          brazo[j].write(PosicionActual[j]);
        }
        if (abs(Pasos[i][j] - PosicionActual[j]) < PasoMover) {
          PosicionActual[j] = Pasos[i][j];
          brazo[j].write(PosicionActual[j]);
        }
        if (!(Pasos[i][j] == PosicionActual[j])) {
          Finalizamos = false;
        }
      }
      MostrarPosicion();
      delay(Descanso);
    }
  }
  DescansarBrazo();
}
