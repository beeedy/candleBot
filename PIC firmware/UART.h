/* 
 * File:   UART.h
 * Author: Tyler
 *
 * Created on April 11, 2015, 8:49 PM
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <xc.h>
#include "GlobalDefines.h"

    typedef enum {
            FONA,
            USB,
            PIXY
    }transmitType_t;

    void UART_init(void);
    void UART_transmitByte(transmitType_t transmitType, char data);
    void UART_transmitString(transmitType_t transmitType, char[], ...);


#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */

