#include "keyboard.h"

sfBool kb_Enabled;
char kb_KeyStates[sfKeyCount];

sfBool kb_IsEnabled() { return kb_Enabled; }

void kb_Enable() {
	kb_Enabled = sfTrue;
	log_LogStr(LOG_INFO, "Keyboard input enabled", sfTrue, sfTrue);
}

void kb_Disable() {
	kb_Enabled = sfFalse;
	log_LogStr(LOG_INFO, "Keyboard input disabled", sfTrue, sfTrue);
}

sfBool kb_TestIdle(sfKeyCode _k) { return kb_KeyStates[_k] == 0; }
sfBool kb_TestPress(sfKeyCode _k) { return kb_KeyStates[_k] == 1; }
sfBool kb_TestHold(sfKeyCode _k) { return kb_KeyStates[_k] == 2; }
sfBool kb_TestRelease(sfKeyCode _k) { return kb_KeyStates[_k] == 3; }

sfBool kb_TestPressAnyKey() {
	for (int i = 0; i < sfKeyCount; i++) if (kb_KeyStates[i] == 1) return sfTrue;
	return sfFalse;
}

void kb_Update() {
	if (!w_HasFocus() || !kb_IsEnabled()) {
		for (int i = 0; i < sfKeyCount; i++) kb_KeyStates[i] = 0;
	}
	else {
		for (int i = 0; i < sfKeyCount; i++) {
			if (sfKeyboard_isKeyPressed(i)) {
				if (kb_KeyStates[i] == 0 || kb_KeyStates[i] == 3) kb_KeyStates[i] = 1;
				else kb_KeyStates[i] = 2;
			}
			else {
				if (kb_KeyStates[i] == 1 || kb_KeyStates[i] == 2) kb_KeyStates[i] = 3;
				else kb_KeyStates[i] = 0;
			}
		}
	}
}