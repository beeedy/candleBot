/*                           _____ _____  _____
                            |_   _/ __  \/  __ \
                              | | `' / /'| /  \/
                              | |   / /  | |
                             _| |_./ /___| \__/\
                             \___/\_____/ \____/
 * File:   I2C.h
 * Author: Tyler Holmes
 *
 * This file is responsible for handling all the fundamental I2C functions that
 * are required for talking to devices over I2C. These functions are made
 * available to the user, however all on board devices can be communicated with
 * through specific functions and files dedicated to each devices. It is highly
 * reccomended those are used instead of trying to manual communicated with
 * devices using these functions.
 *
 * -------------------------------Function List---------------------------------
 * void I2C_init(unsigned char channel)
 * void I2C_wait(unsigned char channel)
 * signed char I2C_open(unsigned char channel)
 * signed char I2C_repeatedStart(unsigned char channel)
 * signed char I2C_close(unsigned char channel)
 * signed char I2C_write(unsigned char channel, unsigned char data)
 * signed char I2C_writeRegister(unsigned char channel, unsigned char slaveAdr,
        unsigned char startRegAdr, unsigned char data)
 * signed char I2C_writeRegisters(unsigned char channel, unsigned char slaveAdr,
        unsigned char startRegAdr, unsigned char* data, unsigned char len)
 * signed char I2C_readRegesters(unsigned char channel, unsigned char slaveAdr,
        unsigned char startRegAdr, unsigned char len, unsigned char* dataRetAdr)
 * signed char I2C_read(unsigned char channel, signed char* dataRetAdr,
        unsigned char Ack)
 *
 * ---------------------------Function Descriptions-----------------------------
 * void I2C_init(unsigned char channel)
 *      This funcition is designed to intialize one of the on board I2C modules.
 *      The module to initialize is designated by the single input argument,
 *      and the function does not return anything. It is important that both I2C
 *      lines are initialized before attemping to talk to devices on the two 
 *      lines.
 * 
 * void I2C_wait(unsigned char channel)
 *      This function is simply a delay that waits until a specific channel is
 *      available for the PIC to become the master. It is important to remember
 *      that I2C_init() must be called prior to this function. This function is
 *      used by other functions as not direcly benefit the user. 
 * 
 * signed char I2C_open(unsigned char channel)
 *      This function generates a start condition on the specified line in order
 *      to begin the writing processes. This function is used by other functions
 *      and is not meant to be used directly by the user. Dicretly interfacing
 *      with this function can cause serious errors that are not immedietly 
 *      apparent to the PIC. 
 * 
 * signed char I2C_repeatedStart(unsigned char channel)
 *      This function is used by other functions to generates a repeated start 
 *      condition on the specified channel in order to begin data transmission 
 *      from the same sensor without letting other sensors/masters taking 
 *      control of the line. It is important that users do not directly access
 *      this function as directly interfacing with this function can cause
 *      serious errors that are not immedietly apparent to the PIC.
 * 
 * signed char I2C_close(unsigned char channel)
 *      This function is used by other functions to generate a close condition
 *      on the specified line. It is important that users do nto direclty access
 *      this function as directly interfcing with this function can cause
 *      serious errors that are not immedietly apparent to the PIC.
 * 
 * signed char I2C_write(unsigned char channel, unsigned char data)
 *      This function is used to send a byte of information over a specified
 *      channel. This function takes in both the channel number and the byte of
 *      information to be transmitted and returns a value corresonding to a
 *      success or a failure in transmition. It is important that the funciton
 *      I2C_init() is called prior to this function otherwise unpredictable
 *      behavior may occur. 
 * 
 * signed char I2C_writeRegister(unsigned char channel, unsigned char slaveAdr,
        unsigned char startRegAdr, unsigned char data)
 *      This function writes the given byte at the given address on the given 
 *      channel. This function has four arguments relating to the channel, the
 *      slaves address, the register address, and the byte of data. This 
 *      function returns a single byte of data that informs the user of an error
 *      such as a no acknowledge or bus collision. It is important to remember
 *      that I2C_init() must be called prior to this function otherwise 
 *      unpredictable behavior may occur.
 * 
 * signed char I2C_writeRegisters(unsigned char channel, unsigned char slaveAdr,
        unsigned char startRegAdr, unsigned char* data, unsigned char len)
 *      This function writes the given bytes at the given address on the given 
 *      channel. This function has five arguments relating to the channel, the
 *      slaves address, the register address, and the bytes of data. This 
 *      function returns a single byte of data that informs the user of an error
 *      such as a no acknowledge or bus collision. It is important to remember
 *      that I2C_init() must be called prior to this function otherwise 
 *      unpredictable behavior may occur.
 * 
 * signed char I2C_readRegesters(unsigned char channel, unsigned char slaveAdr,
        unsigned char startRegAdr, unsigned char len,unsigned char* dataRetAdr)
 *      This function reads the bytes at the given address on the given 
 *      channel. This function has five arguments relating to the channel, the
 *      slaves address, the register address, and the byte of data. This 
 *      function returns a single byte of data that informs the user of an error
 *      such as a no acknowledge or bus collision. It is important to remember
 *      that I2C_init() must be called prior to this function otherwise 
 *      unpredictable behavior may occur.
 * 
 * signed char I2C_read(unsigned char channel, signed char* dataRetAdr,
        unsigned char Ack)
 *      This function reads the byte at the given address on the given 
 *      channel. This function has four arguments relating to the channel, the
 *      slaves address, the register address, and the byte of data. This 
 *      function returns a single byte of data that informs the user of an error
 *      such as a no acknowledge or bus collision. It is important to remember
 *      that I2C_init() must be called prior to this function otherwise 
 *      unpredictable behavior may occur.
 * 
 * --------------------------Communicating over I2C-----------------------------
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

#ifndef I2C_H
#define	I2C_H

#include <XC.h>


void I2C_init(unsigned char channel);
void I2C_wait(unsigned char channel);
signed char I2C_open(unsigned char channel);
signed char I2C_repeatedStart(unsigned char channel);
signed char I2C_close(unsigned char channel);
signed char I2C_write(unsigned char channel, unsigned char data);
signed char I2C_writeRegister(unsigned char channel, unsigned char slaveAdr,
        unsigned char startRegAdr, unsigned char data);
signed char I2C_writeRegisters(unsigned char channel, unsigned char slaveAdr,
        unsigned char startRegAdr, unsigned char* data, unsigned char len);
signed char I2C_readRegesters(unsigned char channel, unsigned char slaveAdr,
        unsigned char startRegAdr, unsigned char len,unsigned char* dataRetAdr);
signed char I2C_read(unsigned char channel, signed char* dataRetAdr,
        unsigned char Ack);


#endif

