#include "i2c.h"


void I2C_Master_Init(){
    /*Reseting I2C Module Registers */
    I2CRCV = 0x0000;
    I2CTRN = 0x00ff;
    I2CCON = 0x1000;
    I2CSTAT = 0x0000;
    I2CADD = 0x0000;
    
    I2CBRG = (_XTAL_FREQ/SCL_CLK - _XTAL_FREQ/1111111) - 1 ; 
    /*Alternative Formula Baudrate Generation
     * I2CBRG = (_XTAL_FREQ/(SCL_CLK/1000) - _XTAL_FREQ/1000 )/1000 -1 
     */
    
    /*Set I2C Pins as Inputs*/
    TRISB |= 0x30;                     
}


void I2C_Master_Wait(){
    while((I2CSTAT & 0x0004) || (I2CCON & 0x001F)); //Transmit is in progress
}

void I2C_Master_Start(){
    I2C_Master_Wait();
    I2CCONbits.SEN = 1;                //Initiate Start Condition;
}

void I2C_Master_Restart(){
    I2C_Master_Wait();
    I2CCONbits.RSEN = 1;               //Initiate repeated start condition
}

void I2C_Master_Stop(){
    I2C_Master_Wait();
    I2CCONbits.PEN = 1;                //Initiate stop condition
}

void I2C_Master_Write(uint8_t d){
    I2C_Master_Wait();
    I2CTRN = d;             //Write data to I2C Transmit Register
}

uint8_t I2C_Master_Read(uint8_t camera)
{
  char temp;
  I2C_Master_Wait();
  I2CCONbits.RCEN = 1;
  I2C_Master_Wait();
  temp = I2CRCV;      //Read data from I2C Receive Register
  I2C_Master_Wait();
  
  /*Check if the slave device is the OV7670*/
  if(!camera){              
    I2CCONbits.ACKDT = 0;          //If not send ACK
    I2CCONbits.ACKEN = 1;          //Start Acknowledge sequence
  }
  return temp;
}
