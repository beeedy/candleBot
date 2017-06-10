/* 
 * File:   motorDrive.h
 * Author: broderickcarlin
 *
 * Created on April 20, 2015, 2:50 PM
 */

#ifndef MOTORDRIVE_H
#define	MOTORDRIVE_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "GlobalDefines.h"
#include "xc.h"
#include "pwm.h"

void motorDrive_init();
void motorDrive_setSpeeds(signed char lSpeed, signed char rSpeed);


#ifdef	__cplusplus
}
#endif

#endif	/* MOTORDRIVE_H */

