# ADNS3

This library provides support for ADNS-3xxx optical mouse sensors.
For now it works with ADNS-3030/3040 and maybe with others if you are lucky.
I'll add more support if I have time but feel free to contribute.

## Exemple

In this setup, pins 1, 2, 3, 4 of an ADNS-3030 have been connected to pins 2, 3, 4, 5
of the arduino. The ADNS is powered with 3.3v and all grounds are properly connected (see datasheet).
Arduino's output pins are adapted to ADNS's input voltage thanks to three voltage dividers.
```
      Gnd|---+--+--+
             |  |  |
            | || || | 3x 2k
            | || || |
-----+       |  |  |  +------+
    2|--===--|--|--+--|1     |
    3|-------|--|-----|2     |
    4|--===--|--+-----|3     |
    5|--===--+--------|4     |
     | 3x 1k          +------+
Arduino               ADNS3030
```


```C
#include "ADNS3.h"

/* Creates an instance on pins 2, 3, 4, 5 */
ADNS3 myMouse = ADNS3(2, 3, 4, 5);

void setup() {
  Serial.begin(9600);
}

void loop() {
  /* Gets a new motion report (uses "motion burst") */
  ADNS3::Motion motion = myMouse.readMotion();

  /* Prints out values for this report */
  Serial.print("dx: ");
  Serial.print(motion.deltaX, DEC);
  Serial.print(", dy: ");
  Serial.print(motion.deltaY, DEC);
  Serial.print(", quality: ");
  Serial.println(motion.squal, DEC);

  delay(1000);
}
```

Alternatively, one can access registers directly using `readRegister(reg)` and `writeRegister(reg)`

The .ino sketch provides a working example.
