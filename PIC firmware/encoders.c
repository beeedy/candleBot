/*                    _____                    _
                     |  ___|                  | |
                     | |__ _ __   ___ ___   __| | ___ _ __ ___
                     |  __| '_ \ / __/ _ \ / _` |/ _ \ '__/ __|
                     | |__| | | | (_| (_) | (_| |  __/ |  \__ \
                     \____/_| |_|\___\___/ \__,_|\___|_|  |___/

 * File:   encoders.h
 * Author: Broderick Carlin
 */

#include "encoders.h"

volatile long right_count = 0;
volatile long left_count = 0;

void encoders_init()
{

    TRISBbits.TRISB0 = 1;
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    TRISBbits.TRISB3 = 1;

    /**********************  External Interrupt setup  ************************/
    /*
    /* External Interrupt INT1 and INT3 are tied to RB1 and RB3 respectivly
    /* Low-Priority interrupt
    /*
    /*/

    disablePPSLock();
    RPINR26_27 &= 0xF2;     //INT1 goes to RB1 (RP9)
    RPINR28_29 &= 0xF1;     //INT3 goes to RB3 (RP7)
    enablePPSLock();

    INTCON2bits.INTEDG1 = 1;
    INTCON3bits.INT1IP = 0;
    INTCON3bits.INT1IF = 0;
    INTCON3bits.INT1IE = 1;
    
    
    INTCON2bits.INTEDG3 = 1;
    INTCON2bits.INT3IP = 0;
    INTCON3bits.INT3IF = 0;
    INTCON3bits.INT3IE = 1; 
}

void interrupt low_priority encoderInterrupt()
{
    if(INT1IF == 1)
    {
        if(PORTBbits.RB0 == 1)
        {
            left_count--;
        }
        else
        {
            left_count++;
        }
        INT1IF = 0;
    }
    else if(INT3IF == 1)
    {
        if(PORTBbits.RB2 == 1)
        {
            right_count--;
        }
        else
        {
            right_count++;
        }
        INT3IF = 0;
    }
}


long encoders_readLeft()
{
    int temp = left_count;
    left_count = 0;
    return temp;

}


long encoders_peakLeft()
{
    long temp = left_count;
    return temp;
}


long encoders_readRight()
{
    int temp = right_count;
    right_count = 0;
    return temp;
}


long encoders_peakRight()
{
    long temp = right_count;
    return temp;
}


void encoders_clear()
{
    left_count = 0;
    right_count = 0;
}