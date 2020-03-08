/**************************************************************************/
/*!
  @file     Adafruit_DRV8830.cpp

  @mainpage Adafruit DRV8830 I2C motor driver

  @section intro Introduction

  This is a library for the Adafruit DRV8830 I2C motor driver
  ----> http://www.adafruit.com/products/4558

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  @section author Author

  Limor Fied (Adafruit Industries)

  @section license License

  BSD (see license.txt)
*/
/**************************************************************************/
#include "Adafruit_DRV8830.h"

/**************************************************************************/
/*!
    @brief  Instantiates a new DRV8830 class
*/
/**************************************************************************/
Adafruit_DRV8830::Adafruit_DRV8830() {}

/**************************************************************************/
/*!
    @brief  Sets up the I2C connection and tests that the sensor was found.
    @param theWire Pointer to an I2C device we'll use to communicate
    default is Wire
    @return true if sensor was found, otherwise false.
*/
/**************************************************************************/
bool Adafruit_DRV8830::begin(uint8_t addr, TwoWire *theWire) {
  if (i2c_dev) {
    delete i2c_dev;
  }
  i2c_dev = new Adafruit_I2CDevice(addr, theWire);

  /* Try to instantiate the I2C device. */
  if (!i2c_dev->begin()) {
    return false;
  }

  // define the main power control register
  ctrl_reg = new Adafruit_I2CRegister(i2c_dev, DRV8830_CONTROL);
  fault_reg = new Adafruit_I2CRegister(i2c_dev, DRV8830_FAULT);

  return true;
}


bool Adafruit_DRV8830::setSpeed(uint8_t throttle) {
  throttle = map(throttle, 0, 255, 0x06, 0x3F);
  Adafruit_I2CRegisterBits dac =
      Adafruit_I2CRegisterBits(ctrl_reg, 6, 2); // # bits, bit_shift
  return dac.write(throttle);
}


bool Adafruit_DRV8830::run(DRV8830_Direction direction) {
  Adafruit_I2CRegisterBits dirbits =
      Adafruit_I2CRegisterBits(ctrl_reg, 2, 0); // # bits, bit_shift
  return dirbits.write((uint8_t) direction);
}
