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
#include <stdint.h>
#include <stdlib.h>
#include <xc.h>
#include <libpic30.h>


//General Parameters
#define SYSCLK 120000000L
#define _XTAL_FREQ 120000000L
#define SCL_CLK 400000L
/*
 * 
 */


void I2C_Master_Init();
void I2C_Master_Wait();
void I2C_Master_Start();
void I2C_Master_Restart();
void I2C_Master_Stop();
void I2C_Master_Write(uint8_t);
uint8_t I2C_Master_Read(uint8_t);

#endif	/*I2C_H*/

