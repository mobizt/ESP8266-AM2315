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

#ifndef TEMP_HUMID_AM2315_H
#define TEMP_HUMID_AM2315_H

#include "Arduino.h"
#include "Wire.h"

#define AM2315_I2CADDR       0x5C //I2C address 0xB8 (1011 1000) turns to 7-bit address 0x5c (101 1100)
#define AM2315_READREG       0x03


typedef union {
  byte byteData [2];
  uint16_t uint16Data;
} dataUnion;


class Temp_Humid_AM2315 {
  public:
    Temp_Humid_AM2315();
    boolean begin(uint8_t dataPin, uint8_t clockPin);
    void acquireData(void);
    float temperature(void);
    float humidity(void);
    bool dataReady;

  private:
    float _humid, _temp;
    dataUnion _dataUnion;
};

#endif