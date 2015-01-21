#ifndef __AUDIO_H__
#define __AUDIO_H__

// Feel free to experiment with those
#define FUNDAMENTAL_PITCH (440.0) // A.K.A. C4
#define SAMPLE_RATE (64000)
#define FINE_TUNE (1.06)
#define BREATH_LEN (20)	// Pause between notes in milliseconds

typedef struct {
	uint16_t length;	// Lenght of note in milliseconds
	uint8_t tone;		// Note index on the note_periodds array
	uint8_t effect;		// Can be used to apply effects on notes
} Note;

enum {
	C0, Cs0, D0, Ds0, E0, F0, Fs0, G0, Gs0, A0, As0, B0,
	C1, Cs1, D1, Ds1, E1, F1, Fs1, G1, Gs1, A1, As1, B1,
	C2, Cs2, D2, Ds2, E2, F2, Fs2, G2, Gs2, A2, As2, B2,
	C3, Cs3, D3, Ds3, E3, F3, Fs3, G3, Gs3, A3, As3, B3,
	C4, Cs4, D4, Ds4, E4, F4, Fs4, G4, Gs4, A4, As4, B4,
	C5, Cs5, D5, Ds5, E5, F5, Fs5, G5, Gs5, A5, As5, B5,
	C6, Cs6, D6, Ds6, E6, F6, Fs6, G6, Gs6, A6, As6, B6,
	C7, Cs7, D7, Ds7, E7, F7, Fs7, G7, Gs7, A7, As7, B7,
	REST
};

// Don't touch unless you are me!
#define TONE_RATIO (1.0594630943592953) // 2^(1/2)
#define C0_BASE_FREQ (FUNDAMENTAL_PITCH*0.033108221698727895) // (2^(1/12))^57

// Half the period of each tone (in ticks)
uint16_t tone_periods[REST];

#endif
