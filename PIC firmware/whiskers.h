/*                      _    _ _     _     _                 
 *                     | |  | | |   (_)   | |                
 *                     | |  | | |__  _ ___| | _____ _ __ ___ 
 *                     | |/\| | '_ \| / __| |/ / _ \ '__/ __|
 *                     \  /\  / | | | \__ \   <  __/ |  \__ \
 *                      \/  \/|_| |_|_|___/_|\_\___|_|  |___/
 *
 * File:   whiskers.h
 * Author: Broderick Carlin
 *
 * This file is responsible for returning the values seen by the two whiskers
 * that are mounted on the front two corners of the robot's chassis. These
 * whiskers are used as a secondary method of object avoidance that relies on
 * physical contact with objects. Upon collision with an object, the functions
 * provided can be used to control the control flow to compensate for the error.
 * It is the hope that these whiskers are never used, however they will act be
 * active at all times as a double check against other less robust object
 * avoidance methods. The whiskers are a polled I/O and are not interrupt driven
 * this was done to save external interrupt capabilities for more time critical
 * tasks such as drive train encoders.
 *
 * -------------------------------Function List---------------------------------
 * void whiskers_init()
 * char whiskers_pollLeft()
 * char whiskers_pollRight()
 *
 *
 * ---------------------------Function Descriptions-----------------------------
 * void whiskers_init()
 *      This function is responsible for intializing the pins used by the two
 *      whiskers as well as configuring internal pull up resistors for the
 *      inputs. This function must be called before any other functions in this
 *      file can be reliably used. Nothing is returned by this function.
 *
 * char whiskers_pollLeft()
 * char whiskers_pollRight()
 *      These function returns a 0x00 or 0x01 to signify if the corresponding
 *      whisker is currently being pressed. A return value of 0x00 corresponds
 *      to the whisker NOT being pressed, while a return value of 0x01
 *      corresponds to the whisker currently being pressed.
 
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

#ifndef WHISKERS_H
#define	WHISKERS_H

    void whiskers_init();
    char whiskers_pollLeft();
    char whiskers_pollRight();

#endif

