#include <SPI.h>
#include <SD.h>

const int chipSelect = 8;

unsigned long ValorI = 0;
unsigned long ValorF = 0;

float Periodo = 0;

boolean Estado = false;
boolean EstadoBoton = false;

int Boton = 5;
int LecturaBoton = 0;

int Contador = 0;

void setup() {
  pinMode(Boton, INPUT);

  Serial.begin(9600);
  while (!Serial) {
    ; // Espera se inicia la comunicación serial
  }

  Serial.println("Inicialización de tarjeta SD...\n");        //Mensaje de inicialización
  pinMode(10, OUTPUT);
  pinMode(chipSelect, OUTPUT);                            //Chip Select

  if (!SD.begin(chipSelect)) {                            // Verifica si existe memoria SD
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return;
  }
  Serial.println("card initialized.");
  pinMode(2, INPUT); // Setup for leads off detection LO +
  pinMode(3, INPUT); // Setup for leads off detection LO -
  millis();
}

void loop() {
  //Configuración de boton para captura de frecuencia cardiaca
  LecturaBoton = digitalRead(Boton);
  if (LecturaBoton == 1) {
    EstadoBoton = true;
    do {
      LecturaBoton = digitalRead(Boton);
    } while (LecturaBoton == 1);
  }


  if ((digitalRead(2) == 1) || (digitalRead(3) == 1)) {       //Verifica si existe señal cardiaca
    Serial.println("!");
  }
  else {
    if  (analogRead(A0) > 600 &&  Estado == false) {
      Estado = true;
      ValorI = millis();
    }
    if (analogRead(A0) > 600 &&  Estado == true) {
      Estado = false;
      ValorF = millis();
      Periodo = ValorF - ValorI;
      
      if (Periodo != 0 && EstadoBoton == true) {          //Si se presiono el boton y tambien hay frecuencia cardiaca disponible que entre al if
        EstadoBoton = false;
        Contador++;
        
        String dataString = "Id: ";
        dataString += String(Contador);
        dataString += (" Frecuencia: ");
        dataString += String(1 / Periodo);
        dataString += ("Hz");

        
        File datoFile = SD.open("dat.txt", FILE_WRITE);
       // Serial.println(dataString);
        if (datoFile) {
          datoFile.println(dataString);
          datoFile.close();
          //Serial.println(dataString);
        }
        else {
          //Serial.println("error opening dataheart.txt");
        }
      }
    }
    Serial.println(analogRead(A0));
  }
  delay(1);
}
