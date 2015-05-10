/*          _____       _              _____
           /  __ \     | |            /  ___|
           | /  \/ ___ | | ___  _ __  \ `--.  ___ _ __  ___  ___  _ __
           | |    / _ \| |/ _ \| '__|  `--. \/ _ \ '_ \/ __|/ _ \| '__|
           | \__/\ (_) | | (_) | |    /\__/ /  __/ | | \__ \ (_) | |
            \____/\___/|_|\___/|_|    \____/ \___|_| |_|___/\___/|_|

 * File:   colorSensor.h
 * Author: Tyler Holmes
 *
 * This file contains the functions that are used to  interface with our color
 * (RGBC) sensor, PN:TCS3472. Our color sensor is mounted on the bottom of our
 * robot and is used to determine the color of the flooring under the front of
 * our robot for the specifc purpose of locating the white circle that surrounds
 * a candle. The color sensor can be thought of as a simple single pixel camera.
 *
 * I2C Address: 0x29
 *
 * -------------------------------Function List---------------------------------
 * signed char colorSensor_init()
 * signed char colorSensor_read(unsigned char readType, signed char *retVals)
 *
 * ---------------------------Function Descriptions-----------------------------
 * signed char colorSensor_init()
 *      This function initializes the color sensor so that it can be used to
 *      gather information in regards to the color of the flooring. This
 *      function configures the color sensor to have a 24mS integration time,
 *      not to wait, and to have a gain of x4. It is important that this
 *      function be called prior to trying to communicate with the color sensor,
 *      otherwise unpredictable behvior may occur.
 *
 * signed char colorSensor_read(unsigned char readType, signed char *retVals)
 *      This function reads out either the clear value or the color values that
 *      are being read by the sensor. Depending on what you pass to the function
 *      as your first argument, it will store the corresponding values in the
 *      array pointed to by your second argument. It is important to remember
 *      that colorSensor_init() must be called prior to this function to verify
 *      that the results that are recieved is valid information.
 *
 *
 * -------------------------------Command Table---------------------------------
 *  ??    COMMAND   W     Specifies register address                    0x00
 *  0x00  ENABLE    R/W   Enables states and interrupts                 0x00
 *  0x01  ATIME     R/W   RGBC time                                     0xFF
 *  0x03  WTIME     R/W   Wait time                                     0xFF
 *  0x04  AILTL     R/W   Clear interrupt low threshold low byte        0x00
 *  0x05  AILTH     R/W   Clear interrupt low threshold high byte       0x00
 *  0x06  AIHTL     R/W   Clear interrupt high threshold low byte       0x00
 *  0x07  AIHTH     R/W   Clear interrupt high threshold high byte      0x00
 *  0x0C  PERS      R/W   Interrupt persistence filter                  0x00
 *  0x0D  CONFIG    R/W   Configuration                                 0x00
 *  0x0F  CONTROL   R/W   Control                                       0x00
 *  0x12  ID        R     Device ID ID
 *  0x13  STATUS    R     Device status                                 0x00
 *  0x14  CDATAL    R     Clear data low byte                           0x00
 *  0x15  CDATAH    R     Clear data high byte                          0x00
 *  0x16  RDATAL    R     Red data low byte                             0x00
 *  0x17  RDATAH    R     Red data high byte                            0x00
 *  0x18  GDATAL    R     Green data low byte                           0x00
 *  0x19  GDATAH    R     Green data high byte                          0x00
 *  0x1A  BDATAL    R     Blue data low byte                            0x00
 *  0x1B  BDATAH    R     Blue data high byte                           0x00

Copyright (c) 2015 Broderick Carlin & Tyler Holmes

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

#ifndef COLORSENSOR_H
#define	COLORSENSOR_H

#include "globalDefines.h"

signed char colorSensor_init();
signed char colorSensor_read(unsigned char readType, signed char *retVals);

#endif

