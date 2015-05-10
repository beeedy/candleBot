/*                         _____ _       _           _
                          |  __ \ |     | |         | |
                          | |  \/ | ___ | |__   __ _| |
                          | | __| |/ _ \| '_ \ / _` | |
                          | |_\ \ | (_) | |_) | (_| | |
                           \____/_|\___/|_.__/ \__,_|_|
                        ______      __ _
                        |  _  \    / _(_)
                        | | | |___| |_ _ _ __   ___  ___
                        | | | / _ \  _| | '_ \ / _ \/ __|
                        | |/ /  __/ | | | | | |  __/\__ \
                        |___/ \___|_| |_|_| |_|\___||___/

 * File:   GlobalDefines.h
 * Author: Tyler Holmes
 *
 * This file is responsible for delaring various #defines that are to be used
 * throughout the various files in this project. This includes global constants,
 * device addresses, and inline functions. This file should contain no compiled
 * functions or variables.
 *
 * All titles are created using http://patorjk.com/software/taag/ with font DOOM

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

#ifndef GLOBALDEFINES_H
#define	GLOBALDEFINES_H

// I2C addresses for various devices
#define WII_CAM_ADR        0xB0
// #define WII_CAM_SLAVE_ADR  0x21
#define COMPASS_ADR        0x3C
#define COLOR_SENSOR_ADR   0x52 /* 0x29 <- non shifted version */

    // The folowing sensors are on the following I2C lines
#define COMPASS_PIXY  1
#define WII_CAM_RIGHT 1
#define WII_CAM_LEFT  2
#define COMPASS_MAIN  2
#define COLOR_SENSOR  2

#define READ_CLEAR 1
#define READ_COLOR 2
#define READ_CLEAR_AND_COLOR 3
#define READ_COLOR_AND_CLEAR 3

#define ACK 1
#define NAK 0


#define FONA_BUFF_SIZE 50
#define PIXY_BUFF_SIZE 500
#define USB_BUFF_SIZE 500

#define _XTAL_FREQ 64000000


// Macros for various simple actions
#define MAX(x,y)    ((x > y) ? x : y)
#define MIN(x,y)    ((x < y) ? x : y)
#define ABS(x)      ((x < 0) ? (x*-1) : x)
#define bitSet(x,y) x |= (0x1 << y);

#define disablePPSLock() IOLOCK = 0
#define enablePPSLock() IOLOCK = 1
#define disableInterrupts() GIE = 0
#define enableInterrupts() GIE = 1

#endif

