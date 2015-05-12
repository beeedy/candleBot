/* 
 * File:   FONA.h
 * Author: Tyler
 *
 * Created on April 13, 2015, 6:39 PM
 */

#ifndef FONA_H
#define	FONA_H

#define FONA_TIMEOUT 10


    char FONA_init();
    char FONA_sendCommandCheckReply(const char[], const char[]);
    void FONA_sendCommand(const char[]);
    char FONA_checkReply(const char[]);
    char FONA_Text(char *data, char* phoneNumber);
    char FONA_CheckStrength();


#endif	/* FONA_H */

