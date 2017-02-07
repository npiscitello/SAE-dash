// To talk to the MAX7221 driver
#include "LedControl.h"

/*  Set up MAX7221 object
 *  pin 12: data
 *  pin 13: clock
 *  pin 11: chip select
 *  There is only one MAX7221 attached */
LedControl dashboard(12, 13, 11, 1);

// what to write to the LED row
uint8_t led = 0x00;

void setup() {
  // wake up the chip and increase brightness
  dashboard.shutdown(0, false);
  dashboard.setIntensity(0, 8);
}

void loop() {
  // <MSB> P A B C D E F G <LSB>
  // turn on every LED in order
  for(int i = 0; i < 8; i++) {
    led = 0x00;
    for(int j = 0; j < 8; j++) {
      led = (led >> 1) | 0x80;
      dashboard.setRow(0, i, led);
      delay(75);
    }
  }

  // allow all to revel in the glory of the One True Dashboard
  delay(2000);

  // turn off every LED in order
  for(int i = 7; i >= 0; i--) {
    led = 0xFF;
    for(int j = 7; j >= 0; j--) {
      led = led << 1;
      dashboard.setRow(0, i, led);
      delay(75);
    }
  }

  // allow all to quiver in antici...
  // ...pation!
  delay(2000);
}

