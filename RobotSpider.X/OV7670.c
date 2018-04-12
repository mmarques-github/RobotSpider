#include "OV76070.h"
#define XCLK    TRISA6        //Output
#define PCLK    PORTCbits.RC2 //Input
#define VSYNC   PORTCbits.RC1 //Input
#define HREF    PORTCbits.RC0 //Input
#define DATA    PORTB         //Input
#define SYSCLK 16000000L
#define WIDTH   240
#define LENGTH  320
#define OV7670  1
#pragma config CLKOUTEN = 0      //Output System Clock on pin
#pragma config FOSC = INTOSC   
#define _XTAL_FREQ 16000000L


char camInit(){
    __delay_ms(100);
	regWrite(REG_COM7, 0x80); //Register Reset
	__delay_ms(100);
	regWrite(REG_COM2,0x1); //Enable Standby Mode
    return 1;
}

char regWrite(char reg, char data){
	I2C_Master_Restart();
	I2C_Master_Write(camAddr_WR);
	I2C_Master_Write(reg);
	I2C_Master_Write(data);
	I2C_Master_Stop();
    
    return 1;
}

uint8_t regRead(char reg){
	I2C_Master_Start();
	I2C_Master_Write(camAddr_WR);
	I2C_Master_Write(reg);
	I2C_Master_Stop();

	__delay_ms(1);
	
	I2C_Master_Restart();
    I2C_Master_Write(camAddr_RD);
    __delay_ms(10);
	uint8_t data = I2C_Master_Read(OV7670);
	I2C_Master_Stop();
    __delay_ms(1);

	return data;
}

void captureImage(char w, char h){
    if(fallingEdge(VSYNC));                         //Start of a Frame
    while(!(risingEdge(VSYNC))){                    //Loop goes on until the start of a new frame
        for(int  i = 0; i < WIDTH; i++ ){   
            if(risingEdge(HREF))                    //HREF signals the start of a new row
                for(int j = 0;j < LENGTH; j++ ){
                    if(risingEdge(PCLK));           //Each Pixel is sample at PCLK rising edge
                    //img[i][j] = PORTB;
                    UART_send_char(LATB);          //Send Pixel to PC
                }
            if(fallingEdge(HREF));                  //Check for the end of a row
        }
    }
}

char fallingEdge(char pin){
    while(!(pin & 8));
    while(pin & 8);
    return 1;
}

char risingEdge(char pin){
    while(pin & 8);
    while(!(pin & 8));
    return 1;
}

void Init_OV7670(){
  //Reset All Register Values
  regWrite(0x12,0x80);
  __delay_ms(100);
  regWrite(0x3A, 0x04); //TSLB
 
  regWrite(REG_COM8, 0xC0); //COM8
  regWrite(REG_GAIN, 0x00); //GAIN
  regWrite(REG_AECH, 0x00); //AECH
  regWrite(REG_COM4, 0x40); //COM4
  regWrite(REG_COM9, 0x18); //COM9
  regWrite(REG_AEW, 0x95); //AEW
  regWrite(REG_AEB, 0x33); //AEB
  regWrite(REG_COM8, 0xC5); //COM8
  regWrite(GGAIN, 0x40); //GGAIN
  regWrite(REG_BLUE, 0x40); //BLUE
  regWrite(REG_RED, 0x60); //RED
  regWrite(REG_COM8, 0xC7); //COM8
  regWrite(REG_COM16, 0x08); //COM16
  regWrite(REG_COM10, 0x20); //COM10 - PCLK does not toggle on HBLANK
  }

void Init_QVGA(){
  regWrite(REG_COM3, 0x04);//COM3 - Enable Scaling
  regWrite(REG_COM14, 0x19);//COM14
  regWrite(0x72, 0x11);//
  regWrite(0x73, 0xF1);//
  regWrite(REG_HSTART, 0x16);//HSTART
  regWrite(REG_HSTOP, 0x04);//HSTOP
  regWrite(REG_HREF, 0xA4);//HREF
  regWrite(REG_VSTART, 0x02);//VSTART
  regWrite(REG_VSTOP, 0x7A);//VSTOP
  regWrite(REG_VREF, 0x0A);//VREF
  }

