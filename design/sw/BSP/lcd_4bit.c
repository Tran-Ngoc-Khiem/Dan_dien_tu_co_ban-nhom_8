#include "lcd_4bit.h"
#include <stdio.h> // Ð? dùng sprintf

// Khai báo bi?n toàn c?c c?n thi?t cho LCD_Display
extern uint8_t mode;
extern uint8_t song;

/*--- Khai báo/Ð?nh nghia hàm t? code g?c ---*/
void LCD_Display(void)
{
    // ... N?I DUNG HÀM LCD_Display G?C ...
    char line1[16];
    char line2[16];

    LCD_Clear();

    // Dòng 1: tên ch? d?
    switch (mode)
    {
        case 1: sprintf(line1, "Mode: Choi nhac"); break;
        case 2: sprintf(line1, "Mode: Ghi am"); break;
        case 3: sprintf(line1, "Mode: Phat nhac"); break;
    }
    LCD_GotoXY(0, 0);
    LCD_Puts(line1);

	
	switch (mode)
    {
        case 1: sprintf(line2, " "); break;
        case 2: sprintf(line2, "Bai: %d", song); break;
        case 3: sprintf(line2, "Bai: %d", song); break;
    }
    LCD_GotoXY(1, 0);
    LCD_Puts(line2);
}

void LCD_Send4Bits(uint8_t data)
{
    // ... N?I DUNG HÀM LCD_Send4Bits G?C ...
    HAL_GPIO_WritePin(GPIOB, LCD_D4_Pin, (data >> 0) & 0x01);
    HAL_GPIO_WritePin(GPIOB, LCD_D5_Pin, (data >> 1) & 0x01);
    HAL_GPIO_WritePin(GPIOB, LCD_D6_Pin, (data >> 2) & 0x01);
    HAL_GPIO_WritePin(GPIOB, LCD_D7_Pin, (data >> 3) & 0x01);
}

void LCD_Enable(void)
{
    // ... N?I DUNG HÀM LCD_Enable G?C ...
    HAL_GPIO_WritePin(GPIOB, LCD_E_Pin, GPIO_PIN_SET);
    HAL_Delay(1);
    HAL_GPIO_WritePin(GPIOB, LCD_E_Pin, GPIO_PIN_RESET);
    HAL_Delay(1);
}

void LCD_Command(uint8_t cmd)
{
    // ... N?I DUNG HÀM LCD_Command G?C ...
    HAL_GPIO_WritePin(GPIOB, LCD_RS_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOB, LCD_RW_Pin, GPIO_PIN_RESET);
    LCD_Send4Bits(cmd >> 4);
    LCD_Enable();
    LCD_Send4Bits(cmd & 0x0F);
    LCD_Enable();
    HAL_Delay(2);
}

void LCD_Data(uint8_t data)
{
    // ... N?I DUNG HÀM LCD_Data G?C ...
    HAL_GPIO_WritePin(GPIOB, LCD_RS_Pin, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOB, LCD_RW_Pin, GPIO_PIN_RESET);
    LCD_Send4Bits(data >> 4);
    LCD_Enable();
    LCD_Send4Bits(data & 0x0F);
    LCD_Enable();
    HAL_Delay(2);
}

void LCD_Init(void)
{
    // ... N?I DUNG HÀM LCD_Init G?C ...
    HAL_Delay(50);
    LCD_Send4Bits(0x03);
    LCD_Enable();
    HAL_Delay(5);
    LCD_Send4Bits(0x02);
    LCD_Enable();

    LCD_Command(0x28); // 4-bit, 2 d ng, font 5x8
    LCD_Command(0x0C); // B?t hi?n th?, t?t con tr?
    LCD_Command(0x06); // T? tang con tr?
    LCD_Command(0x01); // X a m n h nh
    HAL_Delay(5);
}

void LCD_Clear(void)
{
    // ... N?I DUNG HÀM LCD_Clear G?C ...
    LCD_Command(0x01);
    HAL_Delay(2);
}

void LCD_GotoXY(uint8_t row, uint8_t col)
{
    // ... N?I DUNG HÀM LCD_GotoXY G?C ...
    uint8_t address = (row == 0) ? (0x80 + col) : (0xC0 + col);
    LCD_Command(address);
}

void LCD_Puts(char *str)
{
    // ... N?I DUNG HÀM LCD_Puts G?C ...
    while (*str)
    {
        LCD_Data(*str++);
    }
}
