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


signed char wiiCams_init();



/*
 * wiiCams_read reads the values from the given camera and stores them in the
 * array that was passed to them. The array must be 12 indeces minimum of type
 * unsigned char.
 *
 *
 */

signed char wiiCams_read(unsigned char camera, unsigned char *rawData);


wiiCams_processData(unsigned char *rawData, int *processedData);
wiiCams_sendData(unsigned char *processedData, unsigned char keyFrame);
wiiCams_findCandle(unsigned char *processedDataL, unsigned char *processedDataR,
        unsigned char angle, unsigned char *x, unsigned char *y, unsigned char *z);

#endif	/* WIICAMS_H */

