int AIN1 = 6;
int AIN2 = 5;


int velocidad = 255;

void setup() {
  pinMode(AIN1,OUTPUT);
  pinMode(AIN2,OUTPUT);

}

void loop() {
  analogWrite(AIN1,velocidad);
  analogWrite(AIN2,0);
  delay(1000);
  analogWrite(AIN2,0);
  analogWrite(AIN1,0);
  delay(1000);
}
