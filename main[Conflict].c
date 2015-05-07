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
#include "i2c.h"

char volatile FONA_BUFF[FONA_BUFF_SIZE], USB_BUFF[USB_BUFF_SIZE],
        PIXY_BUFF[PIXY_BUFF_SIZE], USART4_BUFF[50] = 0;
char volatile FONA_INDEX, USB_INDEX, PIXY_INDEX, UART4_INDEX = 0;

void init()
{
    settings_init();
    fft_init();
    motorDrive_init();
    LCD_init4bit();
    UART_init();
    encoders_init();
    i2c_init();


    clearMillis();
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
        //LCD_printString(0,0, "ana:%i\ntype %i",PS2_analog(PSS_LX),type);
        int left_speed = ((PS2_analog(PSS_LY) * 200) / 255) - 100;
        int right_speed = ((PS2_analog(PSS_RY) * 200) / 255) - 100;

        //scaling for drivability

        motorDrive_setSpeeds(right_speed, left_speed);
        delay_ms(50);
    }
}

void main()
{
    IPEN = 1;
    init();


    /* Tyler's Crap
    delay_s(1);

    LCD_printString(0,0," I2C \n TEST ");

    if(compass_pixyInit() != 0) {

        LCD_printString(0,0,"Pix comp\n Error");
    }
    else {

        LCD_printString(0,0,"Pix comp\nsuccess");
    }

    delay_s(5);

    if(compass_mainBoardInit() != 0) {

        LCD_printString(0,0,"Main com\n Error");
    }
    else {
        LCD_printString(0,0,"Main com\nsuccess");

    }

    */

    ///////
    RCMode();
    ///////

    while(settings_readButton() == 0);
    
    if(settings_selfTest() == 1)
    {
        selfTest();
    }
    
    if(settings_wander() == 1)
    {
        wanderMode();
    }
    
    if(settings_auto() == 1)
    {
        competitionMode();
    }
    
    RCMode();
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