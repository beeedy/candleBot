/*   _    _ _ _   ___________   _____
    | |  | (_|_) |_   _| ___ \ /  __ \
    | |  | |_ _    | | | |_/ / | /  \/ __ _ _ __ ___   ___ _ __ __ _ ___
    | |/\| | | |   | | |    /  | |    / _` | '_ ` _ \ / _ \ '__/ _` / __|
    \  /\  / | |  _| |_| |\ \  | \__/\ (_| | | | | | |  __/ | | (_| \__ \
     \/  \/|_|_|  \___/\_| \_|  \____/\__,_|_| |_| |_|\___|_|  \__,_|___/

 * File:   wiiCams.h
 * Author: Tyler Holmes and Broderick Carlin
 *
 * This file contains the functions needed to interface with the IR cameras that
 * can be used to interpolate two camera feeds to produce a single 3D estimation
 * of locations of IR sources. The IR cameras used are salvaged from older
 * Nintendo Wii remotes where they are used for IR LED tracking.
 *
 * -------------------------------Function List---------------------------------
 * signed char wiiCams_init()
 * void wiiCams_execute(char *x, char *y)
 * signed char wiiCams_read(unsigned char camera, char *rawData)
 * void wiiCams_processData(char *rawData, int *processedData)
 * void wiiCams_findCandle(int *processedDataL, int *processedDataR,
                           unsigned char *x, unsigned char *y)
 *
 * ---------------------------Function Descriptions-----------------------------
 * signed char wiiCams_init()
 *      This function must be called prior to any of the other functions that
 *      take advantage of the IR cameras. It is important to note that prior to
 *      this function, the I2C lines must be configured using a seperate
 *      initialization function. This configures both cameras to be setup into a
 *      mode that returns the (X,Y) coordinates of the 4 brightest points as
 *      10-bit values and the associated size of each of the 4 points seen. In
 *      this mode, the cameras will send back a 0xFFFF as a 'not-seen' condition
 *
 * void wiiCams_execute(char *x, char *y)
 *      This function is the most useful to the user as it wraps up all of the
 *      functionality of the other functions and handles function calls and
 *      variable handling for the user. To use this function, the user sends the
 *      pointers to two variables where they would like the x and y distance of
 *      the closest point to be stored. The Y value is equivelant to the
 *      distance direction forward in the Y axis that the IR point is seen while
 *      the X value represents the distance left or right of center that the IR
 *      point is seen. It is important to note that both of these values are
 *      represented in CM. Before this function is able to return valid data,
 *      the wiiCams_init() function must be called.
 *
 * signed char wiiCams_read(unsigned char camera, char *rawData)
 *      This function is responsible for reading in the data that is transmitted
 *      by the Wii cameras. The user specifies which camera they would like to
 *      talk with followed with the pointer to an array that is at a minimum
 *      12-bytes long. The data that is recieved from the Wii Cameras is stored
 *      in this array so that it may be used by the user throughout their
 *      program control flow. This function also returns a 0x00 if the values
 *      are read successfully, while any other return value signifies an error
 *      occured while communicating with the cameras. It is important to run the
 *      wiiCam initialization function prior to running this program to avoid
 *      errors in the communication process.
 *
 * void wiiCams_processData(char *rawData, int *processedData)
 *      This function takes in raw camera data from the Wii cameras, and returns
 *      processed data that is decompresses the informationt that the Wii cams
 *      output. This allows the user to more easily process the information that
 *      is being returned by the Wii cams. This function takes the pointer to an
 *      array of raw cam data and a pointer to an array to where it should store
 *      the processed and decompressed data. Once this function returns it will
 *      have stored the decompressed data into the integer array.
 *
 * void wiiCams_findCandle(int *processedDataL, int *processedDataR,
                           unsigned char *x, unsigned char *y)
 *      This function is tasked with taking in the processed camera data from
 *      both the right and the left cameras and returning the (X,Y) coordinates
 *      to the single closest IR light source. The X and Y values are in CM. It
 *      is important that the user sends this funtion data that has been already
 *      returned by the processData function otherwise the data recieved from
 *      this function will be completely useless.
 *
 * Special thanks to JOHNNY CHUN LEE at: procrastineering.blogspot.com

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

#ifndef WIICAMS_H
#define	WIICAMS_H

#include "GlobalDefines.h"
#include "I2C.h"
#include "delays.h"
#include "math.h"
#include "UART.h"

#define WII_Y_TOLERANCE 15
#define TAN_FOV_2 0.29621
#define WII_CAM_DISTANCE_APART 2.5

signed char wiiCams_init();
void wiiCams_execute(char *x, char *y);
signed char wiiCams_read(unsigned char camera, char *rawData);
void wiiCams_processData(unsigned char *rawData, int *processedData);
void wiiCams_findCandleCords(int *processedDataL, int *processedDataR,
                        unsigned char *x, unsigned char *y);

signed char wiiCams_findCandle(int *processedDataL, int *processedDataR);

#endif
