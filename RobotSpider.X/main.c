/* Author: Marcelo
 *
 * Created on March 21, 2018, 3:03 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
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
#define DEVICE  1
#define CAM     0
#pragma config CLKOUTEN = 0      //Output System Clock on pin
#pragma config FOSC = INTOSC   
#define _XTAL_FREQ 16000000L


void int2str(char*,int);
void itoa1(int, char[]);
void reverse(char []);
//int strlen(char[]);


int main(void){
    ANSELA = 0;              //Turn Off Analog Inputs;
    ANSELC= 0;
    OSCCONbits.IRCF = 0xf;  //Internal Oscillator Frequency = 16 MHz
    OSCCONbits.SCS = 0x3;   //Select Internal Oscillator as system clock
    
    
    /*Setting up the ports*/
    TRISA6 = 0;         //Set RA6 as Output;
    TRISB = 0xf;        //Set RB pins as Inputs;
    TRISC |= 0x3;       //Set the RC1-0 as Inputs;
    TRISA0 = 1;         //Image capture switch;
    TRISC3 = 1;
    TRISC4 = 1;
    
	/*Initializing the Communication Protocols*/
    I2C_Master_Init();
    Initialize_UART();
   
    
    /*OV7670 Setup*/
    //camInit();
    //Init_OV7670();
    //Init_QVGA();
    
    
    /*Accel/Gyro Setup*/
    MPU6050 *Sensor;
    MPU6050_Init();
    
    /*IR sensors setup*/
    //ADC_Init();
 
    while(1){
        if(PORTAbits.RA0 != 0){
            char buf[10];
            MPU6050_Read(&Sensor);
            itoa1(Sensor->Accel.X, buf);
            UART_send_string("AccelX = ");
            UART_send_string(buf);
            UART_send_string("\n");
        }else{
            UART_send_string("IR =");
            UART_send_char(ADC_Read());    
            UART_send_char('\n');
        }
        __delay_ms(1000);
    }
    return 0;
}



void int2str(char* buf,int16_t num){
    char tmp[5];
    int mul[] = {1000,100,10,1};
    if(num < 0 ) 
    {
        num  = num*(-1);
        tmp[0] = '-';
    } else {
        tmp[0] = '+';
    }
    
    uint16_t x = num;
    uint16_t y = num;
    
    for(uint8_t i = 0; i < 4; i++)
    {
        y = x%mul[i];
        tmp[i+1]= '0' + x/mul[i];
        x = y;
    }
    
    strcpy(buf,tmp);
}

void itoa1(int n, char s[])
{
    int i, sign;

    if ((sign = n) < 0)  /* record sign */
        n = -n;          /* make n positive */
    i = 0;
    do {       /* generate digits in reverse order */
        s[i++] = n % 10 + '0';   /* get next digit */
    } while ((n /= 10) > 0);     /* delete it */
    if (sign < 0)
        s[i++] = '-';
    s[i] = '\0';
    reverse(s);
}

void reverse(char s[])
{
    int i, j;
    char c;

    for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

/* strlen: return length of s */
//int strlen(char s[])
//{
//    int i = 0;
//    while (s[i] != '\0')
//        ++i;
//    return i;
//}