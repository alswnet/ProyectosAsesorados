////////////////////////////////////////////////////////
//Codigo de ALSW
//Para mi informacion: https://github.com/alswnet/ProyectoStreaming
///////////////////////////////////////////////////////


////////////////////////////////////////////////////////
//Este programa necesita permisos para manejar el BT
//En el menu de Android>Sketch Permission
//Seleciona BLUETOOTH y BLUETOOTH_AD
///////////////////////////////////////////////////////

import android.bluetooth.BluetoothAdapter;
import android.bluetooth.BluetoothDevice;
import android.bluetooth.BluetoothSocket;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.app.Activity;
import java.util.ArrayList;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.lang.reflect.Method;
import java.util.UUID;

private static final int REQUEST_ENABLE_BT = 3;
ArrayList dispositivos;
BluetoothAdapter adaptador;
BluetoothDevice dispositivo;
BluetoothSocket socket;
InputStream ins;
OutputStream ons;
boolean registrado = false;
int estado;
String error;
String valor = "";

//
boolean EstadoBoton = false;
int Temperatura = 17;
int TamanoPequeno = 90;
int TamanoGrande = 180;


////////////////////////////////////////////////////////
//Inicia processing 
///////////////////////////////////////////////////////
void setup() {
  orientation(PORTRAIT);//Setea el celular en formar Vertical 
  textAlign(CENTER, CENTER);
  fullScreen();//Pantalla en tamaño completo
  stroke(255);
}

////////////////////////////////////////////////////////
//Inicia proceso de dibujaro dependiendo del estado actual
///////////////////////////////////////////////////////
void draw() {
  switch(estado) {
  case 0:
    listaDispositivos("BUSCANDO DISPOSITIVOS", color(255, 0, 0));
    break;
  case 1:
    listaDispositivos("ELIJA DISPOSITIVO", color(0, 255, 0));
    break;
  case 2:
    conectaDispositivo();
    break;
  case 3:
    muestraDatos();
    break;
  case 4:
    muestraError();
    break;
  }
}

////////////////////////////////////////////////////////
//Funcion llama automaticamente cuando inica la app
//Intenta Activar el BT si no esta activo
///////////////////////////////////////////////////////
void onStart() {
  super.onStart();
  println("onStart");
  adaptador = BluetoothAdapter.getDefaultAdapter();
  if (adaptador != null) {
    if (!adaptador.isEnabled()) {
      Intent enableBtIntent = new Intent(BluetoothAdapter.ACTION_REQUEST_ENABLE);
      Activity Actividad;
      Actividad = this.getActivity();
      Actividad.startActivityForResult(enableBtIntent, REQUEST_ENABLE_BT);
    } else {
      empieza();
    }
  }
}

////////////////////////////////////////////////////////
//Si re Reinicia la app, se verifica que el BT se activo
///////////////////////////////////////////////////////
void onActivityResult (int requestCode, int resultCode, Intent data) {
  println("onActivityResult");
  if (resultCode == Activity.RESULT_OK) {
    println("RESULT_OK");
    empieza();
  } else {
    println("RESULT_CANCELED");
    estado = 4;
    error = "No se ha activado el bluetooth";
  }
}

////////////////////////////////////////////////////////
//Funcion llama automaticamente cuando inica la app
//Intenta Activar el BT si no esta activo
///////////////////////////////////////////////////////
void empieza() {
  dispositivos = new ArrayList();
  for (BluetoothDevice dispositivo : adaptador.getBondedDevices()) {
    dispositivos.add(dispositivo);
  }
  estado = 1;
}

////////////////////////////////////////////////////////
//Muestra los dipositivos sincronizados con el celular
///////////////////////////////////////////////////////
void listaDispositivos(String texto, color c) {
  background(0);
  fill(c);
  textSize(80);
  text(texto, width/2, 50);
  String s = "Por favor empareje el arduino antes de comenzar";
  textSize(40);
  fill(255);
  text(s, 0, 100, width, 50);
  if (dispositivos != null) {
    for (int indice = 0; indice < dispositivos.size(); indice++) {
      BluetoothDevice dispositivo = (BluetoothDevice) dispositivos.get(indice);
      fill(255, 255, 0);
      int posicion = (indice * 140) + 200;
      if (dispositivo.getName() != null) {
        textSize(60);
        text(dispositivo.getName(), width/2, posicion);
      }
      fill(180, 180, 255);
      textSize(40);
      text(dispositivo.getAddress(), width/2, posicion + 50);
      fill(255);
      line(0, posicion + 100, width, posicion + 100);
    }
  }
}

////////////////////////////////////////////////////////
//Funcion que revisa los toques pantalla y actua dependiendo del estado
///////////////////////////////////////////////////////
void mouseReleased() {
  switch(estado) {
  case 0:
    break;
  case 1:
    compruebaEleccion();
    break;
  case 3:
    compruebaBoton();
    break;
  }
}

////////////////////////////////////////////////////////
//Revisa cual BT se seleciono de la lista
///////////////////////////////////////////////////////
void compruebaEleccion() {
  int elegido = (mouseY - 200) / 140;
  if (elegido < dispositivos.size() && elegido > -1) {     
    dispositivo = (BluetoothDevice) dispositivos.get(elegido);     
    println("Conectando con "+dispositivo.getName());     
    estado = 2;
  }
} 

////////////////////////////////////////////////////////
//Intenta Conectarse con el BT
///////////////////////////////////////////////////////
void conectaDispositivo() {   
  try {     
    socket = dispositivo.createRfcommSocketToServiceRecord(UUID.fromString("00001101-0000-1000-8000-00805F9B34FB"));
    socket.connect();     
    ins = socket.getInputStream();     
    ons = socket.getOutputStream();     
    estado = 3;
    String Mensaje = "G\n";
    byte[]  Dato = Mensaje.getBytes();
    ons.write(Dato);
    //Aquimandar
  }   
  catch(Exception ex) {     
    estado = 4;     
    error = ex.toString();     
    println(error);
  }
}

////////////////////////////////////////////////////////
//Muestra en la pantalla el boton y dato recibido 
///////////////////////////////////////////////////////
void muestraDatos() {  
  int Mensaje = -1;
  try {     
    if (ins.available() > 0) {
      Mensaje  = ins.read();
      println("Estado Actual"+Mensaje);
      if (Mensaje == 49) {
        EstadoBoton = true;
        println("Ecendidad");
      } else if (Mensaje == 48) {
        EstadoBoton = false;
        println("Apagado");
      }
    }
  }
  catch(Exception ex) {
    estado = 4;
    error = ex.toString();
    println(error);
  }
  background(0);
  textAlign(CENTER, CENTER);
  textSize(TamanoPequeno*2);
  if ( EstadoBoton ) {
    fill(0, 200, 0);
  } else {
    fill(200, 0, 0);
  }
  ellipse(width/4, height/8, height/5-20, height/5-20);
  fill(0);
  text("E/A", width/4, height/8);
  fill(0, 50, 100);
  rect(3*width/4-width/8, 50, width/4, height/9-80, 50);
  fill(132, 219, 249);
  rect(3*width/4-width/8, height/8+50, width/4, height/9-80, 50);
  // ellipse(3*width/4, height/8, height/8, height/8);
  fill(0);
  text("M", 3*width/4, 13+ height/18);

  text("17°", 3*width/4, 120+ height/8);
  textSize(TamanoGrande);
  fill(0, 200, 0);
  if ( EstadoBoton) {
    triangle(width/2, height/4, width - width/8, height/2, width/8, height/2);
    text(Temperatura + "° C", width/2, (5*height)/8);
    triangle(width/2, height, width -  width/8, (3*height)/4, width/8, (3*height)/4);
  }
}


////////////////////////////////////////////////////////
//Revisa si se preciono el boton y enviar un mensaje 
///////////////////////////////////////////////////////
void compruebaBoton() {
  String Mensaje ;
  byte[] Dato ;
  float Distancia = dist(mouseX, mouseY, width/4, height/8);
  try {
    if (Distancia < (height/5-20)/2) {
      println("boton precionado");
      EstadoBoton = !EstadoBoton;
      Mensaje = "A\n";
      Dato = Mensaje.getBytes();
      ons.write(Dato);
    } else if (mouseX > 3*width/4-width/8 && mouseX < 3*width/4-width/8 +width/4 &&
      mouseY > height/8+50  && mouseY<height/8+50+ height/9-80 ) {
      println("Timpiratura minima");
      Mensaje = "F\n";
      Dato = Mensaje.getBytes();
      ons.write(Dato);
      EstadoBoton = true;
      Temperatura = 17;
    } else if (mouseX > 3*width/4-width/8 &&  mouseX < 3*width/4-width/8 + width/4 &&
      mouseY > 50 && mouseY <50+height/9-80     ) {
      println("boton modo");
      Mensaje = "L\n";
      Dato = Mensaje.getBytes();
      ons.write(Dato);
    }
    if ( EstadoBoton) {
      if (mouseY > (height/4) && mouseY < (height/2)) {
        println("boton s");
        Temperatura = Temperatura +1;
        if (Temperatura > 30) {
          Temperatura = 30;
        }
        Mensaje =""+Temperatura + "\n";
        Dato = Mensaje.getBytes();
        ons.write(Dato);
        //Enviar T
      } else if (mouseY > (3*height)/4) {
        Temperatura = Temperatura-1;
        if (Temperatura < 17) {
          Temperatura = 17;
        }
        Mensaje =""+Temperatura + "\n";
        Dato = Mensaje.getBytes();
        ons.write(Dato);
        //Enviar T
      }
    }
  }
  catch(Exception ex) {
    estado = 4;
    error = ex.toString();
    println(error);
  }
}

////////////////////////////////////////////////////////
//Muestra un errror Fatal si pasa alguno
//Es posible interpretar los errores 
///////////////////////////////////////////////////////
void muestraError() {
  background(255, 0, 0);
  fill(255, 255, 0);
  textAlign(CENTER);
  translate(width / 2, height / 2);
  rotate(3 * PI / 2);
  text(error, 0, 0);
}


////////////////////////////////////////////////////////
//SI el Celular ando buscando lo muestra  
///////////////////////////////////////////////////////
BroadcastReceiver receptor = new BroadcastReceiver() {
  public void onReceive(Context context, Intent intent) {
    println("onReceive");
    String accion = intent.getAction();
    if (BluetoothDevice.ACTION_FOUND.equals(accion)) {
      BluetoothDevice dispositivo = intent.getParcelableExtra(BluetoothDevice.EXTRA_DEVICE);
      println(dispositivo.getName() + " " + dispositivo.getAddress());
      dispositivos.add(dispositivo);
    } else if (BluetoothAdapter.ACTION_DISCOVERY_STARTED.equals(accion)) {
      estado = 0;
      println("Empieza búsqueda");
    } else if (BluetoothAdapter.ACTION_DISCOVERY_FINISHED.equals(accion)) {
      estado = 1;
      println("Termina búsqueda");
    }
  }
};


////////////////////////////////////////////////////////
//Si ce cierra la app en ceserario cerrar la conexion BT
///////////////////////////////////////////////////////
void onStop() {
  println("onStop");
  if (socket != null) {
    try {
      socket.close();
    }
    catch(IOException ex) {
      println(ex);
    }
  }
  super.onStop();
}