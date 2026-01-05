/*****************************************************************************
* | File        :   multi_servo.c
* | Author      :   
* | Function    :   Multi-servo coordination example
* | Info        :   Demonstrates controlling multiple servos simultaneously
*----------------
* | This version:   V1.0
* | Date        :   2026-01-08
******************************************************************************/
#include "Pico_Servo_Driver.h"
#include <math.h>

/**
 * Multi-servo example with coordinated movement
 * 
 * This example demonstrates:
 * - Initializing multiple servos
 * - Moving them in coordinated patterns
 * - Different control strategies
 */
void multi_servo_example(void) {
    printf("\n=== Multi-Servo Example ===\n");
    printf("Controlling 4 servos (GPIO 0-3)\n");
    printf("Demonstrating coordinated movement patterns\n\n");
    
    // Initialize 4 servos on GPIO 0-3
    servo_init(SERVO_CH0 | SERVO_CH1 | SERVO_CH2 | SERVO_CH3);
    
    while (1) {
        // Pattern 1: Wave motion
        printf("\nPattern 1: Wave Motion\n");
        for (int i = 0; i < 3; i++) {
            for (uint8_t servo = 0; servo < 4; servo++) {
                servo_set_angle(servo, 0);
                sleep_ms(100);
                servo_set_angle(servo, 180);
                sleep_ms(100);
                servo_set_angle(servo, 90);  // Return to center
                sleep_ms(100);
            }
        }
        
        sleep_ms(1000);
        
        // Pattern 2: Synchronized sweep
        printf("\nPattern 2: Synchronized Sweep (all servos together)\n");
        for (float angle = 0; angle <= 180; angle += 5) {
            for (uint8_t servo = 0; servo < 4; servo++) {
                servo_set_angle(servo, angle);
            }
            sleep_ms(50);
        }
        for (float angle = 180; angle >= 0; angle -= 5) {
            for (uint8_t servo = 0; servo < 4; servo++) {
                servo_set_angle(servo, angle);
            }
            sleep_ms(50);
        }
        
        sleep_ms(1000);
        
        // Pattern 3: Mirror motion (0 & 3 move together, 1 & 2 move opposite)
        printf("\nPattern 3: Mirror Motion\n");
        for (float angle = 0; angle <= 180; angle += 2) {
            servo_set_angle(0, angle);         // Outer left
            servo_set_angle(3, angle);         // Outer right
            servo_set_angle(1, 180 - angle);   // Inner left (opposite)
            servo_set_angle(2, 180 - angle);   // Inner right (opposite)
            sleep_ms(20);
        }
        
        sleep_ms(1000);
        
        // Pattern 4: Sequential positioning
        printf("\nPattern 4: Individual Positioning\n");
        servo_set_angle(0, 45);
        sleep_ms(300);
        servo_set_angle(1, 90);
        sleep_ms(300);
        servo_set_angle(2, 135);
        sleep_ms(300);
        servo_set_angle(3, 180);
        sleep_ms(1000);
        
        // Return all to center
        printf("\nReturning all servos to center...\n");
        for (uint8_t servo = 0; servo < 4; servo++) {
            servo_set_angle(servo, 90);
        }
        sleep_ms(2000);
    }
}

/**
 * All 16 channel example
 * 
 * Demonstrates using all 16 channels at once
 */
void all_channels_example(void) {
    printf("\n=== All 16 Channels Example ===\n");
    printf("Controlling all 16 servos (GPIO 0-15)\n\n");
    
    // Initialize all 16 channels
    servo_init(SERVO_ALL);
    
    while (1) {
        printf("Sweeping all servos 0° -> 180°\n");
        for (float angle = 0; angle <= 180; angle += 2) {
            for (uint8_t servo = 0; servo < 16; servo++) {
                servo_set_angle(servo, angle);
            }
            sleep_ms(20);
        }
        
        sleep_ms(1000);
        
        printf("Sweeping all servos 180° -> 0°\n");
        for (float angle = 180; angle >= 0; angle -= 2) {
            for (uint8_t servo = 0; servo < 16; servo++) {
                servo_set_angle(servo, angle);
            }
            sleep_ms(20);
        }
        
        sleep_ms(1000);
        
        // Create a "wave" effect across all 16 channels
        printf("Wave effect across all channels\n");
        for (int cycle = 0; cycle < 5; cycle++) {
            for (uint8_t offset = 0; offset < 16; offset++) {
                for (uint8_t servo = 0; servo < 16; servo++) {
                    // Create a sine-wave-like pattern
                    float angle = 90 + 45 * sin((servo + offset) * 3.14159 / 8);
                    servo_set_angle(servo, angle);
                }
                sleep_ms(100);
            }
        }
        
        sleep_ms(2000);
    }
}

