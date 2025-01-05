#include <avr/io.h>  // For setting input/output pins
#include <avr/delay.h>  // For using the delay function

int main() {
  DDRB |= (1 << DDB5);  // Set PB5 (pin 13) as an output

  while(1) {
    PORTB = 0x20;  // Turn the LED on (set PB5 to high)
    _delay_ms(2000);  // Wait for 2000 milliseconds (2 seconds)
    PORTB = 0x00;  // Turn the LED off (set PB5 to low)
    _delay_ms(1000);  // Wait for 1000 milliseconds (1 second)
  }

  return 0;
}
