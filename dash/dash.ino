// To talk to the MAX7221 driver
#include "LedControl.h"

/*  Set up MAX7221 object
 *  pin 12: data
 *  pin 13: clock
 *  pin 11: chip select
 *  There is only one MAX7221 attached 
 *  
 *  Mapping for setRow fuction:
 *  <MSB> P A B C D E F G <LSB> */
LedControl dashboard(12, 13, 11, 1);

void setup() {
  // wake up the chip
  dashboard.shutdown(0, false);

  // POST - turn everything on for a sec
  for(int i = 0; i < 8; i++) {
    dashboard.setRow(0, i, 0xFF);
  }

  // fade everything on (ooooh, ahhhhh)
  for(int i = 0; i <= 12; i++) {
    dashboard.setIntensity(0, i);
    delay(75);
  }
  delay(500);
}

void loop() {
  // make sure all the numbers work (bonus - show 'em on the dots, too!
  for(int i = 0; i <= 0x0F; i++) {
    for(int j = 0; j < 8; j++) {
      dashboard.setChar(0, j, i, false);
    }
    delay(500);
  }
}
