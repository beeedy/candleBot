/*          _____       _              _____
           /  __ \     | |            /  ___|
           | /  \/ ___ | | ___  _ __  \ `--.  ___ _ __  ___  ___  _ __
           | |    / _ \| |/ _ \| '__|  `--. \/ _ \ '_ \/ __|/ _ \| '__|
           | \__/\ (_) | | (_) | |    /\__/ /  __/ | | \__ \ (_) | |
            \____/\___/|_|\___/|_|    \____/ \___|_| |_|___/\___/|_|

 * File:   colorSensor.h
 * Author: Tyler Holmes
 */

#include "I2C.h"

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