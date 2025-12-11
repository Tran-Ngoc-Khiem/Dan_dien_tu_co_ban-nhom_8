#include "song_manager.h"
#include <string.h>

// Ð?nh nghia các bi?n toàn c?c (CODE G?C)
uint16_t song_data[11][MAX_NOTES] = {0};
uint8_t song_len[11] = {0};

uint16_t record_buf[MAX_NOTES] = {0}; 
uint8_t record_len = 0; 
uint8_t isRecording = 0; 
uint8_t isPlaying = 0;
uint8_t play_index = 0;

void SongManager_SaveRecord(uint8_t song_slot)
{
    // Logic luu t? code g?c
    song_len[song_slot] = record_len;
    for (int i = 0; i < record_len; i++) {
        song_data[song_slot][i] = record_buf[i];
    }
    record_len = 0; // Reset buffer
}
