#include "stm32f4xx_conf.h"
#include "lcd_st7735s.h"

/*******************************************************************************
* Function Name  : SPI1_ReadWriteByte
* Description    : Send Data and Read Data from SPI1.
* Input          : None
* Output         : None
* Return         : Read Value
*******************************************************************************/
uint8_t SPI1_ReadWriteByte(uint8_t data)
{
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_TXE) == RESET);
    SPI_I2S_SendData(SPI1, data);
    while (SPI_I2S_GetFlagStatus(SPI1, SPI_I2S_FLAG_RXNE) == RESET);
    return SPI_I2S_ReceiveData(SPI1);
}

/*******************************************************************************
* Function Name  : LCD_ST7735S_SPI_Configure
* Description    : Configure the SPI for ST7735S.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void LCD_ST7735S_SPI_Configure(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    SPI_InitTypeDef  SPI_InitStructure;
    
    // Enable GPIOA and SPI 1 Clock
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1,  ENABLE);

    // Configure PA5/PA6/PA7 as SPI_1 SCK/MISO/MOSI
    GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_5 | GPIO_Pin_6 | GPIO_Pin_7;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    // Pinmux Configurations
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource5, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_SPI1);
    GPIO_PinAFConfig(GPIOA, GPIO_PinSource7, GPIO_AF_SPI1);

    // Reset SPI_1
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, ENABLE);
    RCC_APB2PeriphResetCmd(RCC_APB2Periph_SPI1, DISABLE);

    // Configure SPI
    SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
    SPI_InitStructure.SPI_Mode      = SPI_Mode_Master;
    SPI_InitStructure.SPI_DataSize  = SPI_DataSize_8b;
    SPI_InitStructure.SPI_CPOL      = SPI_CPOL_Low;
    SPI_InitStructure.SPI_CPHA      = SPI_CPHA_1Edge;
    SPI_InitStructure.SPI_NSS       = SPI_NSS_Soft;
    // SYSCLK=>168MHz, AHB=>168MHz, PCLK2=>84MHz, PCLK1=>42MHz;
    // SPI_BaudRatePrescaler_2 =>  SPI1 CLK = 42MHz
    // SPI_BaudRatePrescaler_4 =>  SPI1 CLK = 21MHz
    // SPI_BaudRatePrescaler_8 =>  SPI1 CLK = 10.5MHz
    // SPI_BaudRatePrescaler_16 => SPI1 CLK = 5.25MHz
    // SPI_BaudRatePrescaler_32 => SPI1 CLK = 2.125MHz
    SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_16;//SPI_BaudRatePrescaler_256; // SPI_BaudRatePrescaler_4=>21MHz
    SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
    SPI_InitStructure.SPI_CRCPolynomial = 7;
    SPI_Init(SPI1, &SPI_InitStructure);

    SPI_Cmd(SPI1, ENABLE);
}

/*******************************************************************************
* Function Name  : LCD_ST7735S_CS_Configure
* Description    : Configure the CS for ST7735S.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void LCD_ST7735S_CS_Configure(void)
{
    // Configure PA1 as CS
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : LCD_ST7735S_BL_Configure
* Description    : Configure the Black Light for ST7735S.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void LCD_ST7735S_BL_Configure(void)
{
    // Configure PA2 as Black Light
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : LCD_ST7735S_RST_Configure
* Description    : Configure the Reset for ST7735S.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void LCD_ST7735S_RST_Configure(void)
{
    // Configure PA3 as Reset
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : LCD_ST7735S_CTRL_Configure
* Description    : Configure the DATA/CMD IO for ST7735S.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
static void LCD_ST7735S_CTRL_Configure(void)
{
    // Configure PA4 as Control Line
    GPIO_InitTypeDef GPIO_InitStructure;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

    GPIO_InitStructure.GPIO_Pin     = GPIO_Pin_4;
    GPIO_InitStructure.GPIO_Mode    = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType   = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_Speed   = GPIO_Speed_100MHz;
    GPIO_InitStructure.GPIO_PuPd    = GPIO_PuPd_UP;

    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/*******************************************************************************
* Function Name  : LCD_ST7735S_IO_Configure
* Description    : Configure the I/O ports for ST7735S.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_ST7735S_IO_Configure(void)
{
    LCD_ST7735S_SPI_Configure();
    LCD_ST7735S_CS_Configure();
    LCD_ST7735S_BL_Configure();
    LCD_ST7735S_RST_Configure();
    LCD_ST7735S_CTRL_Configure();
}
/*******************************************************************************
* Function Name  : LCD_ST7735S_Init
* Description    : Configure the I/O port for SPI1.
* Input          : None
* Output         : None
* Return         : None
*******************************************************************************/
void LCD_ST7735S_Init(void)
{
    LCD_ST7735S_IO_Configure();
}
