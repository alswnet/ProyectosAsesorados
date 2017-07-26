#include <BlockDriver.h>
#include <FreeStack.h>
#include <MinimumSerial.h>
#include <SdFat.h>
#include <SdFatConfig.h>
#include <SysCall.h>

//Librerias empleadas
#include <SPI.h>            //Acceso a bus SPI para memoria SD
//#include <SdFat.h>          //Soporte para sistema FAT


//#include <SdFatUtil.h>      //Funciones de soporte para FAT
#include <SFEMP3Shield.h>   //Libreria del escudo MP3

//Instancias de clase para las librerias
SdFat sd;               //Memoria SD
SFEMP3Shield MP3player; //Reproductor MP3

//Cantidad de pulsadores instalados
const int totalPulsadores = 6;

//Pines donde se conectan los pulsadores
const int pinPulsador[totalPulsadores] = {
  A0, A1, A2, A3, A4, A5
};

//Banderas con los estados actuales y anteriores de los
//pulsadores
bool estPulsadorAct[totalPulsadores] = { true, true, true, true, true, true };
bool estPulsadorAnt[totalPulsadores] = { true, true, true, true, true, true };

//Banderas que indican que los pulsadores han sido activados
bool pulsadorActivado[totalPulsadores] = { false, false, false, false, false, false };

void setup() {
  byte resultado;
  byte i;

  //Inicializa la terminal serie, para ver mensajes de error
  Serial.begin(115200);

  //Inicializa todos los pines de entrada de los pulsadores,
  //para que empleen los pull-up internos del Arduino
  for (i = 0; i < totalPulsadores; i++)
    pinMode(pinPulsador[i], INPUT_PULLUP);

  //Se inicializa la memoria SD
  if (!sd.begin(SD_SEL, SPI_FULL_SPEED)) {
    Serial.println("Error al inicializar la SD");
    sd.initErrorHalt();
  }
  else {
    Serial.println("Memoria SD inicializada con exito");
  }

  //Se cambia el directorio actual al directorio raiz
  if (!sd.chdir("/")) {
    Serial.println("Error al cambiar directorio");
    sd.errorHalt("sd.chdir");
  }

  //Se inicializa el escudo MP3
  resultado = MP3player.begin();
  if (resultado != 0 && resultado != 6) {
    Serial.print(F("Error al iniciar el escudo mp3. Codigo: "));
    Serial.print(resultado);
  }
  else {
    Serial.println("Escudo mp3 inicializado con exito");
  }
}

void loop() {
  int i;
  char nombreArchivo[13];

  //Se actualiza el estado de todos los botones
  leerBotones();

  //Se recorre el arreglo de banderas para verificar cuales
  //pulsadores han sido activados
  for (i = 0; i < totalPulsadores; i++) {
    //Se verifica si un pulsador fue activado
    if (pulsadorActivado[i]) {
      //Al activarse el pulsador, se crea un nombre de archivo
      //a partir del numero de pulsador asociado
      sprintf(nombreArchivo, "%i.mp3", i + 1);

      Serial.print("Reproduciendo ");
      Serial.println(nombreArchivo);

      //Para reproducir el archivo se establece el volumen a
      //-10 dB en ambos canales, a continuacion se para la
      //pista en reproduccion (si la hay) y finalmente se
      //reproduce la pista solicitada
      MP3player.setVolume(10, 10);
      MP3player.stopTrack();
      MP3player.playMP3(nombreArchivo);
    }
  }

  //Retardo usado para la eliminacion de rebote
  delay(10);
}

void leerBotones() {
  byte i;

  //Se recorre todos los pulsadores conectados
  for (i = 0; i < totalPulsadores; i++) {
    //Para cada pulsador, se guarda el estado actual, el cual
    //ahora se convierte en el anterior y acto seguido se lee
    //el nuevo estado actual
    estPulsadorAnt[i] = estPulsadorAct[i];
    estPulsadorAct[i] = digitalRead(pinPulsador[i]);

    //Se compara el estado anterior con el actual de cada
    //pulsador para determinar si ha sido presionado
    //recientemente
    if (!estPulsadorAct[i] && estPulsadorAnt[i])
      pulsadorActivado[i] = true;
    else
      pulsadorActivado[i] = false;
  }
}
