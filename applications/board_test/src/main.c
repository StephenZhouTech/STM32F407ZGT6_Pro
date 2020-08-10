#include "stm32f4xx.h"
#include "delay.h"
#include "log.h"
#include "led.h"
#include "lcd_st7735s.h"

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
    LOG_DEBUG("************** Board Test Project Running ****************");
    LOG_DEBUG("**********************************************************");

    LCD_ST7735S_Init();
    SPI1_ReadWriteByte(0x01);
    SPI1_ReadWriteByte(0x02);
    SPI1_ReadWriteByte(0x03);
    SPI1_ReadWriteByte(0x04);
    SPI1_ReadWriteByte(0x05);
    SPI1_ReadWriteByte(0x06);
    SPI1_ReadWriteByte(0x07);
    SPI1_ReadWriteByte(0x08);
    SPI1_ReadWriteByte(0x09);
    SPI1_ReadWriteByte(0x0A);
    SPI1_ReadWriteByte(0x0B);
    SPI1_ReadWriteByte(0x0C);
    SPI1_ReadWriteByte(0x0D);
    SPI1_ReadWriteByte(0x0E);
    SPI1_ReadWriteByte(0x0F);

    while(1)
    {
        LOG_DEBUG("counter:%d",counter++);
        LCD_CS_LOW();
        LCD_BLK_LOW();
        LCD_RST_LOW();
        LCD_CTR_LOW();
        delay_ms(100);
        LCD_CS_HIGH();
        LCD_BLK_HIGH();
        LCD_RST_HIGH();
        LCD_CTR_HIGH();
        BspLEDOn(LED_2 | LED_3 | LED_4);
        delay_ms(100);
        BspLEDOff(LED_2 | LED_3 | LED_4);
    }
}
