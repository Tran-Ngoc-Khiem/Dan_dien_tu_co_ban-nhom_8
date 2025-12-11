#ifndef __LCD_4BIT_H
#define __LCD_4BIT_H

#include "stm32f1xx_hal.h"

// Ð?nh nghia Pin LCD (CODE G?C)
#define LCD_RS_Pin GPIO_PIN_9
#define LCD_RW_Pin GPIO_PIN_8
#define LCD_E_Pin  GPIO_PIN_7

#define LCD_D4_Pin GPIO_PIN_6
#define LCD_D5_Pin GPIO_PIN_5
#define LCD_D6_Pin GPIO_PIN_4
#define LCD_D7_Pin GPIO_PIN_3

// Khai báo các hàm LCD (CODE G?C)
void LCD_Init(void);
void LCD_Command(uint8_t cmd);
void LCD_Data(uint8_t data);
void LCD_Enable(void);
void LCD_Send4Bits(uint8_t data);
void LCD_Clear(void);
void LCD_GotoXY(uint8_t row, uint8_t col);
void LCD_Puts(char *str);
void LCD_Display(void); // Hàm hi?n th? chính (CODE G?C)

#endif /* __LCD_4BIT_H */
