#include <avr/io.h>
#include <avr/interrupt.h>

#include "audio.h"

Note tune[] = {
	{150,	E5,	1},
	{150,	E5,	1},
	{150,	REST,	1},
	{150,	E5,	1},

	{150,	REST,	1},
	{150,	C5,	0},
	{150,	E5,	1},
	{150,	REST,	1},

	{150,	G5,	0},
	{3*150,	REST,	1},

	{2*150,	G4,	0},
	{2*150,	REST,	1},

	{3000,	REST,	1}
};

int main(void) {
	DDRD = 0xFF;		// Set up port D as output

	TCCR0A |= _BV(WGM01);	// Set timer0 mode to CTC
	TCCR0B |= _BV(CS00);	// Set prescaler to 1
	TIMSK0 |= _BV(OCIE0A);	// Enable interrupt on OCR0A match

	// Fire an interrupt at ~40KHz
	OCR0A = FINE_TUNE * (F_CPU/SAMPLE_RATE);

	//Pre-calculating the period of each note
	float freq = C0_BASE_FREQ;
	for(uint8_t tone = 0; tone < REST; ++tone) {
		tone_periods[tone] = (SAMPLE_RATE/2)/freq; 
		freq *= TONE_RATIO;
	}

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
		if(len >= tune[mc].length) {
			len = 0;
			++mc;
			if(mc == sizeof(tune)/sizeof(Note)) mc = 0;
		}
	}

	// Now generate the next sample
	if(wave_tick >= tone_periods[tune[mc].tone] &&
	   len > BREATH_LEN && tune[mc].tone < REST) {
		sample = ~sample;
		wave_tick = 0;
	}
	
	++len_tick;
	++wave_tick;
}
