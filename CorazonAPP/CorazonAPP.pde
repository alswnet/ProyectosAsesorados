PImage ImagenHola;
int CantidadPuntos = 100;
int [] Amplitud;
float AnchoPixel;
PShape LineaElectro;
float InicioCuadro = 0;
int DatoActual = 0;

void setup() {
  fullScreen();
  Iniciar();
  ImagenHola = loadImage("Hola.jpg");
  ImagenHola.resize(width, height);
  Amplitud = new int [CantidadPuntos];
  for (int i = 0; i < CantidadPuntos; i++) {
    Amplitud [i] = 50+(i%5)*2-(i%10)*2;
  }
  Amplitud[0] = 1000;
  AnchoPixel = height/(CantidadPuntos);
}
void draw() {
  if (SePuedeDibujar()) {
    // TU CODIGO DIBUJO
    //  try {     
    /* if (ins.available() > 0) {
     float NumeroDato = 0;
     while (ins.available() > 0) {
     char Letra =  (char)ins.read();
     if (DatoActual >= CantidadPuntos) {
     DatoActual = 0;
     }
     if (Letra == '\n') {
     println("D" + DatoActual  +" V"+ NumeroDato );
     Amplitud[DatoActual] = int(NumeroDato);
     NumeroDato = 0;
     DatoActual ++;
     } else if (Letra >= '0' && Letra <= '9' ) {
     NumeroDato = NumeroDato*10+ int(Letra-'0');
     }
     }
     }
     }*/
    try {     
      int Mensaje;
      if (ins.available() > 0) {
        Mensaje  = ins.read();
        Amplitud[DatoActual] = Mensaje;
        while (ins.available() > 0) {
          ins.read();
        }
        print("Mensaje "+Amplitud[DatoActual]);
        DatoActual++;
        if (DatoActual >= CantidadPuntos) {
          DatoActual = 0;
        }
      }
    }
    catch(Exception ex) {
      estado = 4;
      error = ex.toString();
      println(error);
    }
    background(ImagenHola);
    createShape();
    beginShape();
    strokeWeight(5);
    stroke(0, 200, 0);
    noFill();
    for (int i = 0; i <CantidadPuntos; i++) {
      float PX = map(Amplitud[i], 0, 200, 0, width);
      float PY = map(i, 0, CantidadPuntos, 0, height);
      vertex(PX, PY);
    }
    endShape();
    // InicioCuadro++;
    if (InicioCuadro > height)
      InicioCuadro = 0;
    float Cy = map(DatoActual, 0, CantidadPuntos, 0, height);
    fill(0, 200, 0);
    rect(0, Cy, width, 10);
  }
}

void mouseReleased() {
  if (SePuedePresionar()) {
    // TU CODIGO MOUSE

    // HASTA AQUI CODIGO MOUSE
  }
}

//EstaAvilitada() - boolean - Para ver si hay datos seriales - 
//PedirString() - string - Para pedir un string con lo que tenga el puerto hasta el puerto
//PedirChar() - char -Para pedir un char del string 
//PedirInt() - int - Para pedir un int del arduino
//Enviar(String) - Envia un String
//Enviar(int) - Envia un String