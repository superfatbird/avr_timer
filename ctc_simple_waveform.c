/****************************************************************************** 
 *
 * This is a practice firmware to try timers/counters.
 *
 * This firmware is used to generate waveforms from the two output compare unit
 * of timer 0 in an ATMega328p/Arduino. The timer is set to CTC mode as section
 * 14.7.2 of ATMega328's datasheet indicates. 
 *
 * Reference Figure 14-1. 8-bit Timer/Counter Block diagram and the first sen-
 * tence in 14.7.2: In CTC mode, the OCR0A reg is used to manipulate the
 * counter resolution. That means the number in OCR0A determines the frequency
 * of the output waveform.
 * 
 * If output from OC0B is wanted, the number in OCR0B should be no larger than
 * the one in OCR0A, otherwise the counter will be reset when count to the
 * number of OCR0A and will never count to the one in OCR0B.  
 *
 * In this firmware, the prescaler was set to 1 and OCR0A was set to 79, OCR0B
 * was set to 39. Two 100Khz waveform will be output from OC0A and OC0B 
 * seperately with same frequency (determined by OCR0A) and a phase difference.
 * 
 * License: CC BY-SA 4.0
 * Author:  Dapeng Zhang
 * 
 ******************************************************************************/

#include <avr/io.h>
void init_timer0(void);
int main(void)
{
	init_timer0();
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

	// Set OC0B to toggle mode, COM0B1:0 = 1 
	TCCR0A |= (0b01 << COM0B0); 
	// Set pulse period and width count number
	OCR0B = 39; 	// set the number in this reg to compare to TCNT, equal means action

	// Set output for OC0A, digital pin 6 of arduino
	DDRD |= (1 << PD6);
	// Set output for OC0B, digital pin 5 of arduino
	DDRD |= (1 << PD5);

	// Set no prescalar and start counter
	TCCR0B |= (1 << CS00);	
}	
