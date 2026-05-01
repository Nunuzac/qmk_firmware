#pragma once
#include QMK_KEYBOARD_H

typedef enum {
    WIN,
    LNX,
    OSX
} os_type;

enum layers {
    QWERTY,
    WORKMAN,
    FUNCTION,
    GAMES
};

typedef enum shortcut {
    COPY,
    CUT,
    PASTE,
    SAVE,
    UNDO,
    REDO,
    NEW_TAB,
    LAST_TAB,
    FIND,
    FIND_ALL,
    REPLACE,
    REPLACE_ALL
} shortcut_t;

os_type get_current_os(void);
void set_current_os(os_type val);
uint16_t get_os_shortcut(shortcut_t intended);
