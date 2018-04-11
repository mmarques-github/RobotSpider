/* Author: Marcelo
 *
 * Created on March 21, 2018, 3:03 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "adc.h"
#include "MPU6050.h"
#include "OV76070.h"


#define XCLK    TRISA6        //Output
#define PCLK    PORTCbits.RC2 //Input
#define VSYNC   PORTCbits.RC1 //Input
#define HREF    PORTCbits.RC0 //Input
#define DATA    PORTB         //Input
#define SYSCLK 16000000L
#define WIDTH   240
#define LENGTH  320
#pragma config CLKOUTEN = 0      //Output System Clock on pin
#pragma config FOSC = INTOSC   
#define _XTAL_FREQ 16000000L

//char img[WIDTH][LENGTH];

char regWrite(char reg, char data);
char regRead(char reg);
char camInit(void);
void captureImage(char w, char h);
char I2C_Init(void);
char writeRegCluster(const struct regval_list reglist[]);
char fallingEdge(char pin);
char risingEdge(char pin);
void Init_OV7670();
void Init_QVGA();



int main(void){
    ANSELA = 0;              //Turn Off Analog Inputs;
    ANSELC= 0;
    OSCCONbits.IRCF = 0xf;  //Internal Oscillator Frequency = 16 MHz
    OSCCONbits.SCS = 0x3;   //Select Internal Oscillator as system clock
    
    TRISA6 = 0;         //Set RA6 as Output;
    TRISB = 0xf;        //Set RB pins as Inputs;
    TRISC |= 0x3;       //Set the RC1-0 as Inputs;
    TRISA0 = 1;         //Image capture switch;
    TRISC3 = 1;
    TRISC4 = 1;
    
    MPU6050_Init();
    ADC_Init();
	I2C_Master_Init();
    Initialize_UART();
    camInit();
    Init_OV7670();
    Init_QVGA();
    //if(regRead(REG_COM9) == 0x18){
    //    PORTAbits.RA0 = 1;          //Turn LED ON;
    //}
    while(1){
        if(PORTAbits.RA0 != 0){
            char t = MPU6050_Read();
           
            UART_send_string("REG_COM7 = ");
            UART_send_char(t);
            UART_send_char('\n');
        }else{
            UART_send_string("IR =");
            UART_send_char(ADC_Read());    
            UART_send_char('\n');
        }
        
        __delay_ms(1000);
    }
    return 0;
}

