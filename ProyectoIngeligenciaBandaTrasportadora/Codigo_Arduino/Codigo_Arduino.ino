#include <Servo.h>
#include <WiFi.h>

#include <WiFiMulti.h>
#include <PubSubClient.h>

const char* ssid = "ALSW";
const char* password = "2526-4897";
const char* mqtt_server = "iot.eclipse.org";
int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);
WiFiMulti wifiMulti;

static const int PinServoVidrio = 22;
static const int PinServoPlastico = 19;
static const int PinServoLata = 16;
static const int PinDireccion = 18;
static const int PinPulso = 23;
int Estado = 0; // 0 Nada - 1 Plastico -...

#define Plastico 1
#define Vidrio 2
#define Lata 3
#define Nada 0
#define PosicionDescanzo 180
#define PosicionActivo 110

Servo ServoVidrio;
Servo ServoPlastico;
Servo ServoLata;

void setup() {
  Serial.begin(115200);
  ServoVidrio.attach(PinServoVidrio);
  ServoPlastico.attach(PinServoPlastico);
  ServoLata.attach(PinServoLata);
  pinMode(PinDireccion, OUTPUT);
  digitalWrite(PinDireccion, 1);
  pinMode(PinPulso, OUTPUT);
  digitalWrite(PinPulso, 0);
  wifiMulti.addAP("ALSW", "2526-4897");

  if (wifiMulti.run() == WL_CONNECTED) {
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());



  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);


  ServoVidrio.write(PosicionDescanzo);
  ServoPlastico.write(PosicionDescanzo);
  ServoLata.write(PosicionDescanzo);
  delay(1000);
  ServoVidrio.write(PosicionActivo);
  ServoPlastico.write(PosicionActivo);
  ServoLata.write(PosicionActivo);

}

void loop () {

  if (wifiMulti.run() != WL_CONNECTED) {
    Serial.println("WiFi not connected!");
    delay(1000);
    return;
  }

  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  MoverMotorPaso() ;
  switch (Estado) {
    case Nada :
      ServoVidrio.write(PosicionDescanzo);
      ServoPlastico.write(PosicionDescanzo);
      ServoLata.write(PosicionDescanzo);
      Estado = 5;
      break;
    case Vidrio:
      ServoVidrio.write(PosicionActivo);
      ServoPlastico.write(PosicionDescanzo);
      ServoLata.write(PosicionDescanzo);
      Estado = 5;
      break;
    case Plastico:
      ServoVidrio.write(PosicionDescanzo);
      ServoPlastico.write(PosicionActivo);
      ServoLata.write(PosicionDescanzo);
      Estado = 5;
      break;
    case Lata:
      ServoVidrio.write(PosicionDescanzo);
      ServoPlastico.write(PosicionDescanzo);
      ServoLata.write(PosicionActivo);
      Estado = 5;
      break;
  }
}

void MoverMotorPaso() {
  digitalWrite(PinPulso, 0);
  delay(7);
  digitalWrite(PinPulso, 1);
  delay(7); //PARA CAMBIAR LA VELOCIDAD 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,50 

}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Intentando Conectar con MQTT...");
    if (client.connect("ESP32Client")) {
      Serial.println ("connected");
      client.subscribe("itx/entrada");
    } else {
      Serial.print("Error, rc=");
      Serial.print(client.state());
      Serial.println(", Intentando de nuevo 5 segundos");
      delay(5000);
    }
  }
}


void callback(char* topic, byte* message, unsigned int length) {
  Serial.print ("message arrived on topic: ");
  Serial.print(topic);
  Serial.print(" . message : ");
  String messageTMP;

  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTMP += (char) message [i];
  }
  Serial.println();

  if (String(topic) == "itx/entrada") {
    if (messageTMP == "vidrio") {
      Estado = Vidrio;
    }
    if (messageTMP == "plastico") {
      Estado = Plastico;
    }
    if (messageTMP == "lata") {
      Estado = Lata;
    }
    if (messageTMP == "nada") {
      Estado = Nada;
    }

    Serial.print("Mensaje: ");
    Serial.println(messageTMP);
  }
}

