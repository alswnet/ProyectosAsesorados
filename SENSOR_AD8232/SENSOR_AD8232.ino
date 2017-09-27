#include <SoftwareSerial.h>//Se puede emular mas de un puerto serial

SoftwareSerial BTSerial(3, 2);

int Valor = 0;

void setup() {
  Serial.begin(9600);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  BTSerial.begin(9600);

}

void loop() {

  if ((digitalRead(4) == 1) || (digitalRead(5) == 1)) {
    BTSerial.write(50);
    Serial.print(50);
  }
  else {
    Valor = map(analogRead(A0), 0, 1024, 0, 200);
    BTSerial.write(Valor);
    Serial.print(analogRead(A0));
  }
  // BTSerial.println('*');
  Serial.println();
  delay(1);
}
