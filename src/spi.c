/////////////////////////////////////////////////////
// Project: QPilot FMU                             //
// File: spi.c                                     //
// Target: PIC32MZxxxxEFG064                       // 
// Compiler: XC32                                  //
// Author: Brad McGarvey                           //
// License: GNU General Public License v3.0        //
// Description: Interprocessor spi functions       //
/////////////////////////////////////////////////////

#include "device.h"
#include "spi.h"
#include "led.h"

void initMCUtoFMUchannel(void) {
    TRISBbits.TRISB10 = 1;  //TODO - remove this when when board is correct.
    TRISCbits.TRISC13 = 1;
    SPI1CON = 0;
    char c = SPI1BUF;
    SPI1CONbits.ENHBUF = 0;
    SPI1CONbits.MODE16 = 0;
    SPI1CONbits.MODE32 = 0;  //8 bit transfers for now
    SPI1CONbits.CKE = 1;
    SPI1CONbits.CKP = 0;
    SPI1CONbits.MSTEN = 0;
    IFS3bits.SPI1RXIF = 0;
    IPC27bits.SPI1RXIP = 4;
    IPC27bits.SPI1RXIS = 0;
    IEC3bits.SPI1RXIE = 1;
    SPI1STATbits.SPIROV = 0;
    SPI1CONbits.ON = 1;
    SPI1BUF = 0;  //Initial data
}

void __ISR(_SPI1_RX_VECTOR, IPL4SRS) spi1RxIsr(void) {
    char c;
    c = SPI1BUF;
    if (c == 'f') {
        SPI1BUF = 1;
        LED1Toggle();
    }
    else if (c == 'g') {
        LED2Toggle();
        SPI1BUF = 2;
    } else {
        SPI1BUF = 0;
    }
    IFS3bits.SPI1RXIF = 0;
}