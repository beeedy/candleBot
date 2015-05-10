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


void I2C_init(unsigned char channel);




/*
 * Waits for a few things to finish before continuing
 *
 */

void I2C_wait(unsigned char channel);




/*
 * I2C_open generates a start condition on the specified channel in order to
 * begin data transmission
 *
 */

signed char I2C_open(unsigned char channel);




/*
 * I2C_repeatedStart generates a repeated start condition on the specified
 * channel in order to begin data transmission from the same sensor without
 * letting other sensors/masters taking control of the line
 *
 */

signed char I2C_repeatedStart(unsigned char channel);



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
 * I2C_writeRegister1 writes the given byte at the given address on
 * the given channel and returns:
 *
 *    0  -  successful write, no errors
 *   -1  -  unsuccessful. NAK
 *   -2  -  unsuccessful. Bus collision
 *
 */


signed char I2C_writeRegister(unsigned char channel, unsigned char slaveAdr,
        unsigned char startRegAdr, unsigned char data);








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

signed char I2C_readRegesters(unsigned char channel, unsigned char slaveAdr,
        unsigned char startRegAdr, unsigned char len,
        unsigned char* dataRetAdr);




signed char I2C_read(unsigned char channel, signed char* dataRetAdr,
        unsigned char Ack);


#ifdef	__cplusplus
}
#endif

#endif	/* I2C_H */

