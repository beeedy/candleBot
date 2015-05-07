
/*
 * Function for interfacing with the FONA GSM Module
 *
 *
 */

#define SUCCESS 0
#define INVALID_PHONE_NUMBER 1
#define INSUFFICIENT_CELL 2
#define TEXT_SIZE_ERROR 3
#define RETRY_COUNT 3

#include "GlobalDefines.h"
#include "UART.h"
#include "delays.h"
#include "FONA.h"
#include <string.h>

extern volatile char FONA_BUFF[FONA_BUFF_SIZE];
extern volatile char FONA_INDEX;

char FONA_init() {
    char genString[20] = "AT\r\nOK\r\n";
    // Fona seems to send text and then an \r character, not a \0
    // character, elliminating the possibility of using a string
    // continuous recieve function for little
    short retry = 5;
    FONA_INDEX = 0;
    do {
        UART_transmitByte(FONA, 'A');   // Transmit
        //delay_ms(1);                    // Fona should echo 'A'
        UART_transmitByte(FONA, 'T');
        //delay_ms(1);                    // Fona should echo 'T'
        UART_transmitByte(FONA, '\r');
        //delay_ms(1);                    /// Should echo '\r'
        UART_transmitByte(FONA, '\n');
        delay_ms(5);                    /// Should echo '\n'

        for(signed char i = 7; i >= 0; i--) {
            if( !(FONA_BUFF[i] == genString[i]) ) {
                retry = retry - 1;  // decrement the number of times to retry
                FONA_INDEX = 0;    // Reset the buffer
                break;              // stop checking the arrays
            }
            retry = -1;     // success!
        }
    } while(retry > 0);

    if(retry == -1) {       // Successful communication
        FONA_INDEX = 0;
        for(signed char i = 10; i >= 0; i--) {
            FONA_BUFF[i] = 0;   // clear buffer just in case
        }
        return 0;
    }
    return 1;               // unsuccessful communication
}

/* Given a null terminated string and a 10 digit phone number, this function
 * will text the number the string if it is under 140 characters, the phone
 * number is valid, and the signal strength is sufficient.
 *
 * Return codes:
 *   0 - success
 *   1 - invalid phone number
 *   2 - insufficient cell strength
 *   3 - too long of a string
 *
 */

char FONA_Text(char *data, char *phoneNumber)
{
  char genString[20];
  char error = 1;
  char strength = 0;

    if(phoneNumber[10] == '\0')
    {   // if phoneNumber[] is 10 digits long
        for(int i = 0; i < 141; i++)
        {
            if(data[i] == '\0')
            {   // We have reached the end of the string
                error = 0;
                break;
            }
            if(error == 1)
            {
                return(TEXT_SIZE_ERROR);
            }
        }

        strength = FONA_CheckStrength();

        if(strength < 6)
        {      // Insufficient Cell Strength

            return(INSUFFICIENT_CELL);
        }
        strcpy(genString, "AT+CMGF=1");
        UART_transmitString(FONA, genString);   // Text mode
        delay_ms(5);
        strcpy(genString, "AT+CMGS=");
        for(int i = 17; i > 7; i--)
        {       // String concatination
            genString[i] = phoneNumber[i-7];
        }
        genString[18] = '\0';
        UART_transmitString(FONA, genString);   // Phone Number I'm Texting
        delay_ms(5);
        strcpy(genString, "MESSAGE_GOES_HERE\r\n");
        UART_transmitString(FONA, genString);
        UART_transmitByte(FONA, '\0');      // send message!

        //code for checking if the text went through successfully goes here
    }
    else
    {
        return(INVALID_PHONE_NUMBER);
    }
    return(0);
}


char FONA_CheckStrength()
{

    char genString[21] = "00000000000000000000"; // changed to 21 in length so null could be added. removed error
    FONA_INDEX = 0;
    strcpy(genString, "AT+CSQ\r\n");
    UART_transmitString(FONA, &genString[0]);   // Check call strength
    delay_ms(5);
    for(int i = FONA_INDEX; i >= 0; i--)
    {


    }

    return 'a'; // this is just to remove error, no idea what you are actually doing
}