#include <SPI.h>
#include <ADNS3.h>

ADNS3 sensor;

void setup() {
  Serial.begin(9600);
  Serial.println("Reading ADNS x/y travelled distance. Send something to reset.");
}

int d_x = 0;
int d_y = 0;

void loop() {
  if (Serial.available()) {
    Serial.read();
    d_x = 0;
    d_y = 0;
    Serial.println("Reset");
    printDistance();
  }

  ADNS3::Motion motion = sensor.readMotion();

  d_x += motion.deltaX;
  d_y += motion.deltaY;

  if (motion.deltaX != 0 || motion.deltaY != 0) {
    printDistance();
  }
}

void printDistance() {
  Serial.print("x: ");
  Serial.print(d_x);
  Serial.print(" ; y: ");
  Serial.println(d_y);
}
