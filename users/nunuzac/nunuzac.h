#pragma once
#include QMK_KEYBOARD_H

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

