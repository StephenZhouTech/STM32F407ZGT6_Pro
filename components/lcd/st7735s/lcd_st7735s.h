#ifndef __LCD_ST7735S_H__
#define __LCD_ST7735S_H__

#include <stdint.h>
#include "stm32f4xx.h"

void LCD_ST7735S_Init(void);
uint8_t SPI1_ReadWriteByte(uint8_t data);

// CS => PA1
#define LCD_CS_LOW()   GPIO_ResetBits(GPIOA,GPIO_Pin_1)
#define LCD_CS_HIGH()  GPIO_SetBits(GPIOA,GPIO_Pin_1)

// BL => PA2
#define LCD_BLK_LOW()  GPIO_ResetBits(GPIOA,GPIO_Pin_2)
#define LCD_BLK_HIGH() GPIO_SetBits(GPIOA,GPIO_Pin_2)

// BL => PA3
#define LCD_RST_LOW()  GPIO_ResetBits(GPIOA,GPIO_Pin_3)
#define LCD_RST_HIGH() GPIO_SetBits(GPIOA,GPIO_Pin_3)

// BL => PA4
#define LCD_CTR_LOW()   GPIO_ResetBits(GPIOA,GPIO_Pin_4)
#define LCD_CTR_HIGH()  GPIO_SetBits(GPIOA,GPIO_Pin_4)

#endif //__LCD_ST7735S_H__
