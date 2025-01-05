#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

int main() {
    // Set the reference voltage to AVCC
    ADMUX |= (1 << REFS0); // REFS1 is 0, REFS0 is 1 for AVCC as reference
    
    // Select ADC channel 0 (ADC0)
    ADMUX &= ~(1 << MUX3) & ~(1 << MUX2) & ~(1 << MUX1) & ~(1 << MUX0); 

    // Enable ADC, ADC interrupt, and auto trigger
    ADCSRA |= (1 << ADEN) | (1 << ADIE) | (1 << ADATE);

    // Set ADC prescaler to 16 (ADPS2:0 = 001)
    ADCSRA |= (1 << ADPS1) | (1 << ADPS0); // Prescaler = 16

    // Start the ADC conversion
    ADCSRA |= (1 << ADSC);

    // Configure Timer1 for Fast PWM mode on OC1A (PB1)
    TCCR1A |= (1 << COM1A1) | (1 << WGM11);  // Non-inverted PWM, Fast PWM mode (WGM13:0)
    TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11); // Fast PWM, prescaler 8

    // Set PB1 as output (OC1A)
    DDRB |= (1 << DDB1);

    // Set the top value for Timer1 (10-bit resolution for PWM)
    ICR1 = 1023;  // Top value for 10-bit resolution PWM

    // Enable global interrupts
    SREG |= (1 << 7);  // Set the global interrupt flag

    while (1) {
        // Main loop, doing nothing, ADC conversion and ISR handle PWM
    }
}

// ADC conversion complete ISR
ISR(ADC_vect) {
    OCR1A = ADC;  // Set PWM duty cycle based on ADC value (10-bit result)
}
