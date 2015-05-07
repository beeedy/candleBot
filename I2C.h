/* 
 * File:   I2C.h
 * Author: Tyler
 *
 * Created on May 6, 2015, 12:41 AM
 */

#ifndef I2C_H
#define	I2C_H

#ifdef	__cplusplus
extern "C" {
#endif

#define COMPASS_PIXY  1
#define COLOR_SENSOR  1
#define WII_CAM_LEFT  1
#define WII_CAM_RIGHT 2
#define COMPASS_MAIN  2


void I2C_init(unsigned char channel);
signed char I2C_open(unsigned char channel);
signed char I2C_close(unsigned char channel);
signed char I2C_read(unsigned char channel, unsigned char address, unsigned char* data);
signed char I2C_write(unsigned char channel, unsigned char address,
        unsigned char* data, unsigned char length);



#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

