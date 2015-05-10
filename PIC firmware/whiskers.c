/*                      _    _ _     _     _
 *                     | |  | | |   (_)   | |
 *                     | |  | | |__  _ ___| | _____ _ __ ___
 *                     | |/\| | '_ \| / __| |/ / _ \ '__/ __|
 *                     \  /\  / | | | \__ \   <  __/ |  \__ \
 *                      \/  \/|_| |_|_|___/_|\_\___|_|  |___/
 *
 * File:   whiskers.c
 * Author: Broderick Carlin
 */

#include "whiskers.h"

#define whisker_R PORTJbits.RJ5 // The right whisker is connected to pin RJ5
#define whisker_L PORTJbits.RJ6 // The left whisker is connected to pin RJ6

void whiskers_init()
{
    PADCFG1bits.RJPU = 1;       // Enable pullups on port J

    whisker_R = 0;
    whisker_L = 0;

    TRISJbits.TRISJ5 = 1;
    TRISJbits.TRISJ6 = 1;
}

char whiskers_pollLeft()
{
    return (whisker_L ^ 1);     // The whisker value is XOR'd to invert the LSB
                                //      0x00 : whisker not being pressed
                                //      0x01 : whisker being pressed
}

char whiskers_pollRight()
{
    return (whisker_R ^ 1);     // The whisker value is XOR'd to invert the LSB
                                //      0x00 : whisker not being pressed
                                //      0x01 : whisker being pressed
}