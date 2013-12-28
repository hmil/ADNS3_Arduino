#include "ADNS3.h"

ADNS3 myMouse = ADNS3(2, 3, 4, 5);

void setup() {
  Serial.begin(9600);
}

void loop() {

/* Using motion report, this is more performant.
  ADNS3::Motion motion = myMouse.readMotion();

  Serial.print("dx: ");
  Serial.print(motion.deltaX, DEC);
  Serial.print(", dy: ");
  Serial.print(motion.deltaY, DEC);
  Serial.print(", quality: ");
  Serial.println(motion.squal, DEC);
//*/

//* not using reports, this is more likely to be compatible
  Serial.println("--- measure ---");
  // According to ADNS datasheet, these registers must be read sequencially
  Serial.println(myMouse.readRegister(0x02), BIN); // motion register
  Serial.println((char)myMouse.readRegister(0x03), DEC); // deltaX register
  Serial.println((char)myMouse.readRegister(0x04), DEC); // deltaY register
//*/

  delay(1000);
}
