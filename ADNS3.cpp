
#include "ADNS3.h"

ADNS3::ADNS3() {

    SPI.begin();
    SPI.setBitOrder(MSBFIRST);
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    SPI.setDataMode(SPI_MODE3);

    // resets settings
    writeRegister(0x3a, 0x5a);
}

byte ADNS3::readRegister(byte reg) {
  byte resp;

  digitalWrite(SS, LOW);
  SPI.transfer(reg);
  delayMicroseconds(READ_DELAY);
  resp = SPI.transfer(0);
  digitalWrite(SS, HIGH);

  return resp;
}

void ADNS3::writeRegister(byte reg, byte value) {
  digitalWrite(SS, LOW);

  SPI.transfer(reg | 0x80); // 1 at MSB for write operation
  SPI.transfer(value);

  digitalWrite(SS, HIGH);
}

ADNS3::Motion ADNS3::readMotion() {

  Motion motion;

  digitalWrite(SS, LOW);

  SPI.transfer(MOTION_REG);
  delayMicroseconds(READ_DELAY);
  motion.motion = SPI.transfer(0);
  motion.deltaY = SPI.transfer(0);
  motion.deltaX = SPI.transfer(0);
  motion.squal = SPI.transfer(0);

  unsigned int shutterUpper = SPI.transfer(0);
  motion.shutter = shutterUpper << 8;
  motion.shutter |= SPI.transfer(0);

  motion.maxPixel = SPI.transfer(0);

  digitalWrite(SS, HIGH);

  return motion;
}
