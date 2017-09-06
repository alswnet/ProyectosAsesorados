#include <Keypad.h> //llama a la librería Keypad.h //incluimos libreria 
#include <SoftwareSerial.h> //Requerida internamete por el escudo WiFi
#include <SparkFunESP8266WiFi.h>

//Configuracion de la red inalambrica
const char ssid[] = "Manuel";
const char password[] = "12345678";

//Cadena usada para almacenar la ruta de la URL
String rutaUrl;

//Objetos de clase para el servidor (arduino) y el cliente (navegador)
ESP8266Server server = ESP8266Server(80);
ESP8266Client cliente;

char contrasena[5][4] = {"0000", "1111", "2222", "3333", "4444"}; //aquí escribimos la contraseña de 4 dígitos // contraseña para encender las luces
char contrasenaDesactivar[4] = "1234"; //contraseña para desactivar la alarma
char ContrasenaActivar[4] = "4321"; // Contraseña para activar la alarma
char codigo[4];            //Cadena donde se guardaran los caracteres d0e las teclas presionadas
int cont = 0;        //variable que se incrementara al presionar las teclas
const int Pir[2] = {10, 11};
const int Buzzer = 12;
const int LedEstado = 13;
const byte ROWS = 4; //Numero de filas del teclado que se esta usando
const byte COLS = 4; //Numero de columnas del teclado que se esta usando
const int Led[4] = {A0, A1, A2, A3};
boolean EstadoLed[4] = {false, false, false, false};
int EstadoAlarma = 0;
char hexaKeys[ROWS][COLS] =  //Aquí pondremos la disposición de los caracteres tal cual están en nuestro teclado
{
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {3, 2, 1, 0}; //Seleccionamos los pines en el arduino donde iran conectadas las filas
byte colPins[COLS] = {7, 6, 5, 4}; //Seleccionamos los pines en el arduino donde iran conectadas las columnas

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); //inicializa el teclado

void setup()
{
  IPAddress direccionIP;

  Serial.begin(9600); //inicializar puerto serie

  Serial.println("Iniciando");
  for (int i = 0; i < 4; i++) {
    pinMode (Led[i], OUTPUT);
  }
  pinMode (LedEstado, OUTPUT);
  pinMode(Buzzer, OUTPUT);
  for (int i = 0; i < 2; i++) {
    pinMode (Pir[i], INPUT);
  }

  //Inicializa el modulo WiFi
  Serial.println("Activiando Wifi");
  esp8266.begin();
  esp8266.setMode(ESP8266_MODE_STA);  //Modo estacion (cliente WiFi)


  if (esp8266.status() <= 0) // If we're not already connected
  {
    while (esp8266.connect(ssid, password) < 0)
    {
      Serial.println(F("Error connecting"));
      digitalWrite(LedEstado, 1);
      delay(250);
      digitalWrite(LedEstado, 0);
      delay(250);
    }
  }
  //Comienza a servir la pagina web
  server.begin();

  //Se lee la direccion IP y se indica al usuario a donde ingresar
  Serial.print(F("Servidor listo, visite la direccion "));
  Serial.println(esp8266.localIP());

}

void loop()
{
  Teclado();
  EstadoPir();
  ActualizarLed();
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
        if (rutaUrl == "/Led0E") {
          EstadoLed[0] = true;
          Serial.println("Led 1 Encender");
        }
        else if (rutaUrl == "/Led0P") {
          EstadoLed[0] = false;
          Serial.println("Led 1 Apagado");
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
                              "  <h1>Sistema Leslie </h1> ";
  const char TextoApagado[] = " Apagado ";
  const char TextoEncender[] = " Encendido ";

  const char Nombre0[] = "Conferencia 1: ";
  const char Nombre1[] = "Conferencia 2: ";
  const char Nombre2[] = "Oficina 1: ";
  const char Nombre3[] = "Entrada ";

  const char Numero0[] = "0";

  const char EstadoActivo[] = "E";
  const char EstadoApagado[] = "P";

  const char TextoA[] = " Link: <a href=\"/Led";

  const char TextoFinA[] = "\">";
  const char TextoCierre[] = " </a><br>\n";
  const char TextoFinHTML[] = "</html>\n";

  //El inicio de la pagina siempre es el mismo
  cliente.write(cabeceraHTTP, strlen(cabeceraHTTP));
  cliente.write(cabeceraHTML, strlen(cabeceraHTML));

  //El final de la pagina depende del estado del LED
  if (EstadoLed[0] == true) {
    cliente.write(Nombre0, strlen(Nombre0));
    cliente.write(TextoEncender, strlen(TextoEncender));
    cliente.write(TextoA, strlen(TextoA));
    cliente.write(Numero0, strlen(Numero0));
    cliente.write(EstadoApagado, strlen(EstadoApagado));
    cliente.write(TextoFinA, strlen( TextoFinA));
    cliente.write(TextoApagado, strlen(TextoApagado));
    cliente.write(TextoCierre, strlen(TextoCierre));
  }
  else if (EstadoLed[0] == true) {
    //Les apgado y a enceder

  }
  if (EstadoLed[1] == true) {
    //hola
  }
  cliente.write(TextoFinHTML, strlen(TextoFinHTML));
}

void Teclado() {

  char customKey = customKeypad.getKey(); //se guarda en la variable customKey el caracter de la tecla presionada
  if (customKey != NO_KEY)         //se evalúa si se presionó una tecla
  {
    //Leer Codigo
    codigo[cont] = customKey;        //se guarda caracter por caracter en el arreglo codigo[]
    Serial.println(codigo[cont]);    //se imprime en el puerto serie la tecla presionada
    cont = cont + 1;
    if (cont >= 4)
      cont = 0;

    //Cambiar LED
    if ( EstadoAlarma == 0 ) {
      for (int micu = 0; micu < 5; micu++) {
        boolean SonIgual = true;
        for (int i = 0; i < 4; i++) {
          if (codigo[i] != contrasena[micu][i])
            SonIgual = false;
        }
        if (SonIgual && micu < 4) {
          EstadoLed[micu] = !EstadoLed[micu];
        }
        else if (SonIgual && micu == 4) {
          for (int i = 0; i < 4; i++) {
            EstadoLed[i] = !EstadoLed[i];
          }
        }
      }
    }
    //Desactivar alarma
    boolean IgualDesactivar = true;
    for (int i = 0; i < 4; i++) {
      if (codigo[i] !=  contrasenaDesactivar[i])
        IgualDesactivar = false;
    }
    if (IgualDesactivar) {
      EstadoAlarma = 0;
    }
    //Activar Alarma
    boolean IgualActivar = true;
    for (int i = 0; i < 4; i++) {
      if (codigo[i] !=  contrasenaDesactivar[i])
        IgualActivar = false;
    }
    if (IgualActivar) {
      EstadoAlarma = 1;
    }
  }
}
void ActualizarLed() {
  if ( EstadoAlarma == 2) {
    tone(Buzzer, 800);
    for (int i = 0; i < 4; i++) {
      digitalWrite(Led[i], EstadoLed[i]);
      EstadoLed[i] = !EstadoLed[i];
    }
    //delay(200);
  }
  else if (EstadoAlarma == 1) {

  }
  else if (EstadoAlarma == 0) {
    noTone(Buzzer);
    for (int i = 0; i < 4; i++) {
      digitalWrite(Led[i], EstadoLed[i]);
    }
  }
}

void EstadoPir() {
  if (EstadoAlarma = 1) {
    for (int i = 0; i < 2; i++) {
      int EstadoPir = digitalRead(Pir[i]);
      if (EstadoPir == 1) {
        EstadoAlarma = 2;
      }
    }
  }
}

