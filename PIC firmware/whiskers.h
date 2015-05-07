/* 
 * File:   whiskers.h
 * Author: broderickcarlin
 *
 * Created on April 13, 2015, 7:29 AM
 */
#include <xc.h>

#ifndef WHISKERS_H
#define	WHISKERS_H

#ifdef	__cplusplus
extern "C" {
#endif

    void whiskers_Init();
    char whiskers_pollLeft();
    char whiskers_pollRight();

#ifdef	__cplusplus
}
#endif

#endif	/* WHISKERS_H */

