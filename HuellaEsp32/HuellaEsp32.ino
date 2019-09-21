#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if defined(ARDUINO_ARCH_ESP32)
#include <HardwareSerial.h>
#elif
#include <SoftwareSerial.h>
#endif

#include <GT5X.h>

int PinMotor = 18;
boolean EstadoMotor = true;
int LedIndicador = 5;
/* Enroll fingerprints */
#if defined(ARDUINO_ARCH_ESP32)
/* select UART1 for ESP32 */
HardwareSerial fserial(1);
#elif
/* RX = 2, TX = 3 */
SoftwareSerial fserial(2, 3);
#endif

BluetoothSerial SerialBT;
GT5X finger(&fserial);
GT5X_DeviceInfo info;

void setup() {
  Serial.begin(115200);
  Serial.println("Iniciando sistema");
  pinMode(PinMotor, OUTPUT);
  pinMode(LedIndicador, OUTPUT);
  digitalWrite(PinMotor, EstadoMotor);
  SerialBT.begin("ESP32test");
#if defined(ARDUINO_ARCH_ESP32)
  /* RX = IO16, TX = IO17 */
  Serial.println("Soy ESP32");
  fserial.begin(9600, SERIAL_8N1, 16, 17);
#elif
  fserial.begin(9600);
#endif

  if (finger.begin(&info)) {
    Serial.println("Found fingerprint sensor!");
    Serial.print("Firmware Version: "); Serial.println(info.fwversion);
    finger.set_led(true);
  } else {
    Serial.println("Sensor no encontrado :(");
    while (1) {
      digitalWrite(LedIndicador, 0);
      delay(500);
      digitalWrite(LedIndicador, 1);
      delay(500);
    }

  }
}

void loop() {
  if (Serial.available()) {
    char Letra = Serial.read();
    Serial.write(Letra);
    SerialBT.write(Letra);
    Escanear(Letra);
  }
  if (SerialBT.available()) {
    char Letra = SerialBT.read();
    Serial.write(Letra );
    Escanear(Letra);
  }

  BuscarHuella();

  delay(20);
}

void BuscarHuella() {
  if (!finger.is_pressed()) {
    return;
  }
  uint16_t rc = finger.capture_finger();
  //finger.set_led(true);
  if (rc != GT5X_OK) {
    return;
  }
  uint16_t IDSecreto;
  rc = finger.search_database(&IDSecreto);
  if (rc != GT5X_OK) {
    Serial.println("No encontre la huella");
    SerialBT.print('F');
    return;
  }

  Serial.print("Encontrado el ID: ");
  Serial.println(IDSecreto);
  EstadoMotor = !EstadoMotor;
  digitalWrite(PinMotor, EstadoMotor);
  delay(1000);
  //finger.set_led(false);
}

void Escanear(char Letra) {
  if (Letra == 'd' || Letra == 'D') {
    uint16_t rc = finger.delete_id(0);

    Serial.print(rc);
    switch (rc) {
      case GT5X_OK:
        Serial.println("Borrando huella 0");
        SerialBT.print('T');
        break;
      default:
        Serial.println("Error Fatal");
        SerialBT.print('F');
        break;
    }
  }
  else if (Letra == 'a' || Letra == 'A') {
    Enroll();
  }
  else if (Letra == 'c' || Letra == 'C') {
    uint16_t rc = finger.is_enrolled(0);
    switch (rc) {
      case GT5X_OK:
        Serial.println("Esta lleno");
        SerialBT.print('L');
        break;
      case GT5X_NACK_IS_NOT_USED:
        Serial.println("Esta vacio");
        SerialBT.print('V');
        break;
      default:
        Serial.print("Error code: 0x"); Serial.println(rc, HEX);
        SerialBT.print('F');
        break;
    }
  }
}

void Enroll() {
  uint16_t rc = finger.is_enrolled(0);

  switch (rc) {
    case GT5X_OK:
      Serial.println("Ya esta asignado");
      SerialBT.print('F');
      return;
    case GT5X_NACK_IS_NOT_USED:
      Serial.println("Disponible el ID #0");
      break;
    default:
      Serial.print("Error code: 0x"); Serial.println(rc, HEX);
      SerialBT.print('F');
      return;
  }
  enroll_finger(0);
}


void enroll_finger(uint16_t fid) {
  uint16_t p = finger.start_enroll(fid);
  switch (p) {
    case GT5X_OK:
      Serial.print("Enrolling ID #"); Serial.println(fid);
      break;
    default:
      Serial.print("No empezo a enroal, Error code: 0x"); Serial.println(p, HEX);
      return;
  }

  /* turn on led for print capture */
  finger.set_led(true);

  /* scan finger 3 times */
  for (int scan = 1; scan < 4; scan++) {
    // finger.set_led(true);
    Serial.println("Place your finger.");
    SerialBT.print('P');
    p = finger.capture_finger(true);

    while (p != GT5X_OK) {
      p = finger.capture_finger(true);
      switch (p) {
        case GT5X_OK:
          Serial.println("Image taken.");
          break;
        case GT5X_NACK_FINGER_IS_NOT_PRESSED:
          Serial.println(".");
          break;
        default:
          Serial.print("Error code: 0x"); Serial.println(p, HEX);
          SerialBT.print('F');
          //finger.set_led(false);
          return;
      }
      yield();
    }

    p = finger.enroll_scan(scan);
    switch (p) {
      case GT5X_OK:
        Serial.print("Scan "); Serial.print(scan);
        Serial.println(" complete.");
        break;
      default:
        Serial.print("Error code: 0x"); Serial.println(p, HEX);
        SerialBT.print('F');
        //finger.set_led(false);
        return;
    }

    Serial.println("Remove finger.");
    //finger.set_led(false);
    SerialBT.print('R');
    while (finger.is_pressed()) {
      yield();
    }
    Serial.println();
  }

  /* wr're done so turn it off */
  //finger.set_led(false);

  Serial.println("Enroll complete.");
  SerialBT.print('T');
  return;
}
