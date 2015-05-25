/*                      ___  ___      _
                        |  \/  |     (_)
                        | .  . | __ _ _ _ __    ___
                        | |\/| |/ _` | | '_ \  / __|
                        | |  | | (_| | | | | || (__
                        \_|  |_/\__,_|_|_| |_(_)___|

 * File: main.c
 * Author: Brodeick Carlin and Tyler Holmes
 *
 * This file contains all the functions that control the main flow of logic in
 * the software. This file contans void main(), the initial function that is
 * called when the pic initializes. All other functions in this file are used as
 * methods of condensing or organizing the control flow to make it more legible
 * and easier to follow. main()'s role is only to call a seperate function that
 * will be responsible for the main logic depending on the mode that has been
 * selected using the physical switches on the robots chassis.
 *
 * -------------------------------Function List---------------------------------
 * void loadMap()
 * char checkMap(int, int)
 * void clearArrays()
 * void fixSTR(char *output, char data[], ...)
 * void init()
 * void debug()
 * void selfTest()
 * void wanderMode()
 * void competitionMode()
 * void RCMode()
 * void main()
 * void interrupt high_priority  communicationInterruptHandler()
 *
 * ---------------------------Function Descriptions-----------------------------
 * void loadMap()
 *      This function takes all the data that has been loaded into the PIXY's
 *      UART buffer and formats it into a floor mapping that can be interpreeted
 *      as drivable areas and non-drivable areas. This function takes in no
 *      variables and returns no variables as it acts solely on global variables
 *
 * char checkMap(int, int)
 *      This function takes in a single coordinate in an (x,y) format and
 *      returns 0x00 if the location is drivable or 0x01 if the location is not
 *      drivable. The x and y values are integer numbers representing 2mm X 2mm
 *      squares. (0,0) is located immedietly in front of the robot with directly
 *      forward being the positive Y direction and positive X being to the right
 *      of the robot.
 *
 * void clearArrays()
 *      This function can be called to clear all the global arrays that are used
 *      to buffer incoming information from the various external serial devices.
 *      This function should only be called when the PIC has first powered up
 *      or you risk losing any information that has been added into these
 *      communication buffers.
 *
 * void fixSTR(char *output, char data[], ...)
 *      This function is a custom wrapped string formatting function, which
 *      microchip has ceased support of in the newest version of XC8. This
 *      function has the same interface as sprintf() has, taking a location to
 *      store the formated string, a string to be modified, and arguments to be
 *      formatted into the second string. This function does not directly return
 *      any values but instead works with a pointer that is sent to the function
 *
 * void init()
 *      This function should be called in order to initialize all external
 *      peripherals and interrupt handlers. This function does not take in any
 *      arguments and does not return anything, however it must be called before
 *      any other function can be reliably called.
 *
 * void debug()
 *      This function is called when debug mode is selected using the switches
 *      and buttons. This is a section that can be used to add code for
 *      debugging purposes without having to manipulate control flow that has
 *      been proven to be working.
 *
 * void selfTest()
 *      This function performs a self test on the various peripherals connected
 *      to the PIC and verifies that it is able to communicate with all of them
 *      successfully. This particular function communicates success/failure over
 *      UART as well as to the on board LCD. This double step approach is used
 *      in case an error occurs with either the LCD or the USB converter.
 *
 * void wanderMode()
 *      This is an unimplemented mode that was originally designed to act as a
 *      'roomba' approach. The goal for this mode was to have a robot that would
 *      wander around its environment making notes of its surroundings. This was
 *      never worked on officially and hope is this will be completed at a later
 *      time.
 *
 * void competitionMode()
 *      This is the mode used to compete in the Candle Bot competition. This
 *      function contains all the logic used for responding to a tone and
 *      locating a candle in the 'maze'. This function was able to reliably find
 *      the candle in approximatly 19Sec.
 *
 * void RCMode()
 *      This is the mode to enter when RC is decisired over the robots movements
 *      It is important to check and verify that a PS2 controller has been
 *      connected to the appropriate jack on the robot before this function is
 *      called. This allows control of the motors two drive motors using the
 *      analog sticks on the controller.
 *
 * void main()
 *      This is the very first function that is called upon startup, and is used
 *      as a menu system to select the mode that is desired. Main is not
 *      responsible for any of the logic seen in any single mode, rather is
 *      allows the user to select and enter any single one of these modes using
 *      the dip switches and button to select the mode they desire.
 *
 * void interrupt high_priority  communicationInterruptHandler()
 *      This function is the interrrupt handler for all high priority interrupts
 *      that may occur during program flow. This handler is responsible for
 *      handling all interrupts that relate to data communication as well as
 *      accurate time keeping through the use of Timer 0 as a millisecond timer. 
 
Copyright (c) 2015 Broderick Carlin & Tyler Holmes

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
the Software, and to permit persons to whom the Software is furnished to do so,
subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
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

#define textMode


char volatile FONA_BUFF[FONA_BUFF_SIZE], USB_BUFF[USB_BUFF_SIZE],
        PIXY_BUFF[PIXY_BUFF_SIZE], USART4_BUFF[50] = 0;
char volatile FONA_INDEX, USB_INDEX, PIXY_INDEX, UART4_INDEX = 0;

char volatile drivableMap[40][5];


void loadMap()
{
    for(int i = 0; i < 200; i++)
    {
        //remapping pixy buffer to the map buffer
        drivableMap[i/5][i%5] = PIXY_BUFF[i];
    }
}

char checkMap(int x, int y)
{
    // accessing an individual bit from the 2D byte array
    return (drivableMap[x][y/8] >> (y%8)) & 0x01;
}

void clearArrays()
{
    for(int i = 0; i < FONA_BUFF_SIZE; i++)
    {
        //Filling Fona buffer with nulls
        FONA_BUFF[i] = '\0';
    }

    for(int i = 0; i < USB_BUFF_SIZE; i++)
    {
        //Filling USB buffer with nulls
        USB_BUFF[i] = '\0';
    }

    for(int i = 0; i < PIXY_BUFF_SIZE; i++)
    {
        //Filling Pixy buffer with nulls
        PIXY_BUFF[i] = '\0';
    }

}

void fixSTR(char *output, char data[], ...)
{
    //create a va list to handle the unknown arguments
    va_list aptr;
    va_start(aptr,data);

    //create a 0 length string at our output
    output[0] = '\0';

    //iterate through the input string and place variabes where need be
    for(int i = 0; data[i] != '\0' && i < 200; i++)
    {
        if(data[i] == '%')
        {
            if(data[i+1] == '%')
            {
                strcat(output, "%");
            }
            else
            {
                int val = va_arg(aptr, int);
                char tempString[20];
                sprintf(tempString,"%i",val);
                strcat(output, tempString);
            }
            i++;
        }
        else
        {
            char tempString[2];
            tempString[0] = data[i];
            tempString[1] = '\0';
            strcat(output,tempString);
        }
    }

    //deallocate va list
    va_end(aptr);
}

void init()
{
    IPEN = 1;   //enable interrupt priority

    //create variable to handle error values
    signed char retVal = 0;

    clearArrays();
    settings_init();
    LCD_init4bit();
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

    //a check of retval could be done at this point to alert the control flow
    //of any errors that occured during initialization.
}

void debug()
{

}

void selfTest()
{

    signed char retVal = 0;
    signed char errors = 0;

    LCD_printString(0, 0, "INITSELF\nTEST(5s)");
    UART_transmitString(USB, "Init Self Test in 5 sec...\n\r");
    delay_s(5);


    I2C_open(WII_CAM_LEFT);
    retVal = I2C_write(WII_CAM_LEFT, WII_CAM_ADR);
    I2C_close(WII_CAM_LEFT);
    if(retVal != 0) {
        LCD_printString(0, 0, "LEFT WII\n--FAIL--");
        UART_transmitString(USB, "Left Wii Init Fail. Error: %i\n\r\n\r", retVal);
        delay_s(5);
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
    //FONA_Text("Ready to begin", BroderickFoneNumber);

    UART_transmitByte(PIXY, 24);

    

    ////////////////////////////////////////////////////////////////////////////
    /////////// Wait for start tone and determine direction to begin  //////////
    ////////////////////////////////////////////////////////////////////////////

    char direction = 0;

    do
    {
        char W = 0;
        char E = 0;

        for(int i = 0; i < 5; i++)
        {
            fft_execute();
            int freq = fft_maxFreq();

            if(freq > 2300 && freq < 2700)
            {
                ++W;
            }
           else if(freq > 3600 && freq < 4000)
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

    unsigned char rawDataLeft[12], rawDataRight[12];
    int processedDataLeft[12], processedDataRight[12];

    UART_transmitByte(PIXY, 30);

    motorDrive_drive(650, 120);
    MOVEDELAY();

    if(settings_readSettings() == 0x00)
    {
        if(direction == WEST_SIDE)
        {
            direction == EAST_SIDE;
        }
        else
        {
            direction == WEST_SIDE;
        }
    }

    if(direction == WEST_SIDE)
    {
        motorDrive_turn(80);
        MOVEDELAY();
    }
    else
    {
        motorDrive_turn(-90);
    }

    motorDrive_drive(300, 30);
    MOVEDELAY();
    motorDrive_turn(-80);
    MOVEDELAY();

    for(int i = 0; i < 7; i++)
    {

        motorDrive_turn(5 * i);
        MOVEDELAY();
        wiiCams_read(WII_CAM_LEFT, rawDataLeft);
        wiiCams_read(WII_CAM_RIGHT, rawDataRight);

        wiiCams_processData(rawDataLeft, processedDataLeft);
        wiiCams_processData(rawDataRight, processedDataRight);

        if(wiiCams_findCandle(processedDataLeft, processedDataRight) == 1)
        {
            motorDrive_drive(2000, 0);
            // found candle
            char dat[144];
            fixSTR(dat, "Found Candle in %i seconds",(int)(millis()/1000));
            FONA_Text(dat, BroderickFoneNumber);

            while(1);
        }
    }
    

    MOVEDELAY();
    motorDrive_drive(320, 30);
    MOVEDELAY();
    motorDrive_turn(75);
    MOVEDELAY();
    motorDrive_drive(350, 30);

    for(int i = 0; i < 50; i++)
    {

        motorDrive_turn(2);
        MOVEDELAY();
        wiiCams_read(WII_CAM_LEFT, rawDataLeft);
        wiiCams_read(WII_CAM_RIGHT, rawDataRight);

        wiiCams_processData(rawDataLeft, processedDataLeft);
        wiiCams_processData(rawDataRight, processedDataRight);

        if(wiiCams_findCandle(processedDataLeft, processedDataRight) == 1)
        {
            motorDrive_drive(2000, 0);
            // found candle

            char dat[144];
            fixSTR(dat, "Found Candle in %i seconds",(int)(millis()/1000));
            FONA_Text(dat, BroderickFoneNumber);

            while(1);
        }
    }
}

void RCMode()
{
    LCD_printString(0,0, "RC Mode\nSearch..");
    UART_transmitString(USB, "RC Mode: Searching...\n\r");
    char done = PS2_init();
    while( done != 0 )
    {
        //attempt to connect to a PS2 controller every 500ms until one is found
        LCD_printString(0,0, "RC Mode\nERR: %i  ",done);
        UART_transmitString(USB, "RC Mode: Error: %i \n\r", done);
        delay_ms(500);
        done = PS2_init();
    }

    char type = PS2_readType();

    LCD_printString(0,0, "RC Mode\nConnectd");

    while(1)
    {
        // loop continuously, reading values of the controls I/O
        PS2_readGamepad();
        LCD_printString(0,0, "ana:%i\ntype %i",PS2_analog(PSS_LX),type);
        UART_transmitString(USB, "analog: %i\n\rtype: %i\n\r", PS2_analog(PSS_LX), type);
        int left_speed = ((PS2_analog(PSS_LY) * 120) / 255) - 60;
        int right_speed = ((PS2_analog(PSS_RY) * 120) / 255) - 60;
        motorDrive_setSpeeds(right_speed, left_speed);
    }
}

void main()
{
    enableInterrupts();
    init();

    while(1)
    {
        char mode;

        //loop through until the user pressed the button to select a mode
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

        // enter the mode selected by the user
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
    //interrupt to keep the millis() timer running, this will be called every ms
    if(TMR0IF == 1)
    {
        TMR0L = millisStart; //When timer overflows, it will have taken 1ms
        TMR0IF = 0;  //Clear any flag to avoid errors
        TMR0IE = 1;  //Enable overflow interrupt
        tickMillis();
        return;
    }
    
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