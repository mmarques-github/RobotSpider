


#ifndef MPU6050_H
#define	MPU6050_H

#include <xc.h>
#include "i2c.h"
#include "MPU6050_Reg_Values.h"

typedef struct
{
 struct
 {
  signed int X;
  signed int Y;
  signed int Z;
 }Accel;
 signed int Temperature;
 struct
 {
  signed int X;
  signed int Y;
  signed int Z;
 }Gyro;
}MPU6050;

void MPU6050_Init();

<<<<<<< HEAD
void MPU6050_Read(MPU6050* );
=======
int MPU6050_Read();


>>>>>>> parent of 9a4dca4... Int2Str Coversion
#endif	/*MPU6050_H*/