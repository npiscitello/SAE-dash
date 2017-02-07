// To talk to the MAX7221 driver
#include "LedControl.h"

/*  Set up MAX7221 object
 *  pin 12: data
 *  pin 13: clock
 *  pin 11: chip select
 *  There is only one MAX7221 attached */
LedControl dashboard(12, 13, 11, 1);

void setup() {
  // wake up the chip and increase brightness
  dashboard.shutdown(0, false);
  dashboard.setIntensity(0, 8);
  
  // turn on every LED
  for( int i = 0; i < 8; i++ ) {
    dashboard.setRow(0, i, 0xFF);
  }
}

void loop() {}
