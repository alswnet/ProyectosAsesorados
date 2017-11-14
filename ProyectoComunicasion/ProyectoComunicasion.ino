#define BLYNK_PRINT Serial //Para ver el depurador  - se puede quitar
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "785b4e8f1b634ee784ae4f0b5c298ef9";//Contraseña Blynk
char ssid[] = "TURBONETT_ALSW";//Nombre de red
char pass[] = "2526-4897";//Contraseña

int PinSensor = 4;
int PinRele = 5;
boolean EnvioMensaje = false;


void setup() {
  Serial.begin(115200);
  pinMode(PinSensor, INPUT);
  pinMode(PinRele, OUTPUT);
  digitalWrite(PinRele, 0);
  Blynk.begin(auth, ssid, pass);
}

void loop() {
  // Serial.println(digitalRead(PinSensor));
  if (digitalRead(PinSensor) == 1 && !EnvioMensaje) {
    EnvioMensaje = true;
    digitalWrite(PinRele, 1);
    Serial.println("armada alarma");
    Blynk.notify("ALERTA DE INTRUSO");
  }
  Blynk.run();
}

BLYNK_WRITE(V0) {
  EnvioMensaje = false;
  digitalWrite(PinRele, 0);
  Serial.println("Apagar alarma");
}
