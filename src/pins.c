/////////////////////////////////////////////////////
// Project: QPilot FMU                             //
// File: pins.c                                    //
// Target: PIC32MZxxxxEFG064                       // 
// Compiler: XC32                                  //
// Author: Brad McGarvey                           //
// License: GNU General Public License v3.0        //
// Description: I/O pin configuration              //
/////////////////////////////////////////////////////
#include "device.h"
#include "pins.h"

void initPins(void) {
    //Set all pins to digital output low level
    LATB = 0;
    LATC = 0;
    LATD = 0;
    LATE = 0;
    LATF = 0;
    LATG = 0;
    ANSELB = 0;
    ANSELE = 0;
    ANSELG = 0;
    TRISB = 0;
    TRISC = 0;  
    TRISD = 0;
    TRISE = 0;
    TRISF = 0;
    TRISG = 0;
}

void setPPS(void) {
    /* unlock system for PPS configuration */
    SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    CFGCONbits.IOLOCK = 0;
    /* PPS Input Remapping */
    U2RXR = 0b0111;
    SDI1R = 0b0110;
    INT2R = 0b0000;
    SDI4R = 0b0011;
    INT4R = 0b0110;
    INT1R = 0b1000;

    /* PPS Output Remapping */
    RPB6R = 0b0010;
    RPB9R = 0b0111;
    RPC14R = 0b0101;
    RPD0R = 0b1000;

            /* Lock back the system after PPS configuration */
            SYSKEY = 0x00000000;
    SYSKEY = 0xAA996655;
    SYSKEY = 0x556699AA;
    CFGCONbits.IOLOCK = 1;
}
