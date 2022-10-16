#pragma once
#include "../Resources/resource.h"

/// PROGRAM CUSTOM CONSTANTS

#define BUTTON_CLOSE 101
#define BUTTON_MINIMIZE 102
#define BUTTON_CONFIRM 103
#define BUTTON_CANCEL 104
#define BUTTON_FMODEON 105
#define BUTTON_FMODEOFF 106
#define BUTTON_EMODEON 107
#define BUTTON_EMODEOFF 108
#define BUTTON_GITHUB 109

/// PROGRAM CUSTOM WINDOW STYLES
#define C_WS_OVERLAPPEDWINDOW (WS_OVERLAPPED     | \
                             WS_CAPTION        | \
                             WS_SYSMENU        | \
                             WS_THICKFRAME     | \
                             WS_MINIMIZEBOX)