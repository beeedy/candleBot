/*                           _     ___________
                            | |   /  __ \  _  \
                            | |   | /  \/ | | |
                            | |   | |   | | | |
                            | |___| \__/\ |/ /
                            \_____/\____/___/
 * File:   LCD.c
 * Author: Broderick Carlin
 */

#include "LCD.h"

#define mode_4bit 1
#define mode_8bit 2

#define LCD_DB0 PORTEbits.RE5
#define LCD_DB1 PORTHbits.RH2
#define LCD_DB2 PORTHbits.RH1
#define LCD_DB3 PORTHbits.RH0
#define LCD_DB4 PORTEbits.RE2 /* RF2 */
#define LCD_DB5 PORTEbits.RE0 /* RF4 */
#define LCD_DB6 PORTEbits.RE1 /* RF5 */
#define LCD_DB7 PORTHbits.RH5 /* RF6 */
#define LCD_E   PORTEbits.RE4 /* RF3 */
#define LCD_RS  PORTDbits.RD0 /* RD0 */
#define LCD_RW  PORTGbits.RG7

// Inline function for writing out the 8 values for 8-bit mode
#define LCD_write8bit(data_in) \
    {\
    LCD_DB7 = ((data_in >> 7) & 1);\
    LCD_DB6 = ((data_in >> 6) & 1);\
    LCD_DB5 = ((data_in >> 5) & 1);\
    LCD_DB4 = ((data_in >> 4) & 1);\
    LCD_DB3 = ((data_in >> 3) & 1);\
    LCD_DB2 = ((data_in >> 2) & 1);\
    LCD_DB1 = ((data_in >> 1) & 1);\
    LCD_DB0 = (data_in & 1);\
    }

// Inline function for writing out the 4 values for 4-bit mode
#define LCD_write4bit(data_in) \
    {\
    LCD_DB7 = ((data_in >> 3) & 1);\
    LCD_DB6 = ((data_in >> 2) & 1);\
    LCD_DB5 = ((data_in >> 1) & 1);\
    LCD_DB4 = (data_in & 1);\
    }


volatile char mode = 0;

void LCD_init4bit()
{

    mode = mode_4bit;

    ANSEL21 = 0;    //configure H3 as digital I/O
    ANSEL6  = 0;
    ANSEL11 = 0;
    ANSEL10 = 0;
    ANSEL9  = 0;

    MEMCONbits.EBDIS = 1;
    PSPCONbits.PSPMODE = 0;
    LCDMD = 0;
    LCDCONbits.WERR = 0;
    CPEN = 0;
    LCDA = 0;

    LCD_DB4 = 0;      // LCD DB4
    LCD_DB5 = 0;      // LCD DB5
    LCD_DB6 = 0;      // LCD DB6
    LCD_DB7 = 0;      // LCD DB7

    LCD_E = 0;      // LCD E
    LCD_RS = 0;      // LCD RS
    LCD_RW = 0;      // LCD R/W



    TRISDbits.TRISD0 = 0;
    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    TRISEbits.TRISE2 = 0;
    TRISEbits.TRISE3 = 0;
    TRISEbits.TRISE4 = 0;
    TRISHbits.TRISH5 = 0;

    delay_init();
    delay_ms(100);

    LCD_RS = 0;
    LCD_RW = 0;

    ////////////////////// Function Set //////////////////////
    delay_long();
    LCD_E = 1;
    LCD_write4bit(0x3);
    delay_long();
    LCD_E = 0;

    delay_ms(50); // 50

    ////////////////////// Function Set //////////////////////
    delay_long();
    LCD_E = 1;
    LCD_write4bit(0x3);
    delay_long();
    LCD_E = 0;

    delay_ms(50); // 50

    ////////////////////// Function Set //////////////////////
    delay_long();
    LCD_E = 1;
    LCD_write4bit(0x3);
    delay_long();
    LCD_E = 0;

    delay_ms(50); // 50

    //////////////////// 4-bit interface ////////////////////
    delay_long();
    LCD_E = 1;
    LCD_write4bit(0x2);
    delay_long();
    LCD_E = 0;

    delay_ms(50); // 5

    ///////////////// font and # of lines  /////////////////
    delay_long();
    LCD_E = 1;
    LCD_write4bit(0x2);
    delay_long();
    LCD_E = 0;

    delay_long();
    LCD_E = 1;
    LCD_write4bit(0x8);
    delay_long();
    LCD_E = 0;

    ///////////////// cursor and disp on  /////////////////
    delay_long();
    LCD_E = 1;
    LCD_write4bit(0x0);
    delay_long();
    LCD_E = 0;

    delay_long();
    LCD_E = 1;
    LCD_write4bit(0xF);
    delay_long();
    LCD_E = 0;

    /////////////////// clear display  ///////////////////
    delay_long();
    LCD_E = 1;
    LCD_write4bit(0x0);
    delay_long();
    LCD_E = 0;

    delay_long();
    LCD_E = 1;
    LCD_write4bit(0x1);
    delay_long();
    LCD_E = 0;

    //////////////// increment on write  ////////////////
    delay_long();
    LCD_E = 1;
    LCD_write4bit(0x0);
    delay_long();
    LCD_E = 0;

    delay_long();
    LCD_E = 1;
    LCD_write4bit(0x6);
    delay_long();
    LCD_E = 0;
    
}


void LCD_init8bit()
{
    mode = mode_8bit;

    ANSEL16 = 0;    //configure H0 as digital I/O
    ANSEL17 = 0;    //configure H1 as digital I/O
    ANSEL18 = 0;    //configure H2 as digital I/O
    ANSEL19 = 0;    //configure H3 as digital I/O

    LCD_DB0 = 0;    // LCD DB0
    LCD_DB1 = 0;    // LCD DB1
    LCD_DB2 = 0;    // LCD DB2
    LCD_DB3 = 0;    // LCD DB3
    LCD_DB4 = 0;    // LCD DB4
    LCD_DB5 = 0;    // LCD DB5
    LCD_DB6 = 0;    // LCD DB6
    LCD_DB7 = 0;    // LCD DB7

    LCD_E = 0;      // LCD E
    LCD_RS = 0;     // LCD RS
    LCD_RW = 0;     // LCD R/W


    TRISE5 = 0;     // LCD DB0
    TRISH2 = 0;     // LCD DB1
    TRISH1 = 0;     // LCD DB2
    TRISH0 = 0;     // LCD DB3
    TRISE2 = 0;     // LCD DB4
    TRISE0 = 0;     // LCD DB5
    TRISE1 = 0;     // LCD DB6
    TRISH3 = 0;     // LCD DB7

    TRISE4 = 0;     // LCD E
    TRISE3 = 0;     // LCD RS
    TRISG7 = 0;     // LCD R/W

    delay_init();
    delay_ms(100);

    LCD_RS = 0;
    LCD_RW = 0;

    ////////////////////// Function Set //////////////////////
    delay_short();
    LCD_E = 1;
    LCD_write4bit(0x3);
    delay_long();
    LCD_E = 0;

    delay_ms(50);

    ////////////////////// Function Set //////////////////////
    delay_short();
    LCD_E = 1;
    LCD_write4bit(0x3);
    delay_long();
    LCD_E = 0;

    delay_ms(50);

    ////////////////////// Function Set //////////////////////
    delay_short();
    LCD_E = 1;
    LCD_write4bit(0x3);
    delay_long();
    LCD_E = 0;

    delay_us(100);
    
    ////////////////////// line # and font /////////////////////
    delay_short();
    LCD_E = 1;
    LCD_write8bit(0x28);
    delay_long();
    LCD_E = 0;

    //////////////////// cursor and disp on ////////////////////
    delay_short();
    LCD_E = 1;
    LCD_write8bit(0x08);
    delay_long();
    LCD_E = 0;
    
    ////////////////////// clear display //////////////////////
    delay_short();
    LCD_E = 1;
    LCD_write8bit(0x01);
    delay_long();
    LCD_E = 0;

    /////////////////// increment on write ///////////////////
    delay_short();
    LCD_E = 1;
    LCD_write8bit(0x06);
    delay_long();
    LCD_E = 0;
}

void LCD_placeCursor(char x, char y)
{

    // 0x80 + lineNum * 0x40 + x
    char address = 0x80 + x + (0x40 * y);
    delay_ms(3);
    switch(mode)
    {
        case mode_4bit:
            delay_long();
            LCD_E = 1;
            LCD_write4bit(0x80 + (address >> 4));
            delay_long();
            LCD_E = 0;

            delay_long();
            LCD_E = 1;
            LCD_write4bit((address & 0x0F));
            delay_long();
            LCD_E = 0;
            break;

        case mode_8bit:
            delay_short();
            LCD_E = 1;
            LCD_write8bit(address);
            delay_long();
            LCD_E = 0;
            break;
    }
}


void LCD_printString(char x, char y, const char input[], ...)
{
    char string[20] = "\0";

    va_list aptr;
    va_start(aptr,input);

    LCD_placeCursor(x,y);


    for(int i = 0; input[i] != '\0' && i < 200; i++)
    {
        if(input[i] == '%')
        {
            if(input[i+1] == '%')
            {
                strcat(string, "%");
            }
            else
            {
                int val = va_arg(aptr, int);
                char tempString[20];
                sprintf(tempString,"%i",val);
                strcat(string, tempString);
            }
            i++;
        }
        else
        {
            char tempString[2];
            tempString[0] = input[i];
            tempString[1] = '\0';
            strcat(string,tempString);
        }
    }

    va_end(aptr);


    for(int i = 0; string[i] != '\0' && i < 200; i++)
    {
        if(string[i] == '\n')
        {
            LCD_placeCursor(0,y+1);
        }
        else
        {
            delay_ms(2);
            LCD_RS = 1;

            switch(mode)
            {
                case mode_4bit:
                    delay_long();
                    LCD_E = 1;
                    LCD_write4bit((string[i] >> 4));
                    delay_long();
                    LCD_E = 0;

                    delay_long();
                    LCD_E = 1;
                    LCD_write4bit((string[i] & 0x0F));
                    delay_long();
                    LCD_E = 0;
                    break;

                case mode_8bit:
                    delay_short();
                    LCD_E = 1;
                    LCD_write8bit(string[i]);
                    delay_long();
                    LCD_E = 0;
                    break;
            }
            delay_ms(2);
            LCD_RS = 0;
        }
    }
}


void LCD_printChar(char x, char y, const char a)
{
    char string[2];
    string[0] = a;
    string[1] = '\0';
    LCD_printString(x, y, string);
}


void LCD_printVal(char x, char y, const int a)
{
    char temp[] = "%i";
    LCD_printString(x, y, temp, a);
}

void LCD_printBin(char x, char y, char a)
{
    char string[9];
    for(int i = 0; i < 8; i++)
    {
        string[i] = ((a >> (7-i)) & 1) + 48;
    }
    string[8] = '\0';
    LCD_printString(x, y, string);
}

void LCD_clearDisplay()
{
  switch(mode)
    {
        case mode_4bit:
            delay_short();
            LCD_E = 1;
            LCD_write4bit(0x0);
            delay_long();
            LCD_E = 0;

            delay_short();
            LCD_E = 1;
            LCD_write4bit(0x1);
            delay_long();
            LCD_E = 0;
            break;

        case mode_8bit:
            delay_short();
            LCD_E = 1;
            LCD_write8bit(0x01);
            delay_long();
            LCD_E = 0;
            break;
    }
}



