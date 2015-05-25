/*              ___  ___      _              ______      _
                |  \/  |     | |             |  _  \    (_)
                | .  . | ___ | |_ ___  _ __  | | | |_ __ ___   _____
                | |\/| |/ _ \| __/ _ \| '__| | | | | '__| \ \ / / _ \
                | |  | | (_) | || (_) | |    | |/ /| |  | |\ V /  __/
                \_|  |_/\___/ \__\___/|_|    |___/ |_|  |_| \_/ \___|

 * File:   motorDrive.h
 * Author: Broderick Carlin
 *
 * This file contains the functions that are responsible for interfacing with 
 * the two MC33926PNB H-bridge IC chips. These functions in turn control the
 * speed and direction of the motors that are connected through the two 
 * MC33926PNB chips.
 *
 * -------------------------------Function List---------------------------------
 * void motorDrive_init()
 * void motorDrive_setSpeeds(signed char, signed char)
 * char motorDrive_limitedAccelerationSetSpeeds(signed char, signed char)
 * void motorDrive_drive(int, int)
 * void motorDrive_driveAvoidObstacles(int, int)
 *
 * ---------------------------Function Descriptions-----------------------------
 * void motorDrive_init()
 *      This function initializes the I/O and PWM channels needed to interface
 *      with and control the motors. This function must be called before the
 *      motors can be controlled. Upon completion of this function, the motors
 *      are both set to stopped mode and the wheels will not spin until the
 *      speed is changed. Each motor used one PWM channel for speed control and
 *      one digital output for direction control.
 *
 * void motorDrive_setSpeeds(signed char, signed char)
 *      This function controls the speed and direction of both motors
 *      similtaneously. The inputs can be values between -100 and 100. All
 *      positive values correspond to forward rotation while negative values
 *      correspond to the reverse rotation. The absolute value of the input
 *      is the PWM pulse width percentage. It is important to note that to make
 *      both motors spin in the same direction and propel the robot forward, the
 *      inputs should both be positive. To make the motors spin in the opposite
 *      direction and have the robot move backwards, both values should be made
 *      negative.
 *
 * char motorDrive_limitedAccelerationSetSpeeds(signed char, signed char)
 *      This function controls the speed and direction of both motors
 *      similtaneously. The inputs can be values between -100 and 100. All
 *      positive values correspond to forward rotation while negative values
 *      correspond to the reverse rotation. The absolute value of the input
 *      is the PWM pulse width percentage. It is important to note that to make
 *      both motors spin in the same direction and propel the robot forward, the
 *      inputs should both be positive. To make the motors spin in the opposite
 *      direction and have the robot move backwards, both values should be made
 *      negative. This function has the benefit of being acceration limited so
 *      as to reduce the likelyhood of tire slippage on the ground surface. It
 *      is important to understand that this is a passive speed control function
 *      so it does not always gaurentee the speed or motor rotation, rather it
 *      increases motors rotation closer to the goal value. This function will
 *      return a 0x00 if one or both of the motors is not current at its target
 *      speed. This function will return a 0x01 if both motors have infact
 *      reached their target velocity.
 * 
 * void motorDrive_drive(int distance, int distanceCutOff)
 *      This function is a full fledged closed loop control of the wheels to 
 *      allow accurate and repeatable driving of the robot in a straight line. 
 *      This function takes in two arguments, the first being the distance in mm
 *      that we wish for the robot to travel directly forward and the second 
 *      argument is the amount of distance, in mm, that we reserve to allow the 
 *      robot to begin to slow down. By adjusting the cutOff distance we can 
 *      tune the deceleration of the robots movements to avoid events such as 
 *      tipping or loss of traction. This function implements object avoidance 
 *      using the Pixy cam and will stop the robot before it collides with any
 *      obstance. This function makes no attempt to move around the obstacle, so
 *      we must check the distance traveled by the encoders after this function
 *      has completed in order to verify that the function completed beause it
 *      reached its target distance and not because it detected an obstacle.
 *
 * void motorDrive_driveAvoidObstacles(int distance, int cutOff)
 *      This function is a derivation of motorDrive_drive() with object full
 *      object avoidance built in. Interfacing with the function is the same as
 *      the less robust motorDrive_drive() with distance and cutOff values used
 *      to determine distance to travel and distance used to decelerate. When
 *      this function encounters an obstacle, it will begin an attempt to find a
 *      path around the obstacle so that it may continue on its orignial path.
 *      There is no need to check encoder values after this function as this
 *      function guarentees that the robot will either reach its target location
 *      or rather it will get stuck in a loop trying to reach an unreachable
 *      target location.
 *
 * void motorDrive_turn(int angle)
 *      Similar to motorDrive_drive(), this function is a closed loop controller
 *      used to accuratly control the motor drives on the robot. This function
 *      allows accurate control over a specified turning angle. The desired
 *      angle of rotation is sent to this function in degrees, with a positive
 *      angle being clockwise and a negative angle being counter clockwise. 

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

#ifndef MOTORDRIVE_H
#define	MOTORDRIVE_H

#include "GlobalDefines.h"
#include "xc.h"
#include "pwm.h"
#include "encoders.h"
#include "delays.h"
#include "colorSensor.h"

#define MAX_ACCEL 1
#define MOVEDELAY() delay_ms(350)

void motorDrive_init();
void motorDrive_setSpeeds(signed char, signed char);
char motorDrive_limitedAccelerationSetSpeeds(signed char, signed char);
void motorDrive_drive(int, int);
void motorDrive_turn(int);

#endif

