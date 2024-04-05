#include "menu_controls.h"

char menu_CtrlEdit = 0;
char menu_CtrlSpacePressed = 0;
char menu_CtrlSelRow = 0, menu_CtrlSelCol = 0;

void m_ctrl_Init() {
	menu_CtrlEdit = 0;
	menu_CtrlSpacePressed = 0;
	menu_CtrlSelRow = 0;
	menu_CtrlSelCol = 0;
}

void m_ctrl_Update() {
	if (!menu_CtrlEdit) {
		if (kb_TestPress(sfKeyDown) && menu_CtrlSelRow != 4) menu_CtrlSelRow++;
		if (kb_TestPress(sfKeyUp) && menu_CtrlSelRow != 0) menu_CtrlSelRow--;
		if (kb_TestPress(sfKeyRight) && menu_CtrlSelCol != 1) menu_CtrlSelCol++;
		if (kb_TestPress(sfKeyLeft) && menu_CtrlSelCol != 0) menu_CtrlSelCol--;

		if (kb_TestPress(sfKeySpace)) {
			if (menu_CtrlSelRow == 4) {
				if (menu_CtrlSelCol == 0) ctrl_SetDefaults();
				else menu_SetSubstate(MENU_MAIN);
			}
			else {
				menu_CtrlSpacePressed = 1;
				menu_CtrlEdit = 1 + 4 * menu_CtrlSelCol + menu_CtrlSelRow;
			}
		}
	}
	else {
		if (menu_CtrlSpacePressed) {
			if (kb_TestRelease(sfKeySpace)) menu_CtrlSpacePressed = 0;
		}
		else if ((w_Get())->e.type == sfEvtKeyPressed) {
			ctrl_MapKeyToControl((w_Get())->e.key.code, menu_CtrlEdit);
			sav_Save();
			menu_CtrlEdit = 0;
		}
		else if ((w_Get())->e.type == sfEvtTextEntered) {
			ctrl_MapTextToControl((w_Get())->e.text.unicode, menu_CtrlEdit);
			sav_Save();
			menu_CtrlEdit = 0;
		}
	}
}

void m_ctrl_Render() {
	menu_RenderLogo(0.f);

	sfColor colors[5][2] = { 0 };
	for (int i = 0; i < 5; i++) for (int j = 0; j < 2; j++) colors[i][j] = clrDGray;
	colors[menu_CtrlSelRow][menu_CtrlSelCol] = sfWhite;
	vt_DrawText(Vector2f(190.f, 625.f), "MOVE UP", 25, TXT_LEFT, colors[0][0]);
	vt_DrawText(Vector2f(190.f, 675.f), "MOVE DOWN", 25, TXT_LEFT, colors[1][0]);
	vt_DrawText(Vector2f(190.f, 725.f), "MOVE LEFT", 25, TXT_LEFT, colors[2][0]);
	vt_DrawText(Vector2f(190.f, 775.f), "MOVE RIGHT", 25, TXT_LEFT, colors[3][0]);
	vt_DrawText(Vector2f(980.f, 625.f), "SHOOT/CONFIRM", 25, TXT_LEFT, colors[0][1]);
	vt_DrawText(Vector2f(980.f, 675.f), "EXTRA", 25, TXT_LEFT, colors[1][1]);
	vt_DrawText(Vector2f(980.f, 725.f), "CHANGE WEAPON", 25, TXT_LEFT, colors[2][1]);
	vt_DrawText(Vector2f(980.f, 775.f), "BACK/PAUSE", 25, TXT_LEFT, colors[3][1]);

	vt_DrawText(Vector2f(940.f, 625.f),  menu_CtrlEdit == 1 ? "PRESS KEY" : ctrl_ToString(KEY_UP), 25, TXT_RIGHT, colors[0][0]);
	vt_DrawText(Vector2f(940.f, 675.f),  menu_CtrlEdit == 2 ? "PRESS KEY" : ctrl_ToString(KEY_DOWN), 25, TXT_RIGHT, colors[1][0]);
	vt_DrawText(Vector2f(940.f, 725.f),  menu_CtrlEdit == 3 ? "PRESS KEY" : ctrl_ToString(KEY_LEFT), 25, TXT_RIGHT, colors[2][0]);
	vt_DrawText(Vector2f(940.f, 775.f),  menu_CtrlEdit == 4 ? "PRESS KEY" : ctrl_ToString(KEY_RIGHT), 25, TXT_RIGHT, colors[3][0]);
	vt_DrawText(Vector2f(1730.f, 625.f), menu_CtrlEdit == 5 ? "PRESS KEY" : ctrl_ToString(KEY_FIRE), 25, TXT_RIGHT, colors[0][1]);
	vt_DrawText(Vector2f(1730.f, 675.f), menu_CtrlEdit == 6 ? "PRESS KEY" : ctrl_ToString(KEY_EXTRA), 25, TXT_RIGHT, colors[1][1]);
	vt_DrawText(Vector2f(1730.f, 725.f), menu_CtrlEdit == 7 ? "PRESS KEY" : ctrl_ToString(KEY_CHANGE), 25, TXT_RIGHT, colors[2][1]);
	vt_DrawText(Vector2f(1730.f, 775.f), menu_CtrlEdit == 8 ? "PRESS KEY" : ctrl_ToString(KEY_PAUSE),    25, TXT_RIGHT, colors[3][1]);

	vt_DrawText(Vector2f(565.f, 850.f), "DEFAULTS", 25, TXT_CENTER, colors[4][0]);
	vt_DrawText(Vector2f(1315.f, 850.f), "DONE", 25, TXT_CENTER, colors[4][1]);
}

void m_ctrl_Unload() {

}