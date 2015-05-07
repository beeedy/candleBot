#include "settings.h"

/*
 Settings dip switch's
 0: (Tyler/!Broderick)      RL2
 1: (Call/!Text)            RG4
 2: (Auto/!Remote)          RL1
 3:  Debug to USB           RG3
 4: (Wander/!Competition    RG2
 5: (Cams/!Cripple)         RG1
 6: Self Test               RG0

 button                     RL3
 */

void settings_init()
{
    CM1CONbits.CON = 0;
    ANCON1 = 0;
    ANCON2 = 0;

    TRISGbits.TRISG0 = 1;
    TRISGbits.TRISG1 = 1;
    TRISGbits.TRISG2 = 1;
    TRISGbits.TRISG3 = 1;
    TRISGbits.TRISG4 = 1;
    TRISLbits.TRISL1 = 1;
    TRISLbits.TRISL2 = 1;
    TRISLbits.TRISL3 = 1;


    PADCFG1 = 0b00010001;   //enable pullups on port G enable pullups on port L
}


char settings_readSettings()
{
    char t = 0;

    t = (PORTLbits.RL3<<7) | (PORTGbits.RG0<<6) | (PORTGbits.RG1<<5) | (PORTGbits.RG2<<4) | (PORTGbits.RG3<<3) | (PORTLbits.RL1<<2) | (PORTGbits.RG4<<1) | PORTLbits.RL2;
    return t;
}


char settings_readButton()
{
    char t = RL3;
    return t;
}


char settings_tylerOrBroderick()
{
    char t = RL2;
    return t;
}


char settings_call()
{
     char t = RG4;
    return t;
}


char settings_auto()
{
    char t = RL1;
    return t;
}


char settings_debugMode()
{
    char t = RG3;
    return t;
}


char settings_wander()
{
    char t = RG2;
    return t;
}


char settings_cams()
{
    char t = RG1;
    return t;
}


char settings_selfTest()
{
    char t = RG0;
    return t;
}