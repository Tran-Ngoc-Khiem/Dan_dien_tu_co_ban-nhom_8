#ifndef __MCU_CONFIG_H
#define __MCU_CONFIG_H

#include "stm32f1xx_hal.h"

// Khai báo Handle Timer (du?c d?nh nghia trong mcu_config.c)
extern TIM_HandleTypeDef htim2;

void SystemClock_Config(void);
void Error_Handler(void);
void MCU_Initialize(void); // Hàm t?ng h?p d? g?i t?t c? init

#endif /* __MCU_CONFIG_H */
