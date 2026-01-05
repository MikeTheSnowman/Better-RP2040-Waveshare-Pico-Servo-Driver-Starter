/*****************************************************************************
* | File        :   single_servo.c
* | Author      :   
* | Function    :   Minimal single servo example
* | Info        :   Simple demonstration of controlling one servo
*----------------
* | This version:   V1.0
* | Date        :   2026-01-08
******************************************************************************/
#include "Pico_Servo_Driver.h"

/**
 * Simple single servo example
 * 
 * This example demonstrates the most basic servo control:
 * - Initialize one servo on GPIO 0
 * - Sweep it from 0° to 180° and back continuously
 */
void single_servo_example(void) {
    printf("\n=== Single Servo Example ===\n");
    printf("Controlling servo on GPIO 0\n");
    printf("Sweeping between 0° and 180°\n\n");
    
    // Initialize servo on GPIO 0
    servo_init(SERVO_CH0);
    
    // Infinite loop: sweep back and forth
    while (1) {
        printf("Sweeping 0° -> 180°...\n");
        servo_sweep(0, 0, 180, 10);
        
        sleep_ms(500);  // Pause at 180°
        
        printf("Sweeping 180° -> 0°...\n");
        servo_sweep(0, 180, 0, 10);
        
        sleep_ms(500);  // Pause at 0°
    }
}

