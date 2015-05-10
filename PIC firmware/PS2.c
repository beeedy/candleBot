/*                          ______  _____  _____
                            | ___ \/  ___|/ __  \
                            | |_/ /\ `--. `' / /'
                            |  __/  `--. \  / /
                            | |    /\__/ /./ /___
                            \_|    \____/ \_____/
                        ______                     _
                        | ___ \                   | |
                        | |_/ /___ _ __ ___   ___ | |_ ___
                        |    // _ \ '_ ` _ \ / _ \| __/ _ \
                        | |\ \  __/ | | | | | (_) | ||  __/
                        \_| \_\___|_| |_| |_|\___/ \__\___|

 * File:   PS2.h
 * Author: Broderick Carlin
 */

#include "PS2.h"

static char enter_config[]={0x01,0x43,0x00,0x01,0x00};
static char set_mode[]={0x01,0x44,0x00,0x01,0x03,0x00,0x00,0x00,0x00};
static char exit_config[]={0x01,0x43,0x00,0x00,0x5A,0x5A,0x5A,0x5A,0x5A};
volatile char type_read[]={0x01,0x45,0x00,0x5A,0x5A,0x5A,0x5A,0x5A,0x5A};
volatile unsigned char PS2data[21];
volatile unsigned int last_buttons;
volatile unsigned int buttons;
volatile char read_delay;
volatile char controller_type;
volatile unsigned long last_read = 0;

char PS2_init()
{
    char temp[sizeof(type_read)];

    TRISFbits.TRISF2 = 0;
    TRISFbits.TRISF3 = 1;
    TRISFbits.TRISF5 = 0;
    TRISFbits.TRISF6 = 0;


    CMD = 1;
    CLK = 1;

    PS2_readGamepad();
    PS2_readGamepad();

    if(PS2data[1] != 0x41 && PS2data[1] != 0x73 && PS2data[1] != 0x79)
    {
        return 1; //return error code 1
    }

    //try setting mode, increasing delays if need be.
    read_delay = 1;

    for(int y = 0; y <= 10; y++)
    {
        PS2_sendCommandString(enter_config, sizeof(enter_config)); //start config run

        //read type
        delay_us(CTRL_BYTE_DELAY);

        CMD = 1;
        CLK = 1;
        ATT = 0; // low enable joystick

        delay_us(CTRL_BYTE_DELAY);

        for (int i = 0; i<9; i++)
        {
            temp[i] = PS2_shiftInOut(type_read[i]);
        }

        ATT = 1; // HI disable joystick

        controller_type = temp[3];

        PS2_sendCommandString(set_mode, sizeof(set_mode));

        PS2_sendCommandString(exit_config, sizeof(exit_config));

        PS2_readGamepad();

        if(PS2data[1] == 0x73)
        break;

        if(y == 10)
        {
            return 2; //exit function with error
        }
        read_delay += 1; //add 1ms to read_delay
  }
  return 0; //no error if here
}

void PS2_readGamepad()
{
    long temp = millis() - last_read;

    if (temp > 1500) //waited to long
    {
        PS2_reconfig();
    }

    if(temp < read_delay)  //waited too short
    {
        delay_ms(read_delay - temp);
    }

    last_buttons = buttons;

    CMD = 1;
    CLK = 1;
    ATT = 0; // low enable joystick

    delay_us(CTRL_BYTE_DELAY);
    //Send the command to send button and joystick data;

    char dword[9] = {0x01,0x42,0,0,0x00,0,0,0,0};
    char dword2[12] = {0,0,0,0,0,0,0,0,0,0,0,0};


    for (int i = 0; i<9; i++)
    {
        PS2data[i] = PS2_shiftInOut(dword[i]);
    }

    if(PS2data[1] == 0x79)
    {  //if controller is in full data return mode, get the rest of data
        for (int i = 0; i<12; i++)
        {
            PS2data[i+9] = PS2_shiftInOut(dword2[i]);
        }
    }

    ATT = 1;

    buttons = *(unsigned int*)(PS2data+3);   //store as one value for multiple functions
    last_read = millis();
}

void PS2_reconfig()
{
    PS2_sendCommandString(enter_config, sizeof(enter_config));
    PS2_sendCommandString(set_mode, sizeof(set_mode));
    PS2_sendCommandString(exit_config, sizeof(exit_config));
}

void PS2_sendCommandString(char string[], char len)
{
    ATT = 0; // low enable joystick
    for (int y=0; y < len; y++)
    {
        PS2_shiftInOut(string[y]);
    }

    ATT = 1; //high disable joystick
    delay_ms(read_delay);                  //wait a few
}

char PS2_shiftInOut(char byte)
{
    unsigned char tmp = 0;
    for(unsigned char i = 0; i < 8; i++)
    {
        if(CHK(byte,i))
        {
            CMD = 1;
        }
        else
        {
            CMD = 0;
        }

        CLK = 0;
        delay_us(CTRL_CLK);

        if(DAT == 1)
        {
            bitSet(tmp,i);
        }

        CLK = 1;
    }
    CMD = 1;
    delay_us(CTRL_BYTE_DELAY);
    return tmp;
}

char PS2_readType()
{
    if(controller_type == 0x03)
        return 1;
    else if(controller_type == 0x01)
        return 2;
    else if(controller_type == 0x0C)
        return 3;  //2.4G Wireless Dual Shock PS2 Game Controller

    return controller_type;
}


/****************************************************************************************/
char PS2_newButtons()
{
    if((last_buttons ^ buttons) > 0)
    {
        return 1;
    }
    return 0;
}

/****************************************************************************************/
char PS2_newButtonState(unsigned int button)
{
  if(((last_buttons ^ buttons) & button) > 0)
    {
        return 1;
    }
    return 0;
}

/****************************************************************************************/
char PS2_buttonPressed(unsigned int button)
{
  if((PS2_newButtonState(button) & PS2_button(button)) > 0)
    {
        return 1;
    }
    return 0;
}

/****************************************************************************************/
char PS2_buttonReleased(unsigned int button)
{
    if((PS2_newButtonState(button)) & ((~last_buttons & button) > 0))
    {
        return 1;
    }
    return 0;
}

/****************************************************************************************/
char PS2_button(unsigned int button)
{
    if((~buttons & button) > 0)
    {
        return 1;
    }
    return 0;
}

/****************************************************************************************/
unsigned int PS2_buttonDataByte()
{
   return (~buttons);
}

/****************************************************************************************/
char PS2_analog(char button)
{
   return PS2data[button];
}
