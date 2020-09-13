#include "stm32f4xx.h"
#include "delay.h"
#include "log.h"
#include "led.h"
#include "gsensor_mpu6050_api.h"

int main(void)
{
    uint32_t counter = 0;

    LogInit();
    BspLedInit();
    delay_init(168);
    GSensor_MPU6050_Init();

    LOG_DEBUG("**********************************************************");
    LOG_DEBUG("**************** MPU6050 Project Running *****************");
    LOG_DEBUG("**********************************************************");

    uint16_t A_data_x = 0;
    uint16_t A_data_y = 0;
    uint16_t A_data_z = 0;

    uint16_t G_data_x = 0;
    uint16_t G_data_y = 0;
    uint16_t G_data_z = 0;
    while(1)
    {
        //LOG_DEBUG("System Running Counter:%d",counter++);
        //delay_ms(200);
        {
            MPU_Get_Accelerometer(&A_data_x,&A_data_y,&A_data_z);
            MPU_Get_Gyroscope(&G_data_x,&G_data_y,&G_data_z);
            LOG_DEBUG("A_data_x:%d, A_data_y=%d, A_data_z=%d",A_data_x, A_data_y, A_data_z);
            LOG_DEBUG("G_data_x:%d, G_data_y=%d, G_data_z=%d",G_data_x, G_data_y, G_data_z);
        }
        BspLEDOn(LED_2 | LED_3 | LED_4);
        delay_ms(200);
        BspLEDOff(LED_2 | LED_3 | LED_4);
    }
}
