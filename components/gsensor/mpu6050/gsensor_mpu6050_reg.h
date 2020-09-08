#ifndef __GSENSOR_MPU6050_REG_H__
#define __GSENSOR_MPU6050_REG_H__

#define SELF_TEST_X_REG                 0x0D
#define SELF_TEST_Y_REG                 0x0E
#define SELF_TEST_Z_REG                 0x0F
#define SELF_TEST_A_REG                 0x10

#define SMPLRT_DIV_REG                  0x19
#define CONFIG_REG                      0x1A
#define GYRO_CONFIG_REG                 0x1B
#define ACCEL_CONFIG_REG                0x1C

#define I2C_MST_CTRL_REG                0x24

#define INT_PIN_CFG_REG                 0x37
#define INT_ENABLE_REG                  0x38
#define INT_STATUS_REG                  0x3A

#define ACCEL_XOUT_H_REG                0x3B 
#define ACCEL_XOUT_L_REG                0x3C 
#define ACCEL_YOUT_H_REG                0x3D 
#define ACCEL_YOUT_L_REG                0x3E 
#define ACCEL_ZOUT_H_REG                0x3F 
#define ACCEL_ZOUT_L_REG                0x40 

#define TEMP_OUT_H_REG                  0x41 
#define TEMP_OUT_L_REG                  0x42 

#define GYRO_XOUT_H_REG                 0x43
#define GYRO_XOUT_L_REG                 0x44 
#define GYRO_YOUT_H_REG                 0x45 
#define GYRO_YOUT_L_REG                 0x46 
#define GYRO_ZOUT_H_REG                 0x47 
#define GYRO_ZOUT_L_REG                 0x48 

#define PWR_MGMT_1_REG                  0x6B
#define PWR_MGMT_2_REG                  0x6C

#define WHO_AM_I_REG                    0x75
#endif // __GSENSOR_MPU6050_REG_H__