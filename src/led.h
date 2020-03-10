/////////////////////////////////////////////////////
// Project: QPilot FMU                             //
// File: led.h                                     //
// Target: PIC32MZxxxxEFG064                       // 
// Compiler: XC32                                  //
// Author: Brad McGarvey                           //
// License: GNU General Public License v3.0        //
// Description: LED macros                         //
/////////////////////////////////////////////////////

//////////////////////////////
// Pin Map
//
//
//////////////////////////////
#ifndef LED_H
#define	LED_H

//TODO Update these for correct pins
    #define LED1On()        (LATBbits.LATB2 = 1)
    #define LED1Off()       (LATBbits.LATB2 = 0)
    #define LED1Toggle()    (LATBbits.LATB2 ^= 1)
    #define LED2On()        (LATBbits.LATB3 = 1)
    #define LED2Off()       (LATBbits.LATB3 = 0)
    #define LED2Toggle()    (LATBbits.LATB3 ^= 1)

#endif	/* LED_H */

