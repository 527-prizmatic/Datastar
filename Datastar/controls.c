#include "controls.h"

sfKeyCode* ctrl_GetKeyPtr(CtrlKeyId _id);

void ctrl_SetDefaults() {
	ctrl = ctrl_GetDefaults();
}

CtrlMap ctrl_GetDefaults() { return (CtrlMap) { sfKeyUp, sfKeyDown, sfKeyLeft, sfKeyRight, sfKeySpace, sfKeyE, sfKeyTab, sfKeyEscape }; }

void ctrl_MapKeyToControl(sfKeyCode _code, CtrlKeyId _id) {
	_id--;
	switch (_id) {
		case KEY_UP: ctrl.up = _code; break;
		case KEY_DOWN: ctrl.down = _code; break;
		case KEY_LEFT: ctrl.left = _code; break;
		case KEY_RIGHT: ctrl.right = _code; break;
		case KEY_FIRE: ctrl.fire = _code; break;
		case KEY_EXTRA: ctrl.extra = _code; break;
		case KEY_CHANGE: ctrl.change = _code; break;
		case KEY_PAUSE: ctrl.pause = _code; break;
	}
	for (int i = 0; i < 8; i++) {
		if (i != _id && *ctrl_GetKeyPtr(i) == _code) *ctrl_GetKeyPtr(i) = -1;
	}
}

void ctrl_MapTextToControl(int _code, CtrlKeyId _id) {
	sfKeyCode key = -1;
	if (_code >= 97 && _code <= 122) key = _code - 97;
	if (_code >= 48 && _code <= 57) key = _code - 22;
	else {
		switch (_code) {
		case ',':	key = sfKeyComma; break;
		case ';':	key = sfKeySemicolon; break;
		case '.':	key = sfKeyPeriod; break;
		case '-':	key = sfKeyHyphen; break;
		case ' ':	key = sfKeySpace; break;
		case 9:		key = sfKeyTab; break;
		case 127:	key = sfKeyBackspace; break;
		case '(':	key = sfKeyLBracket; break;
		case ')':	key = sfKeyRBracket; break;
		case '~':	key = sfKeyTilde; break;
		case 10:
		case 13:	key = sfKeyEnter; break;
		case '=':	key = sfKeyEqual; break;
		}
	}

	ctrl_MapKeyToControl(key, _id);
}

sfKeyCode ctrl_GetKey(CtrlKeyId _id) {
	switch (_id) {
		case KEY_UP: return ctrl.up;
		case KEY_DOWN: return ctrl.down;
		case KEY_LEFT: return ctrl.left;
		case KEY_RIGHT: return ctrl.right;
		case KEY_FIRE: return ctrl.fire;
		case KEY_EXTRA: return ctrl.extra;
		case KEY_CHANGE: return ctrl.change;
		case KEY_PAUSE: return ctrl.pause;
	}
}

sfKeyCode* ctrl_GetKeyPtr(CtrlKeyId _id) {
	switch (_id) {
	case KEY_UP: return &ctrl.up;
	case KEY_DOWN: return &ctrl.down;
	case KEY_LEFT: return &ctrl.left;
	case KEY_RIGHT: return &ctrl.right;
	case KEY_FIRE: return &ctrl.fire;
	case KEY_EXTRA: return &ctrl.extra;
	case KEY_CHANGE: return &ctrl.change;
	case KEY_PAUSE: return &ctrl.pause;
	}
}

char* ctrl_ToString(CtrlKeyId _id) {
	int key;
	switch (_id) {
		case KEY_UP: key = ctrl.up; break;
		case KEY_DOWN: key = ctrl.down; break;
		case KEY_LEFT: key = ctrl.left; break;
		case KEY_RIGHT: key = ctrl.right; break;
		case KEY_FIRE: key = ctrl.fire; break;
		case KEY_EXTRA: key = ctrl.extra; break;
		case KEY_CHANGE: key = ctrl.change; break;
		case KEY_PAUSE: key = ctrl.pause; break;
	}

	switch (key) {
		case sfKeyUnknown: return "";
		case sfKeyA: return "A";
		case sfKeyB: return "B";
		case sfKeyC: return "C";
		case sfKeyD: return "D";
		case sfKeyE: return "E";
		case sfKeyF: return "F";
		case sfKeyG: return "G";
		case sfKeyH: return "H";
		case sfKeyI: return "I";
		case sfKeyJ: return "J";
		case sfKeyK: return "K";
		case sfKeyL: return "L";
		case sfKeyM: return "M";
		case sfKeyN: return "N";
		case sfKeyO: return "O";
		case sfKeyP: return "P";
		case sfKeyQ: return "Q";
		case sfKeyR: return "R";
		case sfKeyS: return "S";
		case sfKeyT: return "T";
		case sfKeyU: return "U";
		case sfKeyV: return "V";
		case sfKeyW: return "W";
		case sfKeyX: return "X";
		case sfKeyY: return "Y";
		case sfKeyZ: return "Z";
		case sfKeyNum0: return "0";
		case sfKeyNum1: return "1";
		case sfKeyNum2: return "2";
		case sfKeyNum3: return "3";
		case sfKeyNum4: return "4";
		case sfKeyNum5: return "5";
		case sfKeyNum6: return "6";
		case sfKeyNum7: return "7";
		case sfKeyNum8: return "8";
		case sfKeyNum9: return "9";
		case sfKeyEscape: return "ESCAPE";
		case sfKeyLControl: return "LCTRL";
		case sfKeyLShift: return "LSHIFT";
		case sfKeyLAlt: return "LALT";
		case sfKeyLSystem: return "LSYSTEM";
		case sfKeyRControl: return "RCTRL";
		case sfKeyRShift: return "RSHIFT";
		case sfKeyRAlt: return "RALT";
		case sfKeyRSystem: return "RSYSTEM";
		case sfKeyMenu: return "MENU";
		case sfKeyLBracket: return "LBRACKET";
		case sfKeyRBracket: return "RBRACKET";
		case sfKeySemicolon: return "SEMICOLON";
		case sfKeyComma: return "COMMA";
		case sfKeyPeriod: return "PERIOD";
		case sfKeyQuote: return "QUOTE";
		case sfKeySlash: return "SLASH";
		case sfKeyBackslash: return "BASH";
		case sfKeyTilde: return "TILDE";
		case sfKeyEqual: return "EQUAL";
		case sfKeyHyphen: return "HYPHEN";
		case sfKeySpace: return "SPACE";
		case sfKeyEnter: return "RETURN";
		case sfKeyBackspace: return "BACKSPACE";
		case sfKeyTab: return "TAB";
		case sfKeyPageUp: return "PAGEUP";
		case sfKeyPageDown: return "PAGEDOWN";
		case sfKeyEnd: return "END";
		case sfKeyHome: return "HOME";
		case sfKeyInsert: return "INS";
		case sfKeyDelete: return "DEL";
		case sfKeyAdd: return "ADD";
		case sfKeySubtract: return "SUBTRACT";
		case sfKeyMultiply: return "MULTIPLY";
		case sfKeyDivide: return "DIVIDE";
		case sfKeyLeft: return "LARROW";
		case sfKeyRight: return "RARROW";
		case sfKeyUp: return "UARROW";
		case sfKeyDown: return "DARROW";
		case sfKeyNumpad0: return "NUM0";
		case sfKeyNumpad1: return "NUM1";
		case sfKeyNumpad2: return "NUM2";
		case sfKeyNumpad3: return "NUM3";
		case sfKeyNumpad4: return "NUM4";
		case sfKeyNumpad5: return "NUM5";
		case sfKeyNumpad6: return "NUM6";
		case sfKeyNumpad7: return "NUM7";
		case sfKeyNumpad8: return "NUM8";
		case sfKeyNumpad9: return "NUM9";
		case sfKeyF1: return "F1";
		case sfKeyF2: return "F2";
		case sfKeyF3: return "F3";
		case sfKeyF4: return "F4";
		case sfKeyF5: return "F5";
		case sfKeyF6: return "F6";
		case sfKeyF7: return "F7";
		case sfKeyF8: return "F8";
		case sfKeyF9: return "F9";
		case sfKeyF10: return "F10";
		case sfKeyF11: return "F11";
		case sfKeyF12: return "F12";
		case sfKeyF13: return "F13";
		case sfKeyF14: return "F14";
		case sfKeyF15: return "F15";
		case sfKeyPause: return "PAUSE";
		default: return "NONE";
	}
}