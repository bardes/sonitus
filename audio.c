#include <avr/io.h>
#include <avr/interrupt.h>

// Feel free to experiment with those
#define FUNDAMENTAL_PITCH (440.0) // A.K.A. C4
#define SAMPLE_RATE (64000)
#define FINE_TUNE (1.06)
#define BREATH_LEN (20)	// Pause between notes in milliseconds

// Don't touch unless you are me!
#define TONE_RATIO (1.0594630943592953) // 2^(1/2)
#define C0_BASE_FREQ (FUNDAMENTAL_PITCH*0.033108221698727895) // (2^(1/12))^57
#define N_TONES (96)
uint16_t note_periods[N_TONES];

typedef struct {
	uint16_t length;	// Lenght of note in milliseconds
	uint8_t code;		// Note index on the note_periodds array
	uint8_t effect;		// Can be used to apply effects on notes
} note;

note tune[] = {
	{150, 63, 1},	// E4
	{150, 63, 1},	// E4
	{150, 96, 1},	// Pause
	{150, 63, 1},	// E4

	{150, 96, 1},	// Pause
	{150, 59, 0},	// C4
	{150, 63, 1},	// E4
	{150, 96, 1},	// Pause

	{150, 66, 0},	// G4
	{3*150, 96, 1},	// Pause

	{2*150, 54, 0},	// G3
	{2*150, 96, 1},	// Pause

	{3000, 96, 1}	// Pause 3s
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
	for(uint8_t note = 0; note < N_TONES; ++note) {
		note_periods[note] = (SAMPLE_RATE/2)/freq; 
		freq *= TONE_RATIO;
	}


	sei();				// Enable interrupts globally
	
	while(1);
	return 0;
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
			if(mc == sizeof(tune)/sizeof(note)) mc = 0;
		}
	}

	// Now generate the next sample
	if(wave_tick >= note_periods[tune[mc].code] &&
	   len > BREATH_LEN && tune[mc].code < N_TONES) {
		sample = ~sample;
		wave_tick = 0;
	}
	
	++len_tick;
	++wave_tick;
}
