/* ATtiny85_3pinPWM

  P Barber
  Dec 2013

  based on http://matt16060936.blogspot.co.uk/2012/04/attiny-pwm.html

*/

//#define DO_NOT_FADE
//#define DO_NOT_RANDOMISE

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>

// Convinience defines for the duty cycles
#define BLUE_DUTY OCR0A
#define GREEN_DUTY OCR0B
#define RED_DUTY OCR1B

#define MIN(X,Y) ((X) < (Y) ? (X) : (Y))
#define MAX(X,Y) ((X) > (Y) ? (X) : (Y))

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

#ifndef DO_NOT_RANDOMISE
unsigned long m_w = 1;
unsigned long m_z = 2;

uint8_t getRandom255()
{
    m_z = 36969L * (m_z & 65535L) + (m_z >> 16);
    m_w = 18000L * (m_w & 65535L) + (m_w >> 16);
    return (((m_z << 16) + m_w) % 255);
}
#endif
/*
void getRGBforVal(uint8_t val, uint8_t *R, uint8_t *G, uint8_t *B)
{
	// Get rgb proportions for false colour display of a val (0-255)

	     if ( val < 2 ) { *R = 255;      *G = 0;        *B = 0;       }
	else if ( val < 42 ) { *R = 255; *G = 0;        *B = (val-2)*6;       }
	else if ( val < 84 ) { *R = (84-val)*6; *G = 0;        *B = 255;       }
	else if ( val < 126 ) { *R = 0;       *G = (val-84)*6; *B = 255;       }
	else if ( val < 168 ) { *R = 0;       *G = 255;      *B = (168-val)*6; }
	else if ( val < 210 ) { *R =(val-168)*6; *G = 255;     *B = 0;         }
	else if ( val < 253 ) { *R = 255;      *G = (253-val)*6; *B = 0;       }
	else                  { *R = 255;      *G = 0;        *B = 0;        }
}
*/

float RGB (float q1, float q2, float hue)
{
	if      (hue > 360.0) hue -= 360.0;
	else if (hue < 0.0)   hue += 360.0;
	if (hue < 60.0)
		return(q1+(q2-q1)*hue/60.0);
	else if (hue < 180.0) 
		return(q2);
	else if (hue < 240.0) 
		return(q1+(q2-q1)*(240.0-hue)/60.0);
	else
		return(q1);
}


int HLSToRGB (float H, float L, float S, float *R, float *G, float *B)
{
// adapted from
// http://astronomy.swin.edu.au/~pbourke/colour/conversion.html, Compiled by Paul Bourke, February 1994 
// and seems to correspond to how CVI and PSP seem to work according to lab book 2, p25.
	float p1, p2;

	if (L <= 0.5) p2 = L*(1+S);
	else          p2 = L+S-(L*S);
	p1 = 2.0*L-p2;

	if (S == 0.0)
	{
		*R = L; 
		*G = L;
		*B = L;
	}
	else
	{
		*R = RGB(p1, p2, H+120.0);
		*G = RGB(p1, p2, H);
		*B = RGB(p1, p2, H-120.0);
	}
	return(0);
}


int main()
{
    uint8_t r=0, g=85, b=10;
    int l=0, h=0, count=0;
    //int R, G, B;
    float R, G, B, H, L, S;

    setup_ATtiny85_3pinPWM();

    // Setup ADC inputs 1 and 3 on pins 7 and 2 
    ADMUX = ( ( 1 << ADLAR ) | ( 1 << MUX1 ) | ( 1 << MUX0 ) );  // left adjust and select ADC3 to start with 
    ADCSRA |= ( ( 1 << ADEN ) | ( 1 << ADPS2 ) | ( 1 << ADPS1 ) ); // ADC enable and clock divide 8MHz by 64 for 125khz sample rate  
    DIDR0 |= ( 1 << ADC3D ) | ( 1 << ADC2D ); // disable digital input on analog input channel to conserve power

    for (;;){

        // setup ADC3 (pin 2)
        ADMUX = ( ( 1 << ADLAR ) | ( 1 << MUX1 ) | ( 1 << MUX0 ) );

        // read pot
        ADCSRA |= ( 1 << ADSC );   // start the ADC Conversion  
        while( ADCSRA & ( 1 << ADSC ));  // wait for the conversion to be complete  

        h = ADCH;

        // setup ADC1 (pin 7)
        ADMUX = ( ( 1 << ADLAR ) | ( 1 << MUX0 ) );

        // read pot
        ADCSRA |= ( 1 << ADSC );   // start the ADC Conversion  
        while( ADCSRA & ( 1 << ADSC ));  // wait for the conversion to be complete  

        l = ADCH;

        if (l>10){

            H = (float)(h*360.0/255.0);
            S = 1.0;
            L = (float)(l/255.0);

            HLSToRGB (H, L, S, &R, &G, &B);

            r = (uint8_t)(R*255.0);
            g = (uint8_t)(G*255.0);
            b = (uint8_t)(B*255.0);

            setColour(r, g, b);

            count = 0;
        }
        else {
           count++;
           if (count > 200){
               fadeColour(getRandom255(), getRandom255(), getRandom255(), 1000);
               count = 0;
           }
        }

        _delay_ms(50);
    }

    return (0);
}
