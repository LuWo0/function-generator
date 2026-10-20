#include "waveform.h"

static uint16_t square[TABLE_LEN]; // not const because change in duty cycle will rewrite it
static const uint16_t triangle[TABLE_LEN];
static const uint16_t sawtooth[TABLE_LEN];

static const uint16_t sine[TABLE_LEN] = { 1861, 1900, 1939, 1978, 2017, 2056,
		2094, 2133, 2171, 2210, 2248, 2286, 2324, 2361, 2399, 2436, 2473, 2510,
		2546, 2582, 2618, 2653, 2688, 2723, 2758, 2792, 2825, 2858, 2891, 2923,
		2955, 2986, 3017, 3047, 3077, 3106, 3135, 3163, 3191, 3218, 3244, 3270,
		3295, 3319, 3343, 3367, 3389, 3411, 3432, 3453, 3473, 3492, 3510, 3528,
		3545, 3561, 3577, 3591, 3605, 3618, 3631, 3643, 3653, 3664, 3673, 3681,
		3689, 3696, 3702, 3707, 3712, 3715, 3718, 3720, 3722, 3722, 3722, 3720,
		3718, 3715, 3712, 3707, 3702, 3696, 3689, 3681, 3673, 3664, 3653, 3643,
		3631, 3618, 3605, 3591, 3577, 3561, 3545, 3528, 3510, 3492, 3473, 3453,
		3432, 3411, 3389, 3367, 3343, 3319, 3295, 3270, 3244, 3218, 3191, 3163,
		3135, 3106, 3077, 3047, 3017, 2986, 2955, 2923, 2891, 2858, 2825, 2792,
		2758, 2723, 2688, 2653, 2618, 2582, 2546, 2510, 2473, 2436, 2399, 2361,
		2324, 2286, 2248, 2210, 2171, 2133, 2094, 2056, 2017, 1978, 1939, 1900,
		1861, 1822, 1783, 1744, 1705, 1666, 1628, 1589, 1551, 1512, 1474, 1436,
		1398, 1361, 1323, 1286, 1249, 1212, 1176, 1140, 1104, 1069, 1034, 999,
		964, 931, 897, 864, 831, 799, 767, 736, 705, 675, 645, 616, 587, 559,
		531, 504, 478, 452, 427, 403, 379, 355, 333, 311, 290, 269, 249, 230,
		212, 194, 177, 161, 145, 131, 117, 104, 91, 79, 69, 58, 49, 41, 33, 26,
		20, 15, 10, 7, 4, 2, 0, 0, 0, 2, 4, 7, 10, 15, 20, 26, 33, 41, 49, 58,
		69, 79, 91, 104, 117, 131, 145, 161, 177, 194, 212, 230, 249, 269, 290,
		311, 333, 355, 379, 403, 427, 452, 478, 504, 531, 559, 587, 616, 645,
		675, 705, 736, 767, 799, 831, 864, 897, 931, 964, 999, 1034, 1069, 1104,
		1140, 1176, 1212, 1249, 1286, 1323, 1361, 1398, 1436, 1474, 1512, 1551,
		1589, 1628, 1666, 1705, 1744, 1783, 1822 };

static const uint16_t *tables[4] = { square, triangle, sawtooth, sine };

static Waveform wave = { .shape = SQUARE, .duty = 50, .step = 1, .index = 0,
		.active = square };

void Waveform_Init(void) {

	// Triangle:
	for (int16_t i = 0; i < TABLE_LEN / 2; i++) {
		triangle[i] = HIGH_CODE * i / (TABLE_LEN / 2);
	}
	for (int16_t i = TABLE_LEN / 2; i < TABLE_LEN; i++) {
		triangle[i] = HIGH_CODE * (TABLE_LEN - i) / (TABLE_LEN / 2);
	}

	// Sawtooth:
	for (int16_t i = 0; i < TABLE_LEN; i++) {
		sawtooth[i] = HIGH_CODE * i / (TABLE_LEN - 1);
	}

}
uint16_t next_sample(void) {
	const uint16_t *table = wave.active;
	uint16_t idx = wave.index;
	uint16_t code = table[idx];

	idx += wave.step;
	if (idx >= TABLE_LEN) {
		i -= TABLE_LEN;
	}
	wave.index = idx;
	return code;
}

void set_frequency(uint16_t hz) {
	wave.step = hz / 100;
}

void set_shape(wave_state shape) {
	wave.shape = shape;
	wave.active = shape;
}

void change_duty(int8_t delta) {
	if (wave.shape != SQUARE)
		return;
	wave.duty = CLAMP(wave.duty + delta, 10, 90);
	// TODO: rebuild square
}
void reset_duty(void) {
	if (wave.shape != SQUARE)
		return;
	wave.duty = 50;
	// TODO: rebuild_square
}
