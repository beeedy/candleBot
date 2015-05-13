/* 
 * File:   wiiCams.h
 * Author: Tyler
 *
 * Created on May 10, 2015, 12:53 AM
 */

#ifndef WIICAMS_H
#define	WIICAMS_H

#include "GlobalDefines.h"
#include "I2C.h"
#include "delays.h"
#include "math.h"

#define WII_Y_TOLERANCE 5
#define WII_FOV 0.576
#define TAN_FOV_2 0.296236
#define WII_CAM_DISTANCE_APART 3.5


signed char wiiCams_init();



/*
 * wiiCams_read reads the values from the given camera and stores them in the
 * array that was passed to them. The array must be 12 indeces minimum of type
 * unsigned char.
 *
 *
 */
void wiiCams_execute(char *x, char *y);
signed char wiiCams_read(unsigned char camera, char *rawData);
void wiiCams_processData(char *rawData, int *processedData);
void wiiCams_sendData(unsigned char *processedData, unsigned char keyFrame);
void wiiCams_findCandle(int *processedDataL, int *processedDataR,
                        unsigned char *x, unsigned char *y);

#endif	/* WIICAMS_H */

