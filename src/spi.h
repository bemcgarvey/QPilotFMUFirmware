/////////////////////////////////////////////////////
// Project: QPilot FMU                             //
// File: spi.h                                     //
// Target: PIC32MZxxxxEFG064                       // 
// Compiler: XC32                                  //
// Author: Brad McGarvey                           //
// License: GNU General Public License v3.0        //
// Description: Interprocessor spi functions       //
/////////////////////////////////////////////////////

#ifndef SPI_H
#define	SPI_H

#ifdef	__cplusplus
extern "C" {
#endif

    void initMCUtoFMU(void);
    void initFMUtoMCUch1(void);
    bool transferFMUtoMCUch1(uint8_t *txBuff, int txBytes, uint8_t *rxBuff, int rxBytes);


#ifdef	__cplusplus
}
#endif

#endif	/* SPI_H */

