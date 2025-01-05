#include <avr/io.h>  // For setting input/output pins
#include <util/delay.h>  // For using the delay function (optional here)

int main() {
    DDRB |= (1 << DDB5);  // Set PB5 (pin 13) as an output
    DDRD &= ~(1 << DDD2);  // Set PD2 (pin 2) as an input

    while(1) {
        if(PIND & (1 << PIND2)) {  // Check if PD2 is high (button pressed)
            PORTB = 0x20;  // Turn the LED on (set PB5 to high)
        }
        else {
            PORTB = 0x00;  // Turn the LED off (set PB5 to low)
        }
    }

    return 0;
}
