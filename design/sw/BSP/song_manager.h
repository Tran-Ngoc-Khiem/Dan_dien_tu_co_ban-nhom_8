#ifndef __SONG_MANAGER_H
#define __SONG_MANAGER_H

#include "stm32f1xx_hal.h"

#define MAX_NOTES 128

// Khai báo các bi?n toàn c?c (CODE G?C)
extern uint16_t song_data[11][MAX_NOTES];
extern uint8_t song_len[11];

extern uint16_t record_buf[MAX_NOTES]; 
extern uint8_t record_len; 
extern uint8_t isRecording; 
extern uint8_t isPlaying; 
extern uint8_t play_index; 

// Khai báo hàm luu d? li?u
void SongManager_SaveRecord(uint8_t song_slot);

#endif /* __SONG_MANAGER_H */
