/* Copyright 2021 unreal <ilovesony1@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "ds1307.h"
#include "ws2812c.h"

// Defines the keycodes used by our macros in process_record_user
enum layer_names {
    _LAYER_1,
    _LAYER_2,
    _LAYER_3,
    _LAYER_4
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  LAYER_1 = SAFE_RANGE,
  LAYER_2,
  LAYER_3,
  LAYER_4,
  KC_TIME
};

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _LAYER_1));
    rgblight_set_layer_state(1, layer_state_cmp(state, _LAYER_2));
    rgblight_set_layer_state(2, layer_state_cmp(state, _LAYER_3));
    rgblight_set_layer_state(3, layer_state_cmp(state, _LAYER_4));
    return state;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* _LAYER_1
 *|---------------|
 *|NXT|MTW|M_P|PLY|
 *|---+---+---+---|
 *|7  |8  |9  |LT(|
 *|---+---+---|_L2|
 *|4  |5  |6  |,BS|
 *|---+---+---+---|
 *|1  |2  |3  |Ent|
 *|-------+---|   |
 *|0      | . |   |
 *|---------------|
 * Encoder setting
 *|---------------|
 *|VA-|VA+|Vo-|Vo+|
 *|---+---+---+---|
 */
[_LAYER_1] = LAYOUT( \
    KC_MNXT,  RGB_M_TW, RGB_M_P,  KC_MPLY,
    KC_7,     KC_8,     KC_9,     LT(_LAYER_2,KC_BSPC),
    KC_4,     KC_5,     KC_6,
    KC_1,     KC_2,     KC_3,     KC_ENT,
    KC_0,     KC_DOT,
    RGB_VAD,  RGB_VAI,  KC_VOLD,  KC_VOLU
),
/* _LAYER_2
 *|---------------|
 *|F24| / | * | - |
 *|---+---+---+---|
 *|HOM|UP |PGU| + |
 *|---+---+---|   |
 *|LET|DWN|RHT|   |
 *|---+---+---+---|
 *|END|   |PGD|Ent|
 *|-------+---|   |
 *|       |DEL|   |
 *|---------------|
 * Encoder setting 
 *|---------------|
 *|   |   |   |   |
 *|---+---+---+---|
 * 
 *  F24 key is used to set the time.
 *  After pressing F24, please enter the 8 numbers in the following order
 *  
 *  year XX -> month XX -> day XX -> hours XX -> minutes XX -> seconds XX
 *   
 *  Time is displayed in 24-hour format.
*/

[_LAYER_2] = LAYOUT( \
    KC_F24,    KC_PSLS,   KC_PAST,   KC_PMNS,
    KC_HOME,   KC_UP,     KC_PGUP,   KC_PPLS,
    KC_LEFT,   KC_DOWN,   KC_RGHT,
    KC_END,    XXXXXXX,   KC_PGDN,   KC_ENT,
    XXXXXXX,   KC_DEL,
    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX
),

[_LAYER_3] = LAYOUT( \
    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
    XXXXXXX,   XXXXXXX,   XXXXXXX,
    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
    XXXXXXX,   XXXXXXX,
    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX
),

[_LAYER_4] = LAYOUT( \
    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
    XXXXXXX,   XXXXXXX,   XXXXXXX,
    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,
    XXXXXXX,   XXXXXXX,
    XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX
)
};

keyevent_t encoder1_ccw = {
    .key = (keypos_t){.row = 5, .col = 2},
    .pressed = false
};

keyevent_t encoder1_cw = {
    .key = (keypos_t){.row = 5, .col = 3},
    .pressed = false
};

keyevent_t encoder2_ccw = {
    .key = (keypos_t){.row = 5, .col = 0},
    .pressed = false
};

keyevent_t encoder2_cw = {
    .key = (keypos_t){.row = 5, .col = 1},
    .pressed = false
};


static uint8_t hours, minutes, seconds, day, month, year;
static uint8_t b_h, b_s, b_v;

static bool is_in_time_disp;
static bool is_in_set_time;
static bool is_in_effect_mode;
static uint16_t update_time;
static uint16_t last_update;

static bool toggle_pic = false;
static char new_time[12];
static uint8_t new_time_index = 0;

void keyboard_post_init_user(void) {
	//I2C initialize
	i2c_init();  // on pins D(1,0)
	// set backgraound color
	rgblight_mode(RGBLIGHT_MODE_STATIC_LIGHT);
	b_h = 0;
	b_s = 0;
	b_v = 0;
	Disp_background(b_h, b_s, b_v);
	rgblight_set(); 
	
	is_in_time_disp = true;
	is_in_set_time = false;
	is_in_effect_mode = false;
	update_time = 10000;
	last_update = 0;
}

void matrix_scan_user(void) {
	if (IS_PRESSED(encoder1_ccw)) {
		encoder1_ccw.pressed = false;
		encoder1_ccw.time = (timer_read() | 1);
		action_exec(encoder1_ccw);
	}

	if (IS_PRESSED(encoder1_cw)) {
		encoder1_cw.pressed = false;
		encoder1_cw.time = (timer_read() | 1);
		action_exec(encoder1_cw);
	}

	if (IS_PRESSED(encoder2_ccw)) {
		encoder2_ccw.pressed = false;
		encoder2_ccw.time = (timer_read() | 1);
		action_exec(encoder2_ccw);
	}

	if (IS_PRESSED(encoder2_cw)) {
		encoder2_cw.pressed = false;
		encoder2_cw.time = (timer_read() | 1);
		action_exec(encoder2_cw);
	}

	if ( (is_in_time_disp == true) && (update_time - last_update > 8000) ) {
		last_update = update_time;
		toggle_pic = false;
		
		ds1307_get_time(&year, &month, &day, &hours, &minutes, &seconds);
		uint8_t h2, h1, m1, m2;

		h2 = hours/10;
		h1 = hours-h2*10;
		m2 = minutes/10;
		m1 = minutes-m2*10;
		
		uint8_t digit_offset = 4;
		
		Disp_background(b_h, b_s, b_v);

		if(h2 == 0){
			Disp_0(0 * digit_offset);
		}
		else if(h2 == 1){
			Disp_1(0 * digit_offset);
		}
		else if(h2 == 2){
			Disp_2(0 * digit_offset);
		}
			
		if(h1 == 0){
			Disp_0(1 * digit_offset);
		}
		else if(h1 == 1){
			Disp_1(1 * digit_offset);
		}
		else if(h1 == 2){
			Disp_2(1 * digit_offset);
		}
		else if(h1 == 3){
			Disp_3(1 * digit_offset);
		}
		else if(h1 == 4){
			Disp_4(1 * digit_offset);
		}
		else if(h1 == 5){
			Disp_5(1 * digit_offset);
		}
		else if(h1 == 6){
			Disp_6(1 * digit_offset);
		}
		else if(h1 == 7){
			Disp_7(1 * digit_offset);
		}
		else if(h1 == 8){
			Disp_8(1 * digit_offset);
		}
		else if(h1 == 9){
			Disp_9(1 * digit_offset);
		}

		if(m2 == 0){
			Disp_0(2 * digit_offset + 1);
		}
		else if(m2 == 1){
			Disp_1(2 * digit_offset + 1);
		}
		else if(m2 == 2){
			Disp_2(2 * digit_offset + 1);
		}
		else if(m2 == 3){
			Disp_3(2 * digit_offset + 1);
		}
		else if(m2 == 4){
			Disp_4(2 * digit_offset + 1);
		}
		else if(m2 == 5){
			Disp_5(2 * digit_offset + 1);
		}
		else if(m2 == 6){
			Disp_6(2 * digit_offset + 1);
		}

		if(m1 == 0){
			Disp_0(3 * digit_offset + 1);
		}
		else if(m1 == 1){
			Disp_1(3 * digit_offset + 1);
		}
		else if(m1 == 2){
			Disp_2(3 * digit_offset + 1);
		}
		else if(m1 == 3){
			Disp_3(3 * digit_offset + 1);
		}
		else if(m1 == 4){
			Disp_4(3 * digit_offset + 1);
		}
		else if(m1 == 5){
			Disp_5(3 * digit_offset + 1);
		}
		else if(m1 == 6){
			Disp_6(3 * digit_offset + 1);
		}
		else if(m1 == 7){
			Disp_7(3 * digit_offset + 1);
		}
		else if(m1 == 8){
			Disp_8(3 * digit_offset + 1);
		}
		else if(m1 == 9){
			Disp_9(3 * digit_offset + 1);
		}

		Disp_DP_time(); // set DP
		rgblight_set(); 
		#ifdef CONSOLE_ENABLE
		uprintf("update_time: %u\n", hours);
		uprintf("update_time: %u\n", minutes);
		uprintf("update_time: %u\n", seconds);
		#endif
    }// if update_time end
	
    update_time = timer_read32();

}//matrix_scan_user(void) end

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_F24 && record->event.pressed) {
		is_in_effect_mode = true;
        is_in_set_time = true;
        is_in_time_disp = false;
        new_time_index = 0;
        toggle_pic = false;        
    } else if (is_in_set_time) {
        if (!record->event.pressed && keycode >= KC_1 && keycode <= KC_0) {
            new_time[new_time_index++] = (keycode == KC_0) ? 0 : keycode - KC_1 + 1;
            if (new_time_index == 12) {
                is_in_set_time = false;
                is_in_effect_mode = false;
        		is_in_time_disp = true;
                ds1307_set_time(
                        (new_time[0]) * 10 + (new_time[1]),
                        (new_time[2]) * 10 + (new_time[3]),
                        (new_time[4]) * 10 + (new_time[5]),
                        (new_time[6]) * 10 + (new_time[7]),
                        (new_time[8]) * 10 + (new_time[9]),
                        (new_time[10]) * 10 + (new_time[11])
                );
                for (int i = 0; i < 12; i++) {
                    tap_code(KC_BSPACE);
                }
                #ifdef CONSOLE_ENABLE
				uprintf("new_time[0]: %u\n", new_time[0]);
				uprintf("new_time[1]: %u\n", new_time[1]);
				uprintf("new_time[2]: %u\n", new_time[2]);
				uprintf("new_time[3]: %u\n", new_time[3]);
				uprintf("new_time[4]: %u\n", new_time[4]);
				uprintf("new_time[5]: %u\n", new_time[5]);
				uprintf("new_time[6]: %u\n", new_time[6]);
				uprintf("new_time[7]: %u\n", new_time[7]);
				uprintf("new_time[8]: %u\n", new_time[8]);
				uprintf("new_time[9]: %u\n", new_time[9]);
				uprintf("new_time[10]: %u\n", new_time[10]);
				uprintf("new_time[11]: %u\n", new_time[11]);
				#endif
            }
        }
    }
    else if ( ( (keycode == KC_0) || (keycode == KC_1) || (keycode == KC_2) || (keycode == KC_3) || (keycode == KC_4) || (keycode == KC_5) || (keycode == 6) || (keycode == KC_7) || (keycode == KC_6) || (keycode == KC_7) || (keycode == KC_8) || (keycode == KC_9) || (keycode == KC_DOT) ) && (is_in_set_time == false) && (is_in_effect_mode == false) && (record->event.pressed) ) {
		if(toggle_pic == false){
			toggle_pic = true;
			//Please Paste the code generated by the Excel tool. Start first image.
sethsv(0, 0, 0, (LED_TYPE *)&led[0]);
sethsv(0, 0, 0, (LED_TYPE *)&led[1]);
sethsv(0, 0, 0, (LED_TYPE *)&led[2]);
sethsv(0, 0, 0, (LED_TYPE *)&led[3]);
sethsv(0, 0, 0, (LED_TYPE *)&led[4]);
sethsv(0, 0, 0, (LED_TYPE *)&led[5]);
sethsv(0, 0, 0, (LED_TYPE *)&led[6]);
sethsv(0, 0, 0, (LED_TYPE *)&led[7]);
sethsv(0, 0, 0, (LED_TYPE *)&led[8]);
sethsv(0, 0, 0, (LED_TYPE *)&led[9]);
sethsv(0, 0, 0, (LED_TYPE *)&led[10]);
sethsv(0, 0, 0, (LED_TYPE *)&led[11]);
sethsv(0, 0, 0, (LED_TYPE *)&led[12]);
sethsv(0, 0, 0, (LED_TYPE *)&led[13]);
sethsv(0, 0, 0, (LED_TYPE *)&led[14]);
sethsv(0, 0, 0, (LED_TYPE *)&led[15]);
sethsv(0, 0, 0, (LED_TYPE *)&led[16]);
sethsv(0, 0, 0, (LED_TYPE *)&led[17]);
sethsv(0, 0, 0, (LED_TYPE *)&led[18]);
sethsv(0, 0, 0, (LED_TYPE *)&led[19]);
sethsv(0, 0, 0, (LED_TYPE *)&led[20]);
sethsv(0, 0, 0, (LED_TYPE *)&led[21]);
sethsv(0, 0, 0, (LED_TYPE *)&led[22]);
sethsv(0, 0, 0, (LED_TYPE *)&led[23]);
sethsv(0, 0, 0, (LED_TYPE *)&led[24]);
sethsv(0, 255, 255, (LED_TYPE *)&led[25]);
sethsv(0, 0, 0, (LED_TYPE *)&led[26]);
sethsv(0, 0, 0, (LED_TYPE *)&led[27]);
sethsv(0, 0, 0, (LED_TYPE *)&led[28]);
sethsv(0, 0, 0, (LED_TYPE *)&led[29]);
sethsv(0, 0, 0, (LED_TYPE *)&led[30]);
sethsv(0, 0, 0, (LED_TYPE *)&led[31]);
sethsv(0, 0, 141, (LED_TYPE *)&led[32]);
sethsv(0, 0, 141, (LED_TYPE *)&led[33]);
sethsv(0, 0, 141, (LED_TYPE *)&led[34]);
sethsv(0, 0, 0, (LED_TYPE *)&led[35]);
sethsv(0, 0, 0, (LED_TYPE *)&led[36]);
sethsv(0, 0, 0, (LED_TYPE *)&led[37]);
sethsv(0, 0, 0, (LED_TYPE *)&led[38]);
sethsv(0, 0, 0, (LED_TYPE *)&led[39]);
sethsv(0, 0, 0, (LED_TYPE *)&led[40]);
sethsv(0, 255, 255, (LED_TYPE *)&led[41]);
sethsv(0, 255, 255, (LED_TYPE *)&led[42]);
sethsv(0, 0, 0, (LED_TYPE *)&led[43]);
sethsv(0, 0, 141, (LED_TYPE *)&led[44]);
sethsv(0, 0, 141, (LED_TYPE *)&led[45]);
sethsv(0, 0, 0, (LED_TYPE *)&led[46]);
sethsv(0, 0, 0, (LED_TYPE *)&led[47]);
sethsv(0, 0, 0, (LED_TYPE *)&led[48]);
sethsv(0, 0, 0, (LED_TYPE *)&led[49]);
sethsv(0, 0, 141, (LED_TYPE *)&led[50]);
sethsv(0, 0, 0, (LED_TYPE *)&led[51]);
sethsv(28, 163, 232, (LED_TYPE *)&led[52]);
sethsv(0, 255, 255, (LED_TYPE *)&led[53]);
sethsv(28, 163, 232, (LED_TYPE *)&led[54]);
sethsv(0, 255, 255, (LED_TYPE *)&led[55]);
sethsv(28, 163, 232, (LED_TYPE *)&led[56]);
sethsv(0, 255, 255, (LED_TYPE *)&led[57]);
sethsv(0, 0, 0, (LED_TYPE *)&led[58]);
sethsv(0, 0, 0, (LED_TYPE *)&led[59]);
sethsv(0, 0, 0, (LED_TYPE *)&led[60]);
sethsv(0, 0, 0, (LED_TYPE *)&led[61]);
sethsv(0, 0, 0, (LED_TYPE *)&led[62]);
sethsv(0, 0, 0, (LED_TYPE *)&led[63]);
sethsv(0, 0, 0, (LED_TYPE *)&led[64]);
sethsv(0, 0, 0, (LED_TYPE *)&led[65]);
sethsv(0, 0, 141, (LED_TYPE *)&led[66]);
sethsv(0, 0, 0, (LED_TYPE *)&led[67]);
sethsv(28, 163, 232, (LED_TYPE *)&led[68]);
sethsv(0, 255, 255, (LED_TYPE *)&led[69]);
sethsv(28, 163, 232, (LED_TYPE *)&led[70]);
sethsv(0, 255, 255, (LED_TYPE *)&led[71]);
sethsv(28, 163, 232, (LED_TYPE *)&led[72]);
sethsv(0, 255, 255, (LED_TYPE *)&led[73]);
sethsv(0, 0, 0, (LED_TYPE *)&led[74]);
sethsv(0, 0, 0, (LED_TYPE *)&led[75]);
sethsv(0, 0, 141, (LED_TYPE *)&led[76]);
sethsv(0, 0, 141, (LED_TYPE *)&led[77]);
sethsv(0, 0, 0, (LED_TYPE *)&led[78]);
sethsv(0, 0, 141, (LED_TYPE *)&led[79]);
sethsv(0, 0, 0, (LED_TYPE *)&led[80]);
sethsv(0, 0, 141, (LED_TYPE *)&led[81]);
sethsv(0, 0, 0, (LED_TYPE *)&led[82]);
sethsv(0, 0, 0, (LED_TYPE *)&led[83]);
sethsv(0, 0, 0, (LED_TYPE *)&led[84]);
sethsv(0, 0, 255, (LED_TYPE *)&led[85]);
sethsv(0, 0, 255, (LED_TYPE *)&led[86]);
sethsv(0, 0, 255, (LED_TYPE *)&led[87]);
sethsv(0, 0, 255, (LED_TYPE *)&led[88]);
sethsv(0, 0, 0, (LED_TYPE *)&led[89]);
sethsv(0, 0, 0, (LED_TYPE *)&led[90]);
sethsv(0, 0, 0, (LED_TYPE *)&led[91]);
sethsv(0, 0, 0, (LED_TYPE *)&led[92]);
sethsv(0, 0, 0, (LED_TYPE *)&led[93]);
sethsv(0, 0, 141, (LED_TYPE *)&led[94]);
sethsv(0, 0, 0, (LED_TYPE *)&led[95]);
sethsv(0, 0, 141, (LED_TYPE *)&led[96]);
sethsv(0, 0, 0, (LED_TYPE *)&led[97]);
sethsv(0, 0, 141, (LED_TYPE *)&led[98]);
sethsv(0, 0, 0, (LED_TYPE *)&led[99]);
sethsv(0, 0, 0, (LED_TYPE *)&led[100]);
sethsv(0, 0, 255, (LED_TYPE *)&led[101]);
sethsv(0, 0, 255, (LED_TYPE *)&led[102]);
sethsv(0, 0, 255, (LED_TYPE *)&led[103]);
sethsv(0, 0, 255, (LED_TYPE *)&led[104]);
sethsv(0, 0, 0, (LED_TYPE *)&led[105]);
sethsv(0, 0, 0, (LED_TYPE *)&led[106]);
sethsv(0, 0, 0, (LED_TYPE *)&led[107]);
sethsv(0, 0, 141, (LED_TYPE *)&led[108]);
sethsv(0, 0, 141, (LED_TYPE *)&led[109]);
sethsv(0, 0, 0, (LED_TYPE *)&led[110]);
sethsv(0, 0, 0, (LED_TYPE *)&led[111]);
sethsv(0, 0, 0, (LED_TYPE *)&led[112]);
sethsv(0, 0, 0, (LED_TYPE *)&led[113]);
sethsv(0, 0, 0, (LED_TYPE *)&led[114]);
sethsv(0, 0, 0, (LED_TYPE *)&led[115]);
sethsv(0, 0, 0, (LED_TYPE *)&led[116]);
sethsv(0, 0, 0, (LED_TYPE *)&led[117]);
sethsv(0, 0, 0, (LED_TYPE *)&led[118]);
sethsv(0, 0, 0, (LED_TYPE *)&led[119]);
sethsv(0, 0, 0, (LED_TYPE *)&led[120]);
sethsv(0, 0, 0, (LED_TYPE *)&led[121]);
sethsv(0, 0, 0, (LED_TYPE *)&led[122]);
sethsv(0, 0, 0, (LED_TYPE *)&led[123]);
sethsv(0, 0, 0, (LED_TYPE *)&led[124]);
sethsv(0, 0, 0, (LED_TYPE *)&led[125]);
sethsv(0, 0, 0, (LED_TYPE *)&led[126]);
sethsv(0, 0, 0, (LED_TYPE *)&led[127]);
			//Please Paste the code generated by the Excel tool. End first image.
			rgblight_set();
		}
		
		else if(toggle_pic == true){
			toggle_pic = false;
			//Please Paste the code generated by the Excel tool. Start second image.
sethsv(0, 0, 0, (LED_TYPE *)&led[0]);
sethsv(0, 0, 0, (LED_TYPE *)&led[1]);
sethsv(0, 0, 0, (LED_TYPE *)&led[2]);
sethsv(0, 0, 0, (LED_TYPE *)&led[3]);
sethsv(0, 0, 0, (LED_TYPE *)&led[4]);
sethsv(0, 0, 0, (LED_TYPE *)&led[5]);
sethsv(0, 0, 0, (LED_TYPE *)&led[6]);
sethsv(0, 0, 0, (LED_TYPE *)&led[7]);
sethsv(0, 0, 0, (LED_TYPE *)&led[8]);
sethsv(0, 0, 0, (LED_TYPE *)&led[9]);
sethsv(0, 0, 0, (LED_TYPE *)&led[10]);
sethsv(0, 0, 0, (LED_TYPE *)&led[11]);
sethsv(0, 0, 0, (LED_TYPE *)&led[12]);
sethsv(0, 0, 0, (LED_TYPE *)&led[13]);
sethsv(0, 0, 0, (LED_TYPE *)&led[14]);
sethsv(0, 0, 0, (LED_TYPE *)&led[15]);
sethsv(0, 0, 0, (LED_TYPE *)&led[16]);
sethsv(0, 0, 0, (LED_TYPE *)&led[17]);
sethsv(0, 0, 0, (LED_TYPE *)&led[18]);
sethsv(0, 0, 0, (LED_TYPE *)&led[19]);
sethsv(0, 0, 0, (LED_TYPE *)&led[20]);
sethsv(0, 0, 0, (LED_TYPE *)&led[21]);
sethsv(0, 0, 0, (LED_TYPE *)&led[22]);
sethsv(0, 0, 0, (LED_TYPE *)&led[23]);
sethsv(0, 0, 0, (LED_TYPE *)&led[24]);
sethsv(0, 0, 0, (LED_TYPE *)&led[25]);
sethsv(0, 0, 0, (LED_TYPE *)&led[26]);
sethsv(0, 0, 0, (LED_TYPE *)&led[27]);
sethsv(0, 0, 0, (LED_TYPE *)&led[28]);
sethsv(0, 0, 0, (LED_TYPE *)&led[29]);
sethsv(0, 0, 0, (LED_TYPE *)&led[30]);
sethsv(0, 0, 0, (LED_TYPE *)&led[31]);
sethsv(0, 0, 141, (LED_TYPE *)&led[32]);
sethsv(0, 0, 141, (LED_TYPE *)&led[33]);
sethsv(0, 0, 141, (LED_TYPE *)&led[34]);
sethsv(0, 0, 0, (LED_TYPE *)&led[35]);
sethsv(0, 0, 0, (LED_TYPE *)&led[36]);
sethsv(0, 0, 0, (LED_TYPE *)&led[37]);
sethsv(0, 0, 0, (LED_TYPE *)&led[38]);
sethsv(0, 0, 0, (LED_TYPE *)&led[39]);
sethsv(0, 0, 0, (LED_TYPE *)&led[40]);
sethsv(0, 0, 0, (LED_TYPE *)&led[41]);
sethsv(0, 0, 0, (LED_TYPE *)&led[42]);
sethsv(0, 0, 0, (LED_TYPE *)&led[43]);
sethsv(0, 0, 141, (LED_TYPE *)&led[44]);
sethsv(0, 0, 141, (LED_TYPE *)&led[45]);
sethsv(0, 0, 0, (LED_TYPE *)&led[46]);
sethsv(0, 0, 0, (LED_TYPE *)&led[47]);
sethsv(0, 0, 0, (LED_TYPE *)&led[48]);
sethsv(0, 0, 0, (LED_TYPE *)&led[49]);
sethsv(0, 0, 141, (LED_TYPE *)&led[50]);
sethsv(0, 0, 0, (LED_TYPE *)&led[51]);
sethsv(0, 255, 255, (LED_TYPE *)&led[52]);
sethsv(0, 255, 255, (LED_TYPE *)&led[53]);
sethsv(0, 255, 255, (LED_TYPE *)&led[54]);
sethsv(0, 255, 255, (LED_TYPE *)&led[55]);
sethsv(0, 255, 255, (LED_TYPE *)&led[56]);
sethsv(0, 255, 255, (LED_TYPE *)&led[57]);
sethsv(0, 255, 255, (LED_TYPE *)&led[58]);
sethsv(0, 0, 0, (LED_TYPE *)&led[59]);
sethsv(0, 0, 0, (LED_TYPE *)&led[60]);
sethsv(0, 0, 0, (LED_TYPE *)&led[61]);
sethsv(0, 0, 0, (LED_TYPE *)&led[62]);
sethsv(0, 0, 0, (LED_TYPE *)&led[63]);
sethsv(0, 0, 0, (LED_TYPE *)&led[64]);
sethsv(0, 0, 0, (LED_TYPE *)&led[65]);
sethsv(0, 0, 141, (LED_TYPE *)&led[66]);
sethsv(0, 0, 0, (LED_TYPE *)&led[67]);
sethsv(0, 255, 255, (LED_TYPE *)&led[68]);
sethsv(0, 255, 255, (LED_TYPE *)&led[69]);
sethsv(0, 255, 255, (LED_TYPE *)&led[70]);
sethsv(0, 255, 255, (LED_TYPE *)&led[71]);
sethsv(0, 255, 255, (LED_TYPE *)&led[72]);
sethsv(0, 255, 255, (LED_TYPE *)&led[73]);
sethsv(0, 255, 255, (LED_TYPE *)&led[74]);
sethsv(0, 0, 0, (LED_TYPE *)&led[75]);
sethsv(0, 0, 141, (LED_TYPE *)&led[76]);
sethsv(0, 0, 141, (LED_TYPE *)&led[77]);
sethsv(0, 0, 0, (LED_TYPE *)&led[78]);
sethsv(0, 0, 141, (LED_TYPE *)&led[79]);
sethsv(0, 0, 0, (LED_TYPE *)&led[80]);
sethsv(0, 0, 141, (LED_TYPE *)&led[81]);
sethsv(0, 0, 0, (LED_TYPE *)&led[82]);
sethsv(0, 0, 0, (LED_TYPE *)&led[83]);
sethsv(0, 0, 0, (LED_TYPE *)&led[84]);
sethsv(0, 0, 255, (LED_TYPE *)&led[85]);
sethsv(0, 0, 255, (LED_TYPE *)&led[86]);
sethsv(0, 0, 255, (LED_TYPE *)&led[87]);
sethsv(0, 0, 255, (LED_TYPE *)&led[88]);
sethsv(0, 0, 255, (LED_TYPE *)&led[89]);
sethsv(0, 0, 0, (LED_TYPE *)&led[90]);
sethsv(0, 0, 0, (LED_TYPE *)&led[91]);
sethsv(0, 0, 0, (LED_TYPE *)&led[92]);
sethsv(0, 0, 0, (LED_TYPE *)&led[93]);
sethsv(0, 0, 141, (LED_TYPE *)&led[94]);
sethsv(0, 0, 0, (LED_TYPE *)&led[95]);
sethsv(0, 0, 141, (LED_TYPE *)&led[96]);
sethsv(0, 0, 0, (LED_TYPE *)&led[97]);
sethsv(0, 0, 141, (LED_TYPE *)&led[98]);
sethsv(0, 0, 0, (LED_TYPE *)&led[99]);
sethsv(0, 0, 0, (LED_TYPE *)&led[100]);
sethsv(0, 0, 255, (LED_TYPE *)&led[101]);
sethsv(0, 0, 255, (LED_TYPE *)&led[102]);
sethsv(0, 0, 255, (LED_TYPE *)&led[103]);
sethsv(0, 0, 255, (LED_TYPE *)&led[104]);
sethsv(0, 0, 255, (LED_TYPE *)&led[105]);
sethsv(0, 0, 0, (LED_TYPE *)&led[106]);
sethsv(0, 0, 0, (LED_TYPE *)&led[107]);
sethsv(0, 0, 141, (LED_TYPE *)&led[108]);
sethsv(0, 0, 141, (LED_TYPE *)&led[109]);
sethsv(0, 0, 0, (LED_TYPE *)&led[110]);
sethsv(0, 0, 0, (LED_TYPE *)&led[111]);
sethsv(0, 0, 0, (LED_TYPE *)&led[112]);
sethsv(0, 0, 0, (LED_TYPE *)&led[113]);
sethsv(0, 0, 0, (LED_TYPE *)&led[114]);
sethsv(0, 0, 0, (LED_TYPE *)&led[115]);
sethsv(0, 0, 0, (LED_TYPE *)&led[116]);
sethsv(0, 0, 0, (LED_TYPE *)&led[117]);
sethsv(0, 0, 0, (LED_TYPE *)&led[118]);
sethsv(0, 0, 0, (LED_TYPE *)&led[119]);
sethsv(0, 0, 0, (LED_TYPE *)&led[120]);
sethsv(0, 0, 0, (LED_TYPE *)&led[121]);
sethsv(0, 0, 0, (LED_TYPE *)&led[122]);
sethsv(0, 0, 0, (LED_TYPE *)&led[123]);
sethsv(0, 0, 0, (LED_TYPE *)&led[124]);
sethsv(0, 0, 0, (LED_TYPE *)&led[125]);
sethsv(0, 0, 0, (LED_TYPE *)&led[126]);
sethsv(0, 0, 0, (LED_TYPE *)&led[127]);
			//Please Paste the code generated by the Excel tool. Second image end .
			rgblight_set();
		}
	}
    else if(keycode == RGB_M_B && record->event.pressed) {
		is_in_effect_mode = true;
		toggle_pic = false;
		is_in_time_disp = false;
	}
    else if(keycode == RGB_M_R && record->event.pressed) {
		is_in_effect_mode = true;
		toggle_pic = false;
		is_in_time_disp = false;
	}
    else if(keycode == RGB_M_SW && record->event.pressed) {
		is_in_effect_mode = true;
		toggle_pic = false;
		is_in_time_disp = false;
	}
    else if(keycode == RGB_M_SN && record->event.pressed) {
		is_in_effect_mode = true;
		toggle_pic = false;
		is_in_time_disp = false;
	}
    else if(keycode == RGB_M_K && record->event.pressed) {
		is_in_effect_mode = true;
		toggle_pic = false;
		is_in_time_disp = false;
	}
    else if(keycode == RGB_M_X && record->event.pressed) {
		is_in_effect_mode = true;
		toggle_pic = false;
		is_in_time_disp = false;
	}
    else if(keycode == RGB_M_G && record->event.pressed) {
		is_in_effect_mode = true;
		toggle_pic = false;
		is_in_time_disp = false;
	}
    else if(keycode == RGB_M_T && record->event.pressed) {
		is_in_effect_mode = true;
		toggle_pic = false;
		is_in_time_disp = false;
	}
    else if(keycode == RGB_M_TW && record->event.pressed) {
		is_in_effect_mode = true;
		toggle_pic = false;
		is_in_time_disp = false;
	}
    else if(keycode == RGB_M_P && record->event.pressed) {
		update_time = 10000;
		last_update = 0;
		is_in_effect_mode = false;
		toggle_pic = false;
		is_in_time_disp = true;
	}

  switch (keycode) {
    case LAYER_1:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_LAYER_1);
      }
      return false;

    case LAYER_2:
      if (record->event.pressed) {
        layer_on(_LAYER_2);
      } else {
        layer_off(_LAYER_2);
      }
      return false;
    
  }
  return true;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { 
        if (clockwise) {
            encoder1_cw.pressed = true;
            encoder1_cw.time = (timer_read() | 1);
            action_exec(encoder1_cw);
        } else {
            encoder1_ccw.pressed = true;
            encoder1_ccw.time = (timer_read() | 1);
            action_exec(encoder1_ccw);
        }
    } else if (index == 1) {
        if (clockwise) {
            encoder2_cw.pressed = true;
            encoder2_cw.time = (timer_read() | 1);
            action_exec(encoder2_cw);
        } else {
            encoder2_ccw.pressed = true;
            encoder2_ccw.time = (timer_read() | 1);
            action_exec(encoder2_ccw);
        }
    }
    return true;
}