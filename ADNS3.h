/*
 * ADNS3 Arduino library
 * Version 0.0.1, December 2013
 * Author Hadrien Milano
 * License: MIT
 *
 * Allows you to control ADNS-3xxx optical mouse sensors over the SPI bus.
 * Be sure to include "SPI.h" in your sketch or it won't compile.
 *
 * INSTRUCTIONS:
 *
 * If you are using ADNS3030 or ADNS3040, it should work out of the box.
 * Otherwithe, find your specific device's datasheet, and look for the "MOTION"
 * register address. Use this value to define MOTION_REG below.
 * Save the file, and try the example.
 * If it doesn't work, make sure "burst mode" on your chip outputs "Motion,
 * Delta_Y, and Delta_X, SQUAL, Shutter_Upper, and Shutter_Lower and Maximum_Pixel"
 * in that order. If it doesn't, you can't use readMotion() unless you edit it yourself.
 *
 * But you can still use readRegister() to read "Motion" AND THEN "Delta_x" and "Delta_y"
 * (These three registers sometimes MUST be read sequencially or it won't work).
*/

#ifndef ADNS3_H
#define ADNS3_H
  #include <SPI.h>
  #include <Arduino.h>

  // You may want to change this value if you are not using ADNS3030/3040
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
  };

#endif
