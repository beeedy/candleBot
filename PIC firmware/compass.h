/* 
 * File:   compass.h
 * Author: Tyler
 *
 * Created on May 5, 2015, 12:03 AM
 */

#ifndef COMPASS_H
#define	COMPASS_H

#ifdef	__cplusplus
extern "C" {
#endif


#define COMPASS_READ_ADDR  0x3C
#define COMPASS_WRITE_ADDR 0x3D


signed char compass_pixyInit();
signed char compass_mainBoardInit();
signed char compass_mainRead(signed char positionData[]);
signed char compass_pixyRead(signed char positionData[]);
void compass_cart2polar(signed char posData[], int *theta, int *phi, int *r);

#ifdef	__cplusplus
}
#endif

#endif	/* COMPASS_H */

