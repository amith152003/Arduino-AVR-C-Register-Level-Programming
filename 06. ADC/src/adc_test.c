#include <avr/io.h>
#include <util/delay.h>

uint16_t readadc(uint8_t channel) {
    // Limit channel to valid range (0-7)
    channel &= 0b00000111;

    // Select the channel
    ADMUX = (ADMUX & 0xF8) | channel;

    // Start ADC conversion
    ADCSRA |= (1 << ADSC);

    // Wait for conversion to complete
    while (ADCSRA & (1 << ADSC));

    return ADC;
}

int main() {
    uint8_t pot_val;

    // ADC configuration: Enable ADC, set prescaler to 128
    ADCSRA |= (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // Set reference voltage to AVCC with external capacitor at AREF pin
    ADMUX |= (1 << REFS0);

    // Configure Timer1 for Fast PWM mode with ICR1 as TOP
    TCCR1A |= (1 << COM1A1) | (1 << WGM11);  // Non-inverting mode
    TCCR1B |= (1 << WGM12) | (1 << WGM13) | (1 << CS11);  // Fast PWM with ICR1 as TOP

    // Set PB1 as output for PWM signal (OC1A)
    DDRB |= (1 << DDB1);

    // Set ICR1 to 255 for 8-bit resolution
    ICR1 = 255;

    while (1) {
        // Read ADC value from channel 0 and scale to 8-bit (0-255)
        pot_val = (uint8_t)((readadc(0) * 255UL) / 1023);

        // Update duty cycle
        OCR1A = pot_val;

        // Small delay to stabilize ADC readings
        _delay_ms(100);
    }

    return 0;
}
