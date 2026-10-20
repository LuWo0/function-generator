#ifndef WAVEFORM_H
#define WAVEFORM_H

#include <stdint.h>

#define TABLE_LEN 	300

// DAC codes given by:
// D = V / 3.3 * 4096

#define LOW_CODE 	0 // 0 / 3.3 * 4096 = 0
#define MID_CODE 	1861  // 1500 / 3.3 * 4096 = ~1861
#define HIGH_CODE 	3722 // 3000 / 3.3 * 4096 = ~3722


typedef enum {
	SQUARE,
	TRIANGLE,
	SAWTOOTH,
	SINE
} wave_state;

typedef struct {
	wave_state shape;
	uint8_t duty;
	volatile uint8_t step;
	uint16_t index;
	const uint16_t *volatile active;

} Waveform;

void Waveform_Init(void);
uint16_t next_sample(void);
void set_frequency(uint16_t hz);
void set_shape(wave_state shape);
void change_duty(uint8_t delta);
void reset_duty(void);


#endif // WAVEFORM_H
