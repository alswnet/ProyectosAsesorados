#include <Servo.h>

int PinMotor[7] = {2, 3, 4, 5, 6, 7, 8};
int PosicionActual[6] = {0, 0, 0, 0, 0, 0};
int PosicionMaxima[6] = {180, 180, 180, 180, 180, 180};
int PosicionMinima[6] = {0, 0, 0, 0, 0, 0};

Servo brazo[7];
int EstadoFlujograma = 0;
int Ptmp = 0;
int Mtmp = 0;

void setup() {
  for (int i = 0 ; i  < 6  ; i ++) {
    brazo[i].attach(PinMotor[i]);
    brazo[i].write(PosicionActual[i]);
  }
  brazo[7].attach(PinMotor[7]);
  brazo[7].write(PosicionActual[1]);
  Serial.begin(9600);
}

void loop() {
  MostrarPosicion();

  if (Serial.available()) {
    char Letra = Serial.read();
    // Serial.print("Letra ");
    // Serial.print(Letra);
    // Serial.print(" E ");
    // Serial.println(EstadoFlujograma);
    if (EstadoFlujograma == 0) {
      if (Letra == 'M') {
        EstadoFlujograma = 1;
        Ptmp = 0;
        Mtmp = 0;
      }
    }
    else if (EstadoFlujograma == 1) {
      if (Letra >= '0' && Letra <= '5') {
        Mtmp = int (Letra - '0');
        //    Serial.print("Mtmp:");
        //    Serial.println(Mtmp);
        EstadoFlujograma = 2;
      } else {
        EstadoFlujograma = 0;
      }
    } else if (EstadoFlujograma == 2) {
      if (Letra == 'P') {
        EstadoFlujograma = 3;
      } else {
        EstadoFlujograma = 0;
      }
    } else if (EstadoFlujograma == 3) {
      if (Letra >= '0' && Letra <= '9') {
        Ptmp = Ptmp * 10 + int(Letra - '0');
      } else if (Letra == 'X') {
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
        if (Ptmp == 1) {
          brazo[6].write( PosicionActual[Mtmp]);
        }
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
