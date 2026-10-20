#include "waveform.h"

static uint16_t square[TABLE_LEN]; // not const because change in duty cycle will rewrite it
static const uint16_t triangle[TABLE_LEN];
static const uint16_t sawtooth[TABLE_LEN];
static const uint16_t sine[TABLE_LEN];
static const uint16_t *tables[4] = {sqaure, triangle, sawtooth, sine};
