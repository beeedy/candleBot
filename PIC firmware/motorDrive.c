/*              ___  ___      _              ______      _
                |  \/  |     | |             |  _  \    (_)
                | .  . | ___ | |_ ___  _ __  | | | |_ __ ___   _____
                | |\/| |/ _ \| __/ _ \| '__| | | | | '__| \ \ / / _ \
                | |  | | (_) | || (_) | |    | |/ /| |  | |\ V /  __/
                \_|  |_/\___/ \__\___/|_|    |___/ |_|  |_| \_/ \___|

 * File:   motorDrive.c
 * Author: Broderick Carlin
 */

#include "motorDrive.h"
#include "UART.h"

#define direction_left PORTLbits.RL0
#define direction_right PORTKbits.RK1

unsigned long prevTime = 0;
char lMotorSpeed = 0;
char rMotorSpeed = 0;



void motorDrive_init()
{
    //setup 2 ECCP modules for 2 PWM outputs
    //Configure motor drive I/O pins as needed

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

    TMR6ON = 1; //enable timer
    T6CKPS1 = 1;

    TMR8ON = 1; //enable timer
    T8CKPS1 = 1;

    OpenEPWM3(0x33, ECCP_3_SEL_TMR36);
    SetDCEPWM3(0x0);
    SetOutputEPWM3( SINGLE_OUT, PWM_MODE_1);

    OpenEPWM1(0x33, ECCP_1_SEL_TMR38);
    SetDCEPWM1(0x0);
    SetOutputEPWM1( SINGLE_OUT, PWM_MODE_1);
    
    CCPTMRS0 = 0b11000010;

    // There was problems getting both PWM moduels running off of the same timer
    // when using the built in functions, we we had to manually set the values
    // that enable us to do this.

    motorDrive_setSpeeds(0,0);
}

void motorDrive_setSpeeds(signed char lSpeed, signed char rSpeed)
{
    lSpeed *= -1;
    rSpeed *= -1;
    
    lMotorSpeed = lSpeed;
    rMotorSpeed = rSpeed;

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

char motorDrive_limitedAccelerationSetSpeeds(signed char lSpeed, signed char rSpeed)
{
    char done = 0x01;

    unsigned long deltaTime = (millis() - prevTime)/100;
    prevTime = millis();

    if(lSpeed < lMotorSpeed)
    {
       lMotorSpeed -= (MAX_ACCEL * deltaTime);
       if(lSpeed > lMotorSpeed)
       {
           lMotorSpeed = lSpeed;
       }
       else
       {
           done = 0x00;
       }
    }
    else if(lSpeed > lMotorSpeed)
    {
        lMotorSpeed += (MAX_ACCEL * deltaTime);
       if(lSpeed < lMotorSpeed)
       {
           lMotorSpeed = lSpeed;
       }
       else
       {
           done = 0x00;
       }
    }

    if(rSpeed < rMotorSpeed)
    {
       rMotorSpeed -= (MAX_ACCEL * deltaTime);
       if(rSpeed > rMotorSpeed)
       {
           rMotorSpeed = rSpeed;
       }
       else
       {
           done = 0x00;
       }
    }
    else if(rSpeed > rMotorSpeed)
    {
        rMotorSpeed += (MAX_ACCEL * deltaTime);
       if(rSpeed < rMotorSpeed)
       {
           rMotorSpeed = rSpeed;
       }
       else
       {
           done = 0x00;
       }
    }

    motorDrive_setSpeeds(lMotorSpeed, rMotorSpeed);
    return done;
}

void motorDrive_drive(int distance, int distanceCutOff) // distance = distance to travel in MM
{
    //65cm to the center

    //43mm diameter wheels, 135mm circumfrence (13.5cm)
    //60 encoder ticks per rev.
    encoders_clear();

    const float differencePGain = 15.0;
    const int baseSpeed = 65;

    int encoderGoal = distance >> 1;

    extern char PIXY_INDEX;
    extern char PIXY_BUFF[PIXY_BUFF_SIZE];

    char waiting = 0;



    while(encoderGoal > (int)encoders_peakLeft() && encoderGoal > (int)encoders_peakRight())
    {
        if(waiting == 0)
        {
            waiting = 1;
            PIXY_INDEX = 0;
            UART_transmitByte(PIXY, 60);
        }

        if(PIXY_INDEX >= 40)
        {
            waiting = 0;
            int count = 0;
            for(int i = 5; i < 35; i++)
            {
             if(PIXY_BUFF[i] < 18)
             {
                 count++;
             }
            }
            if(count > 3)
            {
                motorDrive_setSpeeds(0,0);
                return;
            }
        }

        int rightSpeed;
        int leftSpeed;
        if((encoderGoal - (int)encoders_peakRight()) > distanceCutOff)
        {
            rightSpeed = baseSpeed - (int)(((float)(encoders_peakRight() - encoders_peakLeft()))*differencePGain);
        }
        else
        {
            rightSpeed = baseSpeed - (int)(((float)(encoders_peakRight() - encoders_peakLeft()))*differencePGain);
            rightSpeed *= (((encoderGoal - (int)encoders_peakRight())*100) / (distanceCutOff));
            rightSpeed /= 100;
        }

        if((encoderGoal - (int)encoders_peakLeft()) > distanceCutOff)
        {
            leftSpeed = baseSpeed - (int)(((float)(encoders_peakLeft() - encoders_peakRight()))*differencePGain);
        }
        else
        {
            leftSpeed = baseSpeed - (int)(((float)(encoders_peakLeft() - encoders_peakRight()))*differencePGain);
            leftSpeed *= (((encoderGoal - (int)encoders_peakLeft())*100) / (distanceCutOff));
            leftSpeed /= 100;
        }

        if(rightSpeed < 25 && leftSpeed < 25)
        {
            motorDrive_setSpeeds(0,0);
            return;
        }

        rightSpeed = min(100,rightSpeed);
        leftSpeed = min(100,leftSpeed);

        motorDrive_setSpeeds(rightSpeed, leftSpeed);
    }
    motorDrive_setSpeeds(0,0);
}

void motorDrive_turn(int angle)
{
    // diameter of wheel base: 86mm
    // circumfrence of turning circle: 271mm

    // diameter of wheel: 43mm
    // circumfrece of wheel: 135mm

    //60 encoder ticks per revolution

    // number of encoder ticks per wheel: (271 * angle / 360) / (135/60)

    encoders_clear();

    const float differencePGain = 15.0;
    const int baseSpeed = 60;

    int encoderGoal = (angle * 31 + 5) / 100;

    if(angle > 0)
    {
        while(encoderGoal > (int)encoders_peakLeft() && (-1 * encoderGoal) < (int)encoders_peakRight())
        {
            int rightSpeed = baseSpeed + (int)(((float)(encoders_peakRight() + encoders_peakLeft()))*differencePGain);
            int leftSpeed = baseSpeed - (int)(((float)(encoders_peakLeft() + encoders_peakRight()))*differencePGain);
            motorDrive_setSpeeds(-1 * rightSpeed, leftSpeed);
        }
    }
    else
    {
        while(encoderGoal < (int)encoders_peakLeft() && (-1 * encoderGoal) > (int)encoders_peakRight())
        {
            int rightSpeed = baseSpeed - (int)(((float)(encoders_peakRight() + encoders_peakLeft()))*differencePGain);
            int leftSpeed = baseSpeed + (int)(((float)(encoders_peakLeft() + encoders_peakRight()))*differencePGain);
            motorDrive_setSpeeds(rightSpeed, -1 * leftSpeed);
        }
    }
    motorDrive_setSpeeds(0,0);
}