/*                    _____                    _
                     |  ___|                  | |
                     | |__ _ __   ___ ___   __| | ___ _ __ ___
                     |  __| '_ \ / __/ _ \ / _` |/ _ \ '__/ __|
                     | |__| | | | (_| (_) | (_| |  __/ |  \__ \
                     \____/_| |_|\___\___/ \__,_|\___|_|  |___/

 * File:   encoders.h
 * Author: Broderick Carlin
 *
 * This file is responsible for all the functions related to the encoders that
 * are positioned on the motor shafts. These functions can be used to monitor 
 * the rotation of the motor shafts which coorelates to the rotation of the 
 * wheels. From this information, it is possible to derive position, velocity,
 * and acceleration.
 *
 * -------------------------------Function List---------------------------------
 * void encoders_init();
 * long encoders_readLeft();
 * long encoders_peakLeft();
 * long encoders_readRight();
 * long encoders_peakRight();
 * void encoders_clear();
 * void interrupt low_priority encoderInterrupt();
 *
 *
 * ---------------------------Function Descriptions-----------------------------
 * void encoders_init()
 *      This function is required to configure all the external I/O as well as
 *      the internal PPS connection for the external interrupt pins. It is
 *      important that this function is called before all any other function
 *      that relate to the encoders.
 *
 * long encoders_readLeft()
 * long encoders_readRight()
 *      These functions return the number of steps taken by the motor since the
 *      last read of the function. The sign of the returned number indicates the
 *      direction of the steps (ie. CW or CCW). It is important to remember that
 *      encoders_init() must be called prior to this function, otherwise this
 *      function will not return any valid data.
 *
 * long encoders_peakLeft()
 * long encoders_peakRight()
 *      These functions return the number of steps taken by the motor. Unlike
 *      the simliarly named *_readLeft() and *_readRight() functions, these do
 *      not clear the count after reading the value. the sign of the returned
 *      number indicates the direction of the steps( ie. CW or CCW). It is
 *      important to remember that encoders_init() must be called prior to this
 *      function, otherwise this function will not return any valid data.
 *
 * void encoders_clear()
 *      This function resets both encoder counters. It is important to note that
 *      any step information gathered will be lost after this function is called
 *
 * void interrupt low_priority encoderInterrupt()
 *      This function is called whenever there one of the encoders sends an edge
 *      to the PIC. It is important to note that no other peripherals use the
 *      low priority interrupts. Because this interrupt happens very often it
 *      has been created as low priority so that more important tasks can take
 *      control through a high priority interrupt if need be. 

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

#include <xc.h>
#include "GlobalDefines.h"

#ifndef ENCODERS_H
#define	ENCODERS_H

    void encoders_init();
    long encoders_readLeft();
    long encoders_peakLeft();
    long encoders_readRight();
    long encoders_peakRight();
    void encoders_clear();
    void interrupt low_priority encoderInterrupt();

#endif

