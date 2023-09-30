#include "ht16k33.h"
#include "i2c_master.h"

#define HT16K33_DDAP          0x00 // Display data address pointer: 0000xxxx
#define HT16K33_SS            0x20 // System setup register
#define HT16K33_SS_STANDBY    0x00 // System setup - oscillator in standby mode
#define HT16K33_SS_NORMAL     0x01 // System setup - oscillator in normal mode
#define HT16K33_KDAP          0x40 // Key Address Data Pointer
#define HT16K33_IFAP          0x50 // Read status of INT flag
#define HT16K33_DSP           0x80 // Display setup
#define HT16K33_DSP_OFF       0x00 // Display setup - display off
#define HT16K33_DSP_ON        0x01 // Display setup - display on
#define HT16K33_DSP_NOBLINK   0x00 // Display setup - no blink
#define HT16K33_DSP_BLINK2HZ  0x02 // Display setup - 2hz blink
#define HT16K33_DSP_BLINK1HZ  0x04 // Display setup - 1hz blink
#define HT16K33_DSP_BLINK05HZ 0x06 // Display setup - 0.5hz blink
#define HT16K33_RIS           0xA0 // ROW/INT Set
#define HT16K33_RIS_OUT       0x00 // Set INT as row driver output
#define HT16K33_RIS_INTL      0x01 // Set INT as int active low
#define HT16K33_RIS_INTH      0x03 // Set INT as int active high
#define HT16K33_DIM           0xE0 // Dimming set
#define HT16K33_DIM_1         0x00 // Dimming set - 1/16
#define HT16K33_DIM_2         0x01 // Dimming set - 2/16
#define HT16K33_DIM_3         0x02 // Dimming set - 3/16
#define HT16K33_DIM_4         0x03 // Dimming set - 4/16
#define HT16K33_DIM_5         0x04 // Dimming set - 5/16
#define HT16K33_DIM_6         0x05 // Dimming set - 6/16
#define HT16K33_DIM_7         0x06 // Dimming set - 7/16
#define HT16K33_DIM_8         0x07 // Dimming set - 8/16
#define HT16K33_DIM_9         0x08 // Dimming set - 9/16
#define HT16K33_DIM_10        0x09 // Dimming set - 10/16
#define HT16K33_DIM_11        0x0A // Dimming set - 11/16
#define HT16K33_DIM_12        0x0B // Dimming set - 12/16
#define HT16K33_DIM_13        0x0C // Dimming set - 13/16
#define HT16K33_DIM_14        0x0D // Dimming set - 14/16
#define HT16K33_DIM_15        0x0E // Dimming set - 15/16
#define HT16K33_DIM_16        0x0F // Dimming set - 16/16

#define SEGA      0x01
#define SEGB      0x02
#define SEGC      0x04
#define SEGD      0x08
#define SEGE      0x10
#define SEGF      0x20
#define SEGG      0x40
#define SEGDP     0x80

#define NLEDS   0x08       // Number of Digit

void ht16k33_init(void) {
    uint8_t data;
	uint8_t addr;
	uint8_t reg;
		
	data = HT16K33_SS | HT16K33_SS_NORMAL;// Wakeup
    i2c_transmit(HT16K33_ADDR, &data, 1, 100);

	// Clear all memory
	data = 0;
	for(addr=0;addr<16;addr++) {
    	reg = HT16K33_DDAP | addr;
  		i2c_writeReg(HT16K33_ADDR, reg, &data, 1, 100);
	}

	data = HT16K33_DSP | HT16K33_DSP_ON | HT16K33_DSP_NOBLINK;// Display on and no blinking
    i2c_transmit(HT16K33_ADDR, &data, 1, 100);

	data = HT16K33_RIS | HT16K33_RIS_OUT;// INT pin works as row output 
    i2c_transmit(HT16K33_ADDR, &data, 1, 100);

}

void ht16k33_7seg(uint8_t digit, uint8_t display) {
  uint8_t pattern[] = {
    SEGA+SEGB+SEGC+SEGD+SEGE+SEGF,		// 0
    SEGB+SEGC,							// 1
    SEGA+SEGB+SEGD+SEGE+SEGG,			// 2
    SEGA+SEGB+SEGC+SEGD+SEGG,			// 3
    SEGB+SEGC+SEGF+SEGG,				// 4
    SEGA+SEGC+SEGD+SEGF+SEGG,			// 5
    SEGA+SEGC+SEGD+SEGE+SEGF+SEGG,		// 6
    SEGA+SEGB+SEGC,						// 7
    SEGA+SEGB+SEGC+SEGD+SEGE+SEGF+SEGG,	// 8
    SEGA+SEGB+SEGC+SEGD+SEGF+SEGG,		// 9
    SEGG,								// -
    SEGB+SEGC+SEGE+SEGF+SEGG,			// H
    SEGA+SEGD+SEGE+SEGF+SEGG,			// E
    SEGD+SEGE+SEGF,						// L
    SEGA+SEGB+SEGE+SEGF+SEGG,			// P
    SEGDP,								// DP
    0									// Space
  };

  uint8_t addr;
  if (display > 15) return;
  uint8_t data = pattern[display];
  if (digit < 4) {
    addr = digit * 2;
  } else {
    addr = (digit-4) * 2 + 1;
  }
  
//  printf("display=%d addr=%d data=%02x\n",display,addr,data);
  uint8_t reg = HT16K33_DDAP | addr;
  i2c_writeReg(HT16K33_ADDR, reg, &data, 1, 100);
}