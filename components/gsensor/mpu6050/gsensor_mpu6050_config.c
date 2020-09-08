/*******************************************************************************
* File Name      : gsensor_mpu6050_config.c
* Description    : Init the basic configure of MPU6050.
* Author         : StephenZhou
* Date           : 2020.8.26
*******************************************************************************/
#include "gsensor_mpu6050_config.h"
#include "gsensor_mpu6050_reg.h"
#include "gsensor_mpu6050_driver.h"
#include "delay.h"

uint32_t ulTimeOut_Time = 0;

static void GSensor_MPU6050_IO_Configure(void)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    I2C_InitTypeDef   I2C_InitStructure;
    RCC_ClocksTypeDef rcc_clocks;

    /* GPIO B Peripheral clock enable */
    RCC_AHB1PeriphClockCmd(MPU6050_I2C_IO_RCC, ENABLE);
    RCC_APB1PeriphClockCmd(MPU6050_I2C_RCC,  ENABLE);

    // Configure PB10: I2C2_SCL  PB11: I2C2_SDA
    GPIO_InitStructure.GPIO_Pin   = MPU6050_I2C_SCL_PIN | MPU6050_I2C_SDA_PIN;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIO_Init(MPU6050_I2C_IO_BANK, &GPIO_InitStructure);

    // Pinmux Configurations
    GPIO_PinAFConfig(MPU6050_I2C_IO_BANK, MPU6050_I2C_AF_SCL_PIN_SRC, MPU6050_I2C_AF);
    GPIO_PinAFConfig(MPU6050_I2C_IO_BANK, MPU6050_I2C_AF_SDA_PIN_SRC, MPU6050_I2C_AF);

    /* Reset I2C 2 IP */
    RCC_APB1PeriphResetCmd(MPU6050_I2C_RCC, ENABLE);
    RCC_APB1PeriphResetCmd(MPU6050_I2C_RCC, DISABLE);

    // Configure I2C_1
    I2C_InitStructure.I2C_Mode          = I2C_Mode_I2C;
    I2C_InitStructure.I2C_DutyCycle     = I2C_DutyCycle_2;
    I2C_InitStructure.I2C_OwnAddress1   = 0x00;
    I2C_InitStructure.I2C_Ack           = I2C_Ack_Enable;
    I2C_InitStructure.I2C_ClockSpeed    = MPU6050_FREQ;
    I2C_InitStructure.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C_Init(MPU6050_I2C, &I2C_InitStructure);

    // I2C Enable
    I2C_Cmd(MPU6050_I2C, ENABLE);

    // Timeout Logic
    RCC_GetClocksFreq(&rcc_clocks);
    ulTimeOut_Time = (rcc_clocks.SYSCLK_Frequency /10000);
}

void GSensor_MPU6050_FeatureConfigure(void)
{
    MPU6050_DRV_WriteReg(PWR_MGMT_1_REG, 0x80); // Reset MPU6050
    delay_ms(200);
    MPU6050_DRV_WriteReg(PWR_MGMT_1_REG, 0x00); // Wake up device
    delay_ms(200);
    MPU6050_DRV_WriteReg(SMPLRT_DIV_REG, 0x07);
    MPU6050_DRV_WriteReg(CONFIG_REG, 0x06);
    MPU6050_DRV_WriteReg(GYRO_CONFIG_REG, 0x18);
    MPU6050_DRV_WriteReg(ACCEL_CONFIG_REG, 0x01);
}

void GSensor_MPU6050_Init(void)
{
    GSensor_MPU6050_IO_Configure();
    GSensor_MPU6050_FeatureConfigure();
}
