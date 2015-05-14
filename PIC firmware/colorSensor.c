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
#include "colorSensor.h"

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

/*
    UART_transmitString(USB, "color sensor testing begin\n\r\n\r");
    signed char retVal = 0;
    unsigned char colorVals[8];
    while(1) {
        disableInterrupts();
        retVal = colorSensor_init();
        if(retVal == 0) {
            while(1) {

                enableInterrupts();
                delay_ms(200);           // wait for integration time - 24ms
                disableInterrupts();
                retVal = colorSensor_read(READ_COLOR_AND_CLEAR, colorVals);
                enableInterrupts();
                if(retVal == 0) {
                    UART_transmitString(USB, "Clear: %i \n\r", colorVals[1] << 8 | colorVals[0]);
                    UART_transmitString(USB, "Red: %i \n\r", colorVals[3] << 8 | colorVals[2]);
                    UART_transmitString(USB, "Green: %i \n\r", colorVals[5] << 8 | colorVals[4]);
                    UART_transmitString(USB, "Blue: %i \n\r", colorVals[7] << 8 | colorVals[6]);
                }
                else {
                    UART_transmitString(USB, "Color Sensor Error: %i \n\r", (int)retVal);
                }
            }
        }
    }*/

