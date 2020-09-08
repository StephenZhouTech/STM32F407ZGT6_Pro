/*******************************************************************************
* File Name      : gsensor_mpu6050_driver.c
* Description    : Basic driver of MPU6050.
* Author         : StephenZhou
* Date           : 2020.9.1
*******************************************************************************/
#include "stm32f4xx_conf.h"
#include "gsensor_mpu6050_driver.h"
#include "gsensor_mpu6050_config.h"

#define I2C_TIMEOUT_CHECK(timeout, err)     \
{                                           \
    if(!timeout)                            \
    {                                       \
        error_code = err;                   \
        break;                              \
    }                                       \
}

/*******************************************************************************
***** GLOBAL VARIABLE
*******************************************************************************/
extern uint32_t ulTimeOut_Time;

/*******************************************************************************
* Function Name  : I2C_ReadOneByte
* Description    : Read one byte by using I2C interface.
* Input          :
* @param I2Cx    : I2C descriptor
* @param I2C_Addr: I2C device address
* @param Reg_addr: The device register address which will be read
* @param p_data  : Read data result from register
* Output         : The data read from register
* Return         : If success return MPU6050_NO_ERROR
*******************************************************************************/
static uint8_t I2C_ReadOneByte( I2C_TypeDef *I2Cx,
                                uint8_t I2C_Addr,
                                uint8_t Reg_addr,
                                uint8_t *p_data)
{
    MPU_6050_err_e error_code = MPU6050_NO_ERROR; 
    uint32_t timeout = 0;

    do {
        // Wait I2C DEVICE not in busy
        timeout = ulTimeOut_Time;
        while((--timeout)&&I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
        I2C_TIMEOUT_CHECK(timeout, I2C_DEVICE_BUSY);

        // Generate START Bit
        timeout = ulTimeOut_Time;
        I2C_GenerateSTART(I2Cx, ENABLE);
        while((--timeout)&&(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)));
        I2C_TIMEOUT_CHECK(timeout, I2C_GEN_START_FAILED);

        // Send Address as Master Tx mode
        timeout = ulTimeOut_Time;
        I2C_Send7bitAddress(I2Cx, I2C_Addr, I2C_Direction_Transmitter);
        while((--timeout)&&(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)));
        I2C_TIMEOUT_CHECK(timeout, I2C_SEND_ADDR_TX_FAILED);

        I2C_Cmd(I2Cx, ENABLE);

        // Send Register address
        timeout = ulTimeOut_Time;
        I2C_SendData(I2Cx, Reg_addr);
        while((--timeout)&&(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)));
        I2C_TIMEOUT_CHECK(timeout, I2C_SEND_DATA_FAILED);

        // Re-Generate start bit
        I2C_GenerateSTART(I2Cx, ENABLE);
        timeout = ulTimeOut_Time;
        while((--timeout)&&(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)));
        I2C_TIMEOUT_CHECK(timeout, I2C_GEN_START_FAILED);

        // Send Address as Master RX mode
        timeout = ulTimeOut_Time;
        I2C_Send7bitAddress(I2Cx, I2C_Addr, I2C_Direction_Receiver);
        while((--timeout)&&(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)));
        I2C_TIMEOUT_CHECK(timeout, I2C_SEND_ADDR_RX_FAILED);

        // Generate NACK
        I2C_AcknowledgeConfig(I2Cx, DISABLE);
        // Generate STOP Bit
        I2C_GenerateSTOP(I2Cx, ENABLE);

        timeout = ulTimeOut_Time;
        while((--timeout)&&(!(I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))));  /* EV7 */
        I2C_TIMEOUT_CHECK(timeout, I2C_RECV_DATA_FAILED);

        *p_data = I2C_ReceiveData(I2Cx);

        I2C_AcknowledgeConfig(I2Cx, ENABLE);

    } while(0);

    return error_code;
}

/*******************************************************************************
* Function Name   : I2C_ReadBurst
* Description     : Read bytes by using I2C interface.
* Input           :
* @param I2Cx     : I2C descriptor
* @param I2C_Addr : I2C device address
* @param Reg_addr : The device register address which will be read
* @param p_data   : Read data result from register
* @param burst_len: Read data size, unit in byte
* Output          : The data read from register
* Return          : If success return MPU6050_NO_ERROR
*******************************************************************************/
static uint8_t I2C_ReadBurst( I2C_TypeDef *I2Cx,
                                uint8_t I2C_Addr,
                                uint8_t Reg_addr,
                                void *p_data,
                                uint32_t burst_len )
{
    MPU_6050_err_e error_code = MPU6050_NO_ERROR; 
    uint32_t timeout = 0;
    uint8_t *pBuffer = (uint8_t *)p_data;
    uint32_t len = burst_len;

    do {
        // Wait I2C DEVICE not in busy
        timeout = ulTimeOut_Time;
        while((--timeout)&&I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
        I2C_TIMEOUT_CHECK(timeout, I2C_DEVICE_BUSY);

        // Generate START Bit
        timeout = ulTimeOut_Time;
        I2C_GenerateSTART(I2Cx, ENABLE);
        while((--timeout)&&(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)));
        I2C_TIMEOUT_CHECK(timeout, I2C_GEN_START_FAILED);

        // Send Address as Master Tx mode
        timeout = ulTimeOut_Time;
        I2C_Send7bitAddress(I2Cx, I2C_Addr, I2C_Direction_Transmitter);
        while((--timeout)&&(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)));
        I2C_TIMEOUT_CHECK(timeout, I2C_SEND_ADDR_TX_FAILED);

        I2C_Cmd(I2Cx, ENABLE);

        // Send Register address
        timeout = ulTimeOut_Time;
        I2C_SendData(I2Cx, Reg_addr);
        while((--timeout)&&(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)));
        I2C_TIMEOUT_CHECK(timeout, I2C_SEND_DATA_FAILED);

        // Re-Generate start bit
        I2C_GenerateSTART(I2Cx, ENABLE);
        timeout = ulTimeOut_Time;
        while((--timeout)&&(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)));
        I2C_TIMEOUT_CHECK(timeout, I2C_GEN_START_FAILED);

        // Send Address as Master RX mode
        timeout = ulTimeOut_Time;
        I2C_Send7bitAddress(I2Cx, I2C_Addr, I2C_Direction_Receiver);
        while((--timeout)&&(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)));
        I2C_TIMEOUT_CHECK(timeout, I2C_SEND_ADDR_RX_FAILED);

        while(len)
        {
            if (len == 1)
            {
                // Generate NACK
                I2C_AcknowledgeConfig(I2Cx, DISABLE);
                // Generate STOP Bit
                I2C_GenerateSTOP(I2Cx, ENABLE);
            }
            timeout = ulTimeOut_Time;
            while((--timeout)&&(!(I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_RECEIVED))));  /* EV7 */
            I2C_TIMEOUT_CHECK(timeout, I2C_RECV_DATA_FAILED);
            *pBuffer = I2C_ReceiveData(I2Cx);
            pBuffer++;
            len--;
        }

        I2C_AcknowledgeConfig(I2Cx, ENABLE);

    } while(0);

    return error_code;
}

/*******************************************************************************
* Function Name  : I2C_WriteOneByte
* Description    : Send one byte by using I2C interface.
* Input          :
* @param I2Cx    : I2C descriptor
* @param I2C_Addr: I2C device address
* @param Reg_addr: The device register address
* @param data    : Write data to register
* Output         : None
* Return         : If success return MPU6050_NO_ERROR
*******************************************************************************/
static uint8_t I2C_WriteOneByte( I2C_TypeDef *I2Cx,
                                 uint8_t I2C_Addr,
                                 uint8_t Reg_addr,
                                 uint8_t data)
{
    MPU_6050_err_e error_code = MPU6050_NO_ERROR; 
    uint32_t timeout = 0;

    do {
        // Wait I2C DEVICE not in busy
        timeout = ulTimeOut_Time;
        while((--timeout)&&I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY));
        I2C_TIMEOUT_CHECK(timeout, I2C_DEVICE_BUSY);

        // Generate START Bit
        timeout = ulTimeOut_Time;
        I2C_GenerateSTART(I2Cx, ENABLE);
        while((--timeout)&&(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_MODE_SELECT)));
        I2C_TIMEOUT_CHECK(timeout, I2C_GEN_START_FAILED);

        // Send Address as Master Tx mode
        timeout = ulTimeOut_Time;
        I2C_Send7bitAddress(I2Cx, I2C_Addr, I2C_Direction_Transmitter);
        while((--timeout)&&(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)));
        I2C_TIMEOUT_CHECK(timeout, I2C_SEND_ADDR_TX_FAILED);

        // Send Register address
        timeout = ulTimeOut_Time;
        I2C_SendData(I2Cx, Reg_addr);
        while((--timeout)&&(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)));
        I2C_TIMEOUT_CHECK(timeout, I2C_SEND_DATA_FAILED);

        // Send Data to Register
        timeout = ulTimeOut_Time;
        I2C_SendData(I2Cx, data);
        while((--timeout)&&(!I2C_CheckEvent(I2Cx, I2C_EVENT_MASTER_BYTE_TRANSMITTED)));
        I2C_TIMEOUT_CHECK(timeout, I2C_SEND_DATA_FAILED);

        // Generate STOP Bit
        I2C_GenerateSTOP(I2Cx, ENABLE);

    } while(0);
}

uint8_t MPU6050_DRV_WriteReg(uint8_t RegAddr, uint8_t RegValue)
{
    return I2C_WriteOneByte(MPU6050_I2C, MPU6050_I2C_DEVICE_ADDR, RegAddr, RegValue);
}

uint8_t MPU6050_DRV_ReadReg(uint8_t RegAddr, uint8_t *RegValue)
{
    return I2C_ReadOneByte(MPU6050_I2C, MPU6050_I2C_DEVICE_ADDR, RegAddr, RegValue);
}

uint8_t MPU6050_DRV_ReadRegBurst(uint8_t RegAddr, uint8_t *RegValue, uint32_t RegLen)
{
    return I2C_ReadBurst(MPU6050_I2C, MPU6050_I2C_DEVICE_ADDR, RegAddr, RegValue, RegLen);
}
