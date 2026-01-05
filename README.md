# Pico Servo Driver

A clean, easy-to-use 16-channel PWM servo driver library for the Raspberry Pi Pico.

## Features

- Control up to 16 servos simultaneously (GPIO 0-15)
- Simple angle-based control (0-180 degrees)
- Direct pulse-width control for calibration
- Built-in sweep functionality
- Clear, well-documented API
- Multiple example programs included

## Quick Start

### Hardware Setup

1. **Single Servo (Beginner)**
   - Connect servo signal wire to GPIO 0
   - Connect servo power (red) to VBUS (pin 40) or external 5V
   - Connect servo ground (black/brown) to GND

2. **Multiple Servos**
   - Use external 5V power supply for servos (recommended)
   - Connect all servo grounds together with Pico GND
   - Connect signal wires to GPIO 0-15 as needed

### Software Setup

1. Open `main.c`
2. Uncomment the example you want to run
3. Build the project (F7 in VS Code)
4. Flash the generated `main.uf2` file to your Pico

## API Reference

### Initialization

```c
// Initialize single servo on GPIO 0
servo_init(SERVO_CH0);

// Initialize multiple servos
servo_init(SERVO_CH0 | SERVO_CH1 | SERVO_CH2);

// Initialize all 16 channels
servo_init(SERVO_ALL);
```

### Basic Control

```c
// Set servo to 90 degrees (center)
servo_set_angle(0, 90.0);

// Set servo to 0 degrees
servo_set_angle(0, 0.0);

// Set servo to 180 degrees
servo_set_angle(0, 180.0);
```

### Advanced Control

```c
// Set custom pulse width (for non-standard servos)
servo_set_pulse_us(0, 1500);  // Center position

// Smooth sweep from 0° to 180° over 1.8 seconds
servo_sweep(0, 0, 180, 10);
```

## Examples

### Example 1: Single Servo
Location: `examples/single_servo.c`

Simple demonstration of controlling one servo - great for getting started!

### Example 2: Multi-Servo
Location: `examples/multi_servo.c`

Demonstrates coordinated control of 4 servos with various movement patterns:
- Wave motion
- Synchronized sweep
- Mirror motion
- Sequential positioning

### Example 3: All 16 Channels
Function: `all_channels_example()` in `examples/multi_servo.c`

Shows how to control all 16 servos simultaneously, including wave effects.

## Servo Timing

Standard servos use these pulse widths:
- **0°** = 500 microseconds
- **90°** = 1500 microseconds (center)
- **180°** = 2500 microseconds

Some servos use different ranges (e.g., 1000-2000μs). Use `servo_set_pulse_us()` for these.

## Troubleshooting

### Servo doesn't move
- Verify wiring (signal, power, ground)
- Check servo is receiving 5V power
- Try `servo_set_pulse_us(0, 1500)` to test manually

### Servo jitters or stutters
- Power supply may be inadequate (use external 5V supply)
- Ensure good ground connection
- Add 100-470μF capacitor across servo power/ground

### Wrong range of motion
- Your servo may use a different pulse range
- Use `servo_set_pulse_us()` to find the actual range
- Adjust `SERVO_MIN_PULSE_US` and `SERVO_MAX_PULSE_US` in header

### Serial output not working
- Connect Pico via USB
- Open serial monitor at 115200 baud
- Check `CMakeLists.txt` has: `pico_enable_stdio_usb(main 1)`

## Building

### VS Code (Recommended)
1. Install CMake Tools extension
2. Open project folder
3. Select kit (GCC for arm-none-eabi)
4. Press F7 to build

### Command Line
```bash
mkdir build
cd build
cmake ..
make
```

Output file: `build/main.uf2`

## Project Structure

```
.
├── main.c                          # Main entry point
├── lib/
│   └── Pico_Servo_Driver/
│       ├── Pico_Servo_Driver.h     # Public API
│       └── Pico_Servo_Driver.c     # Implementation
├── examples/
│   ├── single_servo.c              # Single servo example
│   ├── single_servo.h
│   ├── multi_servo.c               # Multi-servo examples
│   └── multi_servo.h
└── CMakeLists.txt                  # Build configuration
```

## License

MIT License - See source files for full license text.

## Version History

- **V2.0** (2026-01-08) - Complete refactor for clarity and ease of use
  - Removed unnecessary abstraction layers
  - Inlined PWM configuration
  - Added clear, simple API
  - Fixed interrupt handler misuse
  - Added comprehensive examples and documentation

- **V1.0** (2021-09-15) - Initial release

