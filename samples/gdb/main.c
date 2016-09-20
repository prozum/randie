#include <avr/io.h>
#include <avr/interrupt.h>
#include "avr8-stub.h"

int cnt = 0;
int function(int a);

int main(void)
{
    debug_init();
    DDRB |= _BV(5);	// Pin PB5 to output (LED)
    sei();			// Enable interrupts
    breakpoint();

    while(1)
    {
    	PORTB |= _BV(5);	// LED on
    	cnt++;
    	cnt = function(cnt);
    	PORTB &= ~_BV(5);	// LED off
    	cnt++;
    }
    return 0;
}

int function(int a)
{
	int n;
	n = 2*a;
	return n;
}

