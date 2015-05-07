/* 
 * File:   FONA.h
 * Author: Tyler
 *
 * Created on April 13, 2015, 6:39 PM
 */

#ifndef FONA_H
#define	FONA_H

#ifdef	__cplusplus
extern "C" {
#endif

    char FONA_init();
    char FONA_Text(char *data, char* phoneNumber);
    char FONA_CheckStrength();


#ifdef	__cplusplus
}
#endif

#endif	/* FONA_H */

