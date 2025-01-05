#include <avr/io.h>  // For setting input/output pins
#include <util/delay.h>  // For using the delay function

int main() {
    unsigned char seven_seg[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7C, 0x07, 0x7F, 0x6F};
    
    DDRD = 0xFF; // Set all Port D pins as output
    PORTD = 0x00; // Initialize Port D to 0

    while (1) {
        for (int i = 0; i < 10; i++) {
            PORTD = seven_seg[i]; // Send data to 7-segment display
            _delay_ms(1000); // 1-second delay
        }
    }

    return 0; 
}
