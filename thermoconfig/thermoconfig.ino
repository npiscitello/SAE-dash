/*  This file is used to configure the IR Thermometer for the first time.
 *  It requires a special pin config between the thermometer and the Arduino;
 *  it will not work with the thermometer mounted in its standard location.
 *  This depends on a modified version of the SparkFun library included below;
 *  it will not compile with the downloadable version. The modified source is
 *  included in this sketch.
  */

/*  Pin Assignments:
 *  Thermometer <-> Arduino
 *            1 <-> A5
 *            2 <-> A4
 *            3 <-> 3V3
 *            4 <-> GND
 */

/*  Default Register Values
 *  ToMIN: 0x62E3
 *  ToMAX: 0x9993
 *  PWMCTRL: 0x0201
 *  CONFIG: 0x9FB4
 *  
 *  New Register Values
 *  ToMIN: 0x6E9B
 *  ToMAX: 0xB8D3
 *  PWMCTRL: 0x0207
 *  CONFIG: 0x9FB4 (unchanged)
 */

#include "SparkFunMLX90614.h"

// thermometer object
IRTherm therm;

// storage for read/write data
uint16_t data;

void setup() {
  // set up pins and libs
  pinMode(13, OUTPUT);
  therm.begin();
  Serial.begin(9600);

  Serial.println("Pre-write:");
  therm.readEEPROM(MLX90614_REGISTER_TOMIN, &data);
  Serial.print("  ToMIN: ");
  Serial.println(data, HEX);
  therm.readEEPROM(MLX90614_REGISTER_TOMAX, &data);
  Serial.print("  ToMAX: ");
  Serial.println(data, HEX);
  therm.readEEPROM(MLX90614_REGISTER_PWMCTRL, &data);
  Serial.print("  PWMCTRL: ");
  Serial.println(data, HEX);
  therm.readEEPROM(MLX90614_REGISTER_CONFIG, &data);
  Serial.print("  CONFIG: ");
  Serial.println(data, HEX);

  Serial.println("Writing...");
  therm.writeEEPROM(MLX90614_REGISTER_TOMIN, 0x6E9B);
  therm.writeEEPROM(MLX90614_REGISTER_TOMAX, 0xB8D3);
  therm.writeEEPROM(MLX90614_REGISTER_PWMCTRL, 0x0207);
  // Config reg is set as needed; I'd rather not mess with it
  
  Serial.println("Post-write:");
  therm.readEEPROM(MLX90614_REGISTER_TOMIN, &data);
  Serial.print("  ToMIN: ");
  Serial.println(data, HEX);
  therm.readEEPROM(MLX90614_REGISTER_TOMAX, &data);
  Serial.print("  ToMAX: ");
  Serial.println(data, HEX);
  therm.readEEPROM(MLX90614_REGISTER_PWMCTRL, &data);
  Serial.print("  PWMCTRL: ");
  Serial.println(data, HEX);
  therm.readEEPROM(MLX90614_REGISTER_CONFIG, &data);
  Serial.print("  CONFIG: ");
  Serial.println(data, HEX);
}

void loop() {}
