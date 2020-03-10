/////////////////////////////////////////////////////
// Project: QPilot fmu                             //
// File: version.c                                 //
// Target: PIC32MZxxxxEFG064                       // 
// Compiler: XC32                                  //
// Author: Brad McGarvey                           //
// License: GNU General Public License v3.0        //
// Description: firmware version data              //
/////////////////////////////////////////////////////
#include "device.h"
#include "version.h"


const unsigned int firmwareVersion = (MAJOR_VERSION << 8) | MINOR_VERSION;
