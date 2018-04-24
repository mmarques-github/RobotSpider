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
    SSPCON2 = 0x20;
    SSPADD = SYSCLK/(4*SIOC_CLK) - 1;   //Set Clock Speed
    TRISC3 = 1;
    TRISC4 = 1;  //Set SSP Pins as Inputs
}


void I2C_Master_Wait(){
<<<<<<< HEAD
    while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)); //Transmit is in progress
=======
    while((SSPSTAT & 0x04) || (SSPCON2 & 0x1F)) //Transmit is in progress
    {
        UART_send_char('w');
        UART_send_char('\n');
        __delay_ms(1000);
    }
>>>>>>> parent of 9a4dca4... Int2Str Coversion
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

int I2C_Master_Read()
{
  char temp;
  I2C_Master_Wait();
  RCEN = 1;
  I2C_Master_Wait();
  temp = SSPBUF;      //Read data from SSPBUF
  I2C_Master_Wait();
  //ACKDT = 0;          //Send NACK because of SSCB
  //ACKEN = 1;          //Acknowledge sequence
  return temp;
}
