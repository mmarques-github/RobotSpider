/* Author: Marcelo
 *
 * Created on March 21, 2018, 3:03 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include "adc.h"
#include "MPU6050.h"
#include <xc.h>

#define WIDTH   240
#define LENGTH  320
#define DEVICE  1
#define CAM     0
_FOSC(CSW_FSCM_OFF & FRC & XT_PLL16);
#define _XTAL_FREQ 120000000L

//int strlen(char[]);


void MPU6050_DeviceDriverTest();
int main(void){
    
    /*Setting up the ports*/
    
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
        if(0){
            I2C_Master_Start();
            I2C_Master_Write( MPU6050_ADDRESS );
            I2C_Master_Write( MPU6050_RA_GYRO_CONFIG );
            I2C_Master_Write( 0 ); //gyro_config, +-250 °/s
            I2C_Master_Write( 0 ); //accel_config +-2g
            I2C_Master_Stop();
            __delay_ms(1000);

        UART_send_string("config over... \n");
        }
        if(1){
            MPU6050_DeviceDriverTest();
        }
    }
    return 0;
}

void MPU6050_DeviceDriverTest(){
    MPU6050 *TestRun;
    MPU6050_Read(&TestRun);
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



/* strlen: return length of s */
//int strlen(char s[])
//{
//    int i = 0;
//    while (s[i] != '\0')
//        ++i;
//    return i;
//}