#include <SoftwareSerial.h>//Se puede emular mas de un puerto serial

SoftwareSerial BTSerial(3, 2);

int Amplitudes[450];

int Valor = 0;
int V = 0;

void setup() {
  Serial.begin(9600);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  BTSerial.begin(9600);

  for (int i = 0; i < 45; i++) {
    Amplitudes[i] = 100 + sin(radians (i * 4)) * 15  ;
  }
  for (int i = 45; i < 90; i++) {
    Amplitudes[i] = 100;
  }
  for (int i = 90; i < 135; i++) {
    if (i % 4) {
      Amplitudes[i] = Amplitudes[i - 1] - 1 ;
    }
    else {
      Amplitudes[i] = Amplitudes[i - 1];
    }
  }
  for (int i = 135; i < 180; i++) {
    Amplitudes[i] = Amplitudes[i - 1] + 2;
  }
  for (int i = 180; i < 225; i++) {
    Amplitudes[i] = Amplitudes[i - 1] - 2;
  }

  for (int i = 225; i < 270; i++) {
    if (i % 4) {
      Amplitudes[i] = Amplitudes[i - 1] + 1 ;
    }
    else {
      Amplitudes[i] = Amplitudes[i - 1];
    }
  }
  for (int i = 270; i < 315; i++) {
    Amplitudes[i] = 100;
  }
  for (int i = 315; i < 405; i++) {
    Amplitudes[i] = 100 + sin(radians ((i - 315)*2)) * 25 ;
  }
  for (int i = 405; i < 450; i++) {
    Amplitudes[i] = 100 + sin(radians ((i-405) * 4))* 5  ;
  }

}

void loop() {
  /*
    if ((digitalRead(4) == 1) || (digitalRead(5) == 1)) {
      BTSerial.write(50);
      Serial.print(50);
    }
    else {
      Valor = map(analogRead(A0), 0, 1024, 0, 200);
      BTSerial.write(Valor);
      Serial.print(analogRead(A0));
    }
  */
  V++;
  if (V >= 450) {
    V = 0;
  }
  BTSerial.write(Amplitudes[V]);
  Serial.println(Amplitudes[V]);
  delay(1);
}
