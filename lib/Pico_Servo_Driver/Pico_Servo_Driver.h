/*****************************************************************************
* | File        :   Pico_Servo_Driver.h
* | Author      :   
* | Function    :   16-Channel PWM Servo Driver for Raspberry Pi Pico
* | Info        :
*----------------
* | This version:   V2.0
* | Date        :   2026-01-08
* | Info        :   Simplified, clear API for servo control
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
******************************************************************************/
#ifndef _PICO_SERVO_DRIVER_H_
#define _PICO_SERVO_DRIVER_H_

#include "pico/stdlib.h"
#include "hardware/pwm.h"
#include <stdio.h>

// Servo timing constants (in microseconds)
// Standard servos: 500us = 0°, 1500us = 90°, 2500us = 180°
#define SERVO_MIN_PULSE_US  500     // Minimum pulse width (0 degrees)
#define SERVO_MAX_PULSE_US  2500    // Maximum pulse width (180 degrees)
#define SERVO_FREQUENCY_HZ  50      // Standard servo frequency (50Hz = 20ms period)

// Channel bitmasks - use these to enable specific GPIO pins
#define SERVO_CH0   (1 << 0)   // GPIO 0
#define SERVO_CH1   (1 << 1)   // GPIO 1
#define SERVO_CH2   (1 << 2)   // GPIO 2
#define SERVO_CH3   (1 << 3)   // GPIO 3
#define SERVO_CH4   (1 << 4)   // GPIO 4
#define SERVO_CH5   (1 << 5)   // GPIO 5
#define SERVO_CH6   (1 << 6)   // GPIO 6
#define SERVO_CH7   (1 << 7)   // GPIO 7
#define SERVO_CH8   (1 << 8)   // GPIO 8
#define SERVO_CH9   (1 << 9)   // GPIO 9
#define SERVO_CH10  (1 << 10)  // GPIO 10
#define SERVO_CH11  (1 << 11)  // GPIO 11
#define SERVO_CH12  (1 << 12)  // GPIO 12
#define SERVO_CH13  (1 << 13)  // GPIO 13
#define SERVO_CH14  (1 << 14)  // GPIO 14
#define SERVO_CH15  (1 << 15)  // GPIO 15
#define SERVO_ALL   0xFFFF     // All 16 channels

/**
 * Initialize the servo driver for specified GPIO pins
 * 
 * @param channel_mask Bitmask of channels to enable (e.g., SERVO_CH0 | SERVO_CH1)
 *                     Use SERVO_ALL (0xFFFF) to enable all 16 channels
 * 
 * Example: servo_init(SERVO_CH0);              // Enable only GPIO 0
 *          servo_init(SERVO_CH0 | SERVO_CH1);  // Enable GPIO 0 and 1
 *          servo_init(SERVO_ALL);              // Enable all 16 channels
 */
void servo_init(uint16_t channel_mask);

/**
 * Set servo position by angle
 * 
 * @param gpio_pin GPIO pin number (0-15)
 * @param angle Angle in degrees (0.0 to 180.0)
 * 
 * Note: Angles outside 0-180 range will be clamped
 * 
 * Example: servo_set_angle(0, 90.0);  // Set servo on GPIO 0 to 90 degrees
 */
void servo_set_angle(uint8_t gpio_pin, float angle);

/**
 * Set servo position by pulse width (for calibration or non-standard servos)
 * 
 * @param gpio_pin GPIO pin number (0-15)
 * @param pulse_us Pulse width in microseconds (typically 500-2500)
 * 
 * Note: Most servos use 500us (0°) to 2500us (180°)
 *       Some servos may use different ranges (e.g., 1000-2000us)
 * 
 * Example: servo_set_pulse_us(0, 1500);  // Set servo to center position
 */
void servo_set_pulse_us(uint8_t gpio_pin, uint16_t pulse_us);

/**
 * Sweep a servo from one angle to another
 * 
 * @param gpio_pin GPIO pin number (0-15)
 * @param start_angle Starting angle in degrees (0.0 to 180.0)
 * @param end_angle Ending angle in degrees (0.0 to 180.0)
 * @param step_delay_ms Delay between each degree step in milliseconds
 * 
 * Example: servo_sweep(0, 0, 180, 10);  // Sweep GPIO 0 from 0° to 180° slowly
 */
void servo_sweep(uint8_t gpio_pin, float start_angle, float end_angle, uint16_t step_delay_ms);

#endif
