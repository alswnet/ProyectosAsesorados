int PinElectro[3] = {12, 2, 3};
int PinTrigger[3] = {6, 8, 10};
int PinEcho[3] = {7, 9, 11};
int PinMotor[2] = {4, 5};
int DistanciaMinima[3] = {10, 10, 10};
int DistanciaMaxima[3] = {15, 15, 15};
int ValorAceptablePH = 5;
int Distancia[3];
int ConteoVeces = 0;
int CantidaVeces = 3;

int Estado = 0;

void setup() {

  Serial.begin(9600);
  Iniciar();
  // put your setup code here, to run once:

}

void loop() {
  ActualizarEntradas();
  switch (Estado) {
    case 0:
      Serial.println("E0:Inicial");
      for (int i = 0; i < 2; i++) {
        digitalWrite(PinMotor[i], LOW);
      }
      Estado = 1;
      break;
    case 1:
      Serial.println("E1:Esperando llene primer tanque");
      if (Distancia[0] <  DistanciaMinima[0]) {
        digitalWrite(PinMotor[0], HIGH);
        Estado = 2;
      }
      break;
    case 2:
      Serial.println("E2:Esperando llene Segundo tanque");
      if (Distancia[1] <  DistanciaMinima[1]) {
        digitalWrite(PinMotor[0], LOW);
        digitalWrite(PinElectro[0], HIGH);
        Estado = 3;
      }
      break;
    case 3:
      Serial.println("E3:Esperando llene Tercer tanque");
      if (Distancia[2] <  DistanciaMinima[2]) {
        digitalWrite(PinElectro[0], LOW);
        Estado = 4;
      }
      break;
    case 4:
      Serial.println("E4:Medir PH");
      if (ValorPH() >  ValorAceptablePH || ConteoVeces > CantidaVeces) {
        digitalWrite(PinElectro[1], HIGH);
        Estado = 5;
      }
      else {
        digitalWrite(PinElectro[2], HIGH);
        digitalWrite(PinMotor[2], HIGH);
        CantidaVeces = CantidaVeces + 1;
        Estado = 6;
      }
      break;
    case 5:
      Serial.println("E5:Regar plantas");
      if (Distancia[2] >  DistanciaMaxima[2]) {
        Estado = 0;
      }
    case 6:
      Serial.println("E6: Llenando otra ves el tanque dos");
      if (Distancia[1] <  DistanciaMinima[1]) {
        digitalWrite(PinElectro[2], LOW);
        digitalWrite(PinMotor[2], LOW);
        digitalWrite(PinElectro[0], HIGH);
        Estado = 3;
      }
      break;
  case default:
      Estado = 0;
      break;
  }
}

float ValorPH() {
  return 5.5;
}//Falta meter PH

void ActualizarEntradas() {
  for (int i = 0; i < 3; i++) {
    Distancia[i] = distancia(i);
    Serial.print(" D");
    Serial.print(i);
    Serial.print(" ");
    Serial.print(Distancia[i]);
  }
  Serial.println();
}

void Iniciar() {
  for (int i = 0; i < 3; i++) {
    pinMode(PinElectro[i], OUTPUT);
    pinMode(PinTrigger[i], OUTPUT);
    pinMode(PinEcho[i], INPUT);
  }
  for (int i = 0; i < 2; i++) {
    pinMode(PinMotor[i], INPUT);
  }
}

int distancia(int cerca) {
  int tiempo, distancia;
  digitalWrite(PinTrigger[cerca], LOW);
  delayMicroseconds(2);
  digitalWrite(PinTrigger[cerca], HIGH);
  delayMicroseconds(10);
  digitalWrite(PinTrigger[cerca], LOW);
  tiempo = pulseIn(PinEcho[cerca], HIGH);
  distancia = tiempo / 58;
  return distancia;
}

