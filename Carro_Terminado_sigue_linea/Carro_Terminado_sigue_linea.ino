void adelante();
void atras();
void derecha();
void izquierda();
void detenido();

int DerechaAdelante = 3;
int IzquierdaAdelante = 5;
int DerechaAtras = 6;
int IzquierdaAtras = 9;

int velocidad = 200;

int sensorDerecho = 0;
int sensorIzquierda = 0;

void setup() {
  pinMode(DerechaAdelante,OUTPUT);
  pinMode(IzquierdaAdelante,OUTPUT);
  pinMode(DerechaAtras,OUTPUT);
  pinMode(IzquierdaAtras,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  sensorDerecho = analogRead(A0);
  sensorIzquierda = analogRead(A2);

  Serial.print(sensorDerecho);
  Serial.print("  ");
  Serial.println(sensorIzquierda);
  if(sensorDerecho < 60 && sensorIzquierda < 60)
  {
    adelante();
  }
  else if(sensorDerecho > 60 && sensorIzquierda < 60)
  {
    izquierda();
  }
  else if(sensorDerecho < 60 && sensorIzquierda > 60)
  {
    derecha();
  }
  else
  {
    detenido();
  }  
  delay(10);
}



void adelante(){
  analogWrite(DerechaAdelante,0);
  analogWrite(IzquierdaAdelante,velocidad);
  analogWrite(DerechaAtras,velocidad);
  analogWrite(IzquierdaAtras,0);
}

void atras(){
  analogWrite(DerechaAdelante,velocidad);
  analogWrite(IzquierdaAdelante,0);
  analogWrite(DerechaAtras,0);
  analogWrite(IzquierdaAtras,velocidad);
}

void derecha(){
  analogWrite(DerechaAdelante,0);
  analogWrite(IzquierdaAdelante,velocidad);
  analogWrite(DerechaAtras,0);
  analogWrite(IzquierdaAtras,velocidad);
}

void izquierda(){
  analogWrite(DerechaAdelante,velocidad);
  analogWrite(IzquierdaAdelante,0);
  analogWrite(DerechaAtras,velocidad);
  analogWrite(IzquierdaAtras,0);
}

void detenido(){
  analogWrite(DerechaAdelante,0);
  analogWrite(IzquierdaAdelante,0);
  analogWrite(DerechaAtras,0);
  analogWrite(IzquierdaAtras,0);
}

