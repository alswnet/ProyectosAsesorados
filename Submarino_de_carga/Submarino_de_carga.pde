import ketai.ui.*;
import ketai.net.bluetooth.*;

PImage Fondo, BT, Flecha, Flecha2, Centro;

KetaiBluetooth Bluetooth;
ArrayList ListaBluetooth;
String NombreBluetooth;

void setup() {
  fullScreen(); 
  orientation(LANDSCAPE);
  Fondo = loadImage("Fondo.jpg");
  BT = loadImage("bluetooth.png");
  Flecha = loadImage("Flecha.png");
  Flecha2 = loadImage("Flecha2.png");
  Centro = loadImage("Stop.png");

  Bluetooth = new KetaiBluetooth(this);

  ListaBluetooth = Bluetooth.getPairedDeviceNames();
  println("Cantidad BT: "+ ListaBluetooth.size() + " Lista BT: ");
  printArray(ListaBluetooth);
  ListaBluetooth.add("Cancelar");
}

void draw() {
  float TamanoBoton = width/4;
  imageMode(CORNERS);
  image(Fondo, 0, 0, width, height);
  imageMode(CENTER);
  image(Flecha2, TamanoBoton/2, height/2, TamanoBoton/1.5, TamanoBoton/1.5);
  image(Centro, TamanoBoton + TamanoBoton/2, height/2, TamanoBoton/1.5, TamanoBoton/1.5);
  image(Flecha, 2*TamanoBoton + TamanoBoton/2, height/2, TamanoBoton/1.5, TamanoBoton/1.5);
  image(BT, 3* TamanoBoton + TamanoBoton/2, height/2, TamanoBoton/1.5, TamanoBoton/1.5);
}

void mousePressed() {
  if (mouseX < width/4 && NombreBluetooth != null) {
    println("Boton Izquierda");
    String MensajeBluetooth = "I";
    Bluetooth.writeToDeviceName(NombreBluetooth, MensajeBluetooth.getBytes());
  } else if (mouseX < 2 * (width/4) && NombreBluetooth != null) {
    String MensajeBluetooth = "C";
    Bluetooth.writeToDeviceName(NombreBluetooth, MensajeBluetooth.getBytes());
    println("Boton Centro");
  } else if (mouseX < 3 * (width/4) && NombreBluetooth != null) {
    String MensajeBluetooth = "D";
    Bluetooth.writeToDeviceName(NombreBluetooth, MensajeBluetooth.getBytes());
    println("Boton Derecha");
  } else if ( mouseX > 4 * (width/4) ) {
    println("Boton BT");
    KetaiList MenuBluetooth = new KetaiList(this, ListaBluetooth);
  }
}


void onKetaiListSelection(KetaiList klist) {
  //Obtiene la cadena recien seleccionada
  String Selecion = klist.getSelection();
  println("Se eleciono "+ Selecion);

  //Imprime el nombre de dispositivo en terminal

  if (Selecion.equals("Cancelar")) {
    println("Seleciono Cancelar");
  } else {
    print("Dispositivo seleccionado:");
    print(Selecion);
    NombreBluetooth = Selecion;
    Bluetooth.connectToDeviceByName(NombreBluetooth);
  }
  klist = null;
}
