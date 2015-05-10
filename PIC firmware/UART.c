/*                       _   _  ___  ______ _____
                        | | | |/ _ \ | ___ \_   _|
                        | | | / /_\ \| |_/ / | |
                        | | | |  _  ||    /  | |
                        | |_| | | | || |\ \  | |
                         \___/\_| |_/\_| \_| \_/
 * File:   UART.h
 * Author: Tyler Holmes and Broderick Carlin
 *
 * UART Connection mapping:
 *      Fona RX maps to U4 TX (RP13) Module 1
 *      Fona TX maps to U1 RX (RP27) Module 4
 *
 *      USB  RX maps to U1 TX (RP22) Module 4
 *      USB  TX maps to U2 RX (RP24) Module 1
 *
 *      Pixy RX maps to U2 TX (RP11) Module 3
 *      Pixy TX maps to U3 RX (RP16) Module 2
 *
 *      Unused RX on Module 2
 *      Unused TX on Module 3
 */

#include "UART.h"

volatile unsigned char config = 0;
volatile unsigned int spbrg = 0;

void UART_init() {

    disablePPSLock();

    RPINR6_7  &= 0xF6;              // Configures RP24(USB TX)  to U4RX
    RPOR22_23 |= 0xF1;              // Configures RP18(USB RX)  to U1TX

    RPINR4_5  &= 0xF4;              // Configures RP16(Pixy TX) to U3RX
    RPOR10_11 |= 0x2F;              // Configures RP11(Pixy RX) to U2TX
    
    RPINR0_1  &= 0xF6;              // Configures RP27(Fona TX) to U1RX
    RPOR12_13 |= 0x3F;              // Configures RP13(Fona RX) to U4TX

    enablePPSLock();
    
    INTCONbits.PEIE = 1;


    /*********************  USART Module 1 setup  *****************************/
    /*
    /* Asynchronous, 8 bit, 115200 Baud, Recieve interrupt on,
    /* Continuous Recieve
    /*
    /*/

    SPBRG1 = 34;
    SPBRGH1 = 0;

    TXSTA1bits.BRGH = 0;

    BAUDCON1bits.ABDOVF = 0;
    BAUDCON1bits.BRG16 = 1;
    BAUDCON1bits.RCIDL = 0;
    BAUDCON1bits.RXDTP = 0;

    TXSTA1bits.SYNC = 0;
    RCSTA1bits.SPEN = 1;
    RCSTA1bits.RX9 = 0;
    RCSTA1bits.CREN = 1;

    TXSTA1bits.TXEN = 1;
    TXSTA1bits.TX9 = 0;


    TX1IE = 0; //disable interrupts
    RC1IE = 1; //enable interrupts for recieve


    /*********************  USART Module 2 setup  *****************************/
    /*
    /* Asynchronous, 8 bit, 115200 Baud, Wake-up monitoring disabled,
    /* Continuous Recieve
    /*
    /*/

    SPBRG2 = 34;
    SPBRGH2 = 0;

    TXSTA2bits.BRGH = 0; // 1?

    BAUDCON2bits.ABDOVF = 0;
    BAUDCON2bits.BRG16 = 1;
    BAUDCON2bits.RCIDL = 0;
    BAUDCON2bits.RXDTP = 0;

    TXSTA2bits.SYNC = 0;
    RCSTA2bits.SPEN = 1;
    RCSTA2bits.RX9 = 0;
    RCSTA2bits.CREN = 1;

    TXSTA2bits.TXEN = 1;
    TXSTA2bits.TX9 = 0;


    TX2IE = 0; //disable interrupts
    RC2IE = 1; //enable interrupts for recieve

    /*********************  USART Module 3 setup  *****************************/
    /*
    /* Asynchronous, 8 bit, 115200 Baud, Wake-up monitoring disabled,
    /* Continuous Recieve
    /*
    /*/


    SPBRG3 = 34;
    SPBRGH3 = 0;

    TXSTA3bits.BRGH = 0; // 1?

    BAUDCON3bits.ABDOVF = 0;
    BAUDCON3bits.BRG16 = 1;
    BAUDCON3bits.RCIDL = 0;
    BAUDCON3bits.RXDTP = 0;

    TXSTA3bits.SYNC = 0;
    RCSTA3bits.SPEN = 1;
    RCSTA3bits.RX9 = 0;
    RCSTA3bits.CREN = 1;

    TXSTA3bits.TXEN = 1;
    TXSTA3bits.TX9 = 0;

    TX3IE = 0; //disable interrupts
    RC3IE = 1; //enable interrupts for recieve


    /**********************  USART Module 4 setup  *******************************/
    /*
    /* Asynchronous, 8 bit, 115200 Baud, Wake-up monitoring disabled,
    /* Continuous Recieve
    /*
    /*/

    TRISDbits.TRISD4 = 1;
    TRISDbits.TRISD2 = 0;
    /////////////////////////// Do the Tris bits need to be set?

    SPBRG4 = 34;
    SPBRGH4 = 0;

    TXSTA4bits.BRGH = 0;

    BAUDCON4bits.ABDOVF = 0;
    BAUDCON4bits.BRG16 = 1;
    BAUDCON4bits.RCIDL = 0;
    BAUDCON4bits.RXDTP = 0;

    TXSTA4bits.SYNC = 0;
    RCSTA4bits.SPEN = 1;
    RCSTA4bits.RX9 = 0;
    RCSTA4bits.CREN = 1;

    TXSTA4bits.TXEN = 1;
    TXSTA4bits.TX9 = 0;


    TX4IE = 0; //disable interrupts for transmit
    RC4IE = 1; //enable interrupts for recieve
}

void UART_transmitByte(transmitType_t transmitType, char data)
{
    switch (transmitType)
    {
        case FONA:
            while(TXSTA4bits.TRMT == 0);
            TXREG4 = data;
            break;
        case USB:
            while(TXSTA1bits.TRMT == 0);
            TXREG1 = data;
            break;
        case PIXY:
            while(TXSTA2bits.TRMT == 0);
            TXREG2 = data;
            break;
    }
}

void UART_transmitString(transmitType_t transmitType, char data[], ...)
{
    char string[200] = "\0";

    va_list aptr;
    va_start(aptr,data);



    for(int i = 0; data[i] != '\0' && i < 200; i++)
    {
        if(data[i] == '%')
        {
            if(data[i+1] == '%')
            {
                strcat(string, "%");
            }
            else
            {
                int val = va_arg(aptr, int);
                char tempString[20];
                sprintf(tempString,"%i",val);
                strcat(string, tempString);
            }
            i++;
        }
        else
        {
            char tempString[2];
            tempString[0] = data[i];
            tempString[1] = '\0';
            strcat(string,tempString);
        }
    }

    va_end(aptr);


    for(int i = 0; string[i] != '\0' && i < 200; i++)
    {
        UART_transmitByte(transmitType, string[i]);
    }
}

