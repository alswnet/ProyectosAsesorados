int sensor1 = 22;
int sensor2 = 25;
int sensor3 = 26;
int PinInicio = 42;
int ValorInicio = 0;
int STOP = 41;
int EV06 = 38;
int EV05 = 37;
int EV04 = 34;
int M03 = 33;
int K02 = 30;
int banda = 29;
int ledprueba = 13;
//declaración de pines para las entradas y salidas
int botonA = 0;
int botonB = 0;
int sensorA = 0;
int sensorB = 0;
int sensorC = 0;
int lecturaStart = 0;
int lecturaSensor1 = 0;


void setup() {
  Serial.begin(9600);
  pinMode (sensor1, INPUT);
  pinMode (sensor2, INPUT);
  pinMode (sensor3, INPUT);
  pinMode (PinInicio, INPUT_PULLUP);
  pinMode (STOP, INPUT);
  pinMode (EV06, OUTPUT);
  pinMode (EV05, OUTPUT);
  pinMode (EV04, OUTPUT);
  pinMode (M03, OUTPUT);
  pinMode (K02, OUTPUT);
  pinMode (banda, OUTPUT);



  // paso 0

}

void loop() {

  sensorA = digitalRead(sensor1);
  sensorB = digitalRead(sensor2);
  sensorC = digitalRead(sensor3);
  ValorInicio = digitalRead(PinInicio);

  Serial.print("El boton esta ");
  Serial.println(ValorInicio);

  if (ValorInicio == 1) {



    lecturaStart = Serial.read();
    //lecturaSensor1 = Serial.read();
    //Serial.println("usb conectado");
    //delay(3000);
  }

  digitalWrite(banda, HIGH);

  if (sensorA == 1)
  {
    digitalWrite(banda, LOW);
    digitalWrite(EV04, HIGH); //pistón
    delay (2000);
    digitalWrite(EV05, HIGH); //lvula liquido
    delay (2000);
    digitalWrite(M03, HIGH); //bomba
    delay(5000);

    digitalWrite(M03, LOW); //
    delay(2000);
    digitalWrite(EV05, LOW); //valvula liquido
    delay(2000);
    digitalWrite(M03, LOW); //bomba
    delay(3000);
    digitalWrite(banda, HIGH);
  }

  //   {
  //    digitalWrite(banda,LOW);
  //    digitalWrite(EV04, LOW); //pistón
  //    digitalWrite(EV05, LOW); //valvula liquido
  //    digitalWrite(M03, LOW); //bomba
  //    delay(5000);

  // }


  if (sensorB == 1)
  {

    digitalWrite(banda, LOW);
    delay(3000);
    digitalWrite(EV06, HIGH); //taponado
    delay(4000);
    digitalWrite(EV06, LOW); //taponado
    delay(3000);
    digitalWrite(banda, HIGH);
  }

  if (sensorC == 1)
  {
    digitalWrite(banda, LOW);

  }
}







/*if(sensorA == 1)
  {
  digitalWrite(banda, LOW);

  digitalWrite(EV04, HIGH); //pistón0
  digitalWrite(M03, HIGH); //bomba
  digitalWrite(EV05, HIGH); //valvula liquido
  delay(8000);

  digitalWrite(banda, HIGH);
  }

  else
  {
  digitalWrite(banda, HIGH);
  }

  if(sensorB == 1)
  {
  digitalWrite(banda, LOW);
  digitalWrite(EV06, HIGH); //pistón
  delay(8000);

  digitalWrite(banda, HIGH); //bomba

  }

  else
  {
  digitalWrite(banda, HIGH);
  }

  if(sensorC == 1)
  {
  digitalWrite(banda, LOW);
  }

  else
  {
  digitalWrite(banda, HIGH);
  }



  }





  /*}
  do{
  if (sensorA == HIGH ){
  digitalWrite(banda,LOW);
  delay(50);
  digitalWrite(EV04, HIGH);
  delay(2000);
  digitalWrite(EV05,HIGH);
  digitalWrite(M03,HIGH);
  delay (5000) ;
  digitalWrite(M03,LOW);
  digitalWrite(EV05,LOW);
  delay (800);
  digitalWrite(EV04,LOW);
  digitalWrite(banda, HIGH);
  delay(5000);
  digitalWrite(banda, HIGH);
  }

  else {
  digitalWrite(banda, HIGH);
  }


  // paso 2
  if (sensorB == HIGH ) {
  digitalWrite(banda, LOW);
  delay (1000);
  digitalWrite(EV06,HIGH);
  delay (4000);
  digitalWrite(K02,HIGH);
  delay (3000);
  digitalWrite(K02,LOW);
  delay (4000);
  digitalWrite(EV06,LOW);
  digitalWrite(banda, HIGH);
  delay (5000);
  digitalWrite(banda, HIGH);
  }
  else {
  digitalWrite(banda, HIGH);
  }

  // paso 3
  if (sensorC == HIGH) {
  digitalWrite(banda, LOW);
  }
  else {
  digitalWrite(banda, HIGH);
  }
  delay(1000);*/



