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






/*
 * I2C_open generates a start condition on the specified channel in order to
 * begin data transmission
 *
 */

signed char I2C_open(unsigned char channel);






/*
 * I2C_close generates a stop condition on the specified channel in order to
 * stop the current data transmission
 *
 */

signed char I2C_close(unsigned char channel);





/*
 * I2C_write writes the given byte to the given channel and waits for an ack or
 * nak and returns:
 *
 *    0  -  slave acknowledged the transmittion
 *   -1  -  slave did not acknowledge the transmittion or bus collision
 *
 */

signed char I2C_write(unsigned char channel, unsigned char data);





/*
 * I2C_writeRegisters writes the given byte(s) starting at the given address on
 * the given channel and returns:
 *
 *    0  -  successful write, no errors
 *   -1  -  unsuccessful. NAK or bus collision
 *
 */


signed char I2C_writeRegisters(unsigned char channel, unsigned char slaveAdr,
        unsigned char startRegAdr, unsigned char* data, unsigned char len);

/*
 * I2C_read reads the register at the given address on the given channel of the
 * given register address and stores the value in the given location in memory
 * and returns:
 *
 *     0  -  successful read, returned the data
 *    -1  -  unsuccessful read, buffer overflow
 *    -2  -  unsuccessful read, other issue
 *
 *
 */

signed char I2C_read(unsigned char channel, unsigned char slaveAdr,
        unsigned char startRegAdr, unsigned char len,
        unsigned char* dataRetAdr);



#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

