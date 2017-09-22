boolean Boton = false;
int PinBoton1 = 7;
int PinBoton2 = 8;
int Relevador = 5;



void setup() {
  Serial.begin(9600);
  pinMode(10, INPUT); // Setup for leads off detection LO +
  pinMode(11, INPUT); // Setup for leads off detection LO -
  pinMode(PinBoton1, INPUT);
  pinMode(PinBoton2, INPUT);
  pinMode(Relevador, OUTPUT);
}

void loop() {
  if (digitalRead(PinBoton1) == 0) {
    Boton = true;
  }
  if (digitalRead(PinBoton2) == 0) {
    Boton = false;

  }

  if (Boton) {
    if ((digitalRead(10) == 1) || (digitalRead(11) == 1)) {
    }
    else {
      Serial.println(analogRead(A0));
      if (analogRead(A0) > 650 && analogRead(A0) < 660) {
        digitalWrite(Relevador, HIGH);
        delay(2000);
        digitalWrite(Relevador, LOW);
      }
    }
    delay(1);
  }
}
