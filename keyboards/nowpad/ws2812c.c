#include "ws2812c.h"
#include "rgblight.h"

#ifdef CONSOLE_ENABLE
  #include <print.h>
#endif

void Disp_0(uint8_t digit_offset){
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 0]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 1]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 2]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 16]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 17]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 18]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 32]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 33]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 34]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 48]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 49]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 50]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 64]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 65]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 66]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 80]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 81]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 82]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 96]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 97]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 98]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 112]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 113]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 114]);
}

void Disp_1(uint8_t digit_offset){
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 0]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 1]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 2]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 16]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 17]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 18]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 32]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 33]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 34]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 48]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 49]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 50]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 64]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 65]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 66]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 80]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 81]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 82]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 96]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 97]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 98]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 112]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 113]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 114]);
}

void Disp_2(uint8_t digit_offset){
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 0]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 1]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 2]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 16]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 17]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 18]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 32]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 33]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 34]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 48]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 49]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 50]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 64]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 65]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 66]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 80]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 81]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 82]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 96]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 97]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 98]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 112]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 113]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 114]);
}

void Disp_3(uint8_t digit_offset){
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 0]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 1]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 2]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 16]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 17]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 18]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 32]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 33]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 34]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 48]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 49]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 50]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 64]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 65]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 66]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 80]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 81]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 82]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 96]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 97]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 98]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 112]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 113]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 114]);
}

void Disp_4(uint8_t digit_offset){
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 0]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 1]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 2]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 16]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 17]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 18]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 32]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 33]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 34]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 48]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 49]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 50]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 64]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 65]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 66]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 80]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 81]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 82]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 96]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 97]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 98]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 112]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 113]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 114]);
}

void Disp_5(uint8_t digit_offset){
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 0]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 1]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 2]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 16]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 17]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 18]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 32]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 33]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 34]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 48]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 49]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 50]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 64]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 65]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 66]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 80]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 81]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 82]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 96]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 97]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 98]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 112]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 113]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 114]);
}

void Disp_6(uint8_t digit_offset){
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 0]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 1]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 2]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 16]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 17]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 18]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 32]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 33]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 34]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 48]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 49]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 50]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 64]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 65]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 66]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 80]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 81]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 82]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 96]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 97]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 98]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 112]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 113]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 114]);
}

void Disp_7(uint8_t digit_offset){
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 0]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 1]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 2]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 16]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 17]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 18]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 32]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 33]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 34]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 48]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 49]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 50]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 64]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 65]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 66]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 80]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 81]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 82]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 96]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 97]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 98]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 112]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 113]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 114]);
}

void Disp_8(uint8_t digit_offset){
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 0]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 1]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 2]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 16]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 17]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 18]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 32]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 33]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 34]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 48]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 49]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 50]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 64]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 65]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 66]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 80]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 81]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 82]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 96]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 97]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 98]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 112]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 113]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 114]);
}

void Disp_9(uint8_t digit_offset){
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 0]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 1]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 2]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 16]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 17]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 18]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 32]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 33]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 34]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 48]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 49]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 50]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 64]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 65]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 66]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 80]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 81]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 82]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 96]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 97]);
	sethsv(85, 255, 255, (LED_TYPE *)&led[digit_offset + 98]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 112]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 113]);
	sethsv(0, 0, 0, (LED_TYPE *)&led[digit_offset + 114]);
}

void Disp_DP_time(){
sethsv(0, 0, 0, (LED_TYPE *)&led[7]);
sethsv(0, 0, 0, (LED_TYPE *)&led[8]);
sethsv(0, 0, 0, (LED_TYPE *)&led[23]);
sethsv(0, 0, 0, (LED_TYPE *)&led[24]);
sethsv(0, 0, 0, (LED_TYPE *)&led[39]);
sethsv(0, 0, 255, (LED_TYPE *)&led[40]);
sethsv(0, 0, 0, (LED_TYPE *)&led[55]);
sethsv(0, 0, 255, (LED_TYPE *)&led[56]);
sethsv(0, 0, 255, (LED_TYPE *)&led[71]);
sethsv(0, 0, 0, (LED_TYPE *)&led[72]);
sethsv(0, 0, 255, (LED_TYPE *)&led[87]);
sethsv(0, 0, 0, (LED_TYPE *)&led[88]);
sethsv(0, 0, 0, (LED_TYPE *)&led[103]);
sethsv(0, 0, 0, (LED_TYPE *)&led[104]);
sethsv(0, 0, 0, (LED_TYPE *)&led[119]);
sethsv(0, 0, 0, (LED_TYPE *)&led[120]);

}
	
void Disp_background(uint8_t b_h, uint8_t b_s, uint8_t b_v){
	uint8_t i;
	for(i = 0; i < RGBLED_NUM; i++){
		sethsv(b_h, b_s, b_v, (LED_TYPE *)&led[i]);
	}
}	
