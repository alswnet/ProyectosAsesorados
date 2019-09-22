import ketai.ui.*;
import ketai.net.bluetooth.*;

PImage Fondo, BT, Flecha, Flecha2;

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

  Bluetooth = new KetaiBluetooth(this);

  ListaBluetooth = Bluetooth.getPairedDeviceNames();
  println("Cantidad BT: "+ ListaBluetooth.size() + " Lista BT: ");
  printArray(ListaBluetooth);
  ListaBluetooth.add("Cancelar");
}


void draw() {
  float TamanoBoton = width/3;
  imageMode(CORNERS);
  image(Fondo, 0, 0, width, height);
  imageMode(CENTER);
  image(Flecha2, TamanoBoton/2, height/2, TamanoBoton/2, TamanoBoton/2);
  image(Flecha, TamanoBoton + TamanoBoton/2, height/2, TamanoBoton/2, TamanoBoton/2);
  image(BT, 2* TamanoBoton + TamanoBoton/2, height/2, TamanoBoton/2, TamanoBoton/2);
}

void mousePressed() {
  if (mouseX < width/3 && NombreBluetooth != null) {
    println("Boton Izquierda");
    String MensajeBluetooth = "I";
    Bluetooth.writeToDeviceName(NombreBluetooth, MensajeBluetooth.getBytes());
  } else if (mouseX < 2 * (width/3) && NombreBluetooth != null) {
    String MensajeBluetooth = "C";
    Bluetooth.writeToDeviceName(NombreBluetooth, MensajeBluetooth.getBytes());
    println("Boton Derecha");
  } else if ( mouseX > 2 * (width/3) ) {
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
