#include "ds1307.h"
#include "i2c_master.h"
#ifdef CONSOLE_ENABLE
  #include <print.h>
#endif

void ds1307_set_time(uint8_t y, uint8_t mo, uint8_t d, uint8_t h, uint8_t m, uint8_t s) {
    uint8_t data[] = {
        ((s % 10) | ((s / 10) << 4)) & 0x7F,
        ((m % 10) | ((m / 10) << 4)) & 0x7F,
        ((h % 10) | ((h / 10) << 4)) & 0x3F,
		0x00,
        ((d % 10) | ((d / 10) << 4)) & 0x3F,
        ((mo % 10) | ((mo / 10) << 4)) & 0x3F,
        ((y % 10) | ((y / 10) << 4)) & 0x7F
    }; // 24-hour mode
    i2c_writeReg(DS1307_ADDR, 0, data, 7, 100);
}

void ds1307_get_time(uint8_t *y, uint8_t *mo, uint8_t *d, uint8_t *h, uint8_t *m, uint8_t *s) {

    uint8_t data[7];
    i2c_status_t ret = i2c_readReg(DS1307_ADDR, 0, data, 7, 200);
    if (ret == I2C_STATUS_SUCCESS) {
    }
    uprintf("OK\n");    
    if (ret == I2C_STATUS_TIMEOUT) {
    }
    if (ret == I2C_STATUS_ERROR) {
    }
    i2c_stop();
    *s = (data[0] & 0b1111) + ((data[0] & 0b1110000) >> 4) * 10;
    *m = (data[1] & 0b1111) + ((data[1] & 0b1110000) >> 4) * 10;
    *h = (data[2] & 0b1111) + ((data[2] & 0b0110000) >> 4) * 10;
    *d = (data[4] & 0b1111) + ((data[4] & 0b1110000) >> 4) * 10;
    *mo = (data[5] & 0b1111) + ((data[5] & 0b0110000) >> 4) * 10;
    *y = (data[6] & 0b1111) + ((data[6] & 0b0110000) >> 4) * 10;
}
