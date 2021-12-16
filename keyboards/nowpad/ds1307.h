#pragma once

#include <stdint.h>

void ds1307_set_time(uint8_t y, uint8_t mo, uint8_t d, uint8_t h, uint8_t m, uint8_t s);
void ds1307_get_time(uint8_t *y, uint8_t *mo, uint8_t *d, uint8_t *h, uint8_t *m, uint8_t *s);