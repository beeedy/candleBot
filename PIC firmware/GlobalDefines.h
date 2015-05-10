/* 
 * File:   GlobalDefines.h
 * Author: Tyler
 *
 * Created on April 14, 2015, 10:32 AM
 */

#ifndef GLOBALDEFINES_H
#define	GLOBALDEFINES_H

#ifdef	__cplusplus
extern "C" {
#endif

#define WII_CAM_ADR        0xB0
#define WII_CAM_SLAVE_ADR  0x21
#define COMPASS_ADR        0x3C
#define COLOR_SENSOR_ADR   0x52 /* 0x29 <- non shifted version */

#define FONA_BUFF_SIZE 50
#define PIXY_BUFF_SIZE 500
#define USB_BUFF_SIZE 500

#define _XTAL_FREQ 64000000

//Macros

#define MAX(x,y)    ((x > y) ? x : y)
#define MIN(x,y)    ((x < y) ? x : y)
#define ABS(x)      ((x < 0) ? (x*-1) : x)
#define bitSet(x,y) x |= (0x1 << y);


#define disablePPSLock() IOLOCK = 0
#define enablePPSLock() IOLOCK = 1
#define disableInterrupts() GIE = 0
#define enableInterrupts() GIE = 1

#ifdef	__cplusplus
}
#endif

#endif	/* GLOBALDEFINES_H */

