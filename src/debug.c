/////////////////////////////////////////////////////
// Project: QPilot MCU                             //
// File: debug.c                                   //
// Target: PIC32MZxxxxEFG064                       // 
// Compiler: XC32                                  //
// Author: Brad McGarvey                           //
// License: GNU General Public License v3.0        //
// Description: debugging tools - USART logging    //
/////////////////////////////////////////////////////

#include "device.h"
#include "debug.h"

void initDebug(void) {
    TRISBbits.TRISB7 = 1;
    U2BRG = 53; //115200 baud
    U2MODEbits.BRGH = 0;
    U2STAbits.URXEN = 1;
    U2STAbits.UTXEN = 1;
    U2STAbits.OERR = 0;
    U2MODEbits.ON = 1;
}

void _mon_putc(char c) {
    while (U2STAbits.UTXBF == 1);
    U2TXREG = c;
}

int _mon_getc(int canblock) {
    char c;
    if (canblock) {
        while (U2STAbits.URXDA == 0);
        c = U2RXREG;
        return c;
    } 
    else if (U2STAbits.URXDA == 1) {
        char c = U2RXREG;
        return c;
    } else {
        return -1;
    }
}