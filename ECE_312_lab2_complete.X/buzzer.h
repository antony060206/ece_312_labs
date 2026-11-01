/*
 * File:   buzzer.h
 * Author: ktaggar, zfeng8
 *
 */

#ifndef BUZZER_H
#define BUZZER_H

#include <stdint.h>
#include "songs.h"     


void buzzer_init(void);

void buzzer_tone(uint8_t voice, uint8_t pitch);


void buzzer_off(uint8_t voice);


void buzzer_silence(void);

#endif