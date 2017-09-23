#include <Servo.h>

Servo myservo;
int Motor1D = 8;
int Motor2D = 2;

int Motor1I = 5;
int Motor2I = 6;

int SensorI = 0;
int SensorD = 0;
int SensorU = 0;

int velocidadI = 180;
int velocidadD = 180;

void setup() {
  analogWrite(12, velocidadI);
  analogWrite(11, velocidadD);
  pinMode(Motor1D, OUTPUT);
  pinMode(Motor2D, OUTPUT);
  pinMode(Motor1I, OUTPUT);
  pinMode(Motor2I, OUTPUT);
  myservo.attach(7);
  Serial.begin(9600);
}

void loop() {
    SensorI = analogRead(A0);
    SensorD = analogRead(A2);
    SensorU = analogRead(A4);
//    Serial.println(SensorI);
//    Serial.println(SensorD);
//    Serial.println(SensorU);
//    Serial.println("***************");
//    delay(500);
    if (SensorD < 600 && SensorI < 600) {
      alto();
    }
    else if (SensorD > 600 && SensorI > 600) {
      delante();
    }
    else if (SensorD > 600 && SensorI < 600) {
      derecha();
    }
    else if (SensorD < 600 && SensorI > 600) {
      izquierda();
    }
    else {
      alto();
    }
    delay(1);
//
//  delante();
//  delay(3000);
//  alto();
//  delay(500);
//  derecha();
//  delay(3000);
//  alto();
//  delay(500);
//  izquierda();
//  delay(3000);
//  alto();
//  delay(500);

  //  if (analogRead(A3) > 600) {
  //    alto();
  //    delay(400);
  //    myservo.write(110);
  //    delay(1500);
  //    myservo.write(10);
  //    delay(100);
  //    delante();
  //    delay(200);
  //  }
}

void alto() {
  analogWrite(Motor2D, 0);
  analogWrite(Motor1D, 0);
  analogWrite(Motor1I, 0);
  analogWrite(Motor2I, 0);
}

void delante() {
  analogWrite(Motor2D, velocidadD);
  analogWrite(Motor1D, 0);
  analogWrite(Motor1I, 0);
  analogWrite(Motor2I, velocidadI);
}

void izquierda() {
  analogWrite(Motor2D, 0);
  analogWrite(Motor1D, velocidadD);
  analogWrite(Motor1I, 0);
  analogWrite(Motor2I, velocidadI);
}

void derecha() {
  analogWrite(Motor2D, velocidadD);
  analogWrite(Motor1D, 0);
  analogWrite(Motor1I, velocidadI);
  analogWrite(Motor2I, 0);
}
