#ifndef __GSENSOR_MPU6050_DRIVER_H__
#define __GSENSOR_MPU6050_DRIVER_H__

#define AD0_CONNECT_WITH_GND        0x68 // AD0 -> GND
#define AD0_CONNECT_WITH_VCC        0x69 // AD0 -> VCC

#define MPU6050_I2C_DEVICE_ADDR     AD0_CONNECT_WITH_GND

typedef enum _MPU_6050_ERROR_CODE
{
    MPU6050_NO_ERROR = 0,
    I2C_DEVICE_BUSY,
    I2C_GEN_START_FAILED,
    I2C_SEND_ADDR_TX_FAILED,
    I2C_SEND_DATA_FAILED,
    I2C_SEND_ADDR_RX_FAILED,
    I2C_RECV_DATA_FAILED,
} MPU_6050_err_e;

uint8_t MPU6050_DRV_WriteReg(uint8_t RegAddr, uint8_t RegValue);
uint8_t MPU6050_DRV_ReadReg(uint8_t RegAddr, uint8_t *RegValue);
uint8_t MPU6050_DRV_ReadRegBurst(uint8_t RegAddr, uint8_t *RegValue, uint32_t RegLen);

#endif // __GSENSOR_MPU6050_DRIVER_H__