//
// begin license header
//
// This file is part of Pixy CMUcam5 or "Pixy" for short
//
// All Pixy source code is provided under the terms of the
// GNU General Public License v2 (http://www.gnu.org/licenses/gpl-2.0.html).
// Those wishing to use Pixy source code, software and/or
// technologies under different licensing terms should contact us at
// cmucam@cs.cmu.edu. Such licensing terms are available for
// all portions of the Pixy codebase presented here.
//
// end license header
//

// 
// This is an additional file added by Tyler Holmes and Broderick Carlin
// of the University of Saint Thomas, adding the functionality of edge detection
// for the purposes of object avoidance on an autonomous vehicle. The function
// gets a frame, processes it using a simple edge detection formula, and returns
// a processed array


#include <stdio.h>
#include "progvideo.h"
#include "pixy_init.h"
#include "camera.h"
#include "conncomp.h"
#include <string.h>
#include "edgedetect.h"	//Tyler Edit
#include "rcservo.h"
#include "edgedetect.h"
#include "led.h"
#include <math.h>



#define RES_WIDTH (320)
#define RES_HEIGHT (200)

#define TAN_FOVH_DIV_2 0.435
#define TAN_FOVW_DIV_2 0.767

// NOT DEFINED TO THE RIGHT VALUES YET
// units in cm
#define H_C 4.0
#define H_B 0.0

extern uint8_t UART_DATA_AVAILABLE;


void edgeDetect_run()
{
	cam_setBrightness(BRIGHTNESS); 				// 0 to 255
	uint8_t *frame = (uint8_t *)SRAM1_LOC;
	uint8_t *frameloc = (uint8_t *)(SRAM1_LOC + 2);
	uint8_t *sendPositions = (uint8_t*)(SRAM1_LOC);
	float theta;
	// recieve the command to get a frame
	while(1) {
		led_setRGB(255, 0, 0);
		
		while(1) {
			if(UART_DATA_AVAILABLE) {
				//rxbuf = UART_ReceiveByte(LPC_USART0);
				theta = (float)UART_DATA_AVAILABLE;
				UART_DATA_AVAILABLE = 0;
				break;
			}
		}
		
		theta = (float)(theta*(3.14159/180.0));
		
		led_setRGB(0, 255, 0);
		
			cam_getFrame(frameloc, SRAM1_SIZE, CAM_GRAB_M1R2, 0, 0, RES_WIDTH, RES_HEIGHT);
			// second time through gets a frame fine
			frameloc = frame;
			for(uint16_t y = 1 + OFFSET; y < (RES_HEIGHT - OFFSET); y += 2) {
				uint16_t ypo = y + 1;
				uint16_t ymo = y - 1;
				for(uint16_t x = 1 + OFFSET; x < (RES_WIDTH - OFFSET); x += 2) {
					uint16_t xpo = x + 1;
					uint16_t xmo = x - 1;
					uint16_t grad; 
					
					uint16_t intense_XPO_Y = frameloc[y*RES_WIDTH + xpo] + frameloc[ypo*RES_WIDTH + xpo+1] + 
							(frameloc[ypo*RES_WIDTH + xpo] + frameloc[y*RES_WIDTH + xpo+1])/2;
					
					uint16_t intense_XMO_Y = frameloc[y*RES_WIDTH + xmo] + frameloc[ypo*RES_WIDTH + x] + 
							(frameloc[ypo*RES_WIDTH + xmo] + frameloc[y*RES_WIDTH + x])/2;
					
					uint16_t intense_X_YPO = frameloc[ypo*RES_WIDTH + x] + frameloc[(ypo+1)*RES_WIDTH + xpo] + 
							(frameloc[(ypo+1)*RES_WIDTH + x] + frameloc[ypo*RES_WIDTH + xpo])/2;
					
					uint16_t intense_XPO_YPO = frameloc[ypo*RES_WIDTH + xpo] + frameloc[(ypo+1)*RES_WIDTH + xpo+1] + 
							(frameloc[(ypo+1)*RES_WIDTH + xpo] + frameloc[ypo*RES_WIDTH + xpo+1])/2;
					
					uint16_t intense_XMO_YPO = frameloc[(ypo)*RES_WIDTH + xmo] + frameloc[(ypo+1)*RES_WIDTH + x] + 
							(frameloc[(ypo+1)*RES_WIDTH + xmo] + frameloc[ypo*RES_WIDTH + x])/2;
					
					uint16_t intense_X_YMO = frameloc[ymo*RES_WIDTH + x] + frameloc[y*RES_WIDTH + xpo] + 
							(frameloc[y*RES_WIDTH + x] + frameloc[ymo*RES_WIDTH + xpo])/2;
							
					uint16_t intense_XPO_YMO = frameloc[ymo*RES_WIDTH + xpo] + frameloc[y*RES_WIDTH + xpo+1] + 
							(frameloc[y*RES_WIDTH + xpo] + frameloc[ymo*RES_WIDTH + xpo+1])/2;
							
					uint16_t intense_XMO_YMO = frameloc[ymo*RES_WIDTH + xmo] + frameloc[y*RES_WIDTH + x] + 
							(frameloc[y*RES_WIDTH + xmo] + frameloc[ymo*RES_WIDTH + x])/2;
					
					uint16_t grad1 = abs(intense_XPO_Y - intense_XMO_Y
						+ intense_XPO_YPO - intense_XMO_YPO
						+ intense_XPO_YMO - intense_XMO_YMO);
						
					uint16_t grad2 = abs(intense_X_YPO -	intense_X_YMO
						+ intense_XPO_YPO -	intense_XPO_YMO
						+ intense_XMO_YPO - intense_XMO_YMO);
					
					grad = grad1 + grad2;
					

					// when it loops a second time through, it cannot make it passed the next line
					// Deleted if statement, hopefully that'll do 'er. Really inefficient though

					if(grad > THREASHOLD) {
						frameloc[ymo*RES_WIDTH + xmo] = 255;
						frameloc[y*RES_WIDTH + xmo] = 255;
						frameloc[ymo*RES_WIDTH + x] = 255;
						frameloc[y*RES_WIDTH + x] = 255;
					}
					else {
						frameloc[ymo*RES_WIDTH + xmo] = 0;
						frameloc[y*RES_WIDTH + xmo] = 0;
						frameloc[ymo*RES_WIDTH + x] = 0;
						frameloc[y*RES_WIDTH + x] = 0;
					}
					
					
					/*				TEST DIAGONAL LINE
					if( y == x) {
						
						frameloc[ymo*RES_WIDTH + xmo] = 255;
						frameloc[y*RES_WIDTH + xmo] = 255;
						frameloc[ymo*RES_WIDTH + x] = 255;
						frameloc[y*RES_WIDTH + x] = 255;
					}
					else {
						frameloc[ymo*RES_WIDTH + xmo] = 0;
						frameloc[y*RES_WIDTH + xmo] = 0;
						frameloc[ymo*RES_WIDTH + x] = 0;
						frameloc[y*RES_WIDTH + x] = 0;
					}
					*/
			}
		}
			
			led_setRGB(255, 0, 255);
		
			// floor detection & 
		uint16_t count = 0;
		for(float x = (POS_OFFSET); x < (RES_WIDTH - POS_OFFSET); x += 2.0) {
			
			float xPos;
			for(float y = (RES_HEIGHT - POS_OFFSET); y > POS_OFFSET; y -= 2.0) {
				
				if(frameloc[((uint8_t)y)*RES_WIDTH + (uint16_t)x] != 0) {
					float yPos;
					
					double theta_ph = atan(((2.0*y-200.0)/200.0)*TAN_FOVH_DIV_2);		// This works
					double cos_theta_ph = cos(theta_ph);
					//sendPositions[count] = cos_theta_ph*128;
					double cos_theta_minus_ph = cos(theta - theta_ph);
					//sendPositions[count] = cos_theta_minus_ph*128;
					//sendPositions[count] = (int8_t)(theta_ph * (180.0/3.142));				// these two lines send x,y pairs
					//sendPositions[count] = (cos_theta_ph)/(cos_theta_minus_ph);
					yPos = ((double)((3.8)*((cos_theta_ph))))/(cos_theta_minus_ph) + 
										(0.0)*tan(theta - theta_ph);
					
					xPos = (yPos*(2.0*x - 320.0))/417.0;	// hopefully the x cord. won't be super inaccurate. Not crucial though.

			  	
					//sendPositions[2*count + 1] = yPos;	  //(int8_t)yPos;
					
					//sendPositions[2*count] = x;				// these two lines send x,y pairs
					sendPositions[count] = yPos;	  //(int8_t)yPos;
					
					count++;
					break;
				}
				else {
					// color the floor a different color. Not used in this scenario
				}
			}
		}
		
		UART_Send(LPC_USART0, sendPositions, count, BLOCKING);	// sends x,y pairs
		//UART_Send(LPC_USART0, sendPositions, count, BLOCKING);	// sends only the y distance
		count = 0;
		
		// Byte packing for processing script
		/*
		for(uint16_t y = 0; y < RES_HEIGHT/2; y += 1) {
			for (uint16_t x = 0; x < RES_WIDTH/2; x += 8) {
		*/
		
	/*		// Checkerboard for configuring things
				if(y&1) 
					frameloc[y*20 + x/8] = 0x55;
				else
					frameloc[y*20 + x/8] = 0xAA;
	*/
	/*
					frameloc[y*(RES_WIDTH/16) + x/8] = (frameloc[(y*2+1)*RES_WIDTH + (2*(x+0)+1)] & 0x80) | 
																					(frameloc[(y*2+1)*RES_WIDTH + (2*(x+1)+1)] & 0x40) |
																					(frameloc[(y*2+1)*RES_WIDTH + (2*(x+2)+1)] & 0x20) |
																					(frameloc[(y*2+1)*RES_WIDTH + (2*(x+3)+1)] & 0x10) |
																					(frameloc[(y*2+1)*RES_WIDTH + (2*(x+4)+1)] & 0x08) |
																					(frameloc[(y*2+1)*RES_WIDTH + (2*(x+5)+1)] & 0x04) |
																					(frameloc[(y*2+1)*RES_WIDTH + (2*(x+6)+1)] & 0x02) |
																					(frameloc[(y*2+1)*RES_WIDTH + (2*(x+7)+1)] & 0x01); 

			}
		}
		*/
				
		// UART_Send(LPC_USART0, frameloc, 16000, BLOCKING);   // Send the frame to see it in tera term. NO BYTE PACK
		// frame[0] = 'A';																		 // key byte
		// UART_Send(LPC_USART0, frameloc, 2001, BLOCKING);		 // Send the frame byte packed to see it in processing
		
		//UART_Send(LPC_USART0, sendPositions, (RES_WIDTH - 2*POS_OFFSET)>>1, BLOCKING);
		
		// clear array
		for(uint8_t x = 0; x < 240; x++) {
			sendPositions[x] = 255;
		}
		
		toggleLED();
		
	}
}


void toggleLED() {
	
			// Toggle LED to see when we're sending frames

	static uint8_t toggle = 0;
	toggle ^= 1;
	if(toggle) {
		led_setRGB(255, 255, 255);
	}
	else {
		led_setRGB(0, 0, 0);
	}
}
