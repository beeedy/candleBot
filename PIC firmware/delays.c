#include "delays.h"
#include <timers.h>
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

    //configure timer 1 to use internal 32kHz clock
    TMR3CS0 = 1;
    TMR3CS1 = 1;

    //configure no prescale of timer 1
    T3CKPS0 = 0;
    T3CKPS1 = 0;

    //configure timer 1, 3, 5 to be 16bit
    RD163 = 1;
    
    //disable interrupting
    TMR3IE = 0;

    //enable timer
    TMR3ON = 1;

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


void delay_clear()
{

    TMR3ON = 0;
    TMR3H = 0;
    TMR3L = 0;
}


void delay_startCount()
{
    TMR3ON = 1;
}


unsigned int delay_readCountMS()
{
    unsigned int val = TMR3L;
    val = val + (TMR3H << 8);

    return (val/32);
}


unsigned int delay_readCountUS()
{
    unsigned int val = TMR3L;
    val = val + (TMR3H << 8);

    return (unsigned int)(val*30.518);
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