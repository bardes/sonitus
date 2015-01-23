#ifndef __AUDIO_H__
#define __AUDIO_H__

// Feel free to experiment with those
#define SAMPLE_RATE (64000)
#define FINE_TUNE (1.06)	// Used to tune the clock variation
#define BREATH_LEN (20)		// Pause between notes in milliseconds

typedef struct {
	uint8_t tone;		// Note index on the note_periodds array
	uint16_t length;	// Lenght of note in milliseconds
	uint8_t effect;		// Can be used to apply effects on notes
} Note;

// Let's make some human friendly names to the notes
// Can't use '#' to denote sharps (damn you, pre processor!)
// gotta use 's' instead
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

enum {
	Db0 = Cs0, Eb0 = Ds0, Gb0 = Fs0, Ab0 = Gs0, Bb0 = As0,
	Db1 = Cs1, Eb1 = Ds1, Gb1 = Fs1, Ab1 = Gs1, Bb1 = As1,
	Db2 = Cs2, Eb2 = Ds2, Gb2 = Fs2, Ab2 = Gs2, Bb2 = As2,
	Db3 = Cs3, Eb3 = Ds3, Gb3 = Fs3, Ab3 = Gs3, Bb3 = As3,
	Db4 = Cs4, Eb4 = Ds4, Gb4 = Fs4, Ab4 = Gs4, Bb4 = As4,
	Db5 = Cs5, Eb5 = Ds5, Gb5 = Fs5, Ab5 = Gs5, Bb5 = As5,
	Db6 = Cs6, Eb6 = Ds6, Gb6 = Fs6, Ab6 = Gs6, Bb6 = As6,
	Db7 = Cs7, Eb7 = Ds7, Gb7 = Fs7, Ab7 = Gs7, Bb7 = As7	
};

// Half the period of each tone (in ticks)
uint16_t tone_periods[96] = {
	1957, 1847, 1743, 1646, 1553, 1466, 1384, 1306, 1233, 1164, 1098, 1037, 
	978, 924, 872, 823, 777, 733, 692, 653, 616, 582, 549, 518, 
	489, 462, 436, 411, 388, 367, 346, 327, 308, 291, 275, 259, 
	245, 231, 218, 206, 194, 183, 173, 163, 154, 145, 137, 130, 
	122, 115, 109, 103, 97, 92, 86, 82, 77, 73, 69, 65, 
	61, 58, 54, 51, 49, 46, 43, 41, 39, 36, 34, 32, 
	31, 29, 27, 26, 24, 23, 22, 20, 19, 18, 17, 16, 
	15, 14, 14, 13, 12, 11, 11, 10, 10, 9, 9, 8 
};

#endif
