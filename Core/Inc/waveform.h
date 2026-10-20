#ifndef WAVEFORM_H
#define WAVEFORM_H

#define TABLE_LEN 	300

// DAC codes given by:
// D = V / 3.3 * 4096

#define LOW_CODE 	0 // 0 / 3.3 * 4096 = 0
#define MID_CODE 	1861  // 1500 / 3.3 * 4096 = ~1861
#define HIGH_CODE 	3722 // 3000 / 3.3 * 4096 = ~3722

#define WAVE_SQUARE 	0
#define WAVE_TRIANGLE 	1
#define WAVE_SAWTOOTH	3
#define WAVE_SINE		4

static uint16_t square[TABLE_LEN]; // not const because change in duty cycle will rewrite it
static const uint16_t triangle[TABLE_LEN];
static const uint16_t sawtooth[TABLE_LEN];
static const uint16_t sine[TABLE_LEN];
static const uint16_t *tables[4] = {sqaure, triangle, sawtooth, sine};




#endif // WAVEFORM_H
