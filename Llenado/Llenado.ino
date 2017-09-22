int sensor1 = 22;
int sensor2 = 25;
int sensor3 = 26;
int PinInicio = 42;
int ValorInicio = 0;
int EV06 = 38;
int EV05 = 37;
int EV04 = 34;
int M03 = 33;
int banda = 29;
//declaración de pines para las entradas y salidas
int sensorA = 0;
int sensorB = 0;
int sensorC = 0;
int Estado = 0;

void setup() {
  Serial.begin(9600);
  pinMode (sensor1, INPUT_PULLUP);
  pinMode (sensor2, INPUT_PULLUP);
  pinMode (sensor3, INPUT_PULLUP);
  pinMode (PinInicio, INPUT_PULLUP);
  pinMode (EV06, OUTPUT);
  pinMode (EV05, OUTPUT);
  pinMode (EV04, OUTPUT);
  pinMode (M03, OUTPUT);
  pinMode (banda, OUTPUT);



}

void loop() {

  sensorA = digitalRead(sensor1);
  sensorB = digitalRead(sensor2);
  sensorC = digitalRead(sensor3);
  ValorInicio = digitalRead(PinInicio);

  Serial.print("Valor A:");
  Serial.print(sensorA);

  Serial.print(" Valor B:");
  Serial.print(sensorB);

  Serial.print(" Valor C:");
  Serial.println(sensorC);

  if (ValorInicio == 0) {
    digitalWrite(banda, LOW);
    digitalWrite(M03, LOW);
    digitalWrite(EV05, LOW);
    digitalWrite(EV04, LOW);
    digitalWrite(EV06, LOW);
    Estado = 0;
  }


  switch (Estado) {
    case 0:
      // Apagada y esperadon boton encendido
      Serial.println("E0-Apagada");
      if (ValorInicio == 1) {
        digitalWrite(banda, HIGH);
        Estado = 1;
      }
      break;
    case 1:
      // Banda Activa y esperando Senso A
      if ( sensorA == 1) {
        Serial.println("E1-Esperando Sensor A");
        digitalWrite(banda, LOW);
        Estado = 2;
      }
      break;
    case 2:
      //Llenando y despues enciende banda
      Serial.println("E2-llenando");
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
      digitalWrite(EV04, LOW); //bomba
      delay(3000);
      digitalWrite(banda, HIGH);
      Estado = 3;
    case 3:
      //Esperando sensor B si apaga la banda
      Serial.println("E3-Esperando Sensor B");
      if ( sensorB == 1) {
        digitalWrite(banda, LOW);
        Estado = 4;
      }
      break;
    case 4:
      //Dandole un poraso a la Tapando
      Serial.println("E4-Tapando");
      digitalWrite(banda, LOW);
      delay(3000);
      digitalWrite(EV06, HIGH); //taponado
      delay(4000);
      digitalWrite(EV06, LOW); //taponado
      delay(3000);
      digitalWrite(banda, HIGH);
      Estado = 5;
      break;
    case 5:
      //Esperando el Sensor C
      Serial.println("E5-Esperando Sensor C");
      if ( sensorC == 1) {
        digitalWrite(banda, LOW);
        delay(6000);
        Estado = 0;
      }
      break;
  }
}
