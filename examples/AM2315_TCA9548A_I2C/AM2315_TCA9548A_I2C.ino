/*
  Test setup for WEMOS D1 Mini (ESP8266), two TCA9548As (8-Channel I2C Switch Module) and  AM2315

  --------------------------------------------------------------------------------------------------------
  WEMOS D1 Mini          TCA9548A         AM2315#1              AM2315#2            Supply
  --------------------------------------------------------------------------------------------------------
  D2 (SDA)               SDA                                                        4.7 k Pull-Up Resistor
  D1 (SCL)               SCL                                                        4.7 k Pull-Up Resistor
                         VIN              Red (VDD)           Red (VDD)             +3.3
  GND                    GND              Black (GND)         Black (GND)           GND
                         SD0              Yelloow (SDA)                             4.7 k Pull-Up Resistor
                         SC0              White (SCL)                               4.7 k Pull-Up Resistor
                         SD1                                  Yelloow (SDA)         4.7 k Pull-Up Resistor
                         SC1                                  White (SCL)           4.7 k Pull-Up Resistor
*/

#include "Wire.h"
#include <AM2315_I2C.h>

//ESP8266 I2C Pins
const uint8_t dataPin = D2;
const uint8_t  clockPin = D1;

#define MUX_Address 0x70 // TCA9548A I2C address

AM2315_I2C am2315;

void setup() {

  Serial.begin(115200);

  Wire.pins(dataPin, clockPin);

  delay(100);

  Serial.println();

  selectI2CChannels(0);

  am2315.begin(dataPin, clockPin);

  if (!am2315.dataReady)
    Serial.println("Sensor 0 was not found");
  else
    Serial.println("Sensor 0 is OK");

  selectI2CChannels(1);

  am2315.begin(dataPin, clockPin);

  if (!am2315.dataReady)
    Serial.println("Sensor 1 was not found");
  else
    Serial.println("Sensor 1 is OK");
}

void selectI2CChannels(uint8_t i) {
  if (i > 7) return;
  Wire.pins(dataPin, clockPin);
  Wire.begin(dataPin, clockPin);
  Wire.beginTransmission(MUX_Address);
  Wire.write(1 << i);
  Wire.endTransmission();
  delayMicroseconds(2000);
}

void loop() {

  //Non-blocking data reading
  selectI2CChannels(0);
  am2315.acquireData();

  if (am2315.dataReady) {

    Serial.print("Humidity 0: ");
    Serial.println(am2315.humidity());
    Serial.print("Temperature 0: ");
    Serial.println(am2315.temperature());
    Serial.println();

  } else {
    Serial.println("Sensor 0 Failed!");
    Serial.println();
  }


  selectI2CChannels(1);
  am2315.acquireData();

  if (am2315.dataReady) {

    Serial.print("Humidity 1: ");
    Serial.println(am2315.humidity());
    Serial.print("Temperature 1: ");
    Serial.println(am2315.temperature());
    Serial.println();

  } else {
    Serial.println("Sesor 1 Failed!");
    Serial.println();
  }


}
