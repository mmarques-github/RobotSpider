/* Author: Marcelo
 *
 * Created on March 21, 2018, 3:03 AM
 */


// CONFIG1
#pragma config FOSC = INTOSC    // Oscillator Selection (INTOSC oscillator: I/O function on CLKIN pin)
#pragma config WDTE = OFF       // Watchdog Timer Enable (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable (PWRT disabled)
#pragma config MCLRE = ON       // MCLR Pin Function Select (MCLR/VPP pin function is MCLR)
#pragma config CP = OFF         // Flash Program Memory Code Protection (Program memory code protection is disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable (Brown-out Reset enabled)
#pragma config CLKOUTEN = ON    // Clock Out Enable (CLKOUT function is enabled on the CLKOUT pin)
#pragma config IESO = ON        // Internal/External Switchover (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor Enable (Fail-Safe Clock Monitor is enabled)

// CONFIG2
#pragma config WRT = OFF        // Flash Memory Self-Write Protection (Write protection off)
#pragma config VCAPEN = OFF     // Voltage Regulator Capacitor Enable bit (VCAP pin function disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a Reset)
#pragma config BORV = LO        // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (Vbor), low trip point selected.)
#pragma config LPBOR = OFF      // Low-Power Brown Out Reset (Low-Power BOR is disabled)
#pragma config LVP = ON         // Low-Voltage Programming Enable (Low-voltage programming enabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <stdio.h>
#include <stdlib.h>
<<<<<<< HEAD
=======
#include <xc.h>
>>>>>>> parent of 9a4dca4... Int2Str Coversion
#include "adc.h"
#include "MPU6050.h"
#include <xc.h>

#define WIDTH   240
#define LENGTH  320
<<<<<<< HEAD
#define DEVICE  1
#define CAM     0
#define _XTAL_FREQ 16000000L
//int strlen(char[]);
=======
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

>>>>>>> parent of 9a4dca4... Int2Str Coversion


void MPU6050_DeviceDriverTest();
int main(void){
<<<<<<< HEAD
    
    /*Setting up the ports*/
    
	/*Initializing the Communication Protocols*/
    I2C_Master_Init();
    Initialize_UART();
   
    
    /*OV7670 Setup*/
    //camInit();
    //Init_OV7670();
    //Init_QVGA();
    
    
    /*Accel/Gyro Setup*/
=======
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
    
>>>>>>> parent of 9a4dca4... Int2Str Coversion
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
<<<<<<< HEAD
        if(1){
            I2C_Master_Start();
            I2C_Master_Write( MPU6050_ADDRESS );
            I2C_Master_Write( MPU6050_RA_GYRO_CONFIG );
            I2C_Master_Write( 0 ); //gyro_config, +-250 °/s
            I2C_Master_Write( 0 ); //accel_config +-2g
            I2C_Master_Stop();
            __delay_ms(1000);

        UART_send_string("config over... \n");
        }
        if(0){
            MPU6050_DeviceDriverTest();
        }
=======
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
>>>>>>> parent of 9a4dca4... Int2Str Coversion
    }
    return 0;
}

<<<<<<< HEAD
void MPU6050_DeviceDriverTest(){
    MPU6050 *TestRun;
    MPU6050_Read(TestRun);
    char buf[10];
    
    
    UART_send_string("\n\n/**********************/\n");
    int2str(TestRun->Accel.X, buf);
    UART_send_string("Accel.X = ");
    UART_send_string(buf);
    UART_send_string("\n");
    
    int2str(TestRun->Accel.Y, buf);
    UART_send_string("Accel.Y = ");
    UART_send_string(buf);
    UART_send_string("\n");
    
    int2str(TestRun->Accel.Z, buf);
    UART_send_string("Accel.Z = ");
    UART_send_string(buf);
    UART_send_string("\n");
    
    int2str(TestRun->Gyro.X, buf);
    UART_send_string("Gyro.X = ");
    UART_send_string(buf);
    UART_send_string("\n");
    
    int2str(TestRun->Gyro.Y, buf);
    UART_send_string("Gyro.Y = ");
    UART_send_string(buf);
    UART_send_string("\n");
    
    int2str(TestRun->Gyro.Z, buf);
    UART_send_string("Gyro.Z = ");
    UART_send_string(buf);
    UART_send_string("\n");
    
    int2str(TestRun->Temperature, buf);
    UART_send_string("Temperature = ");
    UART_send_string(buf);
    UART_send_string("\n");
    UART_send_string("/**********************/ \n\n");

    __delay_ms(1000);
}
=======
>>>>>>> parent of 9a4dca4... Int2Str Coversion
