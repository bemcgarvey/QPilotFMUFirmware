/////////////////////////////////////////////////////
// Project: QPilot FMU                             //
// File: extmem.c                                  //
// Target: PIC32MZxxxxEFG064                       // 
// Compiler: XC32                                  //
// Author: Brad McGarvey                           //
// License: GNU General Public License v3.0        //
// Description: External flash memory functions    //
/////////////////////////////////////////////////////

#include "device.h"
#include "extmem.h"
#include "delays.h"

#define SST26VF_NOP             0x00
#define SST26VF_RESET_ENABLE    0x66
#define SST26VF_RESET           0x99
#define SST26VF_RESET_QIO       0xff
#define SST26VF_READ_STATUS     0x05
#define SST26VF_ENABLE_QUAD     0x38
#define SST26VF_READ            0x03
#define SST26VF_HS_READ         0x0b
#define SST26VF_WREN            0x06
#define SST26VF_ERASE_4K_SECTOR 0x20
#define SST26VF_ERASE           0xc7
#define SST26VF_PAGE_PROGRAM    0x02
#define SST26VF_GLOBAL_UNLOCK   0x98

uint32_t flipAddress(uint32_t address);

//TODO This code needs lots of work!

void initFlash(void) {
    //Setup Reference Clock 2 for SQI
    REFO2CONbits.ON = 0;
    while (REFO2CONbits.ACTIVE);
    //TODO Try 50 MHz
    REFO2CONbits.ROSEL = REFO2CONbits.RODIV = 4; //200MHz / 8 = 25 MHz
    REFO2CONbits.ON = 1;
    REFO2CONbits.OE = 1; //TODO do we need this?
    while (REFO2CONbits.DIVSWEN);

    LATDbits.LATD4 = 1;
    TRISDbits.TRISD4 = 0;
    TRISFbits.TRISF1 = 0;
    LATESET = 0b1000;
    TRISECLR = 0b1000;
    TRISESET = 0b0111;
    SQI1CFGbits.SQIEN = 1;
    SQI1CFGbits.RESET = 1;
    while (SQI1CFGbits.RESET);
    SQI1CFGbits.BURSTEN = 1;
    SQI1CFGbits.CSEN = 0b01;
    SQI1CFGbits.DATAEN = 0b01; //Use two pins until switching to quad io
    //SQI1CFGbits.HOLD = 1;  //Hold does not seem to work!
    //SQI1CFGbits.WP = 1;
    SQI1CFGbits.LSBF = 0;
    SQI1CFGbits.CPOL = 0;
    SQI1CFGbits.CPHA = 0; //Mode 0,0
    SQI1CFGbits.MODE = 0b001; //PIO mode
    uint8_t *tx = (uint8_t *) & SQI1TXDATA;
    SQI1CLKCONbits.EN = 1;
    while (!SQI1CLKCONbits.STABLE);
    SQI1THRbits.THRES = 1;
    SQI1CMDTHRbits.TXCMDTHR = 1;
    SQI1CMDTHRbits.RXCMDTHR = 1;
    SQI1INTTHRbits.TXINTTHR = 1;
    SQI1INTTHRbits.RXINTTHR = 1;
    SQI1INTENbits.TXTHRIE = 1;
    SQI1INTENbits.RXTHRIE = 1;
    SQI1INTENbits.PKTCOMPIE = 1;
    SQI1MEMSTATbits.STATBYTES = 1;
    SQI1MEMSTATbits.STATCMD = SST26VF_READ_STATUS;
    SQI1MEMSTATbits.STATTYPE = 0b10;
    SQI1CON = 0x00410001;
    SQI1CON = 0x00410001;
    *tx = SST26VF_RESET_ENABLE;
    *tx = SST26VF_RESET;
    delay_us(1000);
    SQI1CON = 0x00410001;
    *tx = SST26VF_ENABLE_QUAD;
    while (SQI1INTSTATbits.TXEMPTYIF == 0);
    SQI1CFGbits.DATAEN = 0b10;
    TRISESET = 0b1000;
    SQI1CON = 0x00490001;
    SQI1CON = 0x00490001;
    *tx = SST26VF_WREN;
    *tx = SST26VF_GLOBAL_UNLOCK;
    delay_ms(100);
}

void flashEraseAll(void) {
    SQI1INTENbits.TXEMPTYIE = 1;
    uint8_t *tx = (uint8_t *) &SQI1TXDATA;
    SQI1CON = 0x00490001;
    SQI1CON = 0x01490001;
    *tx = SST26VF_WREN;
    *tx = SST26VF_ERASE;
    while (SQI1INTSTATbits.TXEMPTYIF == 0);
}

void flashErase4Kblock(uint32_t address) {
    uint8_t *tx = (uint8_t *) & SQI1TXDATA;
    address &= 0x00fff000;
    SQI1CON = 0x00490001;
    SQI1CON = 0x01490004;
    *tx = SST26VF_WREN;
    SQI1TXDATA = SST26VF_ERASE_4K_SECTOR | ((address & 0x00ff0000) >> 8) | ((address & 0x0000ff00) << 8);
}

void flashRead(uint32_t address, uint8_t *buffer, int bytes) {
    uint8_t *rx = (uint8_t *) & SQI1RXDATA;
    uint8_t *tx = (uint8_t *) & SQI1TXDATA;
    address = flipAddress(address);
    SQI1INTTHRbits.RXINTTHR = 32;
    SQI1CMDTHRbits.RXCMDTHR = 32;
    SQI1CON = 0x00090001;
    SQI1CON = 0x00090004;
    SQI1CON = 0x00090002;
    SQI1CON = 0x004a0020;
    *tx = SST26VF_HS_READ;
    SQI1TXDATA = address & 0x00ffffff;
    *tx = 0;
    *tx = 0;
    while (SQI1INTSTATbits.RXTHRIF == 0);
    for (int i = 0; i < 32; ++i) {
        *buffer = *rx;
        ++buffer;
    }
}

void flashPageProgram(uint32_t address, uint8_t *buffer, int bytes) {
    uint8_t *tx = (uint8_t *) & SQI1TXDATA;
    int count = 256;

    address &= 0x00ffff00;
    address = flipAddress(address);
    SQI1INTTHRbits.TXINTTHR = 4;
    SQI1CMDTHRbits.TXCMDTHR = 32;
    SQI1CON = 0x00490001;
    SQI1CON = 0x00090004;
    SQI1CON = 0x01490100;
    *tx = SST26VF_WREN;
    SQI1TXDATA = SST26VF_PAGE_PROGRAM | (address << 8);
    while (count > 0) {
        while (!SQI1INTSTATbits.TXTHRIF);
        SQI1TXDATA = *((uint32_t *) buffer);
        buffer += 4;
        count -= 4;
    }
}

uint32_t flipAddress(uint32_t address) {
    uint8_t a1, a2, a3;
    a1 = address >> 16;
    a2 = address >> 8;
    a3 = address;
    address = a1 | (a2 << 8) | (a3 << 16);
    return address;
}