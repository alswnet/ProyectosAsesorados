#include <Keypad.h>

const byte ROWS = 4; //Declaramos el uso de las 4 filas, y decimos que sera constante el uso 4 pines para las flas del teclado
const byte COLS = 3; //declaramos el uso de las 4 columnas y decimos que sera constante el uso 3 pines para las columnas del teclado

#define a 0
#define b 1
#define c 2
#define d 3
#define primero 0
#define segundo 1
#define tercero 2
#define cuarto 3

//Primer dijigo es nivel
//Segundo digito es a b c d
int Display[4][4] = {
  {25, 22, 23, 24},
  {13, 10, 11, 12},
  {6, 5, 4, 3},
  {14, 17, 16, 15}
};

//hacemos el uso de arreglos en dos dimensiones y esto para idicarle en que posicion va cada caracter
char keys[ROWS][COLS] = { //almacenamos los caracteres a utilizar y de este modo inicializamos nuestro keypad
  {'1', '2', '3'},        //ordenando las filas entre corchetes y las columans respectivamente
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

int Boton = 26; //Creamos un arreglo de 3 variables las cuales son de tipo int ya que no son numeros de gran magnitud, este arreglo corresponde a los 3 botones a utilizar


//hacemos el uso de arreglos...
byte rowPins[ROWS] = {30, 31, 32, 33}; //Declaramos los pines de salida de las filas y usamos byte ya que es un numero entre 0 y 255
byte colPins[COLS] = {34, 35, 36,}; //Declaramos los pines de salida de las columnas y usamos byte ya que es un numero entre 0 y 255


// Aqui estamos diciendo que se crea una instancia del tipo keypad, al cual llamaremos teclado, en el cual
//asignaremos los datos que estan en el areglo keys,posteriormente le indicamos que hemos hecho
//coneccion entre las filas y columnas del keypad con los arreglos de los pines de asignacion de las mismas.
Keypad Teclado = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );// Funciones especificas para el Keypad


int Posicion = 0;

int a1 = 25;
int b1 = 22;
int c1 = 23;
int d1 = 24;

char letra = ' ';
int Estado  = 0;

void setup() {

  // for (int i = 0; i < 4; i++) {
  //   for (int j = 0; j < 4; j++) {
  //     pinMode(Display[i][j], OUTPUT);
  //  }
  // }

  for (int i = 0; i < 4; i++) {
    pinMode(Display[primero][i], OUTPUT);
  }
  pinMode(Boton, INPUT);//Configuramos el modo de operacion de los pines integrados en la variabble "Botones" como salida(output)
  Serial.begin(9600);
}

void loop() {
  switch (Estado) {
    case 0:
      letra = Teclado.getKey(); //la variable tipo char llamada key toma el valor de la funcion del keypad para asignar valores
      if (letra) {//Si key...
        if (letra >= '0' && letra <= '9') {
          int ValorTemporal = int(letra - '0'); //Se aclara que valor temporal sera igual a la variable 0 del keypad
          Posicion = Posicion * 10 + ValorTemporal;
          if (Posicion > 9999 || Posicion < 0) {
            Posicion = ValorTemporal ;
          }
          Serial.print("Letra: ");
          Serial.print(letra);
          Serial.print(" Valor: ");
          Serial.println(Posicion);
          CalcularModulo(Posicion);
        }
      }
      if (digitalRead(Boton) == 1) {
        Serial.println("Iniciando Conteo");
        attachInterrupt(0, BajarContador, FALLING);//2 del Mega
        delay(400);
        //Activnaod pulsos
        Estado = 1;
      }
      break;
    case 1:
      //Esperando pulsos
      CalcularModulo(Posicion);
      Serial.print("Posicion ");
      Serial.println(Posicion);
      if (digitalRead(Boton) == 1) {
        Serial.println("Cancelando Conteo");
        detachInterrupt(0);//2 en el mega
        delay(500);
        Estado = 0;
      }
      break;
  }
}

void  BajarContador() {
  Posicion = Posicion - 1;
}

void CalcularModulo(int Valor) {
  int Digito0 = Valor % 10;
  int NuevoValor1 = Valor - Digito0;
  int Digito1 = NuevoValor1 % 10;
  int NuevoValor2 = NuevoValor1 - Digito1;
  int Digito2 = NuevoValor2 % 10;
  int NuevoValor3 = NuevoValor2 - Digito2;
  int Digito3 = NuevoValor3 % 10;
  MostrarNumero(Digito0, primero);
  MostrarNumero(Digito1, segundo);
  MostrarNumero(Digito2, tercero);
  MostrarNumero(Digito3, cuarto);

}

void MostrarNumero (int Numero, int Contador) {
  switch (Numero)  {
    case 0:
      digitalWrite(Display[Contador][a], 0);
      digitalWrite(Display[Contador][b], 0);
      digitalWrite(Display[Contador][c], 0);
      digitalWrite(Display[Contador][d], 0);
      break;
    case 1:
      digitalWrite(Display[Contador][a], 1);
      digitalWrite(Display[Contador][b], 0);
      digitalWrite(Display[Contador][c], 0);
      digitalWrite(Display[Contador][d], 0);
      break;
    case 2:
      digitalWrite(Display[Contador][a], 0);
      digitalWrite(Display[Contador][b], 1);
      digitalWrite(Display[Contador][c], 0);
      digitalWrite(Display[Contador][d], 0);
      break;
    case 3:
      digitalWrite(Display[Contador][a], 1);
      digitalWrite(Display[Contador][b], 1);
      digitalWrite(Display[Contador][c], 0);
      digitalWrite(Display[Contador][d], 0);
      break;
    case 4:
      digitalWrite(Display[Contador][a], 0);
      digitalWrite(Display[Contador][b], 0);
      digitalWrite(Display[Contador][c], 1);
      digitalWrite(Display[Contador][d], 0);
      break;
    case 5:
      digitalWrite(Display[Contador][a], 1);
      digitalWrite(Display[Contador][b], 0);
      digitalWrite(Display[Contador][c], 1);
      digitalWrite(Display[Contador][d], 0);
      break;
    case 6:
      digitalWrite(Display[Contador][a], 0);
      digitalWrite(Display[Contador][b], 1);
      digitalWrite(Display[Contador][c], 1);
      digitalWrite(Display[Contador][d], 0);
      break;
    case 7:
      digitalWrite(Display[Contador][a], 1);
      digitalWrite(Display[Contador][b], 1);
      digitalWrite(Display[Contador][c], 1);
      digitalWrite(Display[Contador][d], 0);
      break;
    case 8:
      digitalWrite(Display[Contador][a], 0);
      digitalWrite(Display[Contador][b], 0);
      digitalWrite(Display[Contador][c], 0);
      digitalWrite(Display[Contador][d], 1);
      break;
    case 9:
      digitalWrite(Display[Contador][a], 1);
      digitalWrite(Display[Contador][b], 0);
      digitalWrite(Display[Contador][c], 0);
      digitalWrite(Display[Contador][d], 1);
      break;
    default:
      digitalWrite(Display[Contador][a], 0);
      digitalWrite(Display[Contador][b], 0);
      digitalWrite(Display[Contador][c], 0);
      digitalWrite(Display[Contador][d], 0);
      break;
  }
}




