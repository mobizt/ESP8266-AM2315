/*
  Test setup for WEMOS D1 Mini (ESP8266) and AM2315

  ---------------------------------------------------------------------------------
  WEMOS D1 Mini          AM2315                  Supply
  ---------------------------------------------------------------------------------
  D2 (SDA)               Yelloow (SDA)           4.7 k Pull-Up Resistor
  D1 (SCL)               White (SCL)             4.7 k Pull-Up Resistor
                         Red (VDD)               +3.3
  GND                    Black (GND)             GND

*/


#include <AM2315_I2C.h>

//ESP8266 I2C Pins
const uint8_t dataPin = D2;
const uint8_t  clockPin = D1;

AM2315_I2C am2315;

void setup() {
  Serial.begin(115200);

  Wire.pins(dataPin, clockPin);

  delay(100);

  Serial.println();

  am2315.begin(dataPin, clockPin);

  if (!am2315.dataReady)
    Serial.println("AM2315 sensor was not found");
  else
    Serial.println("AM2315 sensor is ready");

}

void loop() {

  //Non-blocking data reading
  am2315.acquireData();

  if (am2315.dataReady) {

    Serial.print("Humidity: ");
    Serial.println(am2315.humidity());
    Serial.print("Temperature: ");
    Serial.println(am2315.temperature());
    Serial.println();

  }

}
