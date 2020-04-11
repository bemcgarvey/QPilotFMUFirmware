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

void initMCUtoFMU(void) {
    TRISBbits.TRISB10 = 1;  //TODO - remove this when when board is correct.
    TRISCbits.TRISC13 = 1;
    TRISDbits.TRISD1 = 1;
    SPI1CON = 0;
    char c = SPI1BUF;
    SPI1CONbits.ENHBUF = 0;
    SPI1CONbits.MODE16 = 0;
    SPI1CONbits.MODE32 = 0;  //8 bit transfers for now
    SPI1CONbits.CKE = 1;
    SPI1CONbits.CKP = 0;
    SPI1CONbits.SMP = 1;
    SPI1CONbits.MSTEN = 0;
    IFS3bits.SPI1RXIF = 0;
    IPC27bits.SPI1RXIP = 4;
    IPC27bits.SPI1RXIS = 0;
    IEC3bits.SPI1RXIE = 1;
    SPI1STATbits.SPIROV = 0;
    SPI1CONbits.ON = 1;
    SPI1BUF = 0;  //Initial data
}

void initFMUtoMCUch1(void) {
    TRISDbits.TRISD11 = 1;
    SPI4CON = 0;
    char c = SPI4BUF;
    SPI4CONbits.ENHBUF = 0;
    SPI4CONbits.MODE16 = 0;
    SPI4CONbits.MODE32 = 0;  //8 bit transfers for now
    SPI4CONbits.CKE = 1; 
    SPI4CONbits.CKP = 0;
    SPI4CONbits.SMP = 1;
    SPI4CONbits.MSTEN = 1;
    SPI4BRG = 1; //25 MHz
    SPI4STATbits.SPIROV = 0;
    SPI4CONbits.ON = 1;
}

bool transferFMUtoMCUch1(uint8_t *txBuff, int txBytes, uint8_t *rxBuff, int rxBytes) {
    uint8_t c;
    while (txBytes > 0) {
        SPI4BUF = *txBuff;
        while (SPI4STATbits.SPIRBF == 0);
        c = SPI4BUF;
        --txBytes;
        ++txBuff;
    }
    delay_us(100);
    while (rxBytes > 0) {
        SPI4BUF = 0;
        while (SPI4STATbits.SPIRBF == 0);
        c = SPI4BUF;
        *rxBuff = c;
        --rxBytes;
        ++rxBuff;
    }
    return true;
}

void initFMUtoMCUch2(void) {
    SPI3CON = 0;
    char c = SPI3BUF;
    SPI3CONbits.ENHBUF = 0;
    SPI3CONbits.MODE16 = 0;
    SPI3CONbits.MODE32 = 0;  //8 bit transfers for now
    SPI3CONbits.CKE = 1; 
    SPI3CONbits.CKP = 0;
    SPI3CONbits.SMP = 1;
    SPI3CONbits.MSTEN = 1;
    SPI3BRG = 1; //25 MHz 
    SPI3STATbits.SPIROV = 0;
    SPI3CONbits.DISSDI;
    SPI3CONbits.ON = 1;
}

bool transferFMUtoMCUch2(uint8_t *txBuff, int txBytes) {
    uint8_t c;
    while (txBytes > 0) {
        while (SPI3STATbits.SPITBE == 0);
        SPI3BUF = *txBuff;
        --txBytes;
        ++txBuff;
    }
    return true;
}

//MCU to FMU
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