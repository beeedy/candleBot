/* 
 * File:   motorDrive.c
 * Author: broderickcarlin
 *
 * Created on April 20, 2015, 2:51 PM
 */

#include "motorDrive.h"

#define direction_left PORTLbits.RL0
#define direction_right PORTKbits.RK1



void motorDrive_init()
{
    //setup 2 ECCP modules for 2 PWM outputs
    //Configure motor drive I/O pins as needed
    //brake motor

        //LEFT
    IOLOCK = 0;
        // ECCP3 on RE6 (RP34)
        RPOR34_35  |= 0xF8;
        TRISE6 = 0;

        //RIGHT
        // ECCP1 on RE7 (RP31)
        RPOR30_31  |= 0x4F;
        TRISE7 = 0;

        IOLOCK = 1;

        //digital on:
        //  RL0
        //  RK1

        TRISL0 = 0;
        TRISK1 = 0;
        
        
        
        TMR4ON = 1; //enable timer
        T4CKPS1 = 1;

        TMR6ON = 1; //enable timer
        T6CKPS1 = 1;


        OpenEPWM1(0x33, ECCP_1_SEL_TMR36);
        SetDCEPWM1(0x0);
        SetOutputEPWM1( SINGLE_OUT, PWM_MODE_1);
        
        
        CCP1CON =   0b00001100; //Configure ECCP1
        CCPTMRS0 =  0b01001001;

        
        
        OpenEPWM3(0x33, ECCP_3_SEL_TMR36);
        SetDCEPWM3(0x0);
        SetOutputEPWM3( SINGLE_OUT, PWM_MODE_1);
        
        motorDrive_setSpeeds(0,0);
        
    }

void motorDrive_setSpeeds(signed char lSpeed, signed char rSpeed)
{
    direction_left = (lSpeed >> 7 ) & 0x1 ^ 0x1;    //Set the direction of rotation based on MSB
    direction_right = (rSpeed >> 7 ) & 0x1;         //Set the direction of rotation based on MSB

    lSpeed = MIN(lSpeed,100);
    rSpeed = MIN(rSpeed,100);

    lSpeed = MAX(lSpeed,-100);
    rSpeed = MAX(rSpeed,-100);

    lSpeed = ((lSpeed >> 7 ) & 0x1) ? ABS(lSpeed) : 100-lSpeed;
    rSpeed = ((rSpeed >> 7 ) & 0x1) ? 100 + rSpeed : rSpeed;

    int templ = ((0xD0 * lSpeed) / 100);
    int tempr = ((0xD0 * rSpeed) / 100);

    SetDCEPWM1(tempr);
    SetDCEPWM3(templ);
}