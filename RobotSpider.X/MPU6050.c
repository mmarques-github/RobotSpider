#include "MPU6050.h"

#define DEVICE 1

void MPU6050_Init()
{
 I2C_Master_Start();
 I2C_Master_Write( MPU6050_ADDRESS );
 I2C_Master_Write( MPU6050_RA_PWR_MGMT_1 );
 I2C_Master_Write( 2 ); //Sleep OFF
 I2C_Master_Write( 0 ); 
 I2C_Master_Stop();
 
 I2C_Master_Start();
 I2C_Master_Write( MPU6050_ADDRESS );
 I2C_Master_Write( MPU6050_RA_GYRO_CONFIG );
 I2C_Master_Write( 0 ); //gyro_config, +-250 °/s
 I2C_Master_Write( 0 ); //accel_config +-2g
 I2C_Master_Stop();
}

void MPU6050_Read(MPU6050 *Sensor)
{
 I2C_Master_Start();
 I2C_Master_Write( MPU6050_ADDRESS );
 I2C_Master_Write( MPU6050_RA_ACCEL_XOUT_H );
 I2C_Master_Start();
 I2C_Master_Write( MPU6050_ADDRESS | 1 );
 //Sensor->Accel.X = ( I2C_Master_Read(DEVICE) << 8 ) | I2C_Master_Read(DEVICE);
 Sensor->Accel.X = ( I2C_Master_Read(DEVICE) << 8 );
 I2C_Master_Read(DEVICE);
 Sensor->Accel.Y = ( I2C_Master_Read(DEVICE) << 8 ) | I2C_Master_Read(DEVICE);
 Sensor->Accel.Z = ( I2C_Master_Read(DEVICE) << 8 ) | I2C_Master_Read(DEVICE);
 Sensor->Temperature = ( I2C_Master_Read(DEVICE) << 8 ) | I2C_Master_Read(DEVICE);
 Sensor->Gyro.X = ( I2C_Master_Read(DEVICE)<<8) | I2C_Master_Read(DEVICE);
 Sensor->Gyro.Y = ( I2C_Master_Read(DEVICE) << 8 ) |I2C_Master_Read(DEVICE);
 Sensor->Gyro.Z = ( I2C_Master_Read(DEVICE) << 8 ) | I2C_Master_Read(DEVICE);
 I2C_Master_Stop();
 Sensor->Temperature += 12421;
 Sensor->Temperature /= 340;
 
}
