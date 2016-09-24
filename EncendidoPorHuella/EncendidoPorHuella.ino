#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"

FPS_GT511C3 fps(2, 3);
int PinRele = 4;
bool Estado = false;
void setup()
{
  Serial.begin(9600);
  delay(100);
  fps.Open();
  fps.SetLED(true);
  pinMode(PinRele, OUTPUT);
  digitalWrite(PinRele, Estado);
}

void loop()
{
  if (fps.IsPressFinger())
  {
    fps.CaptureFinger(false);
    int id = fps.Identify1_N();
    if (id == 0)
    {
      Serial.print("Hola");
      Estado = !Estado;
      digitalWrite(PinRele, Estado);
      delay(1000);
    }
  }
}
