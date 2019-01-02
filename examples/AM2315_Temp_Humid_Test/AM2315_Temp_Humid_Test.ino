/*
  Test setup for WEMOS D1 Mini (ESP8266) and AM2315

  ---------------------------------------------------------------------------------
  WEMOS D1 Mini          AM2315                  Supply
  ---------------------------------------------------------------------------------
  D2 (Data)              Yelloow (SDA)           4.7 k Pull-Up Resistor
  D1 (Clock)             White (SCL)             4.7 k Pull-Up Resistor
                         Red (VDD)               +3.3
  GND                    Black (GND)             GND

*/


#include <Temp_Humid_AM2315.h>

//ESP8266 I2C Pins
const uint8_t dataPin = D2;
const uint8_t  clockPin = D1;

Temp_Humid_AM2315 am2315;

void setup() {
  Serial.begin(115200);

  Wire.pins(dataPin, clockPin);

  am2315.begin(dataPin, clockPin);

  if (!am2315.dataReady)
    Serial.println("Sensor not found");

}

void loop() {

  am2315.acquireData();

  if (am2315.dataReady) {

    Serial.print("Humidity: ");
    Serial.println(am2315.humidity());
    Serial.print("Temperature: ");
    Serial.println(am2315.temperature());
    Serial.println();

  }else{
    Serial.println("Failed!");
    Serial.println();
  }


  delay(500);
}
