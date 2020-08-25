#include "stm32f4xx.h"
#include "delay.h"
#include "log.h"
#include "led.h"

#define UART_DEBUG      1
#define USE_LED         1

int main(void)
{
    uint32_t counter = 0;

#if UART_DEBUG
    LogInit();
#endif

#if USE_LED
    BspLedInit();
#endif

    delay_init(168);

    LOG_DEBUG("**********************************************************");
    LOG_DEBUG("**************** MPU6050 Project Running *****************");
    LOG_DEBUG("**********************************************************");

    while(1)
    {
        LOG_DEBUG("System Running Counter:%d",counter++);
        delay_ms(100);
        BspLEDOn(LED_2 | LED_3 | LED_4);
        delay_ms(100);
        BspLEDOff(LED_2 | LED_3 | LED_4);
    }
}
