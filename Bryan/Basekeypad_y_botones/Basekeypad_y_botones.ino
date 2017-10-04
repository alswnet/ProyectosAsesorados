#include <Keypad.h>

const byte ROWS = 4; //Declaramos el uso de las 4 filas, y decimos que sera constante el uso 4 pines para las flas del teclado
const byte COLS = 3; //declaramos el uso de las 4 columnas y decimos que sera constante el uso 3 pines para las columnas del teclado

//hacemos el uso de arreglos en dos dimensiones y esto para idicarle en que posicion va cada caracter
char keys[ROWS][COLS] = { //almacenamos los caracteres a utilizar y de este modo inicializamos nuestro keypad
  {'1', '2', '3'},        //ordenando las filas entre corchetes y las columans respectivamente
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

//hacemos el uso de arreglos...
byte rowPins[ROWS] = {30, 31, 32, 33}; //Declaramos los pines de salida de las filas y usamos byte ya que es un numero entre 0 y 255
byte colPins[COLS] = {34, 35, 36,}; //Declaramos los pines de salida de las columnas y usamos byte ya que es un numero entre 0 y 255

// Aqui estamos diciendo que se crea una instancia del tipo keypad, al cual llamaremos teclado, en el cual
//asignaremos los datos que estan en el areglo keys,posteriormente le indicamos que hemos hecho 
//coneccion entre las filas y columnas del keypad con los arreglos de los pines de asignacion de las mismas.
Keypad Teclado = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );// Funciones especificas para el Keypad

int DisplayPin[2][8] = {{37 , 38, 39, 40, 41, 42, 43, 44},{45, 46, 47, 48, 49, 50, 51, 52}}; //Aqui realizamos un arreglo [2] de arrelos [8] con la variable int debido a que no son numeros de gran cantidad
                                                                                    // en el cual decimos que seran 2 arreglos de 8 digitos cada uno los cuales seran los que iran al display.

int Botones[3] = {27, 28, 29}; //Creamos un arreglo de 3 variables las cuales son de tipo int ya que no son numeros de gran magnitud, este arreglo corresponde a los 3 botones a utilizar

int Tiempo = 0; // declaramos la vriable tiempo a la cual le asignaremos valor luego, para eso el 0
int TiempoResiduo = 0; // declaramos la vriable tiemporesiduo a la cual le asignaremos valor luego, para eso el 0
bool Contando = false; //declaramos la varibale contando la cual tendra el valor de (false)
float TiempoPasado = millis(); //Crearemos la variable float para poder utilizar decimales y le llamaremos tiempopasado
                               // la cual poseera el valor de miliseconds

void setup()
{//Codigo relacionado con :"int DisplayPin[2][8]"
  for (int x = 0; x < 2; x++) { //Utilizamos el ucle for en el cual decimos que la variable x es igual 0 inicialmente, cumple la condición de ser menor que dos (0,1) e incrementa  de 1 en uno (++).
    for (int y = 0; y < 8; y++) { //En esta sentencia decimos que la variable y es igual a 0 y cumple la funcion de ser menor que 8 (0,1,2,3,4,5,6,7) y esta va incrementando de 1 en 1 (++). 
      pinMode(DisplayPin[x][y], OUTPUT);//Configuramos el modo de operacion de los pines integrados en la variabble "DisplayPin" como salida(output)
    }
  }
  for (int i = 0; i < 3; i++){ //Aqui asignamos el bucle for para darle funcion a los botones, los cuales son 3 y la sencencia dice, que i sera igual a 0 ero menor que 3, (0,1,2) que son la 
                              //cantidad de botones existentes, y esto va incrementadose de 1 en 1.
    pinMode(Botones[i], INPUT);//Configuramos el modo de operacion de los pines integrados en la variabble "Botones" como salida(output)
  }
  MostrarTiempo(Tiempo); //Creamos una funcion a la cual le aplicamos el parametro de la variable tiempo
  Serial.begin(9600);    //inicializamos la comunicación serial para utilizar el puerto serial 
}

void loop()
{
  for (int i = 0; i < 3; i++) { //Mandamos a llamar a la funcion for para inicializar la variable i
    if (digitalRead(Botones[i]) == 1) {// Decimos que si alguno de los pines de la variable i detecta uno haga:
      switch (i) { //Establecemos que se ejecutara ell caso depenciendo del case establecido
        case 0:
       
          if (!Contando) {//Si contando es iual a 0, el contador esta en 0
            if (Tiempo != 0) { //y si tiempo no es igual a 0
              TiempoPasado = millis();// (millis) sera parte de la variable tiempopasado, es decir se medira en milisegundo
            
              Contando = true; //Contando procedera a ser un verdadero, o sea un pulso positivo (1)
              Serial.println("Empezar a contar");//Se imprimira en el puerto serial "empezar a contar"
              delay(100);//tiempo sera de 100 milisegundos
            }
           
          }
          break;//ocupamos esta asignacion para cortar este caso
        case 1://Si se presiono el boton cuyo pin es la posicion es 2 (1), en las declaraciones, ocurrira:
          Contando = false;// Contando procedera a ser un pulso negativo o false, ya que se le es asignado con el signo =, es decir se parara
          Tiempo = TiempoResiduo; //Tiempo residuo procedera a ser asignado en la variable Tiempo
          Serial.print("Detenido ...");// Se escribira "detenido..." en el puerto serial
          Serial.println(Tiempo);//Se asignara el valor actual de la variable "tiempo" continuado el texto "detenido"
          MostrarTiempo(Tiempo); //Creamos una funcion a la cual le aplicamos el parametro de la variable tiempo
          break;//ocupamos esta asignacion para cortar este caso
          
        case 2://Si se presiono el boton cuyo pin es la posicion es 2 (1), en las declaraciones, ocurrira:
          Contando = false; // Contando procedera a ser un pulso negativo o false, ya que se le es asignado con el signo =, es decir se parara
          Tiempo = 0; //tiempo procedera a tomar el valor de 0
          Serial.println("Reset");//Se imprimira en el puerto serial "Reset"
          MostrarTiempo(Tiempo);//Creamos una funcion a la cual le aplicamos el parametro de la variable tiempo, se llama la funcion 
          
          break;//ocupamos esta asignacion para cortar este caso
      }
    }
  }

  if (Contando) {//Si la variable contado...esta activada
    if (millis() - TiempoPasado < Tiempo * 1000) {//Si los lilisegundos menos el tiempo pasado (0) es menor que el valor actual del tiempo por mil..
      int TiempoPantalla =  Tiempo - int(millis() - TiempoPasado) / 1000;//insertar la variable tiempo panalla, la cual tomara el valor del tiempo menos(0)
      if (TiempoPantalla != TiempoResiduo) {//Si tiempopantalla no es igual a tiempo residuo
        TiempoResiduo = TiempoPantalla;//Tiempo residuo tomara el valor de tiempo pantalla
        MostrarTiempo(TiempoPantalla);//En este caso la funcion tiempo procedera a tomar el valor del tiempopantalla
        Serial.println(TiempoPantalla);//Imprimir en el puerto serial el valor de tiepo pantalla
      }
    }
    else {
      Contando = false; //Si la variable contando llega a un estado de falsedad
      Tiempo = 0;//y tiempo llega a 0
      Serial.println("Finalizado");//se imprimira en el puerto serial "finalizado"
      Contando = false;//Contando sera falso
    }
  }
  else {
    ActualizarTeclado();//si  no ocurre nada acerca de los else anteriores ejecutar la funcion actualizar teclado
  }
}

void ActualizarTeclado() {
  char key = Teclado.getKey(); //la variable tipo char llamada key toma el valor de la funcion del keypad para asignar valores
  if (key) {//Si key...
    int ValorTemporal = int(key - '0'); //Se aclara que valor temporal sera igual a la variable 0 del keypad
    Tiempo = (Tiempo * 10 + ValorTemporal) % 100; // en este caso tiempo sera igual al valor obtenido de (tiempo multiplicado por 10 sumado al valor temporal)...esto sacando la diferencia de 100
       Serial.println(ValorTemporal);//se imprimira en el puerto serial el valor de la variable "valortemporal"
    Serial.print("Tiempo: ");//se imprimira en el puerto serial "Tiempo:"
    Serial.println(Tiempo);//se imprimira en el puerto serial de la variable tiempo
    MostrarTiempo(Tiempo);//En este caso la funcion tiempo procedera a tomar el valor del tiempo
  }
}

void MostrarTiempo(int Tiempo) {//funcion mostrar tiempo
  int Digito0 = Tiempo % 10;//Insertamos una variable llamada diito 0 la cual es igual al tiempo con la diferencia de 10
  int Digito1 = (Tiempo - Tiempo % 10) / 10;//Insertamos una variable llamada diito 1 la cual es igual al tiempo menos el tiempo diferenciado de 10, todo dividido entre 10
  MostrarDigito(Digito0, 0);//La funcion digito 0 tomara la posicion 1 de las declaraciones de los ´pines de los display, es decir es el display numero 1
  MostrarDigito(Digito1, 1);//La funcion digito 1 tomara la posicion 2 de las declaraciones de los ´pines de los display, es decir es el display numero 2
}

void MostrarDigito(int Numero, int Posicion) {// Funcion mostrardigito, en esta funcion se tomaran los valores de numeros y posicion
  switch (Numero) { //Establecemos que se ejecutara ell caso depenciendo del case establecido
    case 0:
      digitalWrite(DisplayPin[Posicion][0], HIGH);   //SILI     //0
      digitalWrite(DisplayPin[Posicion][1], HIGH);   //SIH
      digitalWrite(DisplayPin[Posicion][2], HIGH);   //SSLI
      digitalWrite(DisplayPin[Posicion][3], LOW);   //SMH
      digitalWrite(DisplayPin[Posicion][4], HIGH);  //SSH
      digitalWrite(DisplayPin[Posicion][5], HIGH);  //SSLD
      digitalWrite(DisplayPin[Posicion][6], HIGH);  //SILD
      digitalWrite(DisplayPin[Posicion][7], HIGH);  //PUNTO
      break;
    case 1:
      digitalWrite(DisplayPin[Posicion][0], LOW);   //SILI     //1
      digitalWrite(DisplayPin[Posicion][1], LOW);   //SIH
      digitalWrite(DisplayPin[Posicion][2], HIGH);   //SSLI
      digitalWrite(DisplayPin[Posicion][3], LOW);   //SMH
      digitalWrite(DisplayPin[Posicion][4], LOW);  //SSH
      digitalWrite(DisplayPin[Posicion][5], LOW);  //SSLD
      digitalWrite(DisplayPin[Posicion][6], HIGH);  //SILD
      digitalWrite(DisplayPin[Posicion][7], LOW);  //PUNTO
      break;
    case 2:
      digitalWrite(DisplayPin[Posicion][0], HIGH); //SILI     //2
      digitalWrite(DisplayPin[Posicion][1], HIGH);   //SIH
      digitalWrite(DisplayPin[Posicion][2], LOW);   //SSLI
      digitalWrite(DisplayPin[Posicion][3], HIGH);   //SMH
      digitalWrite(DisplayPin[Posicion][4], LOW);  //SSH
      digitalWrite(DisplayPin[Posicion][5], HIGH);  //SSLD
      digitalWrite(DisplayPin[Posicion][6], HIGH);  //SILD
      digitalWrite(DisplayPin[Posicion][7], LOW);  //PUNTO
      break;
    case 3:
      digitalWrite(DisplayPin[Posicion][0], LOW);   //SILI     //3
      digitalWrite(DisplayPin[Posicion][1], HIGH);   //SIH
      digitalWrite(DisplayPin[Posicion][2], HIGH);   //SSLI
      digitalWrite(DisplayPin[Posicion][3], HIGH);   //SMH
      digitalWrite(DisplayPin[Posicion][4], LOW);  //SSH
      digitalWrite(DisplayPin[Posicion][5], HIGH);  //SSLD
      digitalWrite(DisplayPin[Posicion][6], HIGH);  //SILD
      digitalWrite(DisplayPin[Posicion][7], LOW);  //PUNTO
      break;
    case 4:
      digitalWrite(DisplayPin[Posicion][0], LOW);   //SILI     //4
      digitalWrite(DisplayPin[Posicion][1], LOW);   //SIH
      digitalWrite(DisplayPin[Posicion][2], HIGH);   //SSLI
      digitalWrite(DisplayPin[Posicion][3], HIGH);   //SMH
      digitalWrite(DisplayPin[Posicion][4], HIGH);  //SSH
      digitalWrite(DisplayPin[Posicion][5], LOW);  //SSLD
      digitalWrite(DisplayPin[Posicion][6], HIGH);  //SILD
      digitalWrite(DisplayPin[Posicion][7], LOW);  //PUNTO
      break;
    case 5:
      digitalWrite(DisplayPin[Posicion][0], LOW);   //SILI     //5
      digitalWrite(DisplayPin[Posicion][1], HIGH);   //SIH
      digitalWrite(DisplayPin[Posicion][2], HIGH);   //SSLI
      digitalWrite(DisplayPin[Posicion][3], HIGH);   //SMH
      digitalWrite(DisplayPin[Posicion][4], HIGH);  //SSH
      digitalWrite(DisplayPin[Posicion][5], HIGH);  //SSLD
      digitalWrite(DisplayPin[Posicion][6], LOW);  //SILD
      digitalWrite(DisplayPin[Posicion][7], LOW);  //PUNTO
      break;
    case 6:
      digitalWrite(DisplayPin[Posicion][0], HIGH);   //SILI     //6
      digitalWrite(DisplayPin[Posicion][1], HIGH);   //SIH
      digitalWrite(DisplayPin[Posicion][2], HIGH);   //SSLI
      digitalWrite(DisplayPin[Posicion][3], HIGH);   //SMH
      digitalWrite(DisplayPin[Posicion][4], HIGH);  //SSH
      digitalWrite(DisplayPin[Posicion][5], HIGH);  //SSLD
      digitalWrite(DisplayPin[Posicion][6], LOW);  //SILD
      digitalWrite(DisplayPin[Posicion][7], LOW);  //PUNTO
      break;
    case 7:
      digitalWrite(DisplayPin[Posicion][0], LOW);   //SILI     //7
      digitalWrite(DisplayPin[Posicion][1], LOW);   //SIH
      digitalWrite(DisplayPin[Posicion][2], HIGH);   //SSLI
      digitalWrite(DisplayPin[Posicion][3], LOW);   //SMH
      digitalWrite(DisplayPin[Posicion][4], LOW);  //SSH
      digitalWrite(DisplayPin[Posicion][5], HIGH);  //SSLD
      digitalWrite(DisplayPin[Posicion][6], HIGH);  //SILD
      digitalWrite(DisplayPin[Posicion][7], LOW);  //PUNTO
      break;
    case 8:
      digitalWrite(DisplayPin[Posicion][0], HIGH);   //SILI     //8
      digitalWrite(DisplayPin[Posicion][1], HIGH);   //SIH
      digitalWrite(DisplayPin[Posicion][2], HIGH);   //SSLI
      digitalWrite(DisplayPin[Posicion][3], HIGH);   //SMH
      digitalWrite(DisplayPin[Posicion][4], HIGH);  //SSH
      digitalWrite(DisplayPin[Posicion][5], HIGH);  //SSLD
      digitalWrite(DisplayPin[Posicion][6], HIGH);  //SILD
      digitalWrite(DisplayPin[Posicion][7], LOW);  //PUNTO
      break;
    case 9:
      digitalWrite(DisplayPin[Posicion][0], LOW);   //SILI     //9
      digitalWrite(DisplayPin[Posicion][1], HIGH);   //SIH
      digitalWrite(DisplayPin[Posicion][2], HIGH);   //SSLI
      digitalWrite(DisplayPin[Posicion][3], HIGH);   //SMH
      digitalWrite(DisplayPin[Posicion][4], HIGH);  //SSH
      digitalWrite(DisplayPin[Posicion][5], HIGH);  //SSLD
      digitalWrite(DisplayPin[Posicion][6], HIGH);  //SILD
      digitalWrite(DisplayPin[Posicion][7], LOW);  //PUNTO
      break;
  }
}
