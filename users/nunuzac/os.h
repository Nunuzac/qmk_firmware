#pragma once
#include "nunuzac.h"

typedef enum {
    WIN,
    LNX,
    OSX
} os_type;

os_type get_current_os(void);
void set_current_os(os_type val);
uint16_t get_os_shortcut(shortcut_t intended);
