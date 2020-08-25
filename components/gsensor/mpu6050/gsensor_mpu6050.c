#include "stm32f4xx_conf.h"
#include "gsensor_mpu6050.h"
#include "delay.h"

void GSensor_MPU6050_IO_Configure(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    I2C_InitTypeDef   I2C_InitStructure;
    RCC_ClocksTypeDef rcc_clocks;

    /* GPIO Peripheral clock enable */
}

void GSensor_MPU6050_Init(void)
{

}
