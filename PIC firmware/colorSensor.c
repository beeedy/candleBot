/*
 * This function interfaces with our color (RGBC) sensor (TCS3472) for the
 * detection of the white circle.
 *
 * Color sensor is on SCL/SDA 2 on pin 81 (SDA2) and pin 79 (SCL2)
 *
 *
 *  ??    COMMAND   W     Specifies register address                    0x00
 *  0x00  ENABLE    R/W   Enables states and interrupts                 0x00
 *  0x01  ATIME     R/W   RGBC time                                     0xFF
 *  0x03  WTIME     R/W   Wait time                                     0xFF
 *  0x04  AILTL     R/W   Clear interrupt low threshold low byte        0x00
 *  0x05  AILTH     R/W   Clear interrupt low threshold high byte       0x00
 *  0x06  AIHTL     R/W   Clear interrupt high threshold low byte       0x00
 *  0x07  AIHTH     R/W   Clear interrupt high threshold high byte      0x00
 *  0x0C  PERS      R/W   Interrupt persistence filter                  0x00
 *  0x0D  CONFIG    R/W   Configuration                                 0x00
 *  0x0F  CONTROL   R/W   Control                                       0x00
 *  0x12  ID        R     Device ID ID
 *  0x13  STATUS    R     Device status                                 0x00
 *  0x14  CDATAL    R     Clear data low byte                           0x00
 *  0x15  CDATAH    R     Clear data high byte                          0x00
 *  0x16  RDATAL    R     Red data low byte                             0x00
 *  0x17  RDATAH    R     Red data high byte                            0x00
 *  0x18  GDATAL    R     Green data low byte                           0x00
 *  0x19  GDATAH    R     Green data high byte                          0x00
 *  0x1A  BDATAL    R     Blue data low byte                            0x00
 *  0x1B  BDATAH    R     Blue data high byte                           0x00
 *
 *
 * I2C Address: 0x29
 *
 */

#include "I2C.h"
#include "globalDefines.h"


/*
 * colorSensor_init initializes the color sensor (TCS3472) to have
 * a 24 ms integration time, no waiting, and a 4 times gain value
 *
 *
 */

signed char colorSensor_init() { 
    signed char retVal = 0;

    I2C_open(COLOR_SENSOR);
    retVal = I2C_write(COLOR_SENSOR, COLOR_SENSOR_ADR); // call out the color sensor
    if(retVal != 0)
        return retVal;
    retVal += I2C_write(COLOR_SENSOR, 0b10100000);      // specify read/write type, point to the 0x00 register
    if(retVal != 0)
        return (retVal - 10);
    retVal += I2C_write(COLOR_SENSOR, 0b00000011);      // wait off, power on, RGBC enable
    if(retVal != 0)
        return (retVal - 20);
    retVal += I2C_write(COLOR_SENSOR, 0xF6);        // integration time of 24 ms
    if(retVal != 0)
        return (retVal -30);
    retVal += I2C_write(COLOR_SENSOR, 0b10101111);  // auto-increment, point to 0x0F
    if(retVal != 0)
        return (retVal - 40);
    retVal += I2C_write(COLOR_SENSOR, 0x01);        // RGBC gain = 4 (LED is very bright)
    if(retVal != 0)
        return (retVal - 50);

    I2C_close(COLOR_SENSOR);
    return 0;
}



/*
 * colorSensor_read reads out either the clear value or the color values
 * depending on what you pass to the function (CLEAR, COLOR, CLEAR_AND_COLOR for
 * the read type input) and returns it in the retVals array
 *
 * format: [ clear LSB, clear MSB, red LSB, red MSB, green LSB, green MSB,
 *           blue LSB, blue MSB]
 *
 * if the read type you selected does not use of some of these values, it will
 * write them as 0.
 *
 */


signed char colorSensor_read(unsigned char readType, signed char *retVals) {

    signed char retVal = 0;
    I2C_open(COLOR_SENSOR);
    if(readType == 1 || readType == 3) {

        retVal += I2C_write(COLOR_SENSOR, COLOR_SENSOR_ADR);
        if(retVal != 0)
            return retVal;
        retVal += I2C_write(COLOR_SENSOR, 0b10110100);      // auto-increment, point to clear LSB
        if(retVal != 0)
            return (retVal - 10);
        I2C_close(COLOR_SENSOR);
        I2C_open(COLOR_SENSOR);
        retVal += I2C_write(COLOR_SENSOR, COLOR_SENSOR_ADR | 0x01); // write
        I2C_read(COLOR_SENSOR, retVals, ACK);
        I2C_read(COLOR_SENSOR, (retVals + 1), NAK);
        if(readType == 1) {
            retVals[2] = retVals[3] = retVals[4] = retVals[5] = 0;
            I2C_close(COLOR_SENSOR);
            return 0;//retVal;
        }
    }
    // readType must be 2 or 3
    I2C_close(COLOR_SENSOR);
    I2C_open(COLOR_SENSOR);
    retVal += I2C_write(COLOR_SENSOR, COLOR_SENSOR_ADR);    // switch to writing
    if(retVal != 0)
            return retVal - 20;
    retVal += I2C_write(COLOR_SENSOR, 0b10110110);      // auto-increment, point to red LSB
    if(retVal != 0)
            return retVal - 30;
    I2C_close(COLOR_SENSOR);
    I2C_open(COLOR_SENSOR);
    retVal += I2C_write(COLOR_SENSOR, COLOR_SENSOR_ADR | 0x01); // write
    I2C_read(COLOR_SENSOR, (retVals + 2), ACK);
    I2C_read(COLOR_SENSOR, (retVals + 3), ACK);
    I2C_read(COLOR_SENSOR, (retVals + 4), ACK);
    I2C_read(COLOR_SENSOR, (retVals + 5), ACK);
    I2C_read(COLOR_SENSOR, (retVals + 6), ACK);
    I2C_read(COLOR_SENSOR, (retVals + 7), NAK);
    if(readType == 2) {
        retVals[0] = retVals[1] = 0;
    }
    I2C_close(COLOR_SENSOR);
    return 0;//retVal;

}