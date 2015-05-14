/*               _____  ________  ___  _____      _ _       _
                |  __ \/  ___|  \/  | /  __ \    | | |     | |
                | |  \/\ `--.| .  . | | /  \/ ___| | |_   _| | __ _ _ __
                | | __  `--. \ |\/| | | |    / _ \ | | | | | |/ _` | '__|
                | |_\ \/\__/ / |  | | | \__/\  __/ | | |_| | | (_| | |
                 \____/\____/\_|  |_/  \____/\___|_|_|\__,_|_|\__,_|_|

 * File:   FONA.h
 * Author: Broderick Carlin
 *
 * This file contains the functions that allow us interface with a GSM cellular
 * module, sold under the name 'FONA' by Adafruit Industries. This file only
 * contains functions to interface over SMS messages and is unable to read
 * incoming messages, only send out messages. All the functions are available
 * that would be needed to build software to access all the other features, this
 * file just has not been flushed out with all possible options for commands.
 *
 * -------------------------------Function List---------------------------------
 * char FONA_init()
 * char FONA_sendCommandCheckReply(const char[], const char[])
 * void FONA_sendCommand(const char[])
 * char FONA_checkReply(const char[])
 * char FONA_Text(char *data, char* phoneNumber)
 *
 * ---------------------------Function Descriptions-----------------------------
 * char FONA_init()
 *      This function must be called before attempting to interface with the GSM
 *      module. This function sets up the module with auto BAUD rate detection
 *      and returns a 0x01 if it successfully establishes communication and
 *      returns a 0x00 if it fails to inititialize communication with the GSM
 *      module.
 *
 * char FONA_sendCommandCheckReply(const char[], const char[])
 *      This function sends a string out to the GSM module and compares the
 *      returned value with a second input string. If the returned string
 *      matches the input string, a 0x01 is returned. If the returned string
 *      does not match, a 0x00 is returned to signify an error has occured.
 *
 * void FONA_sendCommand(const char[])
 *      This function takes in a string and formats it and sends it out to the
 *      GSM module. This function does not return any values as it does not
 *      check for any response from the module and as such, has no way of
 *      checking for possible errors in the communication. This function should
 *      be followed by a check of the GSM modules return value to see if the
 *      transmition was a success or a failure.
 *
 * char FONA_checkReply(const char[])
 *      This function checks the response from the GSM against an input string
 *      value. If the GSM module returned the inputed string, a 0x01 is returned
 *      while if the GSM module did not return the inputed string or the read
 *      timed out, a 0x00 is returned.
 *
 * char FONA_Text(char *data, char* phoneNumber)
 *      This function sends information to the GSM module triggering a SMS text
 *      message to be sent. The string to be sent as the body of the message is
 *      entered as the first argument while the phone number, in string format,
 *      is the second argument. This function returns a 0x01 if the text is
 *      successfully sent over the GSM network and returns a 0x00 if the text
 *      fails to send for any number of reasons. If this function fails, there
 *      is no direct way to tell the source of the failure. It is important
 *      that the FONA_init() function be successfully called prior to any
 *      attempt to call this function. 

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

#ifndef FONA_H
#define	FONA_H

#include "FoneNumbers.h"
#include "GlobalDefines.h"
#include "UART.h"
#include "delays.h"
#include <string.h>


    char FONA_init();
    char FONA_sendCommandCheckReply(const char[], const char[]);
    void FONA_sendCommand(const char[]);
    char FONA_checkReply(const char[]);
    char FONA_Text(char *data, char* phoneNumber);


#endif

