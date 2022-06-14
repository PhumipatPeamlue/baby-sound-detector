#include <avr/io.h>
#define SOUND_DETECTED() ((PINC & (1<<PC1)) != 0)

void init_peri();
void set_led(uint8_t pin, uint8_t state);
uint16_t read_adc(uint8_t channel);
