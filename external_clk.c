/****************************************************************************** 
 *
 * This is a practice firmware to try timers/counters.
 *
 * This firmware use timer 0 to generate a 100Khz square wave and use this as 
 * the external clock source for timer 1. 
 * 
 * The 100khz output from OC0A (pin 6) needs to connect to T1 of timer 1 (pin5)
 * If oscilloscope is available to monitor the signals. One probe could be 
 * hooked to both pin 5 and 6, another probe could be hooked to pin 9, which
 * is the output of timer1's OC1A. 
 *
 * License: CC BY-SA 4.0
 * Author:  Dapeng Zhang
 * 
 ******************************************************************************/

#include <avr/io.h>
void init_timer0(void);
void init_timer1(void);
int main(void)
{
	init_timer0();
	init_timer1();
	while(1){
	
	}
	return 0;  // never reached
}
void init_timer0(void)
{
	// Set to CTC mode, WGM02:0 = 2
	TCCR0A |= (0b10 << WGM00);  // set the 1:0 bit of TCCR1A

	// Set OC0A to toggle mode, COM0A1:0 = 1 
	TCCR0A |= (0b01 << COM0A0); 
	// OCR0A determined the count top here, also the resolution, ref the datasheet
	// if OC0B output is wanted, the OCR0B number should be no larger than OCR0A
	// then, OCR0B get the chance to be equal to TCNT, and get OC0B flipped. 
	OCR0A = 79; 	// set top for the timer

	// Set output for OC0A, digital pin 6 of arduino
	DDRD |= (1 << PD6);

	// Set no prescalar and start counter
	TCCR0B |= (1 << CS00);	
}	
void init_timer1(void)
{
	// Set to CTC mode
	TCCR1B |= (1 << WGM12);
	TCCR1A |= (0b01 << COM1A0);

	OCR1A = 0x04;	// 2*N*(1+OCR2A), get 10Khz
	
	DDRB |= (1 << PB1); 	// set output for OC1A, digital pin 9 of arduino

	// Set exteral clock source on T1 pin and start counter
	TCCR1B |= (0b111 << CS10); 	// T1 is PD5, digital pin 5 of arduino
}
