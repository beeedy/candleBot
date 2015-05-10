/*                           _     ___________
                            | |   /  __ \  _  \
                            | |   | /  \/ | | |
                            | |   | |   | | | |
                            | |___| \__/\ |/ /
                            \_____/\____/___/
 * File:   LCD.h
 * Author: Broderick Carlin
 *
 * This file contains all the functions needed to interface with an LCD that   
 * contains the common Hitatchi LCD driver. Supporting both 4-bit and 8-bit 
 * modes gives the user the ability to decide how to configure their circuit. 
 * Functions are structured to mirror those found in the more popular stdio.h
 * such as printf().
 *
 * -------------------------------Function List---------------------------------
 * void LCD_init4bit()
 * void LCD_init8bit()
 * void LCD_printString(char, char, char[], ...)
 * void LCD_printChar(char, char, char)
 * void LCD_printVal(char, char, int)
 * void LCD_printBin(char, char, char)
 * void LCD_placeCursor(char, char)
 * void LCD_clearDisplay()
 *
 *
 * ---------------------------Function Descriptions-----------------------------
 * void LCD_init4bit()
 *      Intializes the LCD to run in 4-bit mode. This can be useful if there is
 *      not enough I/O or if there is an electrical problem with the circuit
 *      that prohibits the use of all 8 I/O lines. If timing is an important
 *      aspect of the circuit, 4-bit mode should be avoided as all writes to the
 *      LCD screen will take twice as long as it would in 8-bit mode. This
 *      function must be called before any other LCD functions or the LCD will
 *      not work in a predictable way.
 *
 * void LCD_init8bit()
 *      Intializes the LCD to run in 8-bit mode. This is the fastest way to read
 *      and to write to the LCD screen and is the prefered method if able. This
 *      function must be called before any other LCD functions or the LCD will
 *      not work in a predictable way.
 *
 * void LCD_printString(char, char, char[], ...)
 *      This function prints out a string to the LCD using a similar syntax to
 *      the popular printf() statement used in ANSI C. The first two arguments
 *      indicate the X-Y coordinates of the first character in the string,
 *      respectively. The third argument is the string to be printed in the form
 *      of a null terminated char array. If the character pair "%i" appear in
 *      the string, any integer arguments following the string will be inserted
 *      into the string, with the first integer argument going to the first "%i"
 *      and the rest following respectively. This function supports new line
 *      characters in the form of '\n' however any other formatting characters
 *      should be avoided as they may cause unexpected behavior. This function
 *      will automatically decide if it should communicate over a 4-bit or 8-bit
 *      protocol depending on how the LCD screen was initialized.
 *
 * void LCD_printChar(char, char, char)
 *      This function prints a single character to the LCD screen at the
 *      location determined by the first two arguments sent to the function,
 *      with the first two arguments representing x-y respectively. The third
 *      argument is the single character that is to be printed out to the screen
 *      This function will automatically decide if it should communicate over a
 *      4-bit or 8-bit protocol depending on how the LCD screen was initialized.
 *
 * void LCD_printVal(char, char, int)
 *      This function prints a single integer value to the LCD screen at the
 *      location determined by the first two arguments sent to the function,
 *      with the first two arguments representing x-y respectively. The third
 *      argument is the single integer that is to be printed out to the screen
 *      This function will automatically decide if it should communicate over a
 *      4-bit or 8-bit protocol depending on how the LCD screen was initialized.
 *
 * void LCD_printBin(char, char, char)
 *      This function prints a single 8-bit binary number to the LCD screen at
 *      the location determined by the first two arguments sent to the function,
 *      with the first two arguments representing x-y respectively. The third
 *      argument is the 8-bit value that is to be printed out to the screen
 *      This function will automatically decide if it should communicate over a
 *      4-bit or 8-bit protocol depending on how the LCD screen was initialized.
 *
 * void LCD_placeCursor(char, char)
 *      This function simply moves the screens cursor to the position indicated
 *      by two arguments sent to the function, x and y respectively. This
 *      function will automatically decide if it should communicate over a
 *      4-bit or 8-bit protocol depending on how the LCD screen was initialized.
 *
 * void LCD_clearDisplay()
 *      This function clears the screen and places the cursor back at position
 *      (0,0). This function will automatically decide if it should communicate
 *      over a 4-bit or 8-bit protocol depending on how the LCD screen was
 *      initialized.
 
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

#ifndef LCD_H
#define	LCD_H


#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "delays.h"
#include <xc.h>

#define delay_short() asm("NOP")
#define delay_long() delay_us(40);

void LCD_printString(char, char, char[], ...);
void LCD_printChar(char, char, char);
void LCD_printVal(char, char, int);
void LCD_printBin(char, char, char);
void LCD_init4bit();
void LCD_init8bit();
void LCD_placeCursor(char, char);
void LCD_clearDisplay();



#endif
/* LCD_H */

