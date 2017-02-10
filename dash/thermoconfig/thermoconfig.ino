/*  This file is used to configure the IR Thermometer for the first time.
 *  It requires a special pin config between the thermometer and the Arduino;
 *  it will not work with the thermometer mounted in its standard location. */

/*  Pin Assignments:
 *  Thermometer <-> Arduino
 *            1 <-> A5
 *            2 <-> A4
 *            3 <-> 3V3
 *            4 <-> GND
 */

// the factory default slave address
#define ADDRESS 0x5A

#include <Wire.h>

void setup() {
  // set up pins and libs
  pinMode(13, OUTPUT);
  Wire.begin();

  // max temp 200C (~400F)
  Wire.beginTransmission(ADDRESS);
    Wire.write(0x00);
    Wire.write(0xD3);
    Wire.write(0xB8);
  Wire.endTransmission();
  
  // min temp 10C (~50F)
  Wire.beginTransmission(ADDRESS);
    Wire.write(0x01);
    Wire.write(0x9B);
    Wire.write(0x6E);
  Wire.endTransmission();
  
  // RMW ConfigRegister1
  Wire.beginTransmission(ADDRESS);
    Wire.write(0x05);
  Wire.endTransmission();
  uint8_t high = 0x00, low = 0x00;
  Wire.requestFrom(ADDRESS, 2);
    low = Wire.read();
    high = Wire.read();
  if( low == 0x00 || high == 0x00 ) {
    digitalWrite(13, HIGH);
    return;
  }
  low |= 0x30;
  Wire.beginTransmission(ADDRESS);
    Wire.write(0x05);
    Wire.write(low);
    Wire.write(high);
  Wire.endTransmission();
  
  // set PWMCTL
  Wire.beginTransmission(ADDRESS);
    // EEPROM address to write (PWMCTL)
    Wire.write(0x02);
    // PWMCTL 7:0
    Wire.write(0x07);
    // PWMCTL 15:8
    Wire.write(0x02);
  Wire.endTransmission();
}

void loop() {}
