import java.util.*;
import ketai.ui.*;
import ketai.net.bluetooth.*;
import ketai.sensors.*;

String NombreBT;
KetaiBluetooth Kbt;
KetaiSensor Ksen;
ArrayList listaDisp;
String nombreDisp;

void setup() {
  orientation(PORTRAIT);
  size(displayWidth, displayHeight);

  //Inicializa las clases de bluetooth y sensores
  Kbt = new KetaiBluetooth(this);
  Ksen = new KetaiSensor(this);
  Ksen.start();

  //Obtiene la lista de dispositivos bluetooth emparejados
  listaDisp = Kbt.getPairedDeviceNames();

  //Imprime la lista en terminal
  Iterator itr = listaDisp.iterator();
  println("Dispositivos emparejados:");
  while (itr.hasNext()) {
    println(itr.next());
  }
  println("Empezando ");
}


void draw() {
  if (NombreBT == null) {
    KetaiList klist = new KetaiList(this, listaDisp);
  }
  fill(255, 0, 0);// R, G, B
  rect(0, 0, width/2, height/3); /x , y, ancho, alto
  fill(0, 255, 0);
  rect(width/2, 0, width/2, height/3); 
  fill(0, 0, 255);
  rect(0, height/3, width/2, height/3);
}

void mouseClicked() {
  println("X "+mouseX+" Y "+mouseY);
  if (mouseX > 0 && mouseX < width/2 && mouseY > 0 && mouseY < height/3) {
    print("Enviar A");
    String Mensaje = String.format("A");
    Kbt.writeToDeviceName(NombreBT, Mensaje.getBytes());
  }
  if (mouseX > width/2 && mouseX < width && mouseY > 0 && mouseY < height/3) {
    print("Enviar B");
    String Mensaje = String.format("B");
    Kbt.writeToDeviceName(NombreBT, Mensaje.getBytes());
  }
}


void onKetaiListSelection(KetaiList klist) {
  //Obtiene la cadena recien seleccionada
  NombreBT = klist.getSelection();

  //Imprime el nombre de dispositivo en terminal
  print("Dispositivo seleccionado:");
  print(NombreBT);

  //Efectua la conexion bluetooth al dispositivo seleccionado
  Kbt.connectToDeviceByName(NombreBT);

  //Desaloja la lista, ya no es necesaria
  klist = null;
}
