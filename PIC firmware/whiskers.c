#include "whiskers.h"

#define whisker_R PORTJbits.RJ5
#define whisker_L PORTJbits.RJ6

void whiskers_Init()
{
    PADCFG1bits.RJPU = 1;   //enable pullups on port J

    whisker_R = 0;
    whisker_L = 0;

    TRISJbits.TRISJ5 = 1;
    TRISJbits.TRISJ6 = 1;
}

char whiskers_pollLeft()
{
    return (whisker_L ^ 1);
}

char whiskers_pollRight()
{
    return (whisker_R ^ 1);
}