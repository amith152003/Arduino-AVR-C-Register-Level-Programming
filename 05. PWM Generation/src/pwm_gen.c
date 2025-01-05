#include <avr/io.h>  // For setting input/output pins
#include <avr/interrupt.h>  // For interrupt handling (not used here but necessary for Timer/Interrupt operations)
#include <util/delay.h>  // For using the delay function

int main() {
    // Set Timer1 to Fast PWM mode, with ICR1 as the TOP value (10-bit resolution)
    TCCR1A |= (1 << WGM11) | (1 << COM1A1);  // Fast PWM, non-inverted mode
    TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11);  // Fast PWM, prescaler of 8

    DDRB |= (1 << DDB1);  // Set PB1 (OC1A) as output

    ICR1 = 1023;  // Set TOP value for 10-bit resolution

    OCR1A = 0;  // Initialize PWM duty cycle to 0

    while(1) {
        // Ramp up the duty cycle from 0 to 1023
        for(int i = 0; i <= 1023; i++) {
            OCR1A = i;  // Update the duty cycle value
            _delay_us(1000);  // Delay for smooth ramp-up
        }

        // Ramp down the duty cycle from 1023 to 0
        for(int i = 1023; i >= 0; i--) {
            OCR1A = i;  // Update the duty cycle value
            _delay_us(1000);  // Delay for smooth ramp-down
        }
    }

    return 0;
}
