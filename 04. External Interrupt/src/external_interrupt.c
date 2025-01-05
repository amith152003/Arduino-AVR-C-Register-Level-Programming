#include <avr/io.h>  // For setting input/output pins
#include <avr/interrupt.h>  // For interrupt handling
#include <util/delay.h>  // For using the delay function (optional)


// Interrupt Service Routine for INT0 (external interrupt)
ISR(INT0_vect) {
    PORTB |= (1 << PB5);  // Turn on LED on PB5
}

// Interrupt Service Routine for INT1 (external interrupt)
ISR(INT1_vect) {
    PORTB &= ~(1 << PB5);  // Turn off LED on PB5
}

int main() {
    DDRB |= (1 << DDB5);  // Set PB5 (pin 13) as an output

    // Enable INT0 and INT1
    EIMSK |= (1 << INT0) | (1 << INT1);

    // Configure INT0 and INT1 to trigger on rising edge
    EICRA |= (1 << ISC11) | (1 << ISC10) | (1 << ISC01) | (1 << ISC00);

    // Enable global interrupts
    SREG |= (1 << 7);

    while (1) {
        // Main loop does nothing, the program is controlled by interrupts
    }

    return 0;  
}
