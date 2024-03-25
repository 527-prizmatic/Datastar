#include "gamepad.h"

sfBool gp_Enabled;
char gp_ButtonStates[8][32];
sfVector2f gp_StickStates[8][4];

sfBool gp_IsEnabled() { return gp_Enabled; }

void gp_Enable() {
	if (gp_Enabled == sfFalse) {
		gp_Enabled = sfTrue;
		log_LogStr(LOG_INFO, "Gamepad input enabled", sfTrue, sfTrue);
	}
}

void gp_Disable() {
	if (gp_Enabled == sfTrue) {
		gp_Enabled = sfFalse;
		log_LogStr(LOG_INFO, "Gamepad input disabled", sfTrue, sfTrue);
	}
}

sfBool gp_TestIdle(int _gpid, gp_ButtonID _i) {
	if (_i == GP_BUTTON_ANY) {
		for (int i = 0; i < 32; i++) {
			if (gp_ButtonStates[_gpid][i] != 0) return sfFalse;
		}
		return sfTrue;
	}
	return gp_ButtonStates[_gpid][_i] == 0;
}

sfBool gp_TestPress(int _gpid, gp_ButtonID _i) {
	if (_i == GP_BUTTON_ANY) {
		for (int i = 0; i < 32; i++) {
			if (gp_ButtonStates[_gpid][i] == 1) return sfTrue;
		}
		return sfFalse;
	}
	return gp_ButtonStates[_gpid][_i] == 1;
}

sfBool gp_TestHold(int _gpid, gp_ButtonID _i) {
	if (_i == GP_BUTTON_ANY) {
		for (int i = 0; i < 32; i++) {
			if (gp_ButtonStates[_gpid][i] == 2) return sfTrue;
		}
		return sfFalse;
	}
	return gp_ButtonStates[_gpid][_i] == 2;
}

sfBool gp_TestRelease(int _gpid, gp_ButtonID _i) {
	if (_i == GP_BUTTON_ANY) {
		for (int i = 0; i < 32; i++) {
			if (gp_ButtonStates[_gpid][i] == 3) return sfTrue;
		}
		return sfFalse;
	}
	return gp_ButtonStates[_gpid][_i] == 3;
}

sfBool gp_StickIdle(int _gpid, gp_StickID _i) { return v_Mag2(gp_StickStates[_gpid][_i]) < pow2(STICK_DEADZONE); }

sfVector2f gp_StickState(int _gpid, gp_StickID _i) {
	return gp_StickStates[_gpid][_i];
}

void gp_Update() {
	if (!w_HasFocus() || !gp_IsEnabled()) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 16; j++) gp_ButtonStates[i][j] = 0;
			gp_StickStates[i][GP_STICK_LEFT] = NULLVECTF;
			gp_StickStates[i][GP_STICK_RIGHT] = NULLVECTF;
			gp_StickStates[i][GP_STICK_TRIGGERS] = NULLVECTF;
			gp_StickStates[i][GP_STICK_DPAD] = NULLVECTF;
		}
	}
	else {
		sfJoystick_update();
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 32; j++) {
				if (sfJoystick_isButtonPressed(i, j)) {
					if (gp_ButtonStates[i][j] == 0 || gp_ButtonStates[i][j] == 3) gp_ButtonStates[i][j] = 1;
					else gp_ButtonStates[i][j] = 2;
				}
				else {
					if (gp_ButtonStates[i][j] == 1 || gp_ButtonStates[i][j] == 2) gp_ButtonStates[i][j] = 3;
					else gp_ButtonStates[i][j] = 0;
				}
			}
			gp_StickStates[i][GP_STICK_LEFT].x = sfJoystick_getAxisPosition(i, sfJoystickX);
			gp_StickStates[i][GP_STICK_LEFT].y = sfJoystick_getAxisPosition(i, sfJoystickY);
			gp_StickStates[i][GP_STICK_RIGHT].x = sfJoystick_getAxisPosition(i, sfJoystickU);
			gp_StickStates[i][GP_STICK_RIGHT].y = sfJoystick_getAxisPosition(i, sfJoystickV);
			gp_StickStates[i][GP_STICK_TRIGGERS].x = sfJoystick_getAxisPosition(i, sfJoystickZ);
			gp_StickStates[i][GP_STICK_TRIGGERS].y = sfJoystick_getAxisPosition(i, sfJoystickR);
			gp_StickStates[i][GP_STICK_DPAD].x = sfJoystick_getAxisPosition(i, sfJoystickPovX);
			gp_StickStates[i][GP_STICK_DPAD].y = sfJoystick_getAxisPosition(i, sfJoystickPovY);
 		}
	}
}