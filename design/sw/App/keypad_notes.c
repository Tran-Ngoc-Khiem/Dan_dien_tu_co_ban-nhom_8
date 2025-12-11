#include "keypad_notes.h"

/*================= KI?M TRA NÚT NH?N (CODE G?C) =================*/
uint32_t ReadNoteKey(void)
{
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_12) == GPIO_PIN_RESET) return NOTE_C4;
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_13) == GPIO_PIN_RESET) return NOTE_D4;
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_14) == GPIO_PIN_RESET) return NOTE_E4;
    if(HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_15) == GPIO_PIN_RESET) return NOTE_F4;
    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_RESET) return NOTE_G4;
    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10) == GPIO_PIN_RESET) return NOTE_A4;
    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_9) == GPIO_PIN_RESET) return NOTE_B4;
    if(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_8) == GPIO_PIN_RESET) return NOTE_C5;

    return 0; // Khong nhan nut nao
}
