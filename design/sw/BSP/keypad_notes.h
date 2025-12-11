#ifndef __KEYPAD_NOTES_H
#define __KEYPAD_NOTES_H

#include "stm32f1xx_hal.h"

// Ð?nh nghia t?n s? các n?t (CODE G?C)
#define NOTE_C4    262
#define NOTE_D4    294
#define NOTE_E4    330
#define NOTE_F4    349
#define NOTE_G4    392
#define NOTE_A4    440
#define NOTE_B4    494
#define NOTE_C5    523

// Khai báo hàm d?c n?t nh?c (CODE G?C)
uint32_t ReadNoteKey(void);

// Macro ch?ng d?i phím (CODE G?C)
#define IS_BUTTON_PRESSED(PORT, PIN) (HAL_GPIO_ReadPin(PORT, PIN) == GPIO_PIN_RESET)

#endif /* __KEYPAD_NOTES_H */
