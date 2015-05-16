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

void clearArrays()
{
    for(int i = 0; i < FONA_BUFF_SIZE; i++)
    {
        FONA_BUFF[i] = '\0';
    }

    for(int i = 0; i < USB_BUFF_SIZE; i++)
    {
        USB_BUFF[i] = '\0';
    }

    for(int i = 0; i < PIXY_BUFF_SIZE; i++)
    {
        PIXY_BUFF[i] = '\0';
    }

}

void init()
{
    IPEN = 1;   //enable interrupt priority

    signed char retVal = 0;

    clearArrays();
    settings_init();
    //LCD_init4bit();
    motorDrive_init();
    delay_init();
    UART_init();
    encoders_init();
    fft_init();
    clearMillis();
    I2C_init(1);
    I2C_init(2);
    retVal += compass_mainBoardInit();
    retVal += wiiCams_init();
    retVal += colorSensor_init();
}

void debug()
{
    while(1)
    {
        char retVals[8];
        colorSensor_read(READ_CLEAR,retVals);
        int i = (retVals[0] << 8) + retVals[1];
        UART_transmitString(USB,"\rClear: %i",i);
    }

/*
    while(1)
    {
       
        fft_execute();
        int freq = fft_maxFreq();
        UART_transmitString(USB, "Freq: %i\n\r", freq);
    }
*/
        /*
        char W = 0;
        char E = 0;
        for(int i = 0; i < 5; i++)
        {
            
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
        
    }*/
}

void selfTest()
{
    //Code here to self test

    signed char retVal = 0;
    signed char errors = 0;

    enableInterrupts();
    LCD_printString(0, 0, "INITSELF\nTEST(5s)");
    UART_transmitString(USB, "Init Self Test in 5 sec...\n\r");
    delay_s(5);
    disableInterrupts();


    I2C_open(WII_CAM_LEFT);
    retVal = I2C_write(WII_CAM_LEFT, WII_CAM_ADR);
    I2C_close(WII_CAM_LEFT);
    if(retVal != 0) {
        enableInterrupts();
        LCD_printString(0, 0, "LEFT WII\n--FAIL--");
        UART_transmitString(USB, "Left Wii Init Fail. Error: %i\n\r\n\r", retVal);
        delay_s(5);
        disableInterrupts();
        errors++;
    }


    I2C_open(WII_CAM_RIGHT);
    retVal = I2C_write(WII_CAM_RIGHT, WII_CAM_ADR);
    I2C_close(WII_CAM_RIGHT);
    if(retVal != 0) {
        enableInterrupts();
        LCD_printString(0, 0, "RIGHT WII\n--FAIL--");
        UART_transmitString(USB, "Right Wii Init Fail. Error: %i\n\r\n\r", retVal);
        delay_s(5);
        disableInterrupts();
        errors++;
    }

    I2C_open(COLOR_SENSOR);
    retVal = I2C_write(COLOR_SENSOR, COLOR_SENSOR_ADR);
    I2C_close(COLOR_SENSOR);
    if(retVal != 0) {
        enableInterrupts();
        LCD_printString(0, 0, "ColorSen\n--FAIL--");
        UART_transmitString(USB, "Color Sensor Init Fail. Error: %i\n\r\n\r", retVal);
        delay_s(5);
        disableInterrupts();
        errors++;
    }

    I2C_open(COMPASS_MAIN);
    retVal = I2C_write(COMPASS_MAIN, COMPASS_ADR);
    I2C_close(COMPASS_MAIN);
    if(retVal != 0) {
        enableInterrupts();
        LCD_printString(0, 0, "MainComp\n--FAIL--");
        UART_transmitString(USB, "Main Compass Init Fail. Error: %i\n\r\n\r", retVal);
        delay_s(5);
        disableInterrupts();
        errors++;
    }

    if(errors != 0) {
        enableInterrupts();
        LCD_printString(0, 0, "=ERRORS=\nnum: %i", errors);
        UART_transmitString(USB, "Total Errors: %i\n\r\n\r", errors);
        delay_s(10);
        disableInterrupts();
    }

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
    ////////////////////////////////////////////////////////////////////////////
    /////////// PERFORM INITIAL CHECK OF HARDWARE AND NOTIFY OVER SMS //////////
    ////////////////////////////////////////////////////////////////////////////

    signed char retVal = 0;
    retVal += compass_mainBoardInit();
    retVal += (wiiCams_init() << 1);
    retVal += (colorSensor_init() << 2);

    switch(retVal)
    {
        case 0:
            FONA_Text("Ready to begin\nCompass: OK\nIR Cams: OK\nColor: OK\n\n\nWaiting for start tone", TylerFoneNumber);
            FONA_Text("Ready to begin\nCompass: OK\nIR Cams: OK\nColor: OK\n\n\nWaiting for start tone", BroderickFoneNumber);
            break;

        case 1:
            FONA_Text("Ready to begin\nCompass: ERR\nIR Cams: OK\nColor: OK\n\n\nWaiting for start tone", TylerFoneNumber);
            FONA_Text("Ready to begin\nCompass: ERR\nIR Cams: OK\nColor: OK\n\n\nWaiting for start tone", BroderickFoneNumber);
            break;

        case 2:
            FONA_Text("Ready to begin\nCompass: OK\nIR Cams: ERR\nColor: OK\n\n\nWaiting for start tone", TylerFoneNumber);
            FONA_Text("Ready to begin\nCompass: OK\nIR Cams: ERR\nColor: OK\n\n\nWaiting for start tone", BroderickFoneNumber);
            break;

        case 3:
            FONA_Text("Ready to begin\nCompass: ERR\nIR Cams: ERR\nColor: OK\n\n\nWaiting for start tone", TylerFoneNumber);
            FONA_Text("Ready to begin\nCompass: ERR\nIR Cams: ERR\nColor: OK\n\n\nWaiting for start tone", BroderickFoneNumber);
            break;

        case 4:
            FONA_Text("Ready to begin\nCompass: OK\nIR Cams: OK\nColor: ERR\n\n\nWaiting for start tone", TylerFoneNumber);
            FONA_Text("Ready to begin\nCompass: OK\nIR Cams: OK\nColor: ERR\n\n\nWaiting for start tone", BroderickFoneNumber);
            break;

        case 5:
            FONA_Text("Ready to begin\nCompass: ERR\nIR Cams: OK\nColor: ERR\n\n\nWaiting for start tone", TylerFoneNumber);
            FONA_Text("Ready to begin\nCompass: ERR\nIR Cams: OK\nColor: ERR\n\n\nWaiting for start tone", BroderickFoneNumber);
            break;

        case 6:
            FONA_Text("Ready to begin\nCompass: OK\nIR Cams: ERR\nColor: ERR\n\n\nWaiting for start tone", TylerFoneNumber);
            FONA_Text("Ready to begin\nCompass: OK\nIR Cams: ERR\nColor: ERR\n\n\nWaiting for start tone", BroderickFoneNumber);
            break;

        case 7:
            FONA_Text("Ready to begin\nCompass: ERR\nIR Cams: ERR\nColor: ERR\n\n\nWaiting for start tone", TylerFoneNumber);
            FONA_Text("Ready to begin\nCompass: ERR\nIR Cams: ERR\nColor: ERR\n\n\nWaiting for start tone", BroderickFoneNumber);
            break;
    }

    ////////////////////////////////////////////////////////////////////////////
    /////////// Wait for start tone and determine direction to begin  //////////
    ////////////////////////////////////////////////////////////////////////////

    char direction = 0;

    do
    {
        char W = 0;
        char E = 0;

        fft_execute();
        int freq = fft_maxFreq();

        for(int i = 0; i < 5; i++)
        {

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
            clearMillis();
            direction = WEST_SIDE;
        }
        else if(E == 5)
        {
            clearMillis();
            direction = EAST_SIDE;
        }
    }while(direction == 0);

    ////////////////////////////////////////////////////////////////////////////
    /////////// MotorDrive code needs to be placed here based off of  //////////
    ///////////     ground map that is grabbed from the pixy cam      //////////
    ////////////////////////////////////////////////////////////////////////////

}

void RCMode()
{
    //LCD_printString(0,0, "RC Mode\nSearch..");

    UART_transmitString(USB, "RC Mode: Searching...\n\r");
    char done = PS2_init();
    while( done != 0 )
    {
        //LCD_printString(0,0, "RC Mode\nERR: %i  ",done);
        UART_transmitString(USB, "RC Mode: Error: %i \n\r", done);
        delay_ms(500);
        done = PS2_init();
    }

    char type = PS2_readType();

    //LCD_printString(0,0, "ana:%i\ntype %i",PS2_analog(PSS_LX),type);
    UART_transmitString(USB, "analog: %i\n\rtype: %i\n\r", PS2_analog(PSS_LX), type);

    //LCD_printString(0,0, "RC Mode\nConnectd");

    while(1)
    {
        PS2_readGamepad();
        //LCD_printString(0,0, "ana:%i\ntype %i",PS2_analog(PSS_LX),type);
        UART_transmitString(USB, "analog: %i\n\rtype: %i\n\r", PS2_analog(PSS_LX), type);
        int left_speed = ((PS2_analog(PSS_LY) * 120) / 255) - 60;
        int right_speed = ((PS2_analog(PSS_RY) * 120) / 255) - 60;

        //scaling for drivability

        //left_speed = min(left_speed, 65);
        //right_speed = min(right_speed, 65);

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

            //mode = (settings_selfTest() << 2) + (settings_wander() << 1) + settings_auto();
            mode = 4;
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
    
    if(PIR1bits.RC1IF)   // EUSART1 Receive buffer RCREG1 is full
    {
        char temp = RCREG1;
        FONA_BUFF[FONA_INDEX] = temp;
        FONA_INDEX++;

        TXREG1 = RCREG1;
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