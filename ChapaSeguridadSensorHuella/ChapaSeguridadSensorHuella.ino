#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"

// Hardware setup - FPS connected to:
//    digital pin 4(arduino rx, fps tx)
//    digital pin 5(arduino tx - 560ohm resistor fps tx - 1000ohm resistor - ground)
//    this brings the 5v tx line down to about 3.2v so we dont fry our fps

FPS_GT511C3 fps(4, 5);

int disparo = 10;
void setup()
{
  pinMode(13, OUTPUT);
  pinMode(disparo, OUTPUT);
  Serial.begin(9600);
  delay(100);
  fps.Open();
  fps.SetLED(true);
}

void loop()
{

  // Identify fingerprint test
  if (fps.IsPressFinger())
  {
    fps.CaptureFinger(false);
    int id = fps.Identify1_N();
    if (id < 200)
    {
      Serial.print("Verified ID:");
      Serial.println(id);
      digitalWrite(disparo, HIGH);
      digitalWrite(13, HIGH);
      delay(2000);
    }
    else
    {
      Serial.println("intruso");
      digitalWrite(disparo, LOW);
      digitalWrite(13, LOW);
    }
  }
  else {
    digitalWrite(disparo, LOW);
    digitalWrite(13, LOW);
  }
  delay(100);
}
