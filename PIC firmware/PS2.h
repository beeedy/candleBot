/*                          ______  _____  _____
                            | ___ \/  ___|/ __  \
                            | |_/ /\ `--. `' / /'
                            |  __/  `--. \  / /
                            | |    /\__/ /./ /___
                            \_|    \____/ \_____/
                        ______                     _
                        | ___ \                   | |
                        | |_/ /___ _ __ ___   ___ | |_ ___
                        |    // _ \ '_ ` _ \ / _ \| __/ _ \
                        | |\ \  __/ | | | | | (_) | ||  __/
                        \_| \_\___|_| |_| |_|\___/ \__\___|

 * File:   PS2.h
 * Author: Broderick Carlin
 *
 * This file contains functions that allow a PIC18F processor to natively talk
 * with any PlayStation remote through an onboard PS2 female connector. By
 * interfacing with a PS2 controller, we are able to add wireless remote control
 * capabilities using cheap and easily obtainable hardware to any procject that
 * is based around a PIC18F processor.
 *
 * -------------------------------Function List---------------------------------
 * char PS2_init()
 * void PS2_readGamepad()
 * void PS2_reconfig()
 * void PS2_sendCommandString(char string[], char)
 * char PS2_shiftInOut(char)
 * char PS2_readType()
 * char PS2_newButtons()
 * char PS2_newButtonState(unsigned int)
 * char PS2_buttonPressed(unsigned int)
 * char PS2_buttonReleased(unsigned int)
 * char PS2_button(unsigned int)
 * unsigned int PS2_buttonDataByte()
 * char PS2_analog(char)
 *
 * ---------------------------Function Descriptions-----------------------------
 * char PS2_init()
 *      This function must be called before any information can be gathered from
 *      the controller or before any communication can be attempted with the
 *      controller. This function attempts to establish communication with any
 *      remote connected and returns values coresponding to success or error's
 *      that may occur.
 *
 * void PS2_readGamepad()
 *      This function collects the values of all the interfaces on the remote
 *      such as button states and analog stick positions. It is important to
 *      make sure PS2_init() was called prior and that a sucessful response was
 *      recieved. This function does not return any values but rather stores all
 *      of its data in global variables that are accessable by other functions.
 *      It is also important to note this function is timing critical in terms
 *      of the time between calls. If the remote is not pinged enough it will
 *      cut the connection, and if the function is called too often the remote
 *      will also cut the connection. Safety measures have been taken so the
 *      function reacts to always satisfy timing constraints, and to reconnect
 *      if the device has timed out.
 *
 * void PS2_reconfig()
 *      This function is used by other functions to reestablish connection with
 *      the PS2 remote in case of a timeout. This function should NEVER be used
 *      by the user.
 *
 * void PS2_sendCommandString(char string[], char)
 *      This function is used by other functions to send a string to the remote
 *      currently connected. This function should NEVER be used by the user, as
 *      errors may occur unless predefined character arrays are sent to the
 *      remote.
 *
 * char PS2_shiftInOut(char)
 *      This function is used by other functions to shift information into and
 *      out of the connected controller. This function should NEVER be used by
 *      the user as errors will most likely result from use of this function.
 *
 * char PS2_readType()
 *      This function is used to return a value corresponding to the type of
 *      controller that is plugged into the PS2 female slot.
 *
 * char PS2_newButtons()
 *      This function is used to return the a 0x00 or 0x01 depending on if any
 *      buttons have been pressed or released between the last two readings from
 *      the gamepad. A 0x00 is returned if nothing has changed, and a 0x01 is
 *      returned if at least 1 button has changed states. This function just not
 *      specific which button may have changed, but rather that a button did
 *      actually change. A different function would need to be used to check
 *      which button had infact changed state.
 *
 * char PS2_newButtonState(unsigned int)
 *      This function returns the new state that a button is in if it has just
 *      recently changed it states. The button if interrest is sent as an
 *      argument to this function.
 *
 * char PS2_buttonPressed(unsigned int)
 *      This function allows the user to check if a specific button has been
 *      pressed. The button of interest is sent as an argument and a value is
 *      returned in to signify if the button of interest was just pressed.
 *
 * char PS2_buttonReleased(unsigned int)
 *      This function allows the user to check if a specific button has been
 *      released. The button of interest is sent as an argument and a value is
 *      returned in to signify if the button of interest was just released.
 *
 * char PS2_button(unsigned int)
 *      This function returns the current state of a specified button. The
 *      button of interest is sent as an argument to this function and the
 *      function returns a value that signifies the current buttons state.
 *
 * unsigned int PS2_buttonDataByte()
 *      This function returns the current state of all the buttons represented
 *      as individual bits in an integer variable.
 *
 * char PS2_analog(char)
 *      If analog is enabled, this function returns the analog value that
 *      coresponds to a specific button. This analog value is directly related
 *      to the pressure at which the specified button is being pressed.
 *
 * Original code by Shutter for Arduino         ??/??/??
 * Revamped by Bill Porter for Arduino          07/07/13
 * Ported to PIC18F by Broderick Carlin         05/05/15
 
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

#ifndef PS2_H
#define	PS2_H

#include <xc.h>
#include "delays.h"
#include "GlobalDefines.h"

#define CTRL_CLK        5
#define CTRL_CLK_HIGH   5
#define CTRL_BYTE_DELAY 5  //This value is very finicky and needs frequent tune

#define UART_DEBUG

    //These are our button constants
#define PSB_SELECT      0x0001
#define PSB_L3          0x0002
#define PSB_R3          0x0004
#define PSB_START       0x0008
#define PSB_PAD_UP      0x0010
#define PSB_PAD_RIGHT   0x0020
#define PSB_PAD_DOWN    0x0040
#define PSB_PAD_LEFT    0x0080
#define PSB_L2          0x0100
#define PSB_R2          0x0200
#define PSB_L1          0x0400
#define PSB_R1          0x0800
#define PSB_GREEN       0x1000
#define PSB_RED         0x2000
#define PSB_BLUE        0x4000
#define PSB_PINK        0x8000
#define PSB_TRIANGLE    0x1000
#define PSB_CIRCLE      0x2000
#define PSB_CROSS       0x4000
#define PSB_SQUARE      0x8000

//Guitar  button constants
#define UP_STRUM		0x0010
#define DOWN_STRUM		0x0040
#define STAR_POWER		0x0100
#define GREEN_FRET		0x0200
#define YELLOW_FRET		0x1000
#define RED_FRET		0x2000
#define BLUE_FRET		0x4000
#define ORANGE_FRET		0x8000
#define WHAMMY_BAR		8

//These are stick values
#define PSS_RX 5
#define PSS_RY 6
#define PSS_LX 7
#define PSS_LY 8

//These are analog buttons
#define PSAB_PAD_RIGHT    9
#define PSAB_PAD_UP      11
#define PSAB_PAD_DOWN    12
#define PSAB_PAD_LEFT    10
#define PSAB_L2          19
#define PSAB_R2          20
#define PSAB_L1          17
#define PSAB_R1          18
#define PSAB_GREEN       13
#define PSAB_RED         14
#define PSAB_BLUE        15
#define PSAB_PINK        16
#define PSAB_TRIANGLE    13
#define PSAB_CIRCLE      14
#define PSAB_CROSS       15
#define PSAB_SQUARE      16

#define CMD PORTFbits.RF2
#define DAT PORTFbits.RF3
#define ATT PORTFbits.RF6
#define CLK PORTFbits.RF5

#define SET(x,y) (x|=(1<<y))
#define CLR(x,y) (x&=(~(1<<y)))
#define CHK(x,y) (x & (1<<y))
#define TOG(x,y) (x^=(1<<y))

char PS2_init();
void PS2_readGamepad();
void PS2_reconfig();
void PS2_sendCommandString(char string[], char len);
char PS2_shiftInOut(char byte);
char PS2_readType();
char PS2_newButtons();
char PS2_newButtonState(unsigned int button);
char PS2_buttonPressed(unsigned int button);
char PS2_buttonReleased(unsigned int button);
char PS2_button(unsigned int button);
unsigned int PS2_buttonDataByte();
char PS2_analog(char button);

#endif

