/*
 * ADNS3 Arduino library
 * Version 0.0.1, December 2013
 * Author Hadrien Milano
 * License: MIT
 *
 * Allows you to control ADNS-3xxx optical mouse sensors over the SPI bus.
 * Be sure to include "SPI.h" in your sketch or it won't compile.
 *
 * Direct access to registers can be made with readRegister/writeRegister.
 *
 * ReadMotion uses "burst" mode (MOTION_REGISTER)
 *
 * This code works with ADNS3030/ADNS3040. Check register addresses in your
 * specific component's datasheet.
*/



#ifndef ADNS3_H
#define ADNS3_H

  #include <SPI.h>
  #include <Arduino.h>

  // /!\ you mau want to change this value according to the datasheet.
  #define MOTION_REG  0x42

  #define READ_DELAY  75  // microseconds


  class ADNS3 {
    public:
      struct Motion {
        byte motion;
        char deltaX;
        char deltaY;
        unsigned char squal;
        unsigned int shutter;
        unsigned char maxPixel;
      };

      ADNS3();

      byte readRegister(byte reg);
      void writeRegister(byte reg, byte value);

      Motion readMotion();


    private:
      int m_ncsPin;
      int m_misoPin;
      int m_sclkPin;
      int m_mosiPin;
  };

#endif
