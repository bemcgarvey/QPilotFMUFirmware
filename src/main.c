/////////////////////////////////////////////////////
// Project: QPilot FMU                             //
// File: main.c                                    //
// Target: PIC32MZxxxxEFG064                       // 
// Compiler: XC32                                  //
// Author: Brad McGarvey                           //
// License: GNU General Public License v3.0        //
// Description: program entry point and nmi handler//
/////////////////////////////////////////////////////
#include "device.h"
#include <stdlib.h>        
#include "definitions.h"            
#include "led.h"
#include "pins.h"



int main(void) {
    
    SYS_Initialize(NULL);
    initPins();
    LED1Off();
    LED2On();
    while (true) {
        LED1Toggle();
        LED2Toggle();
        delay_ms(1000);
    };
    return ( EXIT_FAILURE);
}

void _nmi_handler(void) {
    
    
    //Clear BEV flag
    _CP0_BIC_STATUS(_CP0_STATUS_BEV_MASK);
    __asm__("ERET");
}

/*******************************************************************************
 End of File
 */

