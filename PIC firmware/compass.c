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
 * 63488 - 2047
 *
 */

#include <xc.h>
#include "i2c.h"
#include "compass.h"
#include "GlobalDefines.h"
#include <math.h>


signed char compass_pixyInit() {    // this sensor is not working currently

    // the compass on the pixy board is on I2C line 1 (SDA: pin 56, SCL: pin 54)

    signed char retVal, data;

    data = SSP1BUF; //read any previous stored content in buffer to clear buffer
                    //full status

    retVal = I2C_writeRegister(COMPASS_PIXY, COMPASS_ADR, 0x00, 0x50);
    retVal += I2C_writeRegister(COMPASS_PIXY, COMPASS_ADR, 0x01, 0x20);
    retVal += I2C_writeRegister(COMPASS_PIXY, COMPASS_ADR, 0x02, 0x00);

    if(retVal <= -3) { //check if bus collision happened
        SSP1CON1bits.WCOL=0; // clear the bus collision status bit
    }

    return retVal;
}


signed char compass_mainBoardInit() { 
    // the compass on the main board is on I2C line 2 (SDA: pin 81, SCL: pin 79)

    signed char retVal, data;

    data = SSP2BUF; //read any previous stored content in buffer to clear buffer
                    //full status

    retVal = I2C_writeRegister(COMPASS_MAIN, COMPASS_ADR, 0x00, 0b01110000);
    retVal += I2C_writeRegister(COMPASS_MAIN, COMPASS_ADR, 0x01, 0x20);
    retVal += I2C_writeRegister(COMPASS_MAIN, COMPASS_ADR, 0x02, 0x00);

    if(retVal <= -3) { //check if bus collision happened
        SSP2CON1bits.WCOL=0; // clear the bus collision status bit
    }

    return retVal;
}


signed char compass_mainRead(unsigned char *positionData) {

    signed char retVal = 0;

    I2C_open(COMPASS_MAIN);
    retVal += I2C_write(COMPASS_MAIN, COMPASS_ADR);
    retVal += I2C_write(COMPASS_MAIN, 0x03);
    I2C_close(COMPASS_MAIN);
    retVal += I2C_open(COMPASS_MAIN);
    retVal += I2C_write(COMPASS_MAIN, COMPASS_ADR | 0x01);
    for(unsigned char x = 0; x < 5; x++) {
        retVal += I2C_read(COMPASS_MAIN, (positionData + x), ACK);
    }
    retVal += I2C_read(COMPASS_MAIN, (positionData + 5), NAK);  // nak on the last data byte
    I2C_close(COMPASS_MAIN);

    return retVal;
}


signed char compass_pixyRead(unsigned char *positionData) {
    
    signed char retVal = 0;

    I2C_open(COMPASS_PIXY);
    retVal += I2C_write(COMPASS_PIXY, COMPASS_ADR);
    retVal += I2C_write(COMPASS_PIXY, 0x03);
    I2C_close(COMPASS_PIXY);
    retVal += I2C_open(COMPASS_PIXY);
    retVal += I2C_write(COMPASS_PIXY, COMPASS_ADR | 0x01);
    for(unsigned char x = 0; x < 5; x++) {
        retVal += I2C_read(COMPASS_PIXY, (positionData + x), ACK);
    }
    retVal += I2C_read(COMPASS_PIXY, (positionData + 5), NAK);  // nak on the last data byte
    I2C_close(COMPASS_PIXY);

    return retVal;
}


void compass_cart2polar(unsigned char *positionData, int *theta, int *phi,
        int *r, int *x, int *y, int *z) {
    signed float xf = (signed float)( positionData[0] << 8 | positionData[1] );
    signed float yf = (signed float)( positionData[4] << 8 | positionData[5] );
    signed float zf = (signed float)( positionData[2] << 8 | positionData[3] );
    (*r)     = (int)(sqrt( (xf*xf) + (yf*yf) + (zf*zf) ));
    (*theta) = (int)( acos((zf)/(*r))*57.296 );     // also converts to degrees
    (*phi)   = (int)( atan( yf/xf )*57.296 );       // also converts to degrees

    *x = (signed int)xf;
    *y = (signed int)yf;
    *z = (signed int)zf;
}


/*
    unsigned char positionData[6];
    int theta, phi, r = 0;
    int x, y, z = 0;
    while(1) {
        disableInterrupts();
        compass_mainRead(positionData);
        compass_cart2polar(positionData, &theta, &phi, &r, &x, &y, &z);
        enableInterrupts();

        UART_transmitString(USB, "x: %i\n\r", x);
        UART_transmitString(USB, "y: %i\n\r", y);
        UART_transmitString(USB, "z: %i\n\r\n\r", z);
        delay_ms(50);
    }
     */
    /*
    unsigned char rawDataL[12], rawDataR[12];
    int processedDataL[12], processedDataR[12];
    int angle, x, y, z;

    while(1) {
        wiiCams_read(WII_CAM_LEFT, rawDataL);
        wiiCams_read(WII_CAM_RIGHT, rawDataR);

        wiiCams_processData(rawDataL, processedDataL);
        wiiCams_processData(rawDataR, processedDataR);

        wiiCams_findCandle(processedDataL, processedDataR, angle,  &x, &y, &z);
    }

 */
