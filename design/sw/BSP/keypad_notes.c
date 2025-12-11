#include "pwm_buzzer.h"
#include "mcu_config.h" // C?n d? truy c?p htim2

/*================= HÀM KH?I T?O PWM (CODE G?C) =================*/
void PWM_SetFrequency(uint32_t freq)
{
    // S? d?ng htim2 du?c d?nh nghia trong mcu_config.c
    if(freq == 0)
    {
        HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_2);
        return;
    }

    uint32_t PSC = 72 - 1;       // 72MHz / 72 = 1MHz
    uint32_t ARR = 1000000 / freq;

    htim2.Instance->PSC  = PSC;
    htim2.Instance->ARR  = ARR;
    htim2.Instance->CCR2 = ARR / 2; // Duty 50%

    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_2);
}
