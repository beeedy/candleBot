/* 
 * File:   LCD.h
 * Author: broderickcarlin
 *
 * Created on April 9, 2015, 10:03 PM
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

