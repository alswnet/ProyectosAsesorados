int pines[8] = {3, 4, 5, 6, 7, 8, 9, 10};
int Boton = 12;
int LecturaBoton = 0;
int k = 0;
boolean EstadoBoton = false;

void setup() {
  pinMode(Boton, INPUT);
  for (int i = 0; i < 8; i++) {
    pinMode(pines[i], OUTPUT);
  }
  Serial.begin(9600);
}

void loop() {
  LecturaBoton = digitalRead(Boton);
  if (LecturaBoton == 1) {
    EstadoBoton = !EstadoBoton;
    Serial.println("llegue");
    do {
      LecturaBoton = digitalRead(Boton);
      Serial.println("Entre");
    } while (LecturaBoton == 1);
  }

  if (EstadoBoton) {
    for (int i = 0; i < 8; i++) {
      if (i == k) {
        digitalWrite(pines[i], HIGH);
      }
      else {
        digitalWrite(pines[i], LOW);
      }
    }
    k++;
    if (k == 8) {
      k = 0;
    }
  }
  delay(30);
}
