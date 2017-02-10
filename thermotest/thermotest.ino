/*  This sketch tests the IR thermometer on a breadboard 
 *  to make sure it works over PWM. Keep in mind, the sensor
 *  is calibrated to read between 50*F and 400*F (10*C - 200*C).
 */

/*  Pin Assignments:
 *  Thermometer <-> Arduino
 *            1 <-> A5
 *            2 <-> A4
 *            3 <-> 3V3
 *            4 <-> GND
 */

/*  There must be a filter on the PWM output of the thermometer!
 *  PWM is coupled to ground through a resistor and capacitor, with
 *  the ADC reading the voltage across the cap.
 *  PWM --- RES -.- CAP --- GND
 *               | 
 *              ADC
 */

void setup() {
  Serial.begin(9600);
  Serial.println("Starting...");
}

float alpha = 0.7; // factor to tune
float value;// = alpha * measurement + (1-alpha) * value;
float volt;
void loop() {
  // take a running average, display every 1000th measurement
  for(int i = 0; i < 1000; i++) {
    value = alpha * analogRead(4) + (1 - alpha) * value;
  }
  volt = value * 3.3 / 1023;
  Serial.print("Voltage: ");
  Serial.print(volt);
  Serial.print(", Temp *F: ");
  // .4125V = 50F, 2.0625V = 400F
  // also, .4125V = 10C, 2.0625V = 200C
  // the below basically maps the value from the voltage to the temp range
  Serial.println((volt - 0.4125) * (400.0 - 50.0) / (2.0625 - .4125) + 50);
}
