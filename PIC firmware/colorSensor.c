/*
 * This function interfaces with our color (RGBC) sensor (TCS3472) for the
 * detection of the white circle.
 *
 * Color sensor is on SCL/SDA 2 on pin 81 (SDA2) and pin 79 (SCL2)
 *
 *
 *  ??   COMMAND    W     Specifies register address                    0x00
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

#define USE_OR_MASKS

signed char colorSensor_init() { /**
    signed char retVal = 0;
    unsigned char data;

    data = SSP2BUF;             // clear out the previous data
*/

    return 0;
}