/*****************************************************************************
* | File        :   main.c
* | Author      :   
* | Function    :   Main entry point for Pico Servo Driver examples
* | Info        :   
*----------------
* | This version:   V2.0
* | Date        :   2026-01-08
* | Info        :   Refactored for clarity and ease of use
*
* QUICK START:
* 1. Choose which example to run by uncommenting ONE of the examples below
* 2. Build the project (F7 in VS Code with CMake Tools)
* 3. Flash the generated .uf2 file to your Pico
* 4. Connect servo(s) to the appropriate GPIO pins
*
* SERVO WIRING:
* - Servo Signal -> GPIO pin (see example for pin numbers)
* - Servo Power (5V) -> VBUS (pin 40) or external 5V supply
* - Servo Ground -> GND (any GND pin on Pico)
*
* Note: For multiple servos or high-torque servos, use an external
*       5V power supply to avoid overloading the Pico's regulator.
*
******************************************************************************/

#include "pico/stdlib.h"
#include "single_servo.h"
#include "multi_servo.h"

int main(void) {
    // ========================================
    // SELECT YOUR EXAMPLE (uncomment ONE)
    // ========================================
    
    // Example 1: Single servo on GPIO 0
    // Simple sweep demonstration - great for getting started!
    // single_servo_example();
    
    // Example 2: Multi-servo (4 servos on GPIO 0-3)
    // Demonstrates coordinated movement patterns
    multi_servo_example();
    
    // Example 3: All 16 channels
    // Use all 16 GPIO pins for maximum servo control
    // all_channels_example();
    
    // Note: Only one example will run. The functions above contain
    // infinite loops, so execution will never reach code after them.
    
    return 0;
}

/*
 * TROUBLESHOOTING:
 * 
 * Servo doesn't move:
 * - Check wiring (signal, power, ground)
 * - Verify servo is getting 5V power
 * - Try servo_set_pulse_us() to manually calibrate
 * 
 * Servo jitters:
 * - Check power supply is adequate
 * - Ensure good ground connection between Pico and servo
 * - Try adding capacitor (100-470uF) across servo power/ground
 * 
 * Wrong range of motion:
 * - Some servos use different pulse ranges (e.g., 1000-2000us)
 * - Use servo_set_pulse_us() instead of servo_set_angle()
 * - Adjust SERVO_MIN_PULSE_US and SERVO_MAX_PULSE_US in header
 * 
 * Serial output not working:
 * - Connect Pico USB cable
 * - Open serial monitor at 115200 baud
 * - In CMakeLists.txt, verify: pico_enable_stdio_usb(main 1)
 */
