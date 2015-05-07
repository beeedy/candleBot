/* 
 * File:   delays.h
 * Author: broderickcarlin
 *
 * Created on April 11, 2015, 5:16 PM
 */

#include <xc.h>

#ifndef DELAYS_H
#define	DELAYS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "GlobalDefines.h"
#include "xc.h"

#define millisStart 193

    void delay_init();
    void delay_us(long x);
    void delay_ms(long x);
    void delay_s(long x);
    void delay_clear();
    void delay_startCount();
    unsigned long millis();
    void clearMillis();
    void tickMillis();
    unsigned int delay_readCountMS();
    unsigned int delay_readCountUS();



#ifdef	__cplusplus
}
#endif

#endif	/* DELAYS_H */

