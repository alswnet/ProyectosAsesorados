int PinSensor = A5;

//Cambiar valor segun fuenta de filtro
//Rango de 0-1
//Valores aproximandose a 0 siguen menos la linea real
//Valores aproximandose a 1 siguien la linea real
float FuerzaFiltro = 0.05;

void setup() {
  pinMode(PinSensor, INPUT);
  Serial.begin(115200);
  delay(1000);
  VanteriorSensor = analogRead(PinSensor);
}

void loop() {
  VactSensor = analogRead(PinSensor);
  //Serial.print(VactSensor);
  //Serial.print(",");
  VactSensor = FiltroPasaBajo(VactSensor);
  Serial.print("V,");
  Serial.print(VactSensor);
  //Serial.print(",");
  //Serial.print(VMaxSensor);
  //Serial.print(",");
  //Serial.print(VminSensor);
  Serial.println();

  delay(15);
}

int FiltroPasaBajo(int Valor) {
  VanteriorSensor = FuerzaFiltro * Valor + (1 - FuerzaFiltro) * VanteriorSensor;
  return VanteriorSensor;
}
