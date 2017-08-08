#include <Servo.h>
Servo myservo1;
Servo myservo2;
Servo myservo3;
Servo myservo4;
Servo myservo5;

int Sensor1 = 0;
int Sensor2 = 0;
int Sensor3 = 0;
int Sensor4 = 0;
int Sensor5 = 0;

int pos1 = 0;
int pos2 = 0;
int pos3 = 0;
int pos4 = 0;
int pos5 = 0;
void setup() {
  myservo1.attach(11);
  myservo2.attach(10);
  myservo3.attach(9);
  myservo4.attach(5);
  myservo5.attach(3);
  Serial.begin(9600);

}

void loop() {
  Sensor1 = analogRead(A0);
  Sensor2 = analogRead(A1);
  Sensor3 = analogRead(A2);
  Sensor4 = analogRead(A3);
  Sensor5 = analogRead(A4);

  pos1 = map(Sensor1,645,680,0,255);
  pos2 = map(Sensor2,645,680,0,255);
  pos3 = map(Sensor3,645,680,0,255);
  pos4 = map(Sensor4,645,680,0,255);
  pos5 = map(Sensor5,645,680,0,255);
  myservo1.write(pos1);
  myservo2.write(pos2);
  myservo3.write(pos3);
  myservo4.write(pos4);
  myservo5.write(pos5);
  delay(500);

}
