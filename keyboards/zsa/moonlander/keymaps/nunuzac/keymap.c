/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include <stdint.h>
#include "nunuzac.h"
#include "tap_dances.h"
#include "caps_word.h"
#include "secrets.h"

enum combo_events {
    CAPS_COMBO,
    LPWD_COMBO,
    SPWD_COMBO,
    MAIL_COMBO,
    WMAL_COMBO,
    LNAM_COMBO,
    SNAM_COMBO,
    COMBO_LENGTH
};

enum custom_keycodes {
    TG_AS = SAFE_RANGE,
    TG_LY,
    CL_GM
};

#define TG_FN TG(FUNCTION)

uint16_t COMBO_LEN = COMBO_LENGTH;
const uint16_t PROGMEM caps_combo[] = {KC_RGHT, KC_UP, COMBO_END};
const uint16_t PROGMEM lpwd_combo[] = {KC_P, KC_W, KC_D, COMBO_END};
const uint16_t PROGMEM spwd_combo[] = {KC_P, KC_W, COMBO_END};
const uint16_t PROGMEM mail_combo[] = {KC_M, KC_L, COMBO_END};
const uint16_t PROGMEM wmal_combo[] = {KC_W, KC_M, KC_L, COMBO_END};
const uint16_t PROGMEM lnam_combo[] = {KC_N, KC_A, KC_M, COMBO_END};
const uint16_t PROGMEM snam_combo[] = {KC_N, KC_M, COMBO_END};

combo_t key_combos[] = {
    [CAPS_COMBO] = COMBO_ACTION(caps_combo),
    [LPWD_COMBO] = COMBO_ACTION(lpwd_combo),
    [SPWD_COMBO] = COMBO_ACTION(spwd_combo),
    [MAIL_COMBO] = COMBO_ACTION(mail_combo),
    [WMAL_COMBO] = COMBO_ACTION(wmal_combo),
    [LNAM_COMBO] = COMBO_ACTION(lnam_combo),
    [SNAM_COMBO] = COMBO_ACTION(snam_combo),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWERTY] = LAYOUT_moonlander(
        KC_TDEC, KC_TDN1,  KC_TDN2,  KC_TDN3,  KC_TDN4,  KC_TDN5, TG_FN,              DM_PLY1, KC_TDN6,  KC_TDN7,  KC_TDN8,  KC_TDN9,  KC_TDN0,  KC_TDLG,
        KC_TDUH, KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,    TG_AS,              DM_PLY2, KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_TDSL,
        KC_TDDE, KC_A,     KC_S,     KC_D,     KC_F,     KC_G,    TG_LY,              CL_GM,   KC_H,     KC_J,     KC_K,     KC_L,     KC_TDEP,  KC_TDQT,
        KC_LSFT, KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                                 KC_N,     KC_M,     KC_TDCL,  KC_TDDG,  KC_TDCN,  KC_TDLN,
        KC_LCTL, KC_LGUI,  KC_LALT,  KC_LEFT,  KC_RGHT,           KC_TAB,             KC_ENT,            KC_UP,    KC_DOWN,  KC_TDCB,  KC_TDRB,  KC_TDSB,
                                               KC_SPC,   KC_TDCC, KC_TDPS,            QK_LEAD, KC_DEL,   KC_BSPC
    ),

    [WORKMAN] = LAYOUT_moonlander(
        KC_TDEC, KC_TDN1,  KC_TDN2,  KC_TDN3,  KC_TDN4,  KC_TDN5,  TG_FN,             DM_PLY1, KC_TDN6,  KC_TDN7,  KC_TDN8,  KC_TDN9,  KC_TDN0,  KC_TDLG,
        KC_TDUH, KC_Q,     KC_D,     KC_R,     KC_W,     KC_B,     TG_AS,             DM_PLY2, KC_J,     KC_F,     KC_U,     KC_P,     KC_TDCN,  KC_TDSL,
        KC_TDDE, KC_A,     KC_S,     KC_H,     KC_T,     KC_G,     TG_LY,             CL_GM,   KC_Y,     KC_N,     KC_E,     KC_O,     KC_I,     KC_TDQT,
        KC_LSFT, KC_Z,     KC_X,     KC_M,     KC_C,     KC_V,                                 KC_K,     KC_L,     KC_TDCL,  KC_TDDG,  KC_TDEP,  KC_TDLN,
        KC_LCTL, KC_LGUI,  KC_LALT,  KC_LEFT,  KC_RGHT,            KC_TAB,            KC_ENT,            KC_UP,    KC_DOWN,  KC_TDCB,  KC_TDRB,  KC_TDSB,
                                               KC_SPC,   KC_TDCC,  KC_TDPS,           QK_LEAD, KC_DEL,   KC_BSPC
    ),

    [GAMES] = LAYOUT_moonlander(
        KC_ESC,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     TG_FN,             _______, KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     _______,
        _______, KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     TG_AS,             _______, KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     _______,
        _______, KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     TG_LY,             CL_GM,   KC_H,     KC_J,     KC_K,     KC_L,     _______,  _______,
        KC_LSFT, KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,                                 KC_N,     KC_M,     _______,  _______,  _______,  _______,
        KC_LCTL, _______,  KC_LALT,  KC_LEFT,  KC_RGHT,            KC_TAB,            KC_ENT,            KC_UP,    KC_DOWN,  _______,  _______,  _______,
                                               KC_SPC,   _______,  _______,           _______, KC_DEL,   KC_BSPC
    ),

    [FUNCTION] = LAYOUT_moonlander(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   TG_FN,                  DM_REC1, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, _______, _______, _______, _______, _______, _______,                DM_REC2, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                DM_RSTP, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                  _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______,                _______,          _______, _______, _______, _______, _______,
                                            _______, _______, _______,                _______,  _______, _______
    ),
};


void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case CAPS_COMBO:
            if (pressed)
                caps_word_set(true);
        break;
        case LPWD_COMBO:
            if (!pressed)
                send_long_password();
        break;
        case SPWD_COMBO:
            if (!pressed)
                send_short_password();
        break;
        case MAIL_COMBO:
            if (!pressed)
                send_mail();
        break;
        case WMAL_COMBO:
            if (!pressed)
                send_work_mail();
        break;
        case LNAM_COMBO:
            if (!pressed)
                send_long_name();
        break;
        case SNAM_COMBO:
            if (!pressed)
                send_short_name();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_caps_word(keycode, record)) { return false; }
    switch (keycode) {
        case TG_AS:
            if (!record->event.pressed) {
                autoshift_toggle();
                ML_LED_2(get_autoshift_state());
            }
        break;
        case TG_LY:
            if (!record->event.pressed) {
                if (layer_state_is(WORKMAN)) {
                    layer_off(WORKMAN);
                    layer_on(QWERTY);
                } else if (layer_state_is(QWERTY)) {
                    layer_off(QWERTY);
                    layer_on(WORKMAN);
                }
            }
        break;
        case CL_GM:
            if (!record->event.pressed) {
                if (layer_state_is(GAMES)) {
                    layer_off(GAMES);
                } else {
                    layer_move(GAMES);
                }
            }
        break;
    }
    return true;
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
    } else if (leader_sequence_one_key(KC_TAB)){
        SEND_STRING(SS_LCTL(SS_LSFT("t")));
    } else if (leader_sequence_two_keys(KC_TAB, KC_TAB)){
        SEND_STRING(SS_LCTL("t"));
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    ML_LED_1(layer_state_cmp(state, FUNCTION));
    ML_LED_2(get_autoshift_state());
    ML_LED_3(layer_state_cmp(state, WORKMAN));
    ML_LED_6(layer_state_cmp(state, GAMES));
    return state;
}
