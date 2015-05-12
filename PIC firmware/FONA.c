
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

char FONA_init()
{
    for(int i = 0; i < 5; i++)
    {
        if(FONA_sendCommandCheckReply("AT","OK"))
        {
            return 0x01;
        }
        delay_ms(100);
    }
    return 0x00;
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

void FONA_sendCommand(const char input[])
{
    char input_fixed[100];

    char inputLength = strlen(input);

    strcpy(input_fixed, input);
    input_fixed[inputLength] = '\n';
    input_fixed[inputLength + 1] = '\0';

    UART_transmitString(FONA, input_fixed);
}

char FONA_checkReply(const char test[])
{
    for(int i = 0; i < strlen(test); i++)
    {
        if(test[i] !=  FONA_BUFF[i])
        {
            return 0x00;
        }
    }
    return 0x01;
}

char FONA_sendCommandCheckReply(const char input[], const char check[])
{
    FONA_INDEX = 0;

    char inputLength = strlen(input);
    char checkLength = strlen(check);

    FONA_sendCommand(input);

    unsigned long timeOut = millis();
    while(FONA_INDEX < (inputLength + checkLength + 3) && millis() - timeOut < FONA_TIMEOUT);

    if(millis() - timeOut >= FONA_TIMEOUT)
    {
        return 0x00;
    }

    char test[100];
    strcpy(test,input);
    test[inputLength] = '\r';
    test[inputLength+1] = '\n';

    for(int i = 0; i < checkLength; i++)
    {
        test[inputLength + 2 + i] = check[i];
    }

    test[inputLength + checkLength + 2] = '\r';
    test[inputLength + checkLength + 3] = '\n';
    test[inputLength + checkLength + 4] = '\0';

    return FONA_checkReply(test);
}