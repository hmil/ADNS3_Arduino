/*
 * ADNS3 Arduino library
 * Version 0.0.1, December 2013
 * Author Hadrien Milano
 * License: MIT
 *
 * Allows you to control ADNS-3xxx optical mouse sensors.
 *
 * This class of sensors is operated through a 4 wire serial interface generally on pins 1, 2, 3 and 4 (see datasheet to make sure of it).
 * If you choose to let the sensor on the mouse PCB, make sure to disconnect these four wires before connecting them to your arduino.
 * If you choose to extract the sensor, make sure to connect all grounds, VCC and LED control pins. Also use a 2/3 voltage divider on
 * "NCS", "SCLK" and "MOSI" lines, and good luck with the unusual pin geometry
 *
 * Usage: see README
*/

#import <Arduino.h>

#ifndef ADNS3_H
#define ADNS3_H

  #define MICRO_DELAY asm("nop\r\nnop\r\nnop\r\nnop");
  #define MOTION_REG  0x42
  #define READ_DELAY  75  // microseconds


  class ADNS3 {
    public:
      struct Motion {
        unsigned char motion;
        char deltaX;
        char deltaY;
        unsigned char squal;
        unsigned char shutterUpper;
        unsigned char shutterLower;
        unsigned char maxPixel;
      };

      /*
        Creates a new driver instance. These pins usually are pins 1, 2, 3 and 4 of the ADNS chip.
      */
      ADNS3(int ncs_pin, int miso_pin, int sclk_pin, int mosi_pin);

      unsigned char readRegister(unsigned char reg);

      void writeRegister(unsigned char reg, unsigned char value);

      Motion readMotion();

    private:
      int m_ncsPin;
      int m_misoPin;
      int m_sclkPin;
      int m_mosiPin;


      inline void writeByte(unsigned char reg);
      inline unsigned char readByte();
  };

#endif
