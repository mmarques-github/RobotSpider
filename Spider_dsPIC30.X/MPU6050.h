


#ifndef MPU6050_H
#define	MPU6050_H

#include <xc.h>
#include "i2c.h"
#include "MPU6050_Reg_Values.h"
#include <stdint.h>

typedef struct
{
 struct
 {
  int16_t X;
  int16_t Y;
  int16_t Z;
 }Accel;
 int16_t Temperature;
 struct
 {
  int16_t X;
  int16_t Y;
  int16_t Z;
 }Gyro;
}MPU6050;

void MPU6050_Init();

void MPU6050_Read(MPU6050* );
#endif	/*MPU6050_H*/