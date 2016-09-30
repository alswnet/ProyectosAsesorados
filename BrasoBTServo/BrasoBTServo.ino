#include <SoftwareSerial.h>//Se puede emular mas de un puerto serial
#include <Servo.h>

Servo Servo[7];

int PinServo[7] = {3, 4, 5, 6, 7, 10, 11};

SoftwareSerial BTSerial(8, 9); // RX | TX Poner los pines que usas

void setup()
{
  for (int i = 0; i < 7; i++) {
    Servo[i].attach(PinServo[i]);
  }
  Serial.begin(9600);
  Serial.println("Iniciando:");
  BTSerial.begin(9600);
  BTSerial.println("Iniciando");
  //Inicializando los puerto seria de ambos lados
}

void loop()
{
  int MoverServo = -1;
  int GradoServo = 0;
  // Leer el puerto HC-05 y lo escrive en el puerto serial de Arduino
  while (BTSerial.available()) {

    char Letra = BTSerial.read();
    Serial.write(Letra);
    if (Letra >= 'a' && Letra <= 'f') {
      Serial.println("Encontro Letra");

      Serial.println(Letra - 'a');
      MoverServo = Letra - 'a';
    }
    else if (Letra >= '0' && Letra <= '9') {
      GradoServo = GradoServo * 10 + int(Letra - '0');
    }
    else if (Letra == 'x') {
      Servo[MoverServo].write(GradoServo);
      if (MoverServo == 5) {
        Servo[6].write(GradoServo);
      }
      Serial.println();
      Serial.print("Servo ");
      Serial.print(MoverServo);
      Serial.print(" Grado ");
      Serial.println(GradoServo);
    }
  }
  // Lee el  puerto serial del arduino y lo escrive en el puerto serial
  while (Serial.available()) {
    char Letra = Serial.read();
    BTSerial.write(Letra);
    if (Letra >= 'a' && Letra <= 'f') {
      Serial.println("Encontro Letra");

      Serial.println(Letra - 'a');
      MoverServo = Letra - 'a';
    }
    else if (Letra >= '0' && Letra <= '9') {
      GradoServo = GradoServo * 10 + int(Letra - '0');
    }
    else if (Letra == 'x') {
      Servo[MoverServo].write(GradoServo);
      if (MoverServo == 5) {
        Servo[6].write(GradoServo);
      }
      Serial.println();
      Serial.print("Servo ");
      Serial.print(MoverServo);
      Serial.print(" Grado ");
      Serial.println(GradoServo);
    }
  }
}
