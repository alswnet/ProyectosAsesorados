import ketai.sensors.*;
import java.util.*;
import ketai.ui.*;
import ketai.net.bluetooth.*;

KetaiSensor sensor;
KetaiBluetooth Bluetooth;
ArrayList ListaBT;
String NombreBT;
float TiempoPasado = 0;

boolean AcelerometroActivo = false;
int AreaX, AreaY;
float AcelerometroX, AcelerometroY;
float PosicionX, PosicionY;// -100 a 100
PImage  LogoConectar, LogoAcelerometro, LogoAyuda;

void setup() {
  fullScreen(); 
  orientation(PORTRAIT);

  AreaX = int(width*1);
  AreaY = int(height*0.9);

  PosicionX = 0;
  PosicionY = 0;

  LogoConectar = loadImage("LogoConectar.png");
  LogoAcelerometro = loadImage("LogoConectar.png");
  LogoAyuda = loadImage("LogoConectar.png");

  sensor = new KetaiSensor(this);
  sensor.start();

  Bluetooth = new KetaiBluetooth(this);

  ListaBT = Bluetooth.getPairedDeviceNames();

  Iterator Dispositivo = ListaBT.iterator();
  print("Lista de BT");
  while (Dispositivo.hasNext()) {
    print(Dispositivo.next());
  }
}

void draw() { 
  ActualizarPuntero();

  dibujarPantalla();

  MandarDatos();
}

void MandarDatos() {
  if (millis() > TiempoPasado + 1000 && NombreBT != null) {
    String Mensaje = "Y/"+PosicionY+"\n" ;
    Bluetooth.writeToDeviceName(NombreBT, Mensaje.getBytes());
    Mensaje = "X/"+PosicionX+"\n" ;
    Bluetooth.writeToDeviceName(NombreBT, Mensaje.getBytes());
    TiempoPasado = millis();
  }
}

void mousePressed() {
  int AnchoBoton = AreaX / 3;

  if ( mouseY >= AreaY) {
    if (mouseX < AnchoBoton) {
      println("Se Activo buscar BT");
      KetaiList klist = new KetaiList(this, ListaBT);
    } else if (mouseX < 2 * AnchoBoton) {
      AcelerometroActivo = !AcelerometroActivo;
      println("Estado Acelerometro: "+AcelerometroActivo);
    } else {
      println("Se pide URL");
    }
  }
}

void ActualizarPuntero() {
  if (AcelerometroActivo) {
    PosicionX = map(AcelerometroX, -5, 5, -100, 100);
    PosicionY = map(AcelerometroY, -5, 5, -100, 100);
  } else if (mousePressed && mouseY < AreaY) {
    PosicionX = map(mouseX, 0, AreaX, -100, 100);
    PosicionY = map(mouseY, 0, AreaY, -100, 100);
  } else {
    PosicionX = 0;
    PosicionY = 0;
  }
  PosicionX = constrain(PosicionX, -100, 100);
  PosicionY = constrain(PosicionY, -100, 100);
}

void dibujarPantalla() {
  int PX, PY;
  int AlturaBarra = height - AreaY;
  int AnchoBoton = AreaX/3;
  int AnchoLinea = int(map(AreaX, 1000, 2000, 5, 50));
  AnchoLinea = constrain(AnchoLinea, 5, 50);

  PX = int(map(PosicionX, -100, 100, 0, AreaX));
  PY = int(map(PosicionY, -100, 100, 0, AreaY));

  background(0);

  strokeWeight(AnchoLinea);
  stroke(255, 0, 0);
  line(PX, 0, PX, AreaY);
  line(0, PY, AreaX, PY);

  stroke(0, 255, 0);
  noFill();
  rectMode(CENTER);
  rect(PX, PY, AreaX/7, AreaX/7, AreaX/30);
  rectMode(CORNER);

  fill(96);
  stroke(0);

  DibujarBoton(0, AreaY, AnchoBoton, AlturaBarra, LogoConectar);
  DibujarBoton(AnchoBoton, AreaY, AnchoBoton, AlturaBarra, LogoAcelerometro);
  DibujarBoton(AnchoBoton*2, AreaY, AnchoBoton, AlturaBarra, LogoAyuda);
}

void DibujarBoton(int X, int Y, int AnchoBoton, int AlturaBoton, PImage Imagen) {
  rect(X, Y, AnchoBoton, AlturaBoton);
  image(Imagen, X + AlturaBoton/2, Y, AlturaBoton, AlturaBoton);
}

void onAccelerometerEvent(float x, float y, float z) {
  AcelerometroX = -x;
  AcelerometroY = y;
}

void onKetaiListSelection(KetaiList klist) {
  //Obtiene la cadena recien seleccionada
  NombreBT = klist.getSelection();

  //Imprime el nombre de dispositivo en terminal
  print("Dispositivo seleccionado:");
  print(NombreBT);

  //Efectua la conexion bluetooth al dispositivo seleccionado
  Bluetooth.connectToDeviceByName(NombreBT);

  klist = null;
}

String MensajeBT = ""; 

void onBluetoothDataEvent(String dispositivo, byte[] datos) {
  MensajeBT += new String(datos);
  String[] CorteMensaje = splitTokens(MensajeBT, "\n\r");
  for (int i = 0; i < CorteMensaje.length-1; i++) {
    String[] PaqueteMensaje = splitTokens(CorteMensaje[i], "/");
    println("Dato " + i + " : "+ PaqueteMensaje[0] + " - " + PaqueteMensaje[1]);
    if (PaqueteMensaje[0].equals("LLama")) {     
      println("Llama es: "+ int(PaqueteMensaje[1]));
    } else if (PaqueteMensaje[0].equals("D")) {
      println("Distancia es: "+ int(PaqueteMensaje[1]));
    }
  }
  MensajeBT = CorteMensaje[CorteMensaje.length-2];
  print("Mensaje: "+MensajeBT);
}
