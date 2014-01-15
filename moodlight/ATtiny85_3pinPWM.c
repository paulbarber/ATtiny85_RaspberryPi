/* ATtiny85_3pinPWM

  P Barber
  Dec 2013

  http://matt16060936.blogspot.co.uk/2012/04/attiny-pwm.html

*/


/*
all my ATtiny85 chips have their 8MHz fuse set
by default they run at 1MHz, so adjust accordingly
this constant is used by delay.h, so make sure it stays above the include
*/
#define F_CPU 8000000

/*
io.h provides lots of handy constants
delay.h provides _delay_ms and _delay_us functions
*/
#include <avr/io.h>
#include <util/delay.h>

/*
program entry-point
*/
int main()
{
    /*
    Starting values for red, green and blue
    */
    uint8_t r=0, g=85, b=170;
    
    /*
    Port B Data Direction Register (controls the mode of all pins within port B)
    DDRB is 8 bits: [unused:unused:DDB5:DDB4:DDB3:DDB2:DDB1:DDB0]
    1<<DDB4: sets bit DDB4 (data-direction, port B, pin 4), which puts PB4 (port B, pin 4) in output mode
    1<<DDB1: sets bit DDB1 (data-direction, port B, pin 1), which puts PB1 (port B, pin 1) in output mode
    1<<DDB0: sets bit DDB0 (data-direction, port B, pin 0), which puts PB0 (port B, pin 0) in output mode
    */
    DDRB = 1<<DDB4 | 1<<DDB1 | 1<<DDB0;

    /*
    Control Register A for Timer/Counter-0 (Timer/Counter-0 is configured using two registers: A and B)
    TCCR0A is 8 bits: [COM0A1:COM0A0:COM0B1:COM0B0:unused:unused:WGM01:WGM00]
    2<<COM0A0: sets bits COM0A0 and COM0A1, which (in Fast PWM mode) clears OC0A on compare-match, and sets OC0A at BOTTOM
    2<<COM0B0: sets bits COM0B0 and COM0B1, which (in Fast PWM mode) clears OC0B on compare-match, and sets OC0B at BOTTOM
    3<<WGM00: sets bits WGM00 and WGM01, which (when combined with WGM02 from TCCR0B below) enables Fast PWM mode
    */
    TCCR0A = 2<<COM0A0 | 2<<COM0B0 | 3<<WGM00;
    
    /*
    Control Register B for Timer/Counter-0 (Timer/Counter-0 is configured using two registers: A and B)
    TCCR0B is 8 bits: [FOC0A:FOC0B:unused:unused:WGM02:CS02:CS01:CS00]
    0<<WGM02: bit WGM02 remains clear, which (when combined with WGM00 and WGM01 from TCCR0A above) enables Fast PWM mode
    1<<CS00: sets bits CS01 (leaving CS01 and CS02 clear), which tells Timer/Counter-0 to not use a prescalar
    */
    TCCR0B = 0<<WGM02 | 1<<CS00;
    
    /*
    Control Register for Timer/Counter-1 (Timer/Counter-1 is configured with just one register: this one)
    TCCR1 is 8 bits: [CTC1:PWM1A:COM1A1:COM1A0:CS13:CS12:CS11:CS10]
    0<<PWM1A: bit PWM1A remains clear, which prevents Timer/Counter-1 from using pin OC1A (which is shared with OC0B)
    0<<COM1A0: bits COM1A0 and COM1A1 remain clear, which also prevents Timer/Counter-1 from using pin OC1A (see PWM1A above)
    1<<CS10: sets bit CS11 which tells Timer/Counter-1  to not use a prescalar
    */
    TCCR1 = 0<<PWM1A | 0<<COM1A0 | 1<<CS10;
    
    /*
    General Control Register for Timer/Counter-1 (this is for Timer/Counter-1 and is a poorly named register)
    GTCCR is 8 bits: [TSM:PWM1B:COM1B1:COM1B0:FOC1B:FOC1A:PSR1:PSR0]
    1<<PWM1B: sets bit PWM1B which enables the use of OC1B (since we disabled using OC1A in TCCR1)
    2<<COM1B0: sets bit COM1B1 and leaves COM1B0 clear, which (when in PWM mode) clears OC1B on compare-match, and sets at BOTTOM
    */
    GTCCR = 1<<PWM1B | 2<<COM1B0;
    
    /*
    loop forever
    */
    for (;;)
    {
        /*
        increment and boundary-check each color
        */
        if (++r>255) r=0;
        if (++g>255) g=0;
        if (++b>255) b=0;
        
        /*
        update compare registers with red, green and blue values
        */
        OCR0A = r;
        OCR0B = g;
        OCR1B = b;
        
        /*
        brief pause so we can perceive what is happening
        */
        _delay_ms(10);
    }

    return (0);
}

