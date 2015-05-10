/*                      ______     _
                        |  _  \   | |
                        | | | |___| | __ _ _   _ ___
                        | | | / _ \ |/ _` | | | / __|
                        | |/ /  __/ | (_| | |_| \__ \
                        |___/ \___|_|\__,_|\__, |___/
                                            __/ |
                                           |___/
 * File:   delays.c
 * Author: Broderick Carlin
 */

#include "delays.h"
#define USE_OR_MASKS

unsigned long millisCount = 0;

void delay_init()
{
    static int config = 0;

    //verify we only configure once
    if(config == 1)
    {
        return;
    }

    config = 1;

    //Setup timer0 to use for millis() functions
    // <7>      Enable timer
    // <6>      8-Bit timer
    // <5:4>    Internal Clock (FOSC/4)
    // <3>      Use Prescaler
    // <2:0>    1:256 Prescaler
    T0CON = 0b11010111;
    TMR0IP = 1;
    TMR0IF = 0;  //Clear any flag to avoid errors
    TMR0IE = 1;  //Enable overflow interrupt
    TMR0L = millisStart; //When timer overflows, it will have taken 1ms

   }


void delay_us(long x)
{
    x -= 3;
    while(x > 0)
    {
    __delay_us(1);
    x -= 2;
    }
}


void delay_ms(long x)
{
    unsigned long time = millis();
    while(millis() - time < x);
    return;
}


void delay_s(long x)
{
    unsigned long time = millis();
    while(millis() - time < (x * 1000));
    return;
}

unsigned long millis()
{
    return millisCount;
}

void clearMillis()
{
    TMR0L = millisStart; //When timer overflows, it will have taken 1ms
    millisCount = 0;
}

void tickMillis()
{
    ++millisCount;
}