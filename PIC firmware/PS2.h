/* 
 * File:   PS2.h
 * Author: broderickcarlin
 *
 * Based on the code by Bill Porter
 *
 * Created on April 22, 2015, 11:04 PM
 */

#ifndef PS2_H
#define	PS2_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>
#include "delays.h"
#include "GlobalDefines.h"

#define CTRL_CLK        5
#define CTRL_CLK_HIGH   5
#define CTRL_BYTE_DELAY 4

#define UART_DEBUG

    //These are our button constants
#define PSB_SELECT      0x0001
#define PSB_L3          0x0002
#define PSB_R3          0x0004
#define PSB_START       0x0008
#define PSB_PAD_UP      0x0010
#define PSB_PAD_RIGHT   0x0020
#define PSB_PAD_DOWN    0x0040
#define PSB_PAD_LEFT    0x0080
#define PSB_L2          0x0100
#define PSB_R2          0x0200
#define PSB_L1          0x0400
#define PSB_R1          0x0800
#define PSB_GREEN       0x1000
#define PSB_RED         0x2000
#define PSB_BLUE        0x4000
#define PSB_PINK        0x8000
#define PSB_TRIANGLE    0x1000
#define PSB_CIRCLE      0x2000
#define PSB_CROSS       0x4000
#define PSB_SQUARE      0x8000

//Guitar  button constants
#define UP_STRUM		0x0010
#define DOWN_STRUM		0x0040
#define STAR_POWER		0x0100
#define GREEN_FRET		0x0200
#define YELLOW_FRET		0x1000
#define RED_FRET		0x2000
#define BLUE_FRET		0x4000
#define ORANGE_FRET		0x8000
#define WHAMMY_BAR		8

//These are stick values
#define PSS_RX 5
#define PSS_RY 6
#define PSS_LX 7
#define PSS_LY 8

//These are analog buttons
#define PSAB_PAD_RIGHT    9
#define PSAB_PAD_UP      11
#define PSAB_PAD_DOWN    12
#define PSAB_PAD_LEFT    10
#define PSAB_L2          19
#define PSAB_R2          20
#define PSAB_L1          17
#define PSAB_R1          18
#define PSAB_GREEN       13
#define PSAB_RED         14
#define PSAB_BLUE        15
#define PSAB_PINK        16
#define PSAB_TRIANGLE    13
#define PSAB_CIRCLE      14
#define PSAB_CROSS       15
#define PSAB_SQUARE      16

#define CMD PORTFbits.RF2
#define DAT PORTFbits.RF3
#define ATT PORTFbits.RF6
#define CLK PORTFbits.RF5

#define SET(x,y) (x|=(1<<y))
#define CLR(x,y) (x&=(~(1<<y)))
#define CHK(x,y) (x & (1<<y))
#define TOG(x,y) (x^=(1<<y))

char PS2_init();
void PS2_readGamepad();
void PS2_reconfig();
void PS2_sendCommandString(char string[], char len);
char PS2_shiftInOut(char byte);
char PS2_readType();
char PS2_newButtons();
char PS2_newButtonState(unsigned int button);
char PS2_buttonPressed(unsigned int button);
char PS2_buttonReleased(unsigned int button);
char PS2_button(unsigned int button);
unsigned int PS2_buttonDataByte();
char PS2_analog(char button);

#ifdef	__cplusplus
}
#endif

#endif	/* PS2_H */

