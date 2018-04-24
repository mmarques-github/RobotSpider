#include "i2c.h"

//General Parameters
#define SYSCLK 16000000L
#define _XTAL_FREQ 16000000L
#define SIOC_CLK 400000L
/*
 * 
 */


void I2C_Master_Init(){
    SSPCON1 = 0x28;                     //SSP Module at I2C Master
    SSPCON2 = 0x0;
    SSPADD = SYSCLK/(4*SIOC_CLK) - 1;   //Set Clock Speed
    TRISC3 = 1;
    TRISC4 = 1;  //Set SSP Pins as Inputs
}


void I2C_Master_Wait(){
    while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); //Transmit is in progress
}

void I2C_Master_Start(){
    I2C_Master_Wait();
    SEN = 1;                //Initiate Start Condition;
}

void I2C_Master_Restart(){
    I2C_Master_Wait();
    RSEN = 1;               //Initiate repeated start condition
}

void I2C_Master_Stop(){
    I2C_Master_Wait();
    PEN = 1;                //Initiate stop condition
}

void I2C_Master_Write(uint8_t d){
    I2C_Master_Wait();
    SSPBUF = d;             //Write data to SSPBUF
}

uint8_t I2C_Master_Read(uint8_t device)
{
  char temp;
  I2C_Master_Wait();
  RCEN = 1;
  I2C_Master_Wait();
  temp = SSPBUF;      //Read data from SSPBUF
  I2C_Master_Wait();
  
  /*Check if the slave device is the OV7670*/
  if(!device){              
    ACKDT = 0;          //If not send ACK
    ACKEN = 1;          //Start Acknowledge sequence
  }
  return temp;
}
