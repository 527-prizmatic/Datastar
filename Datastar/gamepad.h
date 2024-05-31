/// (C) 2024 The Prizmanager
/// Author - J.Sebastien Toussaint
/// 
/// Gamepad input processor.
/// Function prefix: gp_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "window_manager.h"
#include "logger.h"

#define STICK_DEADZONE 10.f
#define STICK_DEADZONE_2 100.f

typedef enum {
	GP_BUTTON_ANY = -1,
	GP_BUTTON_A = 0,
	GP_BUTTON_B = 1,
	GP_BUTTON_X = 2,
	GP_BUTTON_Y = 3,
	GP_BUTTON_LB = 4,
	GP_BUTTON_RB = 5,
	GP_BUTTON_VIEW = 6,
	GP_BUTTON_MENU = 7,
	GP_BUTTON_LJOY = 8,
	GP_BUTTON_RJOY = 9
} gp_ButtonID;

typedef enum {
	GP_STICK_LEFT		= 0,
	GP_STICK_RIGHT		= 1,
	GP_STICK_TRIGGERS	= 2,
	GP_STICK_DPAD		= 3
} gp_StickID;

typedef enum {
	GP_DIR_IDLE			= 0,
	GP_DIR_UP			= 1,
	GP_DIR_DOWN			= 2,
	GP_DIR_LEFT			= 3,
	GP_DIR_RIGHT		= 4,
} gp_Dir;

sfBool gp_IsEnabled();

/// Enables gamepad input.
void gp_Enable();

/// Disables gamepad input.
void gp_Disable();

/// Checks if a gamepad button is currently idle.
sfBool gp_TestIdle(int _gpid, gp_ButtonID _i);

/// Checks if a gamepad button was just pressed.
sfBool gp_TestPress(int _gpid, gp_ButtonID _i);

/// Checks if a gamepad button is being held down.
sfBool gp_TestHold(int _gpid, gp_ButtonID _i);

/// Checks if a gamepad button was just released.
sfBool gp_TestRelease(int _gpid, gp_ButtonID _i);

/// Checks whether a gamepad joystick is registering any input.
sfBool gp_StickIdle(int _gpid, gp_StickID _i);

/// Reads and returns the current state of a gamepad joystick.
sfVector2f gp_StickState(int _gpid, gp_StickID _i);

/// Reads and returns the current direction of a gamepad joystick.
gp_Dir gp_StickDir(int _gpid, gp_StickID _i);

void gp_Update();