/* Basic 'binary' Mood light code

  P Barber
  Dec 2013
*/

#define F_CPU 1000000L  // The default 1 MHz, I think CPU runs at 8 MHz but there is a divide by 8 in the default fuses

#include <avr/io.h>
#include <util/delay.h>

#define B0 0x01
#define B1 0x02
#define B2 0x04
#define B3 0x08
#define B4 0x10
#define B5 0x20
#define B6 0x40
#define B7 0x80

#define BLUE 0x01
#define GREEN 0x02
#define RED 0x04

#define D 500  // ms

int main(void)
{
   DDRB |= (1<<0);   // PORTB pin 0 is output
   DDRB |= (1<<1);   // PORTB pin 1 is output
   DDRB |= (1<<2);   // PORTB pin 2 is output

   PORTB = !(BLUE | GREEN | RED);   // LED's are off

   while(1) {
      PORTB = BLUE;
      _delay_ms(D);
      PORTB = BLUE | GREEN;
      _delay_ms(D);
      PORTB = GREEN;
      _delay_ms(D);
      PORTB = GREEN | RED;
      _delay_ms(D);
      PORTB = RED;
      _delay_ms(D);
      PORTB = RED | BLUE;
      _delay_ms(D);
   }

   return 0;
}

