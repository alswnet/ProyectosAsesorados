#include "BluetoothSerial.h"
#include "FPS_GT511C3.h"
#include "SoftwareSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

int PinMotor = 18;
boolean EstadoMotor = true;


BluetoothSerial SerialBT;
FPS_GT511C3 fps(17, 16);

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando sistema");
  pinMode(PinMotor, OUTPUT);
  digitalWrite(PinMotor, EstadoMotor);
  SerialBT.begin("ESP32test");
  fps.UseSerialDebug = true;
  fps.Open();
  fps.SetLED(true);
}

void loop() {
  if (Serial.available()) {
    char Letra = Serial.read();
    SerialBT.write(Letra);
    Escanear(Letra);
  }
  if (SerialBT.available()) {
    char Letra = SerialBT.read();
    Serial.write(Letra );
    Escanear(Letra);
  }

  if (fps.IsPressFinger())  {
    fps.CaptureFinger(false);
    int id = fps.Identify1_N();
    if (id == 0) {
      EstadoMotor = !EstadoMotor;
      digitalWrite(PinMotor, EstadoMotor);
      delay(1000);
    }
  }

  delay(20);
}

void Escanear(char Letra) {
  if (Letra == 'd' || Letra == 'D') {
    fps.DeleteAll();
  }
  else if (Letra == 'a' || Letra == 'A') {
    Enroll();
  }
  else if (Letra == 'c' || Letra == 'C') {
    if (fps.CheckEnrolled(0)) {
      Serial.println("Esta lleno");
      SerialBT.print('L');
    }
    else {
      Serial.println("Esta vacio");
      SerialBT.print('V');
    }
  }


}

void Enroll()
{
  // Enroll test

  // find open enroll id
  int enrollid = 0;
  bool usedid = true;
  while (usedid == true)
  {
    usedid = fps.CheckEnrolled(enrollid);
    if (usedid == true) enrollid++;
  }
  fps.EnrollStart(enrollid);

  // enroll
  Serial.print("Press finger to Enroll #");
  Serial.println(enrollid);
  SerialBT.print('P');
  while (fps.IsPressFinger() == false) delay(100);
  bool bret = fps.CaptureFinger(true);
  int iret = 0;
  if (bret != false)
  {
    Serial.println("Remove finger");
    SerialBT.print('R');
    fps.Enroll1();
    while (fps.IsPressFinger() == true) delay(100);
    SerialBT.print('P');
    Serial.println("Press same finger again");
    while (fps.IsPressFinger() == false) delay(100);
    bret = fps.CaptureFinger(true);
    if (bret != false)
    {
      SerialBT.print('R');
      Serial.println("Remove finger");
      fps.Enroll2();
      while (fps.IsPressFinger() == true) delay(100);
      Serial.println("Press same finger yet again");
      SerialBT.print('P');
      while (fps.IsPressFinger() == false) delay(100);
      bret = fps.CaptureFinger(true);
      if (bret != false)
      {
        Serial.println("Remove finger");
        SerialBT.print('R');
        iret = fps.Enroll3();
        if (iret == 0)
        {
          Serial.println("Enrolling Successful");
          SerialBT.print('T');
        }
        else
        {
          Serial.print("Enrolling Failed with error code:");
          Serial.println(iret);
          SerialBT.print('F');
        }
      }
      else {
        Serial.println("Failed to capture third finger");
        SerialBT.print('F');
      }
    }
    else {
      Serial.println("Failed to capture second finger");
      SerialBT.print('F');
    }
  }
  else {
    Serial.println("Failed to capture first finger");
    SerialBT.print('F');
  }
}
