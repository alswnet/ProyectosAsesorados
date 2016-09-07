#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int MotorPin1[4] = {44, 0, 0, 0};
int MotorPin2[4] = {45, 0, 0, 0};
int MotorPin3[4] = {46, 0, 0, 0};
int MotorPin4[4] = {47, 0, 0, 0};

int compuerta = 13;
int buttonestado [6] = {0, 0, 0, 0, 0, 0};
int pinbutton[6] = {22, 23, 24, 25, 26, 27};
float Costos[6] = {0.25, 0.25, 0.25, 0.25, 0.25, 0.25};
int Estado = 0;
int led[] = {13};
float dinero = 0;
float Ventas = 0;
int coint = 2;//Es el pin 21
int MoverMotor = -1;
int STEP[2]  = {7, 0};
int DIR[2] = {6, 0};
// se pueden crear un máximo de 8 objetos
int pos = 0;
int DistanciaMax = 0;
int SensorIR = A0;

void setup() {
  for ( int i = 0; i <= 1; i++)
    pinMode(led[i], OUTPUT);
  Serial.begin(9600); //abre el puerto serie y establece la velocidad en 115200 bps
  Serial.println("Encendido Listo");
  for (int i = 0; i < 4; i++) {
    pinMode(MotorPin1[i], OUTPUT);
    pinMode(MotorPin2[i], OUTPUT);
    pinMode(MotorPin3[i], OUTPUT);
    pinMode(MotorPin4[i], OUTPUT);
  }
  for (int i = 0; i < 6 ; i++) {
    pinMode(pinbutton[i], OUTPUT);
  }
  for (int i = 0; i < 2; i++) {
    pinMode(DIR[i], OUTPUT); //Indicamos que los pines son de salida
    pinMode(STEP[i], OUTPUT);
    digitalWrite(DIR[i], HIGH); //Fijamos una direción
  }
  lcd.begin(20, 4); //Define el tamñao del LCD 20,
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.write("la moneda"); //Imprime la indicación a seguir.
  attachInterrupt(coint , ContarDinero, RISING);
}

void loop() {
  ActualizarBoton();
  switch (Estado) {
    case 0 :
      dinero = 0;
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.write("Inserte moneda");
      Estado = 1;
      delay(1000);
      break;
    case 1:
      lcd.setCursor(0, 1);
      lcd.print("D=");
      lcd.print(dinero);
      lcd.print(" V=");
      lcd.print(Ventas);
      lcd.setCursor(0, 2);
      for (int i = 0; i < 6; i++) {
        lcd.print(i + 1);
        lcd.print("/");
        lcd.print(Costos[i]);
        lcd.print(" ");
        if (i == 2) {
          lcd.setCursor(0, 3);
        }
      }
      Serial.println(dinero);
      for (int i = 0; i < 6; i++) {
        if (buttonestado[i] == 1 && dinero > 0 )
        {
          MoverMotor = i;
          dinero = dinero - Costos[i];
          Ventas = Ventas + Costos[i];
          Estado = 2;
        }
      }
      break ;

    case 2 :
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.write("dando producto");
      delay(1000);
      do {
        MoverUL(MoverMotor, 10);
      } while (VerificarDistancia() == 1);
      Estado = 0;
      break;
  }
}


void ActualizarBoton()
{
  for (int i = 0; i < 6 ; i++) {
    buttonestado[i] = digitalRead(pinbutton[i]);
  }
}

void MoverUL(int i, float tiempo) {

  if (i > 1) {
    i = i - 2;
    digitalWrite(MotorPin1[i], HIGH); //– A
    digitalWrite(MotorPin2[i], HIGH); //– B
    digitalWrite(MotorPin3[i], LOW); //– C
    digitalWrite(MotorPin4[i], LOW); //– D
    delay(tiempo); // Un micro segundo de espera

    // Punto B (Segundo)
    digitalWrite(MotorPin1[i], LOW);
    digitalWrite(MotorPin2[i], HIGH );
    digitalWrite(MotorPin3[i], HIGH);
    digitalWrite(MotorPin4[i], LOW);
    delay(tiempo);
    // Punto C (Tercero)
    digitalWrite(MotorPin1[i], LOW);
    digitalWrite(MotorPin2[i], LOW);
    digitalWrite(MotorPin3[i], HIGH);
    digitalWrite(MotorPin4[i], HIGH);
    delay(tiempo);

    // Punto D (Cuarto)
    digitalWrite(MotorPin1[i], HIGH);
    digitalWrite(MotorPin2[i], LOW);
    digitalWrite(MotorPin3[i], LOW);
    digitalWrite(MotorPin4[i], HIGH);
    delay(tiempo);
  }
  else {
    digitalWrite(STEP[i], HIGH);
    delay(1);
    digitalWrite(STEP[i], LOW);
    delay(1);
  }
}

void ContarDinero() {
  dinero = dinero + 0.01;
}

int VerificarDistancia() {
  float sensorValue = analogRead(SensorIR);
  float cm = 10650.08 * pow(sensorValue, -0.935) - 10;
  Serial.println(cm);
  if (cm > DistanciaMax) {
    DistanciaMax = cm;
  }

  else if (cm < DistanciaMax - 4) {

    return 0;
  }
  return 1;
}
