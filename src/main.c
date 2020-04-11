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
#include "debug.h"
#include "spi.h"

int main(void) {
    SYS_Initialize(NULL);
    initPins();
    setPPS();
    initDebug();
    initFMUtoMCUch2();
    LED1Off();
    LED2Off();
    __builtin_set_isr_state(0);
    __builtin_enable_interrupts();
    char count = 0;
    while (true) {
        char c = 0;
        transferFMUtoMCUch2(&count, 1);
        LED1Toggle();
        ++count;
        delay_ms(500);
    };
    return ( EXIT_FAILURE);
}

void _nmi_handler(void) {


    //Clear BEV flag
    _CP0_BIC_STATUS(_CP0_STATUS_BEV_MASK);
    __asm__("ERET");
}
