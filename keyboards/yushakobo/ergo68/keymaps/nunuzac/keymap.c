/* Copyright 2023 yushakobo
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
#include "nunuzac.h"
#include "tap_dances.h"
#include <stdint.h>
#include "secrets.h"

#define TG_FN TG(FUNCTION)

enum custom_keycodes {
    TG_AS = SAFE_RANGE,
    TG_LY,
    CL_GM
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWERTY] = LAYOUT(
        KC_TDEC, KC_TDN1, KC_TDN2, KC_TDN3, KC_TDN4,  KC_TDN5,                         KC_TDN6, KC_TDN7, KC_TDN8, KC_TDN9, KC_TDN0, KC_TDLG,
        KC_TDUH, KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,    TG_FN,         DM_PLY1, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_TDSL,
        KC_TDDE, KC_A,    KC_S,    KC_D,    KC_F,     KC_G,    QK_LEAD,       DM_PLY2, KC_H,    KC_J,    KC_K,    KC_L,    KC_TDEP, KC_TDQT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,    CW_TOGG,       _______, KC_N,    KC_M,    KC_TDCL, KC_TDDG, KC_TDCN, KC_TDLN,
        KC_LCTL, KC_LGUI, KC_LALT, KC_LEFT, KC_RIGHT, KC_SPC,  KC_TAB,        KC_ENT,  KC_BSPC, KC_UP,   KC_DOWN, KC_TDCB, KC_TDRB, KC_TDSB
    ),
    [FUNCTION] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,                           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______
    ),
};

bool caps_word_press_user(uint16_t keycode) {
  switch (keycode) {
    case KC_A ... KC_Z:
    case KC_MINS:
      add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to the next key.
      return true;
    case KC_1 ... KC_0:
    case KC_BSPC:
    case KC_DEL:
    case KC_UNDS:
    case KC_LEFT:
    case KC_TDLN:
      return true;
    default:
      return false;
  }
}

void leader_end_user(void) {
    if (leader_sequence_one_key(KC_C)) {
        SEND_STRING("clear");
        tap_code(KC_ENT);
    } else if (leader_sequence_one_key(KC_E)) {
        SEND_STRING("exit");
        tap_code(KC_ENT);
    } else if (leader_sequence_one_key(KC_G)) {
        SEND_STRING(" | grep ");
    } else if (leader_sequence_one_key(KC_N)) {
        send_short_name();
    } else if (leader_sequence_two_keys(KC_N, KC_M)) {
        send_long_name();
    } else if (leader_sequence_one_key(KC_M)) {
        send_work_mail();
    } else if (leader_sequence_two_keys(KC_M, KC_L)) {
        send_mail();
    } else if (leader_sequence_one_key(KC_P)) {
        send_long_password();
    } else if (leader_sequence_two_keys(KC_P, KC_W)) {
        send_short_password();
    }
}

/* bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) { */
/*     // caps lock cyan */
/*     if (host_keyboard_led_state().caps_lock) { */
/*         RGB_MATRIX_INDICATOR_SET_COLOR(0, 0, 0, 128); */
/*     } else { */
/*         RGB_MATRIX_INDICATOR_SET_COLOR(0, 0, 0, 0); */
/*     } */
/*     // num lock cyan */
/*     if (host_keyboard_led_state().num_lock) { */
/*         RGB_MATRIX_INDICATOR_SET_COLOR(1, 0, 0, 128); */
/*     } else { */
/*         RGB_MATRIX_INDICATOR_SET_COLOR(1, 0, 0, 0); */
/*     } */
/*     // scroll lock cyan */
/*     if (host_keyboard_led_state().scroll_lock) { */
/*         RGB_MATRIX_INDICATOR_SET_COLOR(2, 0, 0, 128); */
/*     } else { */
/*         RGB_MATRIX_INDICATOR_SET_COLOR(2, 0, 0, 0); */
/*     } */
/*     // layer state */
/*     switch (get_highest_layer(layer_state)) { */
/*         case 1: */
/*             RGB_MATRIX_INDICATOR_SET_COLOR(37, 0, 0, 128); */
/*             break; */
/*         case 2: */
/*             RGB_MATRIX_INDICATOR_SET_COLOR(38, 0, 0, 128); */
/*             break; */
/*         case 3: */
/*             RGB_MATRIX_INDICATOR_SET_COLOR(39, 0, 0, 128); */
/*             break; */
/*     } */
/*     return false; */
/* } */
