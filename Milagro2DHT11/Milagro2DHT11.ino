#include "DHT.h"

#define DHTPIN 2
#define DHTTYPE DHT11

float h;
float t;
float f;

DHT dht(DHTPIN, DHTTYPE);
int NivelActivacionVentilador = 30;
int PinVentilador = 3;

void setup() {
  Serial.begin(9600);
  Serial.println("DHTxx test!");
  pinMode(PinVentilador, OUTPUT);
  dht.begin();
}

void loop() {
  ActualizarEntradas();

  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  ActualizarSalida();

  MostarSerial();
}

void ActualizarEntradas() {
  h = dht.readHumidity();
  t = dht.readTemperature();
  f = dht.readTemperature(true);
}

void ActualizarSalida() {
  if (t > NivelActivacionVentilador) {
    digitalWrite(PinVentilador, 1);
  } else {
    digitalWrite(PinVentilador, 0);
  }

}

void MostarSerial() {
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.print(" ");
  Serial.print(" Temperature: ");
  Serial.print(t);

  Serial.print(" ");
  Serial.print(25);
  Serial.print(" ");
  Serial.print(30);
  Serial.print(" ");
  Serial.print(35);
  Serial.print(" ");
  Serial.println();


}
