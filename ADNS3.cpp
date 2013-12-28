
#include "ADNS3.h"

ADNS3::ADNS3(int ncs_pin, int miso_pin, int sclk_pin, int mosi_pin) :
  m_ncsPin(ncs_pin),
  m_misoPin(miso_pin),
  m_sclkPin(sclk_pin),
  m_mosiPin(mosi_pin) {

    pinMode(m_ncsPin, OUTPUT);
    pinMode(m_mosiPin, OUTPUT);
    pinMode(m_sclkPin, OUTPUT);
    pinMode(m_misoPin, INPUT);

    digitalWrite(m_ncsPin, HIGH);
    digitalWrite(m_sclkPin, HIGH);

    writeRegister(0x3a, 0x5a);
    readMotion();
}

unsigned char ADNS3::readRegister(unsigned char reg) {
  unsigned char resp;

  digitalWrite(m_ncsPin, LOW);
  writeByte(reg);
  delayMicroseconds(READ_DELAY);
  resp = readByte();
  digitalWrite(m_ncsPin, HIGH);

  return resp;
}

void ADNS3::writeRegister(unsigned char reg, unsigned char value) {
  digitalWrite(m_ncsPin, LOW);

  writeByte(reg | 0x80); // 1 at MSB for write operation
  writeByte(value);

  digitalWrite(m_ncsPin, HIGH);
}

ADNS3::Motion ADNS3::readMotion() {

  Motion motion;

  digitalWrite(m_ncsPin, LOW);

  writeByte(MOTION_REG);
  delayMicroseconds(READ_DELAY);
  motion.motion = readByte();
  motion.deltaY = readByte();
  motion.deltaX = readByte();
  motion.squal = readByte();
  motion.shutterUpper = readByte();
  motion.shutterLower = readByte();
  motion.maxPixel = readByte();

  digitalWrite(m_ncsPin, HIGH);

  return motion;
}

void ADNS3::writeByte(unsigned char reg) {
  for (int i = 0 ; i < 8 ; i++) {
    digitalWrite(m_sclkPin, LOW);
    digitalWrite(m_mosiPin, ((reg << i) & 0x80) != 0);
    MICRO_DELAY
    digitalWrite(m_sclkPin, HIGH);
    MICRO_DELAY
  }
}

unsigned char ADNS3::readByte() {
  unsigned char resp = 0;

  for (int i = 7 ; i >= 0 ; i--) {
    digitalWrite(m_sclkPin, LOW);
    MICRO_DELAY
    digitalWrite(m_sclkPin, HIGH);

    if (digitalRead(m_misoPin)) {
      resp |= (1 << i);
    }

    MICRO_DELAY
  }

  return resp;
}
