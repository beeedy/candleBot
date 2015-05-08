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
//#include "compass.h"
//#include "I2C.h"

char volatile FONA_BUFF[FONA_BUFF_SIZE], USB_BUFF[USB_BUFF_SIZE],
        PIXY_BUFF[PIXY_BUFF_SIZE], USART4_BUFF[50] = 0;
char volatile FONA_INDEX, USB_INDEX, PIXY_INDEX, UART4_INDEX = 0;

void init()
{
    settings_init();
    motorDrive_init();
    LCD_init4bit();
    UART_init();
    encoders_init();
    fft_init();
    //I2C_init(1);
    //I2C_init(1);

    clearMillis();
}

void debug()
{
    //disableInterrupts();
    while(1)
    {
        fft_collectData();
        fft_execute();
        //LCD_printString(0,0,"Freq:\n%i    ",fft_maxFreq());
        for(int i = 1; i < 32; i++)
        {
            //UART_transmitString(USB,"%i\n\r",fft_readBin(i));
            
            int temp = fft_readBin(i);
            while(temp > 0)
            {
               UART_transmitByte(USB,0xB2);
               temp -= 4;
            }
            UART_transmitByte(USB,'\n');
            UART_transmitByte(USB,'\r');
            
        }
        delay_ms(5);

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
        //LCD_printString(0,0, "ana:%i\ntype %i",PS2_analog(PSS_LX),type);
        int left_speed = ((PS2_analog(PSS_LY) * 120) / 255) - 60;
        int right_speed = ((PS2_analog(PSS_RY) * 120) / 255) - 60;

        //scaling for drivability

        motorDrive_setSpeeds(right_speed, left_speed);
        delay_ms(50);
    }
}

void main()
{
//'########::'########::::'###::::'########:::::'##::::'##:'########:
// ##.... ##: ##.....::::'## ##::: ##.... ##:::: ###::'###: ##.....::
// ##:::: ##: ##::::::::'##:. ##:: ##:::: ##:::: ####'####: ##:::::::
// ########:: ######:::'##:::. ##: ##:::: ##:::: ## ### ##: ######:::
// ##.. ##::: ##...:::: #########: ##:::: ##:::: ##. #: ##: ##...::::
// ##::. ##:: ##::::::: ##.... ##: ##:::: ##:::: ##:.:: ##: ##:::::::
// ##:::. ##: ########: ##:::: ##: ########::::: ##:::: ##: ########:
//..:::::..::........::..:::::..::........::::::..:::::..::........::

    //  DO NOT PUT DEBUG CODE HERE!!!!!
    //
    //  Use the debug function for code you are currently trying to
    //  debug. main() should NOT BE EDITED any more, ie. it is finalized.
    //  Use the dip switches to select debug mode (look at the LCD) and
    //  once selected press the button to enter debug mode.
    //
    //  If there is a mode you would like that is not included already,
    //  feel free to add it into BOTH switch statements and to modify the
    //  do while to correct for any changes.
    //
    //  ps. I took the liberty of moving your I2C code there already

    IPEN = 1;
    enableInterrupts();
    init();
    debug();

    while(1)
    {
        char mode;

        do
        {

            mode = (settings_selfTest() << 2) + (settings_wander() << 1) + settings_auto();

            switch(mode)
            {
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
        }while(settings_readButton() == 1 || mode > 5);
    
        switch(mode)
        {
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