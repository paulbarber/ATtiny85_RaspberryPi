#define F_CPU 8000000L

#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
   DDRB = 0xFF;   // PORTB is output, all pins
   PORTB = 0x00;   // LED's are off

   for (;;) {
      PORTB ^= 0x1;   // invert pins
      _delay_ms(131); // wait some time, remember clock is divided by 8 with default fuses
      PORTB ^= 0x2;   // invert pins
      _delay_ms(131); // wait some time, remember clock is divided by 8 with default fuses
      PORTB ^= 0x4;   // invert pins
      _delay_ms(131); // wait some time, remember clock is divided by 8 with default fuses
   }

   return 0;
}

