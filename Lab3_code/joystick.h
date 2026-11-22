/* 
 * File:   joystick.h
 * Author: zfeng8
 *
 * Created on November 22, 2026, 11:45 AM
 */

#ifndef JOYSTICK_H
#define	JOYSTICK_H

void adc_init(void);

int16_t adc_conversion(uint16_t pos, uint16_t centre);

int16_t adc_read(uint16_t channel);

void joystick_calibrate(void);

int16_t joystick_x(void);
int16_t joystick_y(void);

#endif	/* JOYSTICK_H */

