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
#include "extmem.h"
#include "delays.h"

uint8_t mem[256];
uint8_t memr[256];

int main(void) {
    SYS_Initialize(NULL);
    initPins();
    setPPS();
    initDebug();
    initFlash();
    
    for (int i = 0; i < 256; ++i) {
        mem[i] = i;
        memr[i] = 0xff;
    }
    //flashErase4Kblock(0);
    //delay_ms(100);
    //flashPageProgram(0, mem, 256);
    flashRead(0, memr, 32);
    LED2On();
    
    __builtin_set_isr_state(0);
    //__builtin_enable_interrupts();
    char count = 0;
    while (true) {
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
