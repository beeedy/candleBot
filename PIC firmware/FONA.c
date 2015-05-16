/*               _____  ________  ___  _____      _ _       _
                |  __ \/  ___|  \/  | /  __ \    | | |     | |
                | |  \/\ `--.| .  . | | /  \/ ___| | |_   _| | __ _ _ __
                | | __  `--. \ |\/| | | |    / _ \ | | | | | |/ _` | '__|
                | |_\ \/\__/ / |  | | | \__/\  __/ | | |_| | | (_| | |
                 \____/\____/\_|  |_/  \____/\___|_|_|\__,_|_|\__,_|_|

 * File:   FONA.h
 * Author: Broderick Carlin
 */

#include "FONA.h"

extern volatile char FONA_BUFF[FONA_BUFF_SIZE];
extern volatile char FONA_INDEX;

char FONA_init()
{
    char done = FAILURE;
    for(int i = 0; i < 20; i++)
    {
        if(FONA_sendCommandCheckReply("AT","OK"))
        {
            done = SUCCESS;
            i = 20;
        }
        delay_ms(100);
    }
    return done;
}


char FONA_Text(char *data, char *phoneNumber)
{
    if (!FONA_init()) return FAILURE;
    if (!FONA_sendCommandCheckReply("AT+CMGF=1", "OK")) return FAILURE;

    char sendcmd[30] = "AT+CMGS=\"";
    strncpy(sendcmd+9, phoneNumber, 30-9-2);  // 9 bytes beginning, 2 bytes for close quote + null
    sendcmd[strlen(sendcmd)] = '\"';

    FONA_INDEX = 0;

    FONA_sendCommand(sendcmd);

    UART_transmitString(FONA,data);
    UART_transmitByte(FONA,'\n');
    UART_transmitByte(FONA,'\0');
    UART_transmitByte(FONA,'\n');
    UART_transmitByte(FONA,0x1A);

    unsigned long start = millis();
    while(FONA_INDEX < 8 && millis() - start < 10000);

    if(millis() - start >= 10000)
    {
        return FAILURE;
    }

    FONA_BUFF[8] = '\0';
    if(strcmp(FONA_BUFF,"\r\n+CMGS:") == 0)
    {
        return SUCCESS;
    }

    return FAILURE;
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
            return FAILURE;
        }
    }
    return SUCCESS;
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
        return FAILURE;
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