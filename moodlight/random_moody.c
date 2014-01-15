/* ATtiny85_3pinPWM

  P Barber
  Dec 2013

  based on http://matt16060936.blogspot.co.uk/2012/04/attiny-pwm.html

*/

//#define DO_NOT_FADE

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

// Convinience defines for the duty cycles
#define BLUE_DUTY OCR0A
#define GREEN_DUTY OCR0B
#define RED_DUTY OCR1B

typedef struct {
uint8_t r;
uint8_t g;
uint8_t b;
} rgb_colour;

// Global store of the current colour
rgb_colour gColour;

void setup_ATtiny85_3pinPWM()
{
    /*
       Setup PWM on io pins 0, 1, and 4
       Use OCR0A, OCR0B and OCR1B to set the duty cycles
    */
    DDRB = 1<<DDB4 | 1<<DDB1 | 1<<DDB0;
    TCCR0A = 2<<COM0A0 | 2<<COM0B0 | 3<<WGM00;
    TCCR0B = 0<<WGM02 | 1<<CS00;
    TCCR1 = 0<<PWM1A | 0<<COM1A0 | 1<<CS10;
    GTCCR = 1<<PWM1B | 2<<COM1B0;
}

void setColour(uint8_t red, uint8_t green, uint8_t blue)
{
    // Expect 0-255 for each colour
    RED_DUTY = red;
    GREEN_DUTY = green;
    BLUE_DUTY = blue;

    // Store current values globally
    gColour.r = red;
    gColour.g = green;
    gColour.b = blue;
}

void fadeColour(uint8_t red, uint8_t green, uint8_t blue, int time)
{
#ifndef DO_NOT_FADE
    // Uses setColour, time is time in ms for complete fade
    // This is general purpose which makes the code very big when compiled
    int update_time = 20;
    int steps = time/update_time;
    float red_step = (float)(red - gColour.r)/(float)steps; 
    float green_step = (float)(green - gColour.g)/(float)steps; 
    float blue_step = (float)(blue - gColour.b)/(float)steps; 
    int i;
    float  r, g, b;

    r = (float)gColour.r;
    g = (float)gColour.g;
    b = (float)gColour.b;

    for (i=0; i<steps; i++){
        r += red_step;
        g += green_step;
        b += blue_step;

        setColour((uint8_t)r, (uint8_t)g, (uint8_t)b);

        _delay_ms(update_time);
    }
#else
    setColour(red, green, blue);
    _delay_ms(1000);
#endif
}

unsigned long m_w = 1;
unsigned long m_z = 2;

uint8_t getRandom255()
{
    m_z = 36969L * (m_z & 65535L) + (m_z >> 16);
    m_w = 18000L * (m_w & 65535L) + (m_w >> 16);
    return (((m_z << 16) + m_w) % 255);
}

int main()
{
    uint8_t r=0, g=85, b=170;

    setup_ATtiny85_3pinPWM();

    for (;;){

        fadeColour(getRandom255(), getRandom255(), getRandom255(), 1000);
        _delay_ms(10000);
    }

    return (0);
}
