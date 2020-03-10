/////////////////////////////////////////////////////
// Project: QPilot FMU                             //
// File: pins.h                                    //
// Target: PIC32MZxxxxEFG064                       // 
// Compiler: XC32                                  //
// Author: Brad McGarvey                           //
// License: GNU General Public License v3.0        //
// Description: I/O pin configuration              //
/////////////////////////////////////////////////////

///////////////////////////////
// Pin Map
//
//RB2 = LED1
//RB3 = LED2
//RB4 = MCU_INT
//RB5 = SENSOR_3V3_EN
//RB6 = U2TX
//RB7 = U2RX
//RB9 = SDO3
//RB14 = SCK3
//
//RC13 = SDO1
//RC14 = SDI1
//
//RD0 = SDO4
//RD1 = SCK1
//RD2 = SDA3
//RD3 = SCL3
//RD4 = SQICS0
//RD9 = INT2
//RD10 = SCK4
//RD11 = SDI4
//
//RE0 = SQID0
//RE1 = SQID1
//RE2 = SQID2
//RE3 = SQID3
//RE5 = INT4
//
//RF1 = SQICLK
//RF3 = INT1
//RF4 = SDA5
//RF5 = SCL5
//
//RG6 = BNO055_nReset
//RG7 = SDA4
//RG8 = SCL4

///////////////////////////////

#ifndef PINS_H
#define	PINS_H

#ifdef	__cplusplus
extern "C" {
#endif

    void initPins(void);
    void setPPS(void);


#ifdef	__cplusplus
}
#endif

#endif	/* PINS_H */

