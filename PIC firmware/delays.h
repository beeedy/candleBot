/*                      ______     _
                        |  _  \   | |
                        | | | |___| | __ _ _   _ ___
                        | | | / _ \ |/ _` | | | / __|
                        | |/ /  __/ | (_| | |_| \__ \
                        |___/ \___|_|\__,_|\__, |___/
                                            __/ |
                                           |___/
 * File:   delays.h
 * Author: Broderick Carlin
 *
 * This file is responsible for handling all delays neccessary by other
 * functions in the conrol flow. This file contains functions that themselves
 * provide an accurate calibrated delay while also providing functions to timers
 * that have been calibrated to provide highly accurate feedback of the time the
 * software has been running.
 *
 * -------------------------------Function List---------------------------------
 * void delay_init();
 * void delay_us(long);
 * void delay_ms(long);
 * void delay_s(long);
 * unsigned long millis();
 * void clearMillis();
 * void tickMillis();
 *
 *
 * ---------------------------Function Descriptions-----------------------------
 * void delay_init()
 *      This function ilitializes timer 0 to be used as the highly accuate timer
 *      that keeps track of the actual time the program has been running. It is
 *      important that this function is called before any other delay function
 *      otherwise the user risks getting caught in an infinte loop. It is also
 *      important to note that the timer functions will not return valid data
 *      until after this function has returned.
 *
 * void delay_us(long)
 *      This function provides an alternative to the built in uS delay function.
 *      It is important to note that this function is highly innaccurate for
 *      longer delays and should only be used for delays that are less than
 *      20uS. Any delays longer than that will require some playing with the
 *      values to achieve the delay that is desired.
 *
 * void delay_ms(long)
 *      This function provides the user with a very accurate mS delay that is
 *      accurate within a couple mS over an hour long period. It is important
 *      to note that this function will get caught in an infinite loop unless
 *      delay_init() is called once prior.
 *
 * void delay_s(long)
 *      This function provides the user with a very accurate S delay that is
 *      accurate within a couple seconds over a 5 hour long period. It is
 *      important to note that this function will get caught in an infinite
 *      loop unless delay_init() is called once prior.
 *
 * unsigned long millis()
 *      This function provides the user with a very accurate mS count that
 *      indicates how much time has elapsed since the timer was initialized.
 *      This timer does not take any inputs and is accurate within a couple mS
 *      over an hour long period. For those familiar with the Arduino series, 
 *      this function works in the same way as that found within the Arduino IDE
 *      It is important to note that this functino will not return valid data 
 *      unless delay_init() is called prior.
 *
 * void clearMillis()
 *      This function can be called to return the millis() counter to zero. This
 *      is usefull for creating a highly accurate timer that begins at a
 *      designated time rather than the first initialization. Calling this does
 *      not affect any of the other delay functions.
 *
 * void tickMillis()
 *      This function increments the millis() counter. It is very important that
 *      this function is NEVER called by the user as it is intended to only be
 *      used by the operating system. Any calls made to this by the user will
 *      negatively effect the accuracy of all the timer.

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

#ifndef DELAYS_H
#define	DELAYS_H

// This value is a calibrated start point for timer 0 so that it overflows after
// exactly 1mS. If any changes are made to the system clock, this will need to
// be recalibrated to compensate and verify the accuracy of all timers.
#define millisStart 193

    void delay_init();
    void delay_us(long);
    void delay_ms(long);
    void delay_s(long);
    void delay_startCount();
    unsigned long millis();
    void clearMillis();
    void tickMillis();

#endif

