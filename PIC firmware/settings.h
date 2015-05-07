/* 
 * File:   settings.h
 * Author: broderickcarlin
 *
 * Created on April 13, 2015, 11:25 PM

 Settings dip switch's
 0: (Tyler/!Broderick)      RL2
 1: (Call/!Text)            RG4
 2: (Auto/!Remote)          RL1
 3:  Debug to USB           RG3
 4: (Wander/!Competition    RG2
 5: (Cams/!Cripple)         RG1
 6: Self Test               RG0

 button                     RL3
 */

#ifndef SETTINGS_H
#define	SETTINGS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>

    void settings_init();
    char settings_readSettings();
    char settings_readButton();

    char settings_callee();
    char settings_call();
    char settings_auto();
    char settings_debugMode();
    char settings_wander();
    char settings_cams();
    char settings_selfTest();

#ifdef	__cplusplus
}
#endif

#endif	/* SETTINGS_H */

