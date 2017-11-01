int k = 2;

void setup() {
  for (int i = 2; i < 52; i++) {
    pinMode(i, OUTPUT);
  }
}

void loop() {
  for (int j = 2; j < 52; j++) {
    if (k == j) {
      digitalWrite(j, HIGH);
    }
    else {
      digitalWrite(j, LOW);
    }
  }
  delay(1000);
  k++;
  if (k == 52) {
    k = 2;
  }
}
