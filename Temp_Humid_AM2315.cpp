/*
 * AM2315 Temperature and Humidity Sensor I2C library for Arduino
 * 
 * This library provides microcontroller to read data from Aosong Digital Temperature
 * and Humidity through I2C interface. 
 * 
 * The library was also work well with AM2315 compatible sensors and WEMOS D1 Mini (ESP8266) using
 * the Arduino's standard I2C library.
 * 
 * The MIT License (MIT)
 * Copyright (c) 2018 K. Suwatchai (Mobizt)
 * 
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "Temp_Humid_AM2315.h"

Temp_Humid_AM2315::Temp_Humid_AM2315() {}

boolean Temp_Humid_AM2315::begin(uint8_t dataPin, uint8_t clockPin) {

  Wire.setClock(400000L);
  Wire.begin(dataPin, clockPin);
  acquireData();
  return dataReady;

}

void Temp_Humid_AM2315::acquireData(void) {

  dataReady = false;
  uint8_t regData[6];
  uint8_t totalReg = 4;

  //Wake up
  Wire.beginTransmission(AM2315_I2CADDR);
  Wire.endTransmission();

  //Send the data request
  Wire.beginTransmission(AM2315_I2CADDR);
  Wire.write(AM2315_READREG);
  Wire.write(0x00);  //reg address offset
  Wire.write(totalReg);  //number of reg to read
  Wire.endTransmission();
  delayMicroseconds(800);

  Wire.requestFrom(AM2315_I2CADDR, totalReg + 2);

  for (uint8_t i = 0; i < totalReg + 2; i++)
    regData[i] = Wire.read();


  if (regData[0] == AM2315_READREG && regData[1] == totalReg) {

    _dataUnion.byteData[0] = regData[3];
    _dataUnion.byteData[1] = regData[2];
    _humid = (float)_dataUnion.uint16Data / 10;

    _dataUnion.byteData[0] = regData[5];
    _dataUnion.byteData[1] = regData[4];
    _temp = (float)_dataUnion.uint16Data / 10;

    dataReady = true;

  }

}


float Temp_Humid_AM2315::temperature(void) {
  if (!dataReady) return NAN;
  return _temp;
}

float Temp_Humid_AM2315::humidity(void) {
  if (!dataReady) return NAN;
  return _humid;
}


