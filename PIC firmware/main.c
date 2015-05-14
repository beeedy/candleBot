/*
 * File:   main.c
 * Author: broderickcarlin
 *
 * Created on April 9, 2015, 10:53 PM
 */


#include <xc.h>
#include "LCD.h"
#include "config.h"
#include "LCD.h"
#include "whiskers.h"
#include "UART.h"
#include "GlobalDefines.h"
#include "FONA.h"
#include "fft.h"
#include "motorDrive.h"
#include "delays.h"
#include "settings.h"
#include "encoders.h"
#include "PS2.h"
#include "compass.h"
#include "colorSensor.h"
#include "I2C.h"
#include "wiiCams.h"


char volatile FONA_BUFF[FONA_BUFF_SIZE], USB_BUFF[USB_BUFF_SIZE],
        PIXY_BUFF[PIXY_BUFF_SIZE], USART4_BUFF[50] = 0;
char volatile FONA_INDEX, USB_INDEX, PIXY_INDEX, UART4_INDEX = 0;

void init()
{
    IPEN = 1;   //enable interrupt priority

    signed char retVal = 0;

    settings_init();
    LCD_init4bit();
    motorDrive_init();
    delay_init();
    UART_init();
    encoders_init();
    fft_init();
    UART_init();
    clearMillis();
    I2C_init(1);

    if(retVal != 0) {
        LCD_printString(0, 0, "init /nFail:%i", (int)retVal);
        while(1);
    }
}

void debug()
{
    //delay_s(5);
    LCD_printString(0, 0, "Test\nSuccess");
    
    /*
    if(FONA_init() == SUCCESS)
    {
        char err = FONA_Text("Can we get muffin faded?",BroderickFoneNumber);
        if(err == SUCCESS)
        {
            LCD_printString(0,0,"FOUND\nTEXTED");
        }
        else
        {
            LCD_printString(0,0,"%i\nERROR",err);
        }
    }
    else
    {
         LCD_printString(0,0,"ERROR\nERROR");
    }
    */


    while(1)
    {
       
        

        /*
        char W = 0;
        char E = 0;
        for(int i = 0; i < 5; i++)
        {
            fft_execute();
            int freq = fft_maxFreq();
            if(freq > 2000 && freq < 3000)
            {
                ++W;
            }
            else if(freq > 3000 && freq < 4000)
            {
                ++E;
            }
        }

        if(W == 5)
        {
            LCD_clearDisplay();
            clearMillis();
            while(1)
            {
                LCD_printString(0,0,"West\n%i",millis()/1000);
                delay_ms(200);
            }
        }
        else if(E == 5)
        {
            LCD_clearDisplay();
            clearMillis();
            while(1)
            {
                LCD_printString(0,0,"East\n%i",millis()/1000);
                delay_ms(200);
            }
        }
        */
    }
}

void selfTest()
{
    //Code here to self test

    LCD_printString(0,0, "Self Cal\nWait Plz");
    
    while(settings_readButton() == 0);
    while(settings_readButton() == 1);
}

void wanderMode()
{
    LCD_printString(0,0, "Wanderin\n---..---");
    while(1)
    {

    }
}

void competitionMode()
{
    LCD_printString(0,0, "We are\nwinning!");
    while(1)
    {

    }
}

void RCMode()
{
    LCD_printString(0,0, "RC Mode\nSearch..");
    char done = PS2_init();
    while( done != 0 )
    {
        LCD_printString(0,0, "RC Mode\nERR: %i  ",done);
        delay_ms(500);
        done = PS2_init();
    }

    char type = PS2_readType();

    LCD_printString(0,0, "ana:%i\ntype %i",PS2_analog(PSS_LX),type);

    //LCD_printString(0,0, "RC Mode\nConnectd");

    while(1)
    {
        PS2_readGamepad();
        LCD_printString(0,0, "ana:%i\ntype %i",PS2_analog(PSS_LX),type);
        int left_speed = ((PS2_analog(PSS_LY) * 120) / 255) - 60;
        int right_speed = ((PS2_analog(PSS_RY) * 120) / 255) - 60;

        //scaling for drivability

        left_speed = min(left_speed, 75);
        right_speed = min(right_speed, 75);

        motorDrive_setSpeeds(right_speed, left_speed);
        //motorDrive_setSpeeds(0, 0);
        //motorDrive_limitedAccelerationSetSpeeds(left_speed, right_speed);
    }
}

void main()
{
    enableInterrupts();
    init();
    debug();

    while(1)
    {
        char mode;

        do {

            mode = (settings_selfTest() << 2) + (settings_wander() << 1) + settings_auto();

            switch(mode) {
                case 0:     //RC Mode
                    LCD_printString(0, 0, "Selected\nRC Mode");
                    break;

                case 1:     //Competition Mode
                    LCD_printString(0, 0, "Selected\nMatch");
                    break;

                case 2:     //Wander Mode
                    LCD_printString(0, 0, "Selected\nWander");
                    break;

                case 4:     //Self test
                    LCD_printString(0, 0, "Selected\nSelfTest");
                    break;

                case 5:     //Debug mode
                    LCD_printString(0, 0, "Selected\nDebug");
                    break;

                default:    //Unknown settings selected
                    LCD_printString(0, 0, "Selected\nUnknown");
                    break;
            }
            delay_ms(50);

        } while(settings_readButton() == 1 || mode > 5);
    
        switch(mode) {

            case 0:     //RC Mode
                RCMode();
                break;

            case 1:     //Competition Mode
                competitionMode();
                break;

            case 2:     //Wander Mode
                wanderMode();
                break;

            case 4:     //Self test
                selfTest();
                break;

            case 5:     //Debug mode
                debug();
                break;

            default:    //Error, this should never happen
                break;
        }
    }
}

void interrupt high_priority  communicationInterruptHandler()
{
    if(TMR0IF == 1)
    {
        TMR0L = millisStart; //When timer overflows, it will have taken 1ms
        TMR0IF = 0;  //Clear any flag to avoid errors
        TMR0IE = 1;  //Enable overflow interrupt
        tickMillis();
        return;
    }
    //INTCONbits.INT0IF = 0;  ???

    // Rearange for Priority

    if(0) {

        // I2C Comms 1
    }
    if(0) {

        // I2C Comms 2
    }
    if(PIR1bits.RC1IF)   // EUSART1 Receive buffer RCREG1 is full
    {
        FONA_BUFF[FONA_INDEX] = RCREG1;
        FONA_INDEX++;
    }
    if(PIR3bits.RC2IF)   // EUSART2 Receive buffer RCREG2 is full
    {
        // THIS SHOULD NEVER HAPPEN
    }
    if(PIR6bits.RC3IF)   // EUSART3 Receive buffer RCREG3 is full
    {
        PIXY_BUFF[PIXY_INDEX] = RCREG3;
        PIXY_INDEX++;
    }
    if(PIR6bits.RC4IF)   // EUSART4 Receive buffer RCREG4 is full
    {
        USB_BUFF[USB_INDEX] = RCREG4;
        USB_INDEX++;
    }
}