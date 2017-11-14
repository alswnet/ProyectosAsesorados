#include <ESP8266WiFi.h>

char* ssid = "TURBONETT_ALSW";
char* password = "2526-4897";
WiFiServer server(80);

//Servidor
int respuesta = 0;
int LedPrueba = 5;
int Sensor = 12;
String res;

void setup() {
  Serial.begin(115200);
  pinMode(LedPrueba, OUTPUT);
  pinMode(Sensor,INPUT);
  Serial.println();
  Serial.println();
  Serial.print("Conectado a");
  Serial.println(ssid);


  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");

  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop() {
  //Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  String peticion = client.readStringUntil('\r');
  Serial.println(peticion);
  client.flush();

  if (peticion.indexOf("/Sensor") != -1)
    respuesta = 1;
  else
    respuesta = 0;
  digitalWrite(LedPrueba, respuesta);

  client.flush();
  //preparando la respuesta
  if (respuesta) {
    const char cabeceraHTTP[] = "HTTP/1.1 200 OK\r\n"
                                "Content-Type: text/html\r\n"
                                "Connection: close\r\n\r\n";
    const char cabeceraHTML[] = "<!DOCTYPE html>\n"
                                "<html>\n"
                                "  <body>\n"
                                "    Estado de la habitacion: ";
    const char terminadorHTML[] = " \n"
                                  "    <meta http-equiv=\"refresh\" "
                                  "content=\"5\">\n"
                                  "  </body>\n"
                                  "</html>\n";
    client.write(cabeceraHTTP, strlen(cabeceraHTTP));
    client.write(cabeceraHTML, strlen(cabeceraHTML));
    leerTemperatura();
    client.print(res);
    client.write(terminadorHTML, strlen(terminadorHTML));
  }
  delay(1);
  Serial.println("Client disonnected");
  client.stop();
}


void leerTemperatura() {
  int voltaje;

  voltaje = digitalRead(Sensor);
  if (voltaje == 1) {
    res = "Intruso";
  }
  else {
    res = "Nadie";
  }
}
