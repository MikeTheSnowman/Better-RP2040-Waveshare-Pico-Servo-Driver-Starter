#include "Pico_Servo_Driver.h"

void PWM_initialization()       //PWM initialization
{
    if (DEV_Module_Init() != 0) 
    {
        printf("DEV_Module_Init fail \r\n");
    }
}

void on_pwm_wrap()   //Interrupt handler function
{
    uint16_t channe = CHANNE_N;
    // Clear the interrupt flag that brought us here
    for (int i = 0; i < 16; i++)
    {
        pwm_clear_irq(pwm_gpio_to_slice_num(i));
    }

    for (uint16_t ROTATE = ROTATE_0; ROTATE < ROTATE_180; ROTATE = ROTATE + 10)
    {
        channe = CHANNE_N;
        for (int CHANNE = 0; CHANNE < 16; CHANNE++)
        {
            if (channe & 0x0001)
            {
                printf("i:%d\n", ROTATE);
                pwm_set_gpio_level(CHANNE, ROTATE);
            }
            channe = channe >> 1;
        }
    }
    for (uint16_t ROTATE = ROTATE_180; ROTATE > ROTATE_0; ROTATE = ROTATE - 10)
    {
        channe = CHANNE_N;
        for (int CHANNE = 0; CHANNE < 16; CHANNE++)
        {
            if (channe & 0x0001)
            {
                printf("i:%d\n", ROTATE);
                pwm_set_gpio_level(CHANNE, ROTATE);
            }
            channe = channe >> 1;
        }
    }
}

void Pico_Servo_Driver()
{
    PWM_initialization();
    irq_set_exclusive_handler(PWM_IRQ_WRAP, on_pwm_wrap);
    irq_set_enabled(PWM_IRQ_WRAP, true);
}