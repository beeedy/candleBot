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

#include <stdio.h>
#include "progvideo.h"
#include "pixy_init.h"
#include "pixyvals.h"
#include "camera.h"
//#include "colorlut.h"
#include "blobs.h"
#include "conncomp.h"
#include "param.h"
#include <string.h>


#define RES_WIDTH 320
#define RES_HEIGHT 200
 
Program g_progVideo =
{
	"video",
	"continuous stream of raw camera frames",
	videoSetup, 
	videoLoop
};

int videoSetup()
{
	return 0;
}

void sendCustom(uint8_t renderFlags=RENDER_FLAG_FLUSH)
{
	int32_t len;
	uint8_t *frame = (uint8_t *)SRAM1_LOC;
	uint32_t fcc;
	cam_setBrightness(BRIGHTNESS);

	if (g_execArg==1)
	{
		// fill buffer contents manually for return data 
		len = Chirp::serialize(g_chirpUsb, frame, SRAM1_SIZE, HTYPE(FOURCC('C','M','V','2')), HINT8(renderFlags), UINT16(CAM_RES2_WIDTH), UINT16(CAM_RES2_HEIGHT), UINTS8_NO_COPY(CAM_RES2_WIDTH*CAM_RES2_HEIGHT), END);
		// write frame after chirp args
		cam_getFrame(frame+len, SRAM1_SIZE-len, CAM_GRAB_M1R2, 0, 0, CAM_RES2_WIDTH, CAM_RES2_HEIGHT);

		uint8_t *frameloc = (uint8_t *)(SRAM1_LOC + len);
		
		for(uint16_t y = 1 + OFFSET; y < (RES_HEIGHT - OFFSET); y += 2) {
			uint16_t ypo = y + 1;
			uint16_t ymo = y - 1;
			for(uint16_t x = 1 + OFFSET; x < (RES_WIDTH - OFFSET); x += 2) {
				uint16_t xpo = x + 1;
				uint16_t xmo = x - 1;
				uint16_t grad = 0; 
				
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
								/*
				if(grad > THREASHOLD) {

					frameloc[ymo*RES_WIDTH + xmo] = 255;
					frameloc[y*RES_WIDTH + xmo] = 255;
					frameloc[ymo*RES_WIDTH + x] = 255;
					frameloc[y*RES_WIDTH + x] = 255; */

/*
					frameloc[ymo*RES_WIDTH + xmo] = '1';
					frameloc[y*RES_WIDTH + xmo] = '1';
					frameloc[ymo*RES_WIDTH + x] = '1';
					frameloc[y*RES_WIDTH + x] = '1'; 
*/
/*
				}
				else {

					frameloc[ymo*RES_WIDTH + xmo] = 0;
					frameloc[y*RES_WIDTH + xmo] = 0;
					frameloc[ymo*RES_WIDTH + x] = 0;
					frameloc[y*RES_WIDTH + x] = 0;
*/
					/*
					frameloc[ymo*RES_WIDTH + xmo] = '0';
					frameloc[y*RES_WIDTH + xmo] = '0';
					frameloc[ymo*RES_WIDTH + x] = '0';
					frameloc[y*RES_WIDTH + x] = '0'; 
*/
			 //} 
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
		}	
	} /*
		
	for(uint16_t y = 1 + OFFSET; y < (RES_HEIGHT - OFFSET); y += 2) {
			
				for(uint16_t x = 1 + OFFSET; x < (RES_WIDTH - OFFSET); x += 2) {
					uint8_t numOfPx = 0;
					if(frameloc[y*RES_WIDTH + x+2] == 0) {
						numOfPx++;
					}
					if(frameloc[y*RES_WIDTH + x-2] == 0) {
						numOfPx++;
					}
					if(frameloc[(y+2)*RES_WIDTH + x] == 0) {
						numOfPx++;
					}
					if(frameloc[(y-2)*RES_WIDTH + x] == 0) {
						numOfPx++;
					}
					if(numOfPx > 2) {
						frameloc[(y-1)*RES_WIDTH + x-1] = 0;
						frameloc[y*RES_WIDTH + x-1] = 0;
						frameloc[(y-1)*RES_WIDTH + x] = 0;
						frameloc[y*RES_WIDTH + x] = 0;
					}
				}
		}*/
		
		
		// tell chirp to use this buffer
		g_chirpUsb->useBuffer(frame, len+CAM_RES2_WIDTH*CAM_RES2_HEIGHT); 
	}
	else if (100<=g_execArg && g_execArg<200)
	{
		fcc =  FOURCC('E','X',(g_execArg%100)/10 + '0', (g_execArg%10) + '0');
		len = Chirp::serialize(g_chirpUsb, frame, SRAM1_SIZE, HTYPE(fcc), HINT8(renderFlags), UINT16(CAM_RES2_WIDTH), UINT16(CAM_RES2_HEIGHT), UINTS8_NO_COPY(CAM_RES2_WIDTH*CAM_RES2_HEIGHT), END);
		// write frame after chirp args
		cam_getFrame(frame+len, SRAM1_SIZE-len, CAM_GRAB_M1R2, 0, 0, CAM_RES2_WIDTH, CAM_RES2_HEIGHT);

		
		
		
		// tell chirp to use this buffer
		g_chirpUsb->useBuffer(frame, len+CAM_RES2_WIDTH*CAM_RES2_HEIGHT); 
	}
	else
		cam_getFrameChirp(CAM_GRAB_M1R2, 0, 0, CAM_RES2_WIDTH, CAM_RES2_HEIGHT, g_chirpUsb);

}

int videoLoop()
{
	if (g_execArg==0)
		cam_getFrameChirp(CAM_GRAB_M1R2, 0, 0, CAM_RES2_WIDTH, CAM_RES2_HEIGHT, g_chirpUsb);
	else 
		sendCustom();
	return 0;
}

