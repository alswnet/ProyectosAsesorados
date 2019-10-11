import processing.serial.*;

Serial PuertoSensor;
Serial PuertoBraso;

void setup() {
  printArray(Serial.list());
  PuertoSensor = new Serial(this, "/dev/ttyUSB0", 9600);
  PuertoSensor.bufferUntil('\n');
  PuertoBraso = new Serial(this, "/dev/ttyUSB0", 9600);
  PuertoBraso.bufferUntil('\n');
  size(400, 600);
}

void draw() {
  background(0);
  while (PuertoSensor.available() > 0) {
    PuertoBraso.write(PuertoSensor.read());
    background(255);
  }
  
  while (PuertoBraso.available() > 0) {
    PuertoSensor.write(PuertoBraso.read());
     background(255);
  }
} 
