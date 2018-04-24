#include "MPU6050.h"

<<<<<<< HEAD
#define DEVICE 0

=======
>>>>>>> parent of 9a4dca4... Int2Str Coversion
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

int MPU6050_Read()
{
 MPU6050 Sensor;
 I2C_Master_Start();
 I2C_Master_Write( MPU6050_ADDRESS );
 I2C_Master_Write( MPU6050_RA_ACCEL_XOUT_H );
 I2C_Master_Restart();
 I2C_Master_Write( MPU6050_ADDRESS | 1 );
<<<<<<< HEAD
 uint16_t value_high;
 uint8_t value_low;
 
 value_high = (I2C_Master_Read(DEVICE) << 8);
 value_low = I2C_Master_Read(DEVICE); 
 Sensor->Accel.X = value_high | value_low ;
 
 value_high = (I2C_Master_Read(DEVICE) << 8);
 value_low = I2C_Master_Read(DEVICE);
 Sensor->Accel.Y = value_high | value_low;
 
 value_high = (I2C_Master_Read(DEVICE) << 8);
 value_low = I2C_Master_Read(DEVICE);
 Sensor->Accel.Z = value_high | value_low;
 
 value_high = (I2C_Master_Read(DEVICE) << 8);
 value_low = I2C_Master_Read(DEVICE);
 Sensor->Temperature = value_high | value_low;
 
 value_high = (I2C_Master_Read(DEVICE) << 8);
 value_low = I2C_Master_Read(DEVICE);
 Sensor->Gyro.X = value_high | value_low;
 
 value_high = (I2C_Master_Read(DEVICE) << 8);
 value_low = I2C_Master_Read(DEVICE);
 Sensor->Gyro.Y = value_high | value_low;
 
 value_high = (I2C_Master_Read(DEVICE) << 8);
 value_low = I2C_Master_Read(DEVICE);
 Sensor->Gyro.Z = value_high | value_low;
 
 I2C_Master_Stop();
 Sensor->Temperature += 12421;
 Sensor->Temperature /= 340;
}
=======
 Sensor.Accel.X = ( I2C_Master_Read() << 8 ) | I2C_Master_Read();
 Sensor.Accel.Y = ( I2C_Master_Read() << 8 ) | I2C_Master_Read();
 Sensor.Accel.Z = ( I2C_Master_Read() << 8 ) | I2C_Master_Read();
 Sensor.Temperature = ( I2C_Master_Read() << 8 ) | I2C_Master_Read();
 Sensor.Gyro.X = ( I2C_Master_Read() << 8 ) | I2C_Master_Read();
 Sensor.Gyro.Y = ( I2C_Master_Read() << 8 ) |I2C_Master_Read();
 Sensor.Gyro.Z = ( I2C_Master_Read() << 8 ) | I2C_Master_Read();
 I2C_Master_Stop();
 Sensor.Temperature += 12421;
 Sensor.Temperature /= 340;
 return Sensor.Gyro.X;
}
>>>>>>> parent of 9a4dca4... Int2Str Coversion
