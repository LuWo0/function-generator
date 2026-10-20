#ifndef DAC_H
#define DAC_H
#include "main.h"
#include <stdint.h>

#define DAC_VREF_MV 3300
#define DAC_CS_PORT GPIOB
#define DAC_CS_PIN  GPIO_PIN_6
#define DAC_CODE_MAX 4095
void DAC_init(void);
void DAC_write(uint16_t code12);
uint16_t DAC_volt_conv(uint16_t mv);

#endif /* DAC_H */
