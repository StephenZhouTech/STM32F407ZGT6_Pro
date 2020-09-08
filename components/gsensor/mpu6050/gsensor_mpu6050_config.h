#ifndef __GSENSOR_MPU6050_CONFIG_H__
#define __GSENSOR_MPU6050_CONFIG_H__

#include "stm32f4xx_conf.h"

#define MPU6050_I2C_IO_RCC          RCC_AHB1Periph_GPIOB
#define MPU6050_I2C_IO_BANK         GPIOB
#define MPU6050_I2C_RCC             RCC_APB1Periph_I2C2
#define MPU6050_I2C_SCL_PIN         GPIO_Pin_10
#define MPU6050_I2C_SDA_PIN         GPIO_Pin_11
#define MPU6050_I2C_AF              GPIO_AF_I2C2
#define MPU6050_I2C_AF_SCL_PIN_SRC  GPIO_PinSource10
#define MPU6050_I2C_AF_SDA_PIN_SRC  GPIO_PinSource11
#define MPU6050_I2C_AF              GPIO_AF_I2C2
#define MPU6050_I2C                 I2C2
#define MPU6050_FREQ                100000

void GSensor_MPU6050_Init(void);

#endif // __GSENSOR_MPU6050_CONFIG_H__