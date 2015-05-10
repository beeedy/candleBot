/*                       _   _  ___  ______ _____
                        | | | |/ _ \ | ___ \_   _|
                        | | | / /_\ \| |_/ / | |
                        | | | |  _  ||    /  | |
                        | |_| | | | || |\ \  | |
                         \___/\_| |_/\_| \_| \_/
 * File:   UART.h
 * Author: Tyler Holmes and Broderick Carlin
 *
 * -------------------------------Function List---------------------------------
 * void UART_init(void)
 * void UART_transmitByte(transmitType_t, char)
 * void UART_transmitString(transmitType_t, char[], ...)
 *
 * ---------------------------Function Descriptions-----------------------------
 * void UART_init(void)
 *      This function is used to initialize all of the UART modules that are
 *      used by the various external peripherals. It is important to note that
 *      because of error in the circuitry, all 4 UART modules are used, and the
 *      RX and TX lines of all 4 UART modules are split up between seperate
 *      devices. All 4 modules are configured to operate at 115200 BAUD and as
 *      such there is no ill effects of this configuration. This function must
 *      be called before there can be any communication through any of the UART
 *      modules.
 *
 * void UART_transmitByte(transmitType_t, char)
 *      This function is used to transmit a single byte to a specified device
 *      over a UART connection. The first argument is the device that is desired
 *      and the second argument is the byte of information that needs to be
 *      transmitted to this device. It is important that UART_init() is called
 *      prior to this function in order to avoid unpredictable behavior.
 *
 * void UART_transmitString(transmitType_t, char[], ...)
 *      This function prints out a string to UART using a similar syntax to
 *      the popular printf() statement used in ANSI C. The first argument is the
 *      device that is desired and the second argument is the string to be
 *      printed in the form of a null terminated char array. If the character
 *      pair "%i" appear in the string, any integer arguments following the
 *      string will be inserted into the string, with the first integer argument
 *      going to the first "%i" and the rest following respectively. This
 *      function supports any formatting characters. such as: \n \t \r etc.

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

#ifndef UART_H
#define	UART_H

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <xc.h>
#include "GlobalDefines.h"

    typedef enum {
            FONA,
            USB,
            PIXY
    }transmitType_t;

    void UART_init(void);
    void UART_transmitByte(transmitType_t transmitType, char data);
    void UART_transmitString(transmitType_t transmitType, char[], ...);


#endif

