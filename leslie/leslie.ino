#include <Keypad.h> //llama a la librería Keypad.h //incluimos libreria 
char contrasena[1]="1111";  //aquí escribimos la contraseña de 4 dígitos // contraseña para encender las luces 
char contrasena2[]="2222"; //contraseña para desactivar la alarma 
char contrasena3[]="3333"; // Contraseña para activar la alarma 
char codigo[4];            //Cadena donde se guardaran los caracteres d0e las teclas presionadas 
int cont=0;          //variable que se incrementara al presionar las teclas
int inPin=10;
int Buzzer = 12;
const byte ROWS = 4; //Numero de filas del teclado que se esta usando
const byte COLS = 4; //Numero de columnas del teclado que se esta usando
const int Luces_Conference1 = 13;
const int Luces_Conference2 = 3 ;
const int Luces_Entrada = 4 ;
const int Luces_Oficina = 5 ;
char hexaKeys[ROWS][COLS] =  //Aquí pondremos la disposición de los caracteres tal cual están en nuestro teclado
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; //Seleccionamos los pines en el arduino donde iran conectadas las filas
byte colPins[COLS] = {5, 4, 3, 2}; //Seleccionamos los pines en el arduino donde iran conectadas las columnas

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); //inicializa el teclado

void setup()
{
  pinMode(13, OUTPUT);
  pinMode(11, OUTPUT);//Pin 13 como salida
  pinMode(inPin, INPUT);
  Serial.begin(9600); //inicializar puerto serie
  pinMode (Luces_Conference1, OUTPUT);
  pinMode (Luces_Conference2, OUTPUT);
  pinMode (Luces_Entrada, OUTPUT);
  pinMode (Luces_Oficina, OUTPUT);
  pinMode(Buzzer, OUTPUT);
}

void loop()
{
  char customKey = customKeypad.getKey(); //se guarda en la variable customKey el caracter de la tecla presionada
  if (customKey != NO_KEY)         //se evalúa si se presionó una tecla
  {
    codigo[cont]=customKey;          //se guarda caracter por caracter en el arreglo codigo[]
    Serial.println(codigo[cont]);    //se imprime en el puerto serie la tecla presionada
    cont=cont+1;              //incrementamos la variable cont
    if(cont==4)          //si ya fueron presionadas 4 teclas se evalúa si la contraseña es correcta
    {
      if(codigo[0]==contrasena[0]&&codigo[1]==contrasena[1]&&codigo[2]==contrasena[2]&&codigo[3]==contrasena[3])
      {
        digitalWrite(13,!digitalRead(13));        //si la contraseña fué correcta se enciende o se apaga el led del pin13
        digitalWrite(Luces_Conference1,!digitalRead(Luces_Conference1));
        digitalWrite(Luces_Conference2,!digitalRead(Luces_Conference2));
        digitalWrite(Luces_Entrada,!digitalRead(Luces_Entrada));
        digitalWrite(Luces_Oficina,!digitalRead(Luces_Oficina));
      }
      cont=0;  //resetear a 0 la variable cont
    }
  }
 if(digitalRead(inPin) == HIGH&&!(codigo[0]==contrasena[0]&&codigo[1]==contrasena[1]&&codigo[2]==contrasena[2]&&codigo[3]==contrasena[3])){
            for (int i = 0; i<=4; i++){
             tone(Buzzer, 2700, 250);
             digitalWrite(13, HIGH);
            // delay(100);
            // digitalWrite(13, LOW);
            // digitalWrite(Luces_Conference1, HIGH);
            // delay (100);
            // digitalWrite(Luces_Conference2, HIGH);
            }
}
 else if(codigo[0]==contrasena2[0]&&codigo[1]==contrasena2[1]&&codigo[2]==contrasena2[2]&&codigo[3]==contrasena2[3]){
    //digitalWrite(Luces_Conference1 , LOW);
          //digitalWrite(Luces_Conference2, LOW);
          digitalWrite(11, HIGH);
  }
  if(digitalRead(11)== HIGH)
  {
    digitalWrite(13, LOW);
     }
     if (codigo[0]==contrasena3[0]&&codigo[1]==contrasena3[1]&&codigo[2]==contrasena3[2]&&codigo[3]==contrasena3[3]||codigo[0]==contrasena[0]&&codigo[1]==contrasena[1]&&codigo[2]==contrasena[2]&&codigo[3]==contrasena[3]){
      digitalWrite(11, LOW);
     }
 //if(codigo[0]==contrasena2[0]&&codigo[1]==contrasena2[1]&&codigo[2]==contrasena2[2]&&codigo[3]==contrasena2[3]){
      //    digitalWrite(Luces_Conference1 , LOW);
    //      digitalWrite(Luces_Conference2, LOW);
  //        delay(100);               // esperar 1 segundos
//}
}
