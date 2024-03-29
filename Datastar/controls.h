/// Controls handler.
/// Function prefix: ctrl_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "logger.h"
#include "window_manager.h"

typedef enum {
	KEY_UP,
	KEY_DOWN,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_FIRE,
	KEY_EXTRA,
	KEY_CHANGE,
	KEY_PAUSE
} CtrlKeyId;

typedef struct {
	sfKeyCode up;
	sfKeyCode down;
	sfKeyCode left;
	sfKeyCode right;
	sfKeyCode fire;
	sfKeyCode extra;
	sfKeyCode change;
	sfKeyCode pause;
} CtrlMap;
CtrlMap ctrl;

void ctrl_SetDefaults();
CtrlMap ctrl_GetDefaults();
void ctrl_MapKeyToControl(sfKeyCode _code, CtrlKeyId _id);
void ctrl_MapTextToControl(int _code, CtrlKeyId _id);
sfKeyCode ctrl_GetKey(CtrlKeyId _id);
char* ctrl_ToString(CtrlKeyId _id);