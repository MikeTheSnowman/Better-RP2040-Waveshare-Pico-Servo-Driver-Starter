/*****************************************************************************
* | File        :   Pico_Servo_Driver.c
* | Author      :   
* | Function    :   16-Channel PWM Servo Driver for Raspberry Pi Pico
* | Info        :
*----------------
* | This version:   V2.0
* | Date        :   2026-01-08
* | Info        :   Simplified, clear implementation
******************************************************************************/
#include "Pico_Servo_Driver.h"

// Internal state tracking
static uint16_t initialized_channels = 0;

// PWM configuration constants
// System clock is 125MHz, we need 50Hz for servos
// With clock divider of 38: 125MHz / 38 = 3.289MHz
// Default wrap value is 65535 (16-bit max)
// Frequency: 3.289MHz / 65536 = 50.23Hz (close enough for servos)
#define PWM_CLOCK_DIVIDER   38.0f

/**
 * Convert microseconds to PWM counter value
 */
static inline uint16_t us_to_pwm_level(uint16_t pulse_us) {
    // At 3.289MHz clock (after divider), 1us = 3.289 cycles
    // pulse_us * 3.289 = pulse_us * 3289 / 1000
    return (pulse_us * 3289) / 1000;
}

/**
 * Convert angle (0-180) to pulse width in microseconds
 */
static inline uint16_t angle_to_us(float angle) {
    // Clamp angle to valid range
    if (angle < 0.0f) angle = 0.0f;
    if (angle > 180.0f) angle = 180.0f;
    
    // Linear mapping: 0° = 500us, 180° = 2500us
    // pulse_us = 500 + (angle / 180) * 2000
    return SERVO_MIN_PULSE_US + (uint16_t)((angle / 180.0f) * (SERVO_MAX_PULSE_US - SERVO_MIN_PULSE_US));
}

void servo_init(uint16_t channel_mask) {
    // Initialize stdio for debugging (optional)
    stdio_init_all();
    
    // Configure PWM for each requested channel
    for (uint8_t gpio_pin = 0; gpio_pin < 16; gpio_pin++) {
        if (channel_mask & (1 << gpio_pin)) {
            // Set GPIO function to PWM
            gpio_set_function(gpio_pin, GPIO_FUNC_PWM);
            
            // Get PWM slice for this GPIO
            uint slice_num = pwm_gpio_to_slice_num(gpio_pin);
            
            // Configure PWM
            pwm_config config = pwm_get_default_config();
            pwm_config_set_clkdiv(&config, PWM_CLOCK_DIVIDER);
            // Note: Using default wrap value of 65535 (no need to set explicitly)
            
            // Initialize PWM slice
            pwm_init(slice_num, &config, true);
            
            // Set initial position to center (90 degrees)
            servo_set_angle(gpio_pin, 90.0f);
            
            printf("Servo initialized on GPIO %d (PWM slice %d)\n", gpio_pin, slice_num);
        }
    }
    
    initialized_channels = channel_mask;
    printf("Servo driver initialized for %d channel(s)\n", __builtin_popcount(channel_mask));
}

void servo_set_angle(uint8_t gpio_pin, float angle) {
    // Validate GPIO pin
    if (gpio_pin >= 16) {
        printf("Error: Invalid GPIO pin %d (must be 0-15)\n", gpio_pin);
        return;
    }
    
    // Check if channel is initialized
    if (!(initialized_channels & (1 << gpio_pin))) {
        printf("Warning: GPIO %d not initialized\n", gpio_pin);
        return;
    }
    
    // Convert angle to pulse width, then to PWM level
    uint16_t pulse_us = angle_to_us(angle);
    servo_set_pulse_us(gpio_pin, pulse_us);
}

void servo_set_pulse_us(uint8_t gpio_pin, uint16_t pulse_us) {
    // Validate GPIO pin
    if (gpio_pin >= 16) {
        printf("Error: Invalid GPIO pin %d (must be 0-15)\n", gpio_pin);
        return;
    }
    
    // Check if channel is initialized
    if (!(initialized_channels & (1 << gpio_pin))) {
        printf("Warning: GPIO %d not initialized\n", gpio_pin);
        return;
    }
    
    // Warn if pulse width is outside typical range
    if (pulse_us < 400 || pulse_us > 2600) {
        printf("Warning: Unusual pulse width %dus on GPIO %d (typical: 500-2500us)\n", 
               pulse_us, gpio_pin);
    }
    
    // Convert microseconds to PWM counter value and set
    uint16_t pwm_level = us_to_pwm_level(pulse_us);
    pwm_set_gpio_level(gpio_pin, pwm_level);
}

void servo_sweep(uint8_t gpio_pin, float start_angle, float end_angle, uint16_t step_delay_ms) {
    // Validate GPIO pin
    if (gpio_pin >= 16) {
        printf("Error: Invalid GPIO pin %d (must be 0-15)\n", gpio_pin);
        return;
    }
    
    // Check if channel is initialized
    if (!(initialized_channels & (1 << gpio_pin))) {
        printf("Warning: GPIO %d not initialized\n", gpio_pin);
        return;
    }
    
    // Determine sweep direction
    float step = (start_angle < end_angle) ? 1.0f : -1.0f;
    
    // Sweep from start to end
    for (float angle = start_angle; 
         (step > 0) ? (angle <= end_angle) : (angle >= end_angle); 
         angle += step) {
        servo_set_angle(gpio_pin, angle);
        sleep_ms(step_delay_ms);
    }
    
    // Ensure we end exactly at end_angle
    servo_set_angle(gpio_pin, end_angle);
}
