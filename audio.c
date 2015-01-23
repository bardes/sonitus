#include <avr/io.h>
#include <avr/interrupt.h>

#include "audio.h"
#include "mario_tune.h"

int main(void) {
	DDRD = 0xFF;		// Set up port D as output

	TCCR0A |= _BV(WGM01);	// Set timer0 mode to CTC
	TCCR0B |= _BV(CS00);	// Set prescaler to 1
	TIMSK0 |= _BV(OCIE0A);	// Enable interrupt on OCR0A match

	// Fire an interrupt at ~40KHz
	OCR0A = FINE_TUNE * (F_CPU/SAMPLE_RATE);

	sei();			// Enable interrupts globally
	while(1);		// Tail spin :p
	return 0;		// Good luck whith that
}

ISR(TIMER0_COMPA_vect) {
	static uint16_t mc; 		// Music counter (like program counter)
	static uint16_t wave_tick;	// Tick counter to modulate waveform
	static uint8_t len_tick;	// Tick counter to measure note length
	static uint16_t len;		// Current length of the note (in ms)
	static uint8_t sample;		// Sample "buffer"

	// First of all: output the sample ASAP
	PORTD = sample;

	// Run this every ms
	if(len_tick == SAMPLE_RATE/1000) {
		++len;		// Update the elapsed time
		len_tick = 0;	// Reset the len_tick counter

		// Check if it's time to move to the next note
		if(len >= mario_tune[mc].length) {
			len = 0;
			++mc;
			if(mc == sizeof(mario_tune)/sizeof(Note)) mc = 0;
		}
	}

	// Now generate the next sample
	if(wave_tick >= tone_periods[mario_tune[mc].tone] &&
	   len > BREATH_LEN && mario_tune[mc].tone < REST) {
		sample = ~sample;
		wave_tick = 0;
	}
	
	++len_tick;
	++wave_tick;
}
