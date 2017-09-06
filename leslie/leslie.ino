#include <Keypad.h> //llama a la librería Keypad.h //incluimos libreria 
#include <SoftwareSerial.h> //Requerida internamete por el escudo WiFi
#include <SparkFunESP8266WiFi.h>


//Configuracion de la red inalambrica
const char ssid[] = "TURBONETT_ALSW";
const char password[] = "2124-1324";


//Cadena usada para almacenar la ruta de la URL
String rutaUrl;

//Objetos de clase para el servidor (arduino) y el cliente (navegador)
ESP8266Server server = ESP8266Server(80);
ESP8266Client cliente;

char contrasena[1] = "1111"; //aquí escribimos la contraseña de 4 dígitos // contraseña para encender las luces
char contrasena2[] = "2222"; //contraseña para desactivar la alarma
char contrasena3[] = "3333"; // Contraseña para activar la alarma
char codigo[4];            //Cadena donde se guardaran los caracteres d0e las teclas presionadas
int cont = 0;        //variable que se incrementara al presionar las teclas
int inPin = 10;
int Buzzer = 12;
const int LedEstado = 13;
const byte ROWS = 4; //Numero de filas del teclado que se esta usando
const byte COLS = 4; //Numero de columnas del teclado que se esta usando
const int Luces_Conference1 = A0;
const int Luces_Conference2 = 3 ;
const int Luces_Entrada = 4 ;
const int Luces_Oficina = 5 ;
char hexaKeys[ROWS][COLS] =  //Aquí pondremos la disposición de los caracteres tal cual están en nuestro teclado
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //Seleccionamos los pines en el arduino donde iran conectadas las filas
byte colPins[COLS] = {5, 4, 3, 2}; //Seleccionamos los pines en el arduino donde iran conectadas las columnas

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); //inicializa el teclado

void setup()
{
  Serial.begin(9600); //inicializar puerto serie
  pinMode(inPin, INPUT);
  pinMode (Luces_Conference1, OUTPUT);
  pinMode (Luces_Conference2, OUTPUT);
  pinMode (LedEstado, OUTPUT);
  pinMode (Luces_Entrada, OUTPUT);
  pinMode (Luces_Oficina, OUTPUT);
  pinMode(Buzzer, OUTPUT);


  //Inicializa el modulo WiFi
  esp8266.begin();
  esp8266.setMode(ESP8266_MODE_STA);  //Modo estacion (cliente WiFi)
  while (esp8266.connect(ssid, password) <= 0) {
    //Si no se puede conectar emite un error y para el programa
    Serial.println(F("Reintentando"));
    digitalWrite(LedEstado, 1);
    delay(500);
    digitalWrite(LedEstado, 0);
    delay(500);
  }
  //Comienza a servir la pagina web
  server.begin();

  //Se lee la direccion IP y se indica al usuario a donde ingresar
  direccionIP = esp8266.localIP();
  Serial.print(F("Servidor listo, visite la direccion "));
  Serial.println(direccionIP);

}

void loop()
{
  Teclado();
  ConsultaWifi();
}


void ConsultaWifi() {
  char c;

  //Espera un cliente el proximo medio segundo
  cliente = server.available(500);

  //Verifica si el cliente se conecto
  if (cliente) {
    Serial.println(F("Cliente conectado"));
    //El cliente se procesa mientras haya conexion activa
    while (cliente.connected()) {
      procesarCliente();
    }
  }



}


void procesarCliente() {
  static int estado = 0;
  static boolean lineaEnBlanco = false;
  char c;

  //Determina si hay caracteres disponibles viniendo del cliente
  if (cliente.available()) {
    //La siguiente accion a realizar depende del estado actual
    switch (estado) {
      case 0:
        //En el estado inicial, se espera la secuencia GET y solo
        //salta al siguiente estado si se encontro
        if (cliente.find("GET "))
          estado = 1;
        break;
      case 1:
        //Una vez encontrada la secuencia GET, se lee la URL solicitada,
        //la cual siempre termina con un espacio
        rutaUrl = cliente.readStringUntil(' ');
        Serial.print(F("Pagina solicitada: "));
        Serial.println(rutaUrl);

        //Dependiendo de la URL solicitada, se enciende o apaga el LED
        //(Nota: Si no se especifica ninguna ruta valida, no se hace
        //nada con el LED)
        if (rutaUrl == "/Luces_Conference1") {
          //Codigo Luces_Conference1
        }
        else if (rutaUrl == "/Luces_Conference2") {
          //Codigo Luces_Conference2
        }
        else if (rutaUrl == "/Luces_Entrada") {
          //Codigo Luces_Entrada
        }
        if (rutaUrl == "/Luces_Oficina") {
          //Codigo Luces_Oficina
        }

        //Despues de la solicitud siempre se pasa al siguiente estado
        estado = 2;
        break;
      case 2:
        //En este estado se esperan 2 fines de linea consecutivos
        c = cliente.read();
        if (c == '\n' && lineaEnBlanco) {
          //Si ocrurren, el navegador ya envio la solicitud, asi que se
          //contesta enviando la pagina
          Serial.println(F("Enviando pagina..."));
          enviarPagina();
          delay(100);
          cliente.stop();
          Serial.println(F("Terminado"));

          //Una vez terminado se reinicia la secuencia del automata
          estado = 0;
          lineaEnBlanco = false;
        }

        if (c == '\n')
          //Si se recibio un fin de linea, se marca la bandera por si
          //viene un segundo
          lineaEnBlanco = true;
        else if (c != '\r')
          //Para todos los demas caracteres que no son fin de linea
          //(excepto retorno de carro) se desmarca la bandera
          lineaEnBlanco = false;
        break;
    }
  }
}



void enviarPagina() {
  //Cadenas de texto con los protocolos de comunicacion HTTP y HTML
  const char cabeceraHTTP[] = "HTTP/1.1 200 OK\r\n"
                              "Content-Type: text/html\r\n"
                              "Connection: close\r\n\r\n";
  const char cabeceraHTML[] = "<!DOCTYPE html>\n"
                              "<html>\n"
                              "  Estado del LED: ";
  const char terminadorHTML_0[] = "Apagado \n"
                                  "  <br> <a href=\"/encender\"> Encender </a>\n"
                                  "</html>\n";
  const char terminadorHTML_1[] = "Encendido \n"
                                  "  <br> <a href=\"/apagar\"> Apagar </a>\n"
                                  "</html>\n";

  //El inicio de la pagina siempre es el mismo
  cliente.write(cabeceraHTTP, strlen(cabeceraHTTP));
  cliente.write(cabeceraHTML, strlen(cabeceraHTML));

  //El final de la pagina depende del estado del LED
  if (!estadoLed)
    cliente.write(terminadorHTML_0, strlen(terminadorHTML_0));
  else
    cliente.write(terminadorHTML_1, strlen(terminadorHTML_1));
}

void Teclado() {

  char customKey = customKeypad.getKey(); //se guarda en la variable customKey el caracter de la tecla presionada
  if (customKey != NO_KEY)         //se evalúa si se presionó una tecla
  {
    codigo[cont] = customKey;        //se guarda caracter por caracter en el arreglo codigo[]
    Serial.println(codigo[cont]);    //se imprime en el puerto serie la tecla presionada
    cont = cont + 1;          //incrementamos la variable cont
    if (cont == 4)       //si ya fueron presionadas 4 teclas se evalúa si la contraseña es correcta
    {
      if (codigo[0] == contrasena[0] && codigo[1] == contrasena[1] && codigo[2] == contrasena[2] && codigo[3] == contrasena[3])
      {
        digitalWrite(13, !digitalRead(13));       //si la contraseña fué correcta se enciende o se apaga el led del pin13
        digitalWrite(Luces_Conference1, !digitalRead(Luces_Conference1));
        digitalWrite(Luces_Conference2, !digitalRead(Luces_Conference2));
        digitalWrite(Luces_Entrada, !digitalRead(Luces_Entrada));
        digitalWrite(Luces_Oficina, !digitalRead(Luces_Oficina));
      }
      cont = 0; //resetear a 0 la variable cont
    }
  }
  if (digitalRead(inPin) == HIGH && !(codigo[0] == contrasena[0] && codigo[1] == contrasena[1] && codigo[2] == contrasena[2] && codigo[3] == contrasena[3])) {
    for (int i = 0; i <= 4; i++) {
      tone(Buzzer, 2700, 250);
      digitalWrite(13, HIGH);
      // delay(100);
      // digitalWrite(13, LOW);
      // digitalWrite(Luces_Conference1, HIGH);
      // delay (100);
      // digitalWrite(Luces_Conference2, HIGH);
    }
  }
  else if (codigo[0] == contrasena2[0] && codigo[1] == contrasena2[1] && codigo[2] == contrasena2[2] && codigo[3] == contrasena2[3]) {
    //digitalWrite(Luces_Conference1 , LOW);
    //digitalWrite(Luces_Conference2, LOW);
    digitalWrite(11, HIGH);
  }
  if (digitalRead(11) == HIGH)
  {
    digitalWrite(13, LOW);
  }
  if (codigo[0] == contrasena3[0] && codigo[1] == contrasena3[1] && codigo[2] == contrasena3[2] && codigo[3] == contrasena3[3] || codigo[0] == contrasena[0] && codigo[1] == contrasena[1] && codigo[2] == contrasena[2] && codigo[3] == contrasena[3]) {
    digitalWrite(11, LOW);
  }
  //if(codigo[0]==contrasena2[0]&&codigo[1]==contrasena2[1]&&codigo[2]==contrasena2[2]&&codigo[3]==contrasena2[3]){
  //    digitalWrite(Luces_Conference1 , LOW);
  //      digitalWrite(Luces_Conference2, LOW);
  //        delay(100);               // esperar 1 segundos
  //}

}
