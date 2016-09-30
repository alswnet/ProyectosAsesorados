import java.util.*;
import ketai.ui.*;
import ketai.net.bluetooth.*;
import ketai.sensors.*;

int Tiempo;
KetaiBluetooth Kbt;
ArrayList listaDisp;
String nombreDisp;
//int ancho = 300;
//int alto = 533;
int ancho =720;
int alto = 1280;
int grosor = alto/12;
int[] Valores = {
  0, 0, 0, 0, 0, 0, 0
};
int[] ValoresP = {
  0, 0, 0, 0, 0, 0, 0
};
void setup() {
  orientation(PORTRAIT);
  size(displayWidth, displayHeight);
  ancho =displayWidth;
  alto = displayHeight;
  grosor = alto/12;
  // size(720, 1280);

  //Inicializa las clases de bluetooth y sensores
  Kbt = new KetaiBluetooth(this);
  //Obtiene la lista de dispositivos bluetooth emparejados
  listaDisp = Kbt.getPairedDeviceNames();

  //Imprime la lista en terminal
  Iterator itr = listaDisp.iterator();
  print("Dispositivos emparejados:");
  while (itr.hasNext ()) {
    print(itr.next());
  }

  KetaiList klist = new KetaiList(this, listaDisp);

  size(ancho, alto);
  rect(0, 0, ancho, alto);
  textSize(32);
  textAlign(CENTER);
  fill(0, 0, 0);
  noStroke();
  //textSize(32);
  textSize(64);
  Tiempo = millis();
}

void draw() {
  fill(255, 255, 255);
  rect(0, 0, ancho, alto);

  textAlign(CENTER);
  for (int i = 0; i<6; i++) {
    fill(0, 102, 153);
    rect(0, i*grosor*2+grosor, ancho, grosor);
    //fill(0, 0, 255);
    text("Servo "+(i+1) +" P" + Valores[i], ancho/2, i*grosor*2+grosor);
    fill(0, 50, 100);
    for (int j=0; j<18; j++) {
      rect(j*ancho/18, i*grosor*2+grosor, 2, grosor);
    }
    fill(0, 25, 50);
    rect(Valores[i]*ancho/180, i*grosor*2+grosor, 10, grosor);
    if ( Valores[i] != ValoresP[i] && millis() -Tiempo > 500) {
      String Buffer;
      Tiempo = millis(); 
      char pollo = 'a';
      pollo = char(pollo + i);
      Buffer =pollo +"" +Valores[i]+"x";
      println(Buffer);
      ValoresP[i] =Valores[i];
      //  Buffer = String.format("%d%dx", char('a' +i)int(controlX*100));
      Kbt.writeToDeviceName(nombreDisp, Buffer.getBytes());
    }
  }
}

void mouseDragged() {
  for (int i = 0; i<6; i++) {
    if (mouseY < (i+1)*grosor*2 && mouseY> (i)*grosor*2) {
      Valores[i]= int(map(mouseX, 0, ancho, 0, 180));
      println("Max "+ ((i+1)*grosor*2) +" Min " + (i*grosor*2-grosor*2)+ " MY"+ mouseY);
    }
  }
}

void mouseClicked() {
  for (int i = 0; i<6; i++) {
    if (mouseY < (i+1)*grosor*2 && mouseY> (i)*grosor*2) {
      Valores[i]= int(map(mouseX, 0, ancho, 0, 180));
      println("Max "+ ((i+1)*grosor*2) +" Min " + (i*grosor*2-grosor*2)+ " MY"+ mouseY);
    }
  }
}

void onKetaiListSelection(KetaiList klist) {
  //Obtiene la cadena recien seleccionada
  nombreDisp = klist.getSelection();

  //Imprime el nombre de dispositivo en terminal
  print("Dispositivo seleccionado:");
  print(nombreDisp);

  //Efectua la conexion bluetooth al dispositivo seleccionado
  Kbt.connectToDeviceByName(nombreDisp);

  //Desaloja la lista, ya no es necesaria
  klist = null;
}
