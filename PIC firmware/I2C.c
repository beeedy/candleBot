/*
 * This file contains all of the functions required to set up and communicate
 * over I2C. These functions interface with the two compass sensors, the two
 * wii cameras, and the color sensor.
 *
 * 1. Generate a start condition (set the Start Enable bit, SEN)
 * 2. SSPxIF gets set. The MSSPx module waits for the required start time
 * 3. I load the SSPxBUF with the slave address to transmit.
 * 4. Address gets shifted out the SDAx pin
 * 5. The MSSPx module shifts in the ACK' bit from the slave device and writes
 *    its value into the SSPxCON2 register (SSPxCON2<6>).
 * 6. The MSSPx module generates an interrupt at the end of the 9th clock cycle
 *    by setting the SSPxIF bit.
 * 7. The user loads the SSPxBUF with eight bits of data.
 * 8. repeat steps 4-6
 * 9. generate a stop condition by setting the Stop Enable bit, PEN
 *
 *
 * This file initiates the two I2C buses on the Ladder 42 board. 
 * 
 * bus one is on SDA1: pin 56, SCL1: pin 54 and has:
 *
 *  pixy compass sensor     <- not responding
 *  right wii camera on it.
 * 
 * 
 * bus two is on SDA2: pin 81, SCL2: pin 79. bus two has:
 *
 *  main board compass sensor
 *  color sensor
 *  left wii camera
 *
 * Wii cams are referenced from the ROBOT's point of view.
 * 
 */

#include <XC.h>
#include "I2C.h"

/*
 * Initializes the I2C ports. Sets all of the registers to what they need to
 * be for proper I2C data transmission.
 *
 */


void I2C_init(unsigned char channel) {

    if(channel == 1) {      // initialize channel 1

        TRISCbits.TRISC3 = 1;
        TRISCbits.TRISC4 = 1;

        SSP1CON1 = 0x28;    // I2C master mode. clk = Fosc/(4*SSP1ADD + 1)
        SSP1CON2 = 0x00;    // clear current status
        SSP1CON3 = 0x40;    // buffer overwrite allowed #yoloswag
        SSP1ADD  = 0x9F;     // 100 kHz
        SSP1STAT = 0x80;    // slew rate disabled (100 kHz), SMBus disabled

    }
    else {                  // initialize channel 2

        TRISDbits.TRISD5 = 1;
        TRISDbits.TRISD6 = 1;

        SSP2CON1 = 0x28;    // I2C master mode. clk = Fosc/(4*SSP1ADD + 1)
        SSP2CON2 = 0x00;    // clear current status
        SSP2CON3 = 0x40;    // buffer overwrite allowed #yoloswag
        SSP2ADD  = 0x9F;     // 100kHz
        SSP2STAT = 0x80;    // slew rate disabled (100 kHz), SMBus disabled

    }
}




/*
 * Waits for a few things to finish before continuing
 *
 */

void I2C_wait(unsigned char channel) {
    if(channel == 1) {
        while ( (SSP1CON2 & 0x1F) || (SSP1STAT & 0x04) );
        //only continues when there is not imortant bit set
    }
    else { // channel 2
        while( (SSP2CON2 & 0x1F) || (SSP2STAT & 0x04) );
    }
 }





/*
 * I2C_open generates a start condition on the specified channel in order to
 * begin data transmission
 *
 */

signed char I2C_open(unsigned char channel) {

    if(channel == 1) {
        I2C_wait(1);
        SSP1CON2bits.SEN = 1;       // initate a start condition
        while(SSP1CON2bits.SEN);    // waits for the start condition to end.
        return 0;                   // hardware should wait itself however.
    }
    else {  // channel 2
        I2C_wait(2);
        SSP2CON2bits.SEN = 1;       // initate a start condition
        while(SSP2CON2bits.SEN);    // waits for the start condition to end.
        return 0;                   // hardware should wait itself however.
    }
}



/*
 * I2C_close generates a stop condition on the specified channel in order to
 * stop the current data transmission
 *
 * SSP2CON2bits.PEN=1;
 *  while(SSP2CON2bits.PEN);
 *
 *
 */

signed char I2C_close(unsigned char channel) {

    if(channel == 1) {

        I2C_wait(1);
        SSP1CON2bits.PEN = 1;
        while(SSP1CON2bits.PEN);    // waits for the stop condition to finish
        return 0;
    }
    else {  // channel 2

        I2C_wait(2);
        SSP2CON2bits.PEN = 1;
        while(SSP2CON2bits.PEN);    // waits for the stop condition to finish
        return 0;
    }
}

/*
 * I2C_write writes the given byte to the given channel and waits for an ack or
 * nak and returns:
 *
 *    0  -  slave acknowledged the transmittion
 *   -1  -  slave did not acknowledge the transmittion
 *   -2  -  bus collision
 *
 */

signed char I2C_write(unsigned char channel, unsigned char data) {

    if(channel == 1) {

        // This function assumes the start condition has already been asserted
        SSP1BUF = data;   // send the address in write mode
        I2C_wait(1);
        if(SSP1CON2bits.ACKSTAT) {
            // NAK
            return -1;
        }
        if(SSP1CON1bits.WCOL) {
            // bus collision
            SSP1CON1bits.WCOL = 0;
            return -2;
        }
        return 0;   // acknowledge was recieved, we sent the byte successfully
    }
    else {  // channel two

        // This function assumes the start condition has already been asserted
        SSP2BUF = data;   // send the address in write mode
        I2C_wait(2);
        if(SSP2CON2bits.ACKSTAT) {
            // NAK
            return -1;
        }
        if(SSP2CON1bits.WCOL) {
            // bus collision
            SSP2CON1bits.WCOL = 0;
            return -2;
        }
        return 0;   // acknowledge was recieved, we sent the byte successfully

    }
}


/*
 * I2C_writeRegisters writes the given byte(s) starting at the given address on
 * the given channel and returns:
 *
 *    0  -  successful write, no errors
 *   -1  -  unsuccessful. NAK
 *   -2  -  unsuccessful. Bus collision
 * 
 */


signed char I2C_writeRegisters(unsigned char channel, unsigned char slaveAdr,
        unsigned char startRegAdr, unsigned char* data, unsigned char len) {

    volatile signed char retVal;

    I2C_open(channel);
    retVal = I2C_write(channel, ((slaveAdr << 0) | 0x00) );    // call out slave, write mode
    if(retVal != 0) {
        I2C_close(channel);
        return retVal;
    }

    retVal = I2C_write(channel, startRegAdr);  // specify which register we're writing to
    if(retVal != 0) {
        I2C_close(channel);
        return retVal;
    }

    for(unsigned char x = 0; x < len; x++) {    // write all of the data out
        retVal = I2C_write(channel, data[x]);
        if(retVal != 0) {                       // check for errors
            I2C_close(channel);
            return retVal;
        }
    } // for

    I2C_close(channel);
    return retVal;
}


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
        unsigned char* dataRetAdr) {

    volatile signed char retVal;

    I2C_open(channel);
    retVal = I2C_write(channel, ((slaveAdr << 0)| 0x01) );    // send slave adr, read
    if(retVal != 0) {
        if(SSP1CON1bits.WCOL || SSP2CON1bits.WCOL)
            SSP1CON1bits.WCOL = SSP2CON1bits.WCOL = 0;
        I2C_close(channel);
    }

    retVal = I2C_write(channel, startRegAdr);
    if(retVal != 0) {
        if(SSP1CON1bits.WCOL || SSP2CON1bits.WCOL)
            SSP1CON1bits.WCOL = SSP2CON1bits.WCOL = 0;
        I2C_close(channel);
    }

    if(channel == 1) {
        for(unsigned char x = 0; x < len; x++) {
            SSP1CON2bits.RCEN = 1;          // recieve mode on
            while(!(SSP1STATbits.BF));      // wait for the buffer to fill
            dataRetAdr[x] = SSP1BUF;        // get data
            SSP1CON2bits.ACKEN = 1;         // acknowledge
            SSP1CON2bits.RCEN = 0;          // recieve mode off
        }
        I2C_close(1);        // stop the transmittion on channel 1
    }
    else {  // channel 2
        for(unsigned char x = 0; x < len; x++) {
            SSP2CON2bits.RCEN = 1;          // recieve mode on
            while(!(SSP2STATbits.BF));      // wait for the buffer to fill
            dataRetAdr[x] = SSP2BUF;        // get data
            SSP2CON2bits.ACKEN = 1;         // acknowledge
            SSP2CON2bits.RCEN = 0;          // recieve mode off
        }
        I2C_close(2);        // stop the transmittion on channel 2
    }
    
    return retVal;
}