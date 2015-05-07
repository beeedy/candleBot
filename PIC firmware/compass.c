/*
 * This file deals with both the compass on the main board as well
 * as the compass on the pixy sub-board. The one we care about
 * a lot is the one on the pixy because it will give us our
 * angle measurment of the pixy. The information
 *
 * 00     Configuration Reg. A         R/W
 * 01     Configuration Reg. B         R/W
 * 02     Mode Register                R/W
 * 03     Data Output X MSB Reg.       R
 * 04     Data Output X LSB Reg.       R
 * 05     Data Output Z MSB Reg.       R
 * 06     Data Output Z LSB Reg.       R
 * 07     Data Output Y MSB Reg.       R
 * 08     Data Output Y LSB Reg.       R
 *
 * data format: 0xF800 to 0x07FF
 *
 * 09     Status Reg.                  R
 * 10     Identification Reg. A        R
 * 11     Identification Reg. B        R
 * 12     Identification Reg. C        R
 *
 *
 * HMC5883L 8-bit slave address is 0x3C for write operations,
 *      or 0x3D for read operations.
 *
 * Note:
 *
 *      To minimize the communication between the master and this
 *      device, the address pointer updated automatically without
 *      master intervention. The register pointer will be
 *      incremented by 1 automatically after the current register
 *      has been read successfully.
 *
 *      Any attempt to read an invalid address location returns 0?s,
 *      and any write to an invalid address location or an undefined
 *      bit within a valid address location is ignored by this device.
 *
 *           \/- 4 averages
 * CRA = 0b0 10 100 00
 *               ^- 15 Hz output rate
 *
 * CRB = 0b00100000
 *          ^- Gain settings. Left default
 *
 * Mode Reg. = 0b00000000 <- continuous measure, low speed i2c
 *
 * Data read oddities - Overflow results in data = -4096. when one
 * output registers is read, the others have to be read to get a
 * new reading.
 *
 * Status reg: 0b000000LR - L = Lock bit, R = Ready bit
 *
 * ID reg A: ascii val - H
 * ID reg B: ascii val - 4
 * ID reg C: ascii val - 3
 *
 * write the device's address, the adress you want to read/write,
 * then write/read the value
 *
 */

#include <xc.h>
#include "i2c.h"
#include "compass.h"
#include "GlobalDefines.h"
#include <math.h>

signed char compass_pixyInit() {/*

    // the compass on the pixy board is on I2C line 1 (SDA: pin 56, SCL: pin 54)

    signed char retVal, data;
    unsigned char retry = 3;

    data = SSP1BUF; //read any previous stored content in buffer to clear buffer
                    //full status
    do {
        unsigned char data[] = {
            0x00,
            0x50,
            0x20,
            0x00
        };
        retVal = I2C_write(COMPASS_PIXY, COMPASS_ADR, data, 4);
        if(retVal == -3) { //check if bus collision happened
            SSP1CON1bits.WCOL=0; // clear the bus collision status bit
        }
        retry--;
    } while(retVal!=0 && retry > 0); //write untill successful communication
    if(retry == 0) {
        return -1;
    }
    else */
        return 0;
}


signed char compass_mainBoardInit() { /*
    // the compass on the main board is on I2C line 2 (SDA: pin 81, SCL: pin 79)

    signed char retVal, data;

    StartI2C2();
    data = SSP2BUF; //read any previous stored content in buffer to clear buffer
                    //full status
    do {
        retVal = WriteI2C2(COMPASS_WRITE_ADDR);  // compass address
        if(retVal == -1) { //check if bus collision happened
            data = SSP2BUF; //upon bus collision detection clear the buffer,
            SSP2CON1bits.WCOL=0; // clear the bus collision status bit
        }
    } while(retVal!=0); //write untill successful communication

    // clear/reset retVal
    retVal = WriteI2C2(0x00);                // Config reg A address
    retVal += WriteI2C2(0x50);                // config reg A val

    retVal += WriteI2C2(COMPASS_WRITE_ADDR);  // compass address
    retVal += WriteI2C2(0x01);                // Config reg B address
    retVal += WriteI2C2(0x20);                // config reg B val

    retVal += WriteI2C2(COMPASS_WRITE_ADDR);  // compass address
    retVal += WriteI2C2(0x02);                // Mode reg address
    retVal += WriteI2C2(0x00);                // Continuous Measure

    IdleI2C2(); // close connection

    if(retVal != 0) {
        return -1;
    }
    else {
        WriteI2C1(COMPASS_READ_ADDR);  // compass address
        WriteI2C1(0x0A);               // ID reg. A
        if(ReadI2C1() != 'H')
            return -1;

        // get initial calibration. Must be flat on the floor!

        int x, y, z;
        retVal = compass_mainRead(&x, &y, &z);
        StopI2C1();
        return retVal;
    } */
    return 0;   // remove
}


signed char compass_mainRead(int *x, int *y, int *z) {/*

    signed char retVal;
    retVal += WriteI2C2(COMPASS_READ_ADDR); // compass address
    retVal += WriteI2C2(0x03);              // x MSB address
    if(retVal != 0) {
        (*x) = ReadI2C2();                  // store val
        (*x) = (*x) << 8;                   // shift MSB up
        (*x) = ( 0x00ff & ReadI2C2() );     // read LSB

        (*z) = ReadI2C2();                  // read y MSB address
        (*z) = (*z) << 8;                   // shift MSB up
        (*z) = ReadI2C2();                  // read LSB

        (*y) = ReadI2C2();                  // read z MSB address
        (*y) = (*y) << 8;                   // shift MSB up
        (*y) = ReadI2C2();                  // read LSB
*/
        return 0; /*
    }
    else
        return -1;*/

}


signed char compass_pixyRead(int *x, int *y, int *z) { /*
    
    signed char retVal;
    retVal += WriteI2C1(COMPASS_READ_ADDR); // compass address
    retVal += WriteI2C1(0x03);              // x MSB address
    if(retVal != 0) {
        (*x) = ReadI2C1();                  // store val
        (*x) = (*x) << 8;                   // shift MSB up
        (*x) = ( 0x00ff & ReadI2C1() );     // read LSB

        (*z) = ReadI2C1();                  // read y MSB address
        (*z) = (*z) << 8;                   // shift MSB up
        (*z) = ReadI2C1();                  // read LSB

        (*y) = ReadI2C1();                  // read z MSB address
        (*y) = (*y) << 8;                   // shift MSB up
        (*y) = ReadI2C1();                  // read LSB

        return 0;
    }
    else
        return -1;*/
    return 0; // remove
}


void compass_cart2polar(int *x, int *y, int *z, int *theta, int *phi, int *r) {
    float xf = (float)(*x);
    float yf = (float)(*y);
    float zf = (float)(*z);
    (*r)     = (int)(sqrt( (xf*xf) + (yf*yf) + (zf*zf) ));
    (*theta) = (int)(acos((zf)/(*r)));
    (*phi)   = (int)(atan((*y)/(*x)));
}
