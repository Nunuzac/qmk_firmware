#include "config.h"
#include QMK_KEYBOARD_H
#include "tap_dances.h"
#include <stdint.h>
#include "secrets.h"
#include "transactions.h"

enum layers { QWERTY, FUNCTION, MOUSE };

#define TG_FN TG(FUNCTION)
#define TG_MK TG(MOUSE)

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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [QWERTY] = LAYOUT(
        KC_TDEC, KC_TDN1, KC_TDN2, KC_TDN3, KC_TDN4,  KC_TDN5,                         KC_TDN6, KC_TDN7, KC_TDN8, KC_TDN9, KC_TDN0, KC_TDLG,
        KC_TDUH, KC_Q,    KC_W,    KC_E,    KC_R,     KC_T,    TG_FN,         TG_MK,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_TDSL,
        KC_TDDE, KC_A,    KC_S,    KC_D,    KC_F,     KC_G,    _______,       _______, KC_H,    KC_J,    KC_K,    KC_L,    KC_TDEP, KC_TDQT,
        OS_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,     KC_B,    _______,       _______, KC_N,    KC_M,    KC_TDCL, KC_TDDG, KC_TDCN, KC_TDLN,
        OS_LCTL, OS_LGUI, OS_LALT, KC_LEFT, KC_RIGHT, KC_SPC,  KC_TAB,        KC_ENT,  KC_BSPC, KC_UP,   KC_DOWN, KC_TDCB, KC_TDRB, KC_TDSB
    ),
    [FUNCTION] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,                           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______
    ),
    [MOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______,                          _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, MS_BTN2,        MS_WHLU, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, MS_BTN1,        MS_WHLD, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, MS_LEFT, MS_RGHT, _______, _______,        _______, _______, MS_UP,   MS_DOWN, _______, _______, _______
    ),
};
// clang-format on

void process_combo_event(uint16_t combo_index, bool pressed) {
    switch(combo_index) {
        case CAPS_COMBO:
            if (!pressed) {
                if (is_caps_word_on())
                    caps_word_off();
                else
                    caps_word_on();
            }
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

bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        case KC_A ... KC_Z:
            add_weak_mods(MOD_BIT(KC_LSFT)); // Apply shift to the next key.
            return true;
        // TODO: case KC_DEL:
        case KC_1 ... KC_0:
        case KC_TDN0:
        case KC_TDN1:
        case KC_TDN2:
        case KC_TDN3:
        case KC_TDN4:
        case KC_TDN5:
        case KC_TDN6:
        case KC_TDN7:
        case KC_TDN8:
        case KC_TDN9:
        case KC_BSPC:
        case KC_LEFT:
        case KC_TDLN:
        case KC_UNDS:
        case KC_MINS:
            return true;
        default:
            return false;
    }
}

static bool is_caps_word_enabled = false;

void caps_word_set_user(bool active) {
    is_caps_word_enabled = active;
    if (is_keyboard_master()) {
        transaction_rpc_send(RPC_ID_USER_CAPS_WORD_SYNC, 1, &is_caps_word_enabled);
    }
}

void caps_word_sync(uint8_t initiator2target_buffer_size, const void *initiator2target_buffer, uint8_t target2initiator_buffer_size, void *target2initiator_buffer) {
    memcpy(&is_caps_word_enabled, initiator2target_buffer, sizeof(initiator2target_buffer_size));
}

void housekeeping_task_user(void) {
    if (is_keyboard_master()) {
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 500) {
            if (transaction_rpc_send(RPC_ID_USER_CAPS_WORD_SYNC, 1, &is_caps_word_enabled)) {
                last_sync = timer_read32();
            }
        }
    }
}
void keyboard_post_init_user(void) {
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(0, 0, 0);
    transaction_register_rpc(RPC_ID_USER_CAPS_WORD_SYNC, caps_word_sync);
}

// clang-format off
#define NUMBER_LEDS_COUNT 10
#define LETTER_LEDS_COUNT 26
#define MOUSE_LEDS_COUNT 8
#define MOUSE_LEDS 22, 23, 33, 34, 59, 60, 70, 71
#define NUMBER_LEDS 4, 5, 6, 7, 8, 41, 42, 43, 44, 45
#define LETTER_LEDS 10, 11, 12, 13, 14, \
                    17, 18, 19, 20, 21, \
                    24, 25, 26, 27, 28, \
                    47, 48, 49, 50, 51, \
                    55, 56, 57, 58, \
                    61, 62
// clang-format on

uint8_t function_leds[NUMBER_LEDS_COUNT + 1]                      = {9, NUMBER_LEDS};
uint8_t caps_leds[LETTER_LEDS_COUNT + 1]                          = {3, LETTER_LEDS};
uint8_t caps_word_leds[NUMBER_LEDS_COUNT + LETTER_LEDS_COUNT + 4] = {23, NUMBER_LEDS, LETTER_LEDS, 33, 66, 72};
uint8_t mouse_leds[MOUSE_LEDS_COUNT + 1]                          = {46, MOUSE_LEDS};

void color_leds(uint16_t r, uint16_t g, uint16_t b, uint8_t *leds, uint8_t len) {
    r = r * IND_MAX / 255;
    g = g * IND_MAX / 255;
    b = b * IND_MAX / 255;
    for (uint8_t i = 0; i < len; i++)
        rgb_matrix_set_color(*(leds + i), r, g, b);
}

bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (get_highest_layer(layer_state) == MOUSE) {
        color_leds(50, 250, 10, mouse_leds, MOUSE_LEDS_COUNT + 1);
    } else if (get_highest_layer(layer_state) == FUNCTION) {
        color_leds(50, 160, 240, function_leds, NUMBER_LEDS_COUNT + 1);
    } else if (host_keyboard_led_state().caps_lock) {
        color_leds(210, 150, 250, caps_leds, LETTER_LEDS_COUNT + 1);
    } else if (is_caps_word_enabled) {
        color_leds(210, 50, 100, caps_word_leds, NUMBER_LEDS_COUNT + LETTER_LEDS_COUNT + 4);
    }
    return false;
}
