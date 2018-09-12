#include <Servo.h>
#include <WiFi.h>
#include <PubSubClient.h>

const char* ssid = "ALSW";
const char* password = "2526-4897";
const char* mqtt_server = "broker.mqtt-dashboard.com";

WiFiClient espClient;
PubSubClient client(espClient);

static const int PinServoVidrio = 4;
static const int PinServoPlastico = 17;
static const int PinServoLata = 16;
static const int PinDirecion = 18;
static const int PinPulso = 23;
int Estado = 0;// 0 Nada - 1 Plastico - ...

#define Plastico 1
#define Vidrio 2
#define Lata 3
#define Nada 0
#define PosicionDescando 10
#define PosicionActivo 60

Servo ServoVidrio;
Servo ServoPlastico;
Servo ServoLata;

void setup() {
  Serial.begin(115200);
  ServoVidrio.attach(PinServoVidrio);
  ServoPlastico.attach(PinServoPlastico);
  ServoLata.attach(PinServoLata);
  pinMode(PinDirecion, OUTPUT);
  digitalWrite(PinDirecion, 0);
  pinMode(PinPulso, OUTPUT);
  digitalWrite(PinPulso, 0);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  MoverMotorPaso();
  switch (Estado) {
    case Nada:
      ServoVidrio.write(PosicionDescando);
      ServoPlastico.write(PosicionDescando);
      ServoLata.write(PosicionDescando);
      Estado = 5;
      break;
    case Vidrio:
      ServoVidrio.write(PosicionActivo );
      ServoPlastico.write(PosicionDescando);
      ServoLata.write(PosicionDescando);
      Estado = 5;
      break;
    case Plastico:
      ServoVidrio.write(PosicionDescando);
      ServoPlastico.write(PosicionActivo);
      ServoLata.write(PosicionDescando);
      Estado = 5;
      break;
    case Lata:
      ServoVidrio.write(PosicionDescando);
      ServoPlastico.write(PosicionDescando);
      ServoLata.write(PosicionActivo);
      Estado = 5;
      break;
  }
}

void MoverMotorPaso() {
  digitalWrite(PinPulso, 0);
  delay(1);
  digitalWrite(PinPulso, 1);
  delay(1);
}


void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando Conectar con MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      client.subscribe("ITX/Salida");
    } else {
      Serial.print("Error, rc=");
      Serial.print(client.state());
      Serial.println(", intentando de nuevo 5 segundo");
      delay(5000);
    }
  }
}

