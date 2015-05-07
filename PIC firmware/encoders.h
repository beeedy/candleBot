/* 
 * File:   encoders.h
 * Author: broderickcarlin
 *
 * Created on April 13, 2015, 8:19 AM
 */

#include <xc.h>
#include "GlobalDefines.h"

#ifndef ENCODERS_H
#define	ENCODERS_H

#ifdef	__cplusplus
extern "C" {
#endif

    void encoders_init();
    long encoders_readLeft();
    long encoders_peakLeft();
    long encoders_readRight();
    long encoders_peakRight();
    void encoders_clear();
    void interrupt low_priority encoderInterrupt();


#ifdef	__cplusplus
}
#endif

#endif	/* ENCODERS_H */

