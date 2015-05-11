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
 * array that was passed to them. The array must be 16 indeces minimum of type
 * unsigned char.
 *
 *
 */

signed char wiiCams_read(unsigned char camera, int *intensityDataX,
        int *intensityDataY);

#endif	/* WIICAMS_H */

