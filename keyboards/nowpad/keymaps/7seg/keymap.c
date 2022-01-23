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
#include "ht16k33.h"

#ifdef CONSOLE_ENABLE
  #include <print.h>
#endif

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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* _LAYER_1
 *|---------------|
 *|PLY| / | * | - |
 *|---+---+---+---|
 *|7  |8  |9  |LT(|
 *|---+---+---|_L2|
 *|4  |5  |6  |,+|
 *|---+---+---+---|
 *|1  |2  |3  |Ent|
 *|-------+---|   |
 *|0      | . |   |
 *|---------------|
 * Encoder setting
 *|---------------|
 *|PRV|NXT|Vo-|Vo+|
 *|---+---+---+---|
 */
[_LAYER_1] = LAYOUT( \
    KC_MPLY,  KC_PSLS,  KC_PAST,  KC_PMNS,
    KC_7,     KC_8,     KC_9,     LT(_LAYER_2,KC_PPLS),
    KC_4,     KC_5,     KC_6,
    KC_1,     KC_2,     KC_3,     KC_ENT,
    KC_0,     KC_DOT,
    KC_MPRV,  KC_MNXT,  KC_VOLD,  KC_VOLU
),
/* _LAYER_2
 *|---------------|
 *|F24|   |   |   |
 *|---+---+---+---|
 *|HOM|UP |PGU|   |
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
    KC_F24,    XXXXXXX,   XXXXXXX,   XXXXXXX,
    KC_HOME,   KC_UP,     KC_PGUP,   XXXXXXX,
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

static uint32_t last_update = 0;
static uint32_t last_switch = 0;

static uint8_t hours, minutes, seconds, day, month, year;

// キーボード初期化後に呼ばれる関数
void keyboard_post_init_user(void) {
		i2c_init();  // on pins D(1,0);
        ht16k33_init();

		uint8_t bright,data;
		for(bright=0; bright <= 0x06; bright++) {
			data = 0xE0 | bright;
			i2c_transmit(HT16K33_ADDR, &data, 1, 100);// Change Brightness
	        ht16k33_7seg(0x01,0x0A);// -
	        ht16k33_7seg(0x02,0x0B);// H
	        ht16k33_7seg(0x03,0x0C);// E
	        ht16k33_7seg(0x08,0x0D);// L
	        ht16k33_7seg(0x09,0x0D);// L
	        ht16k33_7seg(0x0A,0x00);// O
	        ht16k33_7seg(0x0B,0x0A);// -
			wait_ms(450);
		}
		wait_ms(1500);
}

static bool time_disp = true;
        
void matrix_scan_user(void) {

    uint32_t update_time = timer_read32();
    uint32_t switch_time = timer_read32();

	if (switch_time - last_switch >5000){
		last_switch = switch_time;
		if (time_disp == false){
			time_disp = true;
		}
		else if(time_disp == true){
			time_disp = true;
		}
	}

	if (update_time - last_update > 350) {
		last_update = update_time;
		ds1307_get_time(&year, &month, &day, &hours, &minutes, &seconds);
		
		uint8_t h2, h1, m2, m1, s2, s1;
		uint8_t mo2, mo1, d2, d1;

		mo2 = month/10;
		mo1 = month-mo2*10;
		d2 = day/10;
		d1 = day-d2*10;


		h2 = hours/10;
		h1 = hours-h2*10;
		m2 = minutes/10;
		m1 = minutes-m2*10;
		s2 = seconds/10;
		s1 = seconds-s2*10;
		
		if (time_disp == true){
			if(h2 == 0){
				ht16k33_7seg(0x00,0);
			}
			else if(h2 == 1){
				ht16k33_7seg(0x00,1);
			}
			else if(h2 == 2){
				ht16k33_7seg(0x00,2);
			}
			
			if(h1 == 0){
				ht16k33_7seg(0x01,0);
			}
			else if(h1 == 1){
				ht16k33_7seg(0x01,1);
			}
			else if(h1 == 2){
				ht16k33_7seg(0x01,2);
			}
			else if(h1 == 3){
				ht16k33_7seg(0x01,3);
			}
			else if(h1 == 4){
				ht16k33_7seg(0x01,4);
			}
			else if(h1 == 5){
				ht16k33_7seg(0x01,5);
			}
			else if(h1 == 6){
				ht16k33_7seg(0x01,6);
			}
			else if(h1 == 7){
				ht16k33_7seg(0x01,7);
			}
			else if(h1 == 8){
				ht16k33_7seg(0x01,8);
			}
			else if(h1 == 9){
				ht16k33_7seg(0x01,9);
			}

			ht16k33_7seg(0x02,0x0A);// -

			if(m2 == 0){
				ht16k33_7seg(0x03,0);
			}
			else if(m2 == 1){
				ht16k33_7seg(0x03,1);
			}
			else if(m2 == 2){
				ht16k33_7seg(0x03,2);
			}
			else if(m2 == 3){
				ht16k33_7seg(0x03,3);
			}
			else if(m2 == 4){
				ht16k33_7seg(0x03,4);
			}
			else if(m2 == 5){
				ht16k33_7seg(0x03,5);
			}
			else if(m2 == 6){
				ht16k33_7seg(0x03,6);
			}

			if(m1 == 0){
				ht16k33_7seg(0x08,0);
			}
			else if(m1 == 1){
				ht16k33_7seg(0x08,1);
			}
			else if(m1 == 2){
				ht16k33_7seg(0x08,2);
			}
			else if(m1 == 3){
				ht16k33_7seg(0x08,3);
			}
			else if(m1 == 4){
				ht16k33_7seg(0x08,4);
			}
			else if(m1 == 5){
				ht16k33_7seg(0x08,5);
			}
			else if(m1 == 6){
				ht16k33_7seg(0x08,6);
			}
			else if(m1 == 7){
				ht16k33_7seg(0x08,7);
			}
			else if(m1 == 8){
				ht16k33_7seg(0x08,8);
			}
			else if(m1 == 9){
				ht16k33_7seg(0x08,9);
			}

			ht16k33_7seg(0x09,0x0A);// -

			if(s2 == 0){
				ht16k33_7seg(0x0A,0);
			}
			else if(s2 == 1){
				ht16k33_7seg(0x0A,1);
			}
			else if(s2 == 2){
				ht16k33_7seg(0x0A,2);
			}
			else if(s2 == 3){
				ht16k33_7seg(0x0A,3);
			}
			else if(s2 == 4){
				ht16k33_7seg(0x0A,4);
			}
			else if(s2 == 5){
				ht16k33_7seg(0x0A,5);
			}
			else if(s2 == 6){
				ht16k33_7seg(0x0A,6);
			}

			if(s1 == 0){
				ht16k33_7seg(0x0B,0);
			}
			else if(s1 == 1){
				ht16k33_7seg(0x0B,1);
			}
			else if(s1 == 2){
				ht16k33_7seg(0x0B,2);
			}
			else if(s1 == 3){
				ht16k33_7seg(0x0B,3);
			}
			else if(s1 == 4){
				ht16k33_7seg(0x0B,4);
			}
			else if(s1 == 5){
				ht16k33_7seg(0x0B,5);
			}
			else if(s1 == 6){
				ht16k33_7seg(0x0B,6);
			}
			else if(s1 == 7){
				ht16k33_7seg(0x0B,7);
			}
			else if(s1 == 8){
				ht16k33_7seg(0x0B,8);
			}
			else if(s1 == 9){
				ht16k33_7seg(0x0B,9);
			}
		}// if time_disp == true end

		else if(time_disp == false){
			ht16k33_7seg(0x00,0x0F);// DP

			if(mo2 == 0){
				ht16k33_7seg(0x01,0);
			}
			else if(mo2 == 1){
				ht16k33_7seg(0x01,1);
			}

			if(mo1 == 0){
				ht16k33_7seg(0x02,0);
			}
			else if(mo1 == 1){
				ht16k33_7seg(0x02,1);
			}
			else if(mo1 == 2){
				ht16k33_7seg(0x02,2);
			}
			else if(mo1 == 3){
				ht16k33_7seg(0x02,3);
			}
			else if(mo1 == 4){
				ht16k33_7seg(0x02,4);
			}
			else if(mo1 == 5){
				ht16k33_7seg(0x02,5);
			}
			else if(mo1 == 6){
				ht16k33_7seg(0x02,6);
			}
			else if(mo1 == 7){
				ht16k33_7seg(0x02,7);
			}
			else if(mo1 == 8){
				ht16k33_7seg(0x02,8);
			}
			else if(mo1 == 9){
				ht16k33_7seg(0x02,9);
			}

			ht16k33_7seg(0x03,0x0A);// -
			ht16k33_7seg(0x08,0x0A);// -

			if(d2 == 0){
				ht16k33_7seg(0x09,0);
			}
			else if(d2 == 1){
				ht16k33_7seg(0x09,1);
			}
			else if(d2 == 2){
				ht16k33_7seg(0x09,2);
			}
			else if(d2 == 3){
				ht16k33_7seg(0x09,3);
			}

			if(d1 == 0){
				ht16k33_7seg(0x0A,0);
			}
			else if(d1 == 1){
				ht16k33_7seg(0x0A,1);
			}
			else if(d1 == 2){
				ht16k33_7seg(0x0A,2);
			}
			else if(d1 == 3){
				ht16k33_7seg(0x0A,3);
			}
			else if(d1 == 4){
				ht16k33_7seg(0x0A,4);
			}
			else if(d1 == 5){
				ht16k33_7seg(0x0A,5);
			}
			else if(d1 == 6){
				ht16k33_7seg(0x0A,6);
			}
			else if(d1 == 7){
				ht16k33_7seg(0x0A,7);
			}
			else if(d1 == 8){
				ht16k33_7seg(0x0A,8);
			}
			else if(d1 == 9){
				ht16k33_7seg(0x0A,9);
			}

			ht16k33_7seg(0x0B,0x0F);// DP
		}// if time_disp == false end
//      #ifdef CONSOLE_ENABLE
//		uprintf("update_time: %u\n", hours);
//		uprintf("update_time: %u\n", minutes);
//		uprintf("update_time: %u\n", seconds);
//		#endif
    }// if update_time end
}//matrix_scan_user(void) end

static bool is_in_set_time = false;
static bool is_init_ht = false;
static char new_time[12];
static uint8_t new_time_index = 0;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == KC_F24 && record->event.pressed) {
        is_in_set_time = true;
        is_init_ht = true;
        new_time_index = 0;
    } else if (is_in_set_time) {
        if (!record->event.pressed && keycode >= KC_1 && keycode <= KC_0) {
            new_time[new_time_index++] = (keycode == KC_0) ? 0 : keycode - KC_1 + 1;
            if (new_time_index == 12) {
                is_in_set_time = false;
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

  switch (keycode) {
    case LAYER_1:
      if (record->event.pressed) {
        // persistant_default_layer_set(1UL<<_QWERTY);
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
