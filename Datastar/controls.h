/// Controls handler.
/// Function prefix: ctrl_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "logger.h"
#include "window_manager.h"

/// All control types required by the game
typedef enum {
	KEY_UP, /// Movement up
	KEY_DOWN, /// Movement down
	KEY_LEFT, /// Movement left
	KEY_RIGHT, /// Movement right
	KEY_FIRE, /// Firing
	KEY_EXTRA, /// \deprecated Useless at the moment, but created in advance in case the need for a new keybind comes up (probably for overdrives)
	KEY_CHANGE, /// Changing weapons
	KEY_PAUSE /// Pause and returning to menu
} CtrlKeyId;

/// Data structure holding control info
typedef struct {
	sfKeyCode up;
	sfKeyCode down;
	sfKeyCode left;
	sfKeyCode right;
	sfKeyCode fire;
	sfKeyCode extra; /// \deprecated
	sfKeyCode change;
	sfKeyCode pause;
} CtrlMap;
CtrlMap ctrl; /// Control map currently in use

/// Resets the control map to its default values - Arrow keys for movement, space for firing, tab to switch weapons and escape to return to the menu.
void ctrl_SetDefaults();

/// \return Control map containing default values
CtrlMap ctrl_GetDefaults();

/// Associates the given key code to the given control.
void ctrl_MapKeyToControl(sfKeyCode _code, CtrlKeyId _id);

/// Converts Unicode characters into their respective key codes, then maps them to the given control.
void ctrl_MapTextToControl(int _code, CtrlKeyId _id);

/// \return The key currently mapped to the given control
sfKeyCode ctrl_GetKey(CtrlKeyId _id);

/// \return Name of the given key
char* ctrl_ToString(CtrlKeyId _id);