/* 
 * File:   PIC16F_I2C_config.h
 * Author: Marcelo
 *
 * Created on March 21, 2018, 3:03 AM
 */


#ifndef I2C_H
#define	I2C_H

#include "uart.h"
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>

//General Parameters
#define SYSCLK 16000000L
#define _XTAL_FREQ 16000000L
#define SIOC_CLK 400000L
/*
 * 
 */


void I2C_Master_Init();
void I2C_Master_Wait();
void I2C_Master_Start();
void I2C_Master_Restart();
void I2C_Master_Stop();
void I2C_Master_Write(char);
int I2C_Master_Read();

#endif	/*I2C_H*/

