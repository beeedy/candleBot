/*
 * File:   LCD.c
 * Author: TylerHolmes
 *
 * Created on April 11, 2015, 3:00 PM
 *
 * Pins:
 *
 * TXD - RD4 (RP24)
 * RXD - RD2 (RP22)
 * CTS - RD1 (RP21) - Active Low
 *      Clear To Send Control Input / Handshake Signal.
 * DTR - RD3 (RP23) - Active Low
 *      Data Terminal Ready Control Output / Handshake Signal.
 *
 * UART interface support for 7 or 8 data bits,
 * 1 or 2 stop bits and odd / even / mark / space / no parity
 *
 */

#include "USB.h"

#define USB_RX PORTDbits.RD2
#define USB_TX PORTCbits.RC3
#define USB_CTS PORTDbits.RD1
#define USB_DTR PORTDbits.RD3


void USB_Init() {
    
    TRISDbits.TRISD2 = 0;   // Configures RX to an output (transmit from PIC)
    TRISCbits.TRISC3 = 1;   // Configures TX to an input (PIC Recieves)

    TRISDbits.TRISD1 = 1;   // Tristate CTS (Don't need to use)
    TRISDbits.TRISD3 = 1;   // Tristate DTR (Don't need to use)

    // UART must be initialized as well in the main
}

void USB_Read() {

    
}