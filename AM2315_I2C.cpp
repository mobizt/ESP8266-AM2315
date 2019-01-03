/*
   AM2315 Temperature and Humidity Sensor I2C library for Arduino

   This library provides microcontroller to read data from Aosong Digital Temperature
   and Humidity sensor through I2C interface with non-blocking operation.

   The library was also work well with AM2315 compatible sensors and WEMOS D1 Mini (ESP8266) using
   the Arduino's standard I2C library.

   The MIT License (MIT)
   Copyright (c) 2018 K. Suwatchai (Mobizt)


   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
   the Software, and to permit persons to whom the Software is furnished to do so,
   subject to the following conditions:

   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
   FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
   COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
   IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "AM2315_I2C.h"

AM2315_I2C::AM2315_I2C() {}

void AM2315_I2C::begin(uint8_t dataPin, uint8_t clockPin) {

  Wire.setClock(400000L); //Set rate to 400 kbps
  Wire.begin(dataPin, clockPin);
  delayMicroseconds(2000);
  acquireData();

}

void AM2315_I2C::acquireData() {

  dataReady = false;
  
  uint8_t totalReg = 4;
  uint8_t regData[totalReg + 2];

  //Wake up
  Wire.beginTransmission(AM2315_I2C_ADDR);
  Wire.write(AM2315_READ_REG);
  Wire.endTransmission();
  delayMicroseconds(2000);

  //Send the data request
  Wire.beginTransmission(AM2315_I2C_ADDR);
  Wire.write(AM2315_READ_REG);
  Wire.write(0x00);  //Reg address offset
  Wire.write(totalReg);  //Number of reg to read
  Wire.endTransmission();
  delayMicroseconds(2000);



  Wire.requestFrom(AM2315_I2C_ADDR, totalReg + 2);

  for (uint8_t i = 0; i < totalReg + 2; i++)
    regData[i] = Wire.read();


  if (regData[0] == AM2315_READ_REG && regData[1] == totalReg) {


    _dataUnion.byteData[0] = regData[3];
    _dataUnion.byteData[1] = regData[2];
    _humid = (float)_dataUnion.uint16Data / 10;

    _dataUnion.byteData[0] = regData[5];
    _dataUnion.byteData[1] = regData[4] & 0x7f;
    _temp = (float)_dataUnion.uint16Data / 10;
    if (regData[4] & 0x80) _temp *= -1; //If bit 15 is set, give the negative temp value

    dataReady = true;

  }

}


float AM2315_I2C::temperature() {
  if (!dataReady) return NAN;
  return _temp;
}

float AM2315_I2C::humidity() {
  if (!dataReady) return NAN;
  return _humid;
}
