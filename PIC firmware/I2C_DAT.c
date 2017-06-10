/*
 * This file initiates the two I2C buses on the Ladder 42 board. bus one is on
 * SDA1: pin 56, SCL1: pin 54 and has the pixy compass sensor, the color sensor,
 * and the _______ wii camera on it. bus two is on SDA2: pin 81, SCL2: pin 79.
 * bus two has the main board compass sensor and the ________ wii camera on it.
 *
 * 
 *
 *
 */


#include <i2c.h>
#define USE_OR_MASKS

signed char i2c_init() {


    OpenI2C1(MASTER, SLEW_OFF);     // initiate in master mode
    SSP1ADD = 0x9F;                 // 100 kHz
    OpenI2C2(MASTER, SLEW_OFF);     // initiate in master mode
    SSP2ADD = 0x9F;                 // 100 kHz

    return 0;
}
