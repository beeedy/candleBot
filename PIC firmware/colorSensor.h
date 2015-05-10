/* 
 * File:   colorSensor.h
 * Author: Tyler
 *
 * Created on May 9, 2015, 10:32 PM
 */

#ifndef COLORSENSOR_H
#define	COLORSENSOR_H

#ifdef	__cplusplus
extern "C" {
#endif

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


/*
 * colorSensor_init initializes the color sensor (TCS3472) to have
 * a 24 ms integration time, no waiting, and a 4 times gain value
 *
 *
 */

signed char colorSensor_init();






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


signed char colorSensor_read(unsigned char readType, signed char *retVals);


#ifdef	__cplusplus
}
#endif

#endif	/* COLORSENSOR_H */

