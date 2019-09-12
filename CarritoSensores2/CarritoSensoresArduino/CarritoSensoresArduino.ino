//Pines de los motores
int MotorD[2] = {3, 2};
int MotorI[2] = {5, 4};
int PwmD = 6;
int PwmI = 7;
int ValX = 0;
int ValY = 0;
int motorI = 0;
int motorD = 0;
const int SensorLlama = A0;

void setup() {
  pinMode(PwmD, OUTPUT);
  pinMode(PwmI, OUTPUT);
  for (int i = 0; i < 2; i++) {
    pinMode(MotorD[i], OUTPUT);
    pinMode(MotorI[i], OUTPUT);
  }
  pinMode(SensorLlama, INPUT);
  Serial.begin(9600);
}

void loop() {
  DecodificarSerial();

  motorI = map(ValY, -100, 100, -255, 255);
  motorI -= map(ValX, -100, 100, -255, 255);
  motorD = map(ValY, -100, 100, -255, 255);
  motorD += map(ValX, -100, 100, -255, 255);

  /*
    Serial.print("I:");
    Serial.print(motorI);
    Serial.print(" D:");
    Serial.println(motorD);
  */
  motorD = constrain(motorD, -255, 255);
  motorI = constrain(motorI, -255, 255);

  VelocidadMotor(MotorI, PwmI, motorI);
  VelocidadMotor(MotorD, PwmD, motorD);

  int ValorLlama = analogRead(SensorLlama);
  Serial.print("Llama/");
  Serial.print(ValorLlama);
  Serial.print("\n");


// Codigo distancia 


//
  Serial.print("D/");
  Serial.print(100);
  Serial.print("\n");
}

//Funcion para Poner una velocidad a un motor
//La velocidad puede ser desde -255 a 255
void VelocidadMotor(int Motor[], int PWM, int Velocidad) {
  if (Velocidad > 0 ) {
    digitalWrite(Motor[0],  1);
    digitalWrite(Motor[1],  0);
  }
  else {
    Velocidad = - Velocidad;
    digitalWrite(Motor[0], 0);
    digitalWrite(Motor[1], 1);
  }
  analogWrite(PWM, Velocidad);
}


void DecodificarSerial() {
  String Mensaje = Serial.readStringUntil('\n');
  int PosicionPleca = Mensaje.indexOf('/');
  int PosicionSaltoLinea = Mensaje.length();
  String Dato = Mensaje.substring(0, PosicionPleca);
  int Valor = Mensaje.substring(PosicionPleca + 1, PosicionSaltoLinea).toInt();
  if (Dato.equals("X")) {
    ValX = Valor;
  }
  else if (Dato.equals("Y")) {
    ValY = Valor;
  }
}
