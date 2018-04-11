/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef OV7670_H
#define	OV7670_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include "i2c.h"
#include "uart.h"
#include "OV7670_Reg_Values.h"


char camInit();

char regWrite(char, char);

char regRead(char);

char writeRegCluster(const struct regval_list reglist[]);

void captureImage(char, char);

char fallingEdge(char);

char risingEdge(char);

void Init_OV7670();

void Init_QVGA();

#endif	/* OV7670_H */

