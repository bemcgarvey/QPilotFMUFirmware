/////////////////////////////////////////////////////
// Project: QPilot FMU                             //
// File: extmem.h                                  //
// Target: PIC32MZxxxxEFG064                       // 
// Compiler: XC32                                  //
// Author: Brad McGarvey                           //
// License: GNU General Public License v3.0        //
// Description: External flash memory functions    //
/////////////////////////////////////////////////////

#ifndef EXTMEM_H
#define	EXTMEM_H

#ifdef	__cplusplus
extern "C" {
#endif

    void initFlash(void);
    void flashEraseAll(void);
    void flashErase4Kblock(uint32_t address);
    void flashRead(uint32_t address, uint8_t *buffer, int bytes);
    void flashPageProgram(uint32_t address, uint8_t *buffer, int bytes);

#ifdef	__cplusplus
}
#endif

#endif	/* EXTMEM_H */

