#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f1xx_hal.h"
#include <stdio.h>

// Khai báo các module
#include "lcd_4bit.h"
#include "pwm_buzzer.h"
#include "keypad_notes.h"
#include "song_manager.h"
#include "mcu_config.h"

// Bi?n toàn c?c t? main.c
extern uint8_t mode; 
extern uint8_t song; 

// Khai báo l?i các hàm t? code g?c (n?u c?n)
void Error_Handler(void);

#endif /* __MAIN_H */
