#include <ESP8266WiFi.h>

char* ssid = "AndroidAP";
char* password = "jteb7719";
WiFiServer server(80);

//Servidor
int estado;
int respuesta = 0;

//Finales de carrera
int PA = 15;
int PB = 13;
int LecturaPA = 0;
int LecturaPB = 0;

//Driver
int PWMA = 16;
int AIN2 = 5;
int AIN1 = 4;
int BIN1 = 2;
int BIN2 = 14;
int PWMB = 12;
boolean EstadoPuente = false;

void setup() {
  //Driver
  pinMode(PWMA, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(AIN1, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
  pinMode(PWMB, OUTPUT);

  pinMode(PA, INPUT);
  pinMode(PB, INPUT);


  Serial.begin(115200);

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
  LecturaPA = digitalRead(PA);
  LecturaPB = digitalRead(PB);
  if (LecturaPA == 1 || LecturaPB == 1) {
    Alto();
  }
  //Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }

  String peticion = client.readStringUntil('\r');
  Serial.println(peticion);
  client.flush();

  if (peticion.indexOf("/Bajar") != -1)
    respuesta = 1;
  else if (peticion.indexOf("/Subir") != -1)
    respuesta = 0;
  else {
    Serial.println("Petición Invalida");
  }
  if (respuesta == 1 && EstadoPuente == false) {
    EstadoPuente = true;
    Subir();
  }
  else if (respuesta == 0 && EstadoPuente == true) {
    EstadoPuente = false;
    Bajar();
  }

  client.flush();
  //preparando la respuesta
  String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
  s += "<h3>Puente ";
  s += (respuesta) ? "Bajar" : "Subir";
  s += "</h3>\r\n";
  s += "<a href=\"";                                                          //<a href=\apagar> cambiar</a>
  s += (respuesta) ? "Subir" : "Bajar";
  s += "\"> Cambiar</a> </html> \n";

  client.print(s);
  delay(1);
  Serial.println("Client disonnected");
  client.stop();
}




void Subir() {
  //Inicio Subir 1
  digitalWrite(AIN2, 1);
  digitalWrite(AIN1, 0);
  analogWrite(PWMA, 110);//0 - 255

  digitalWrite(BIN2, 1);
  digitalWrite(BIN1, 0);
  analogWrite(PWMB, 110);//0 - 255
  delay(500);
}
void Alto() {
  //Ariba
  digitalWrite(AIN2, 1);
  digitalWrite(AIN1, 1);
  analogWrite(PWMA, 255);//0 - 255

  digitalWrite(BIN2, 1);
  digitalWrite(BIN1, 1);
  analogWrite(PWMB, 255);//0 -
}


void Bajar() {
  //Bajando1
  digitalWrite(AIN2, 0);
  digitalWrite(AIN1, 1);
  analogWrite(PWMA, 255);//0 - 255

  digitalWrite(BIN2, 0);
  digitalWrite(BIN1, 1);
  analogWrite(PWMB, 255);//0 - 255
  delay(500);
}

void Espera() {
  //Reposo
  digitalWrite(AIN2, 0);
  digitalWrite(AIN1, 0);
  analogWrite(PWMA, 0);//0 - 255

  digitalWrite(BIN2, 0);
  digitalWrite(BIN1, 0);
  analogWrite(PWMB, 0);//0 - 255
}
