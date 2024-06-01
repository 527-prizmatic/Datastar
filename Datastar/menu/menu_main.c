#include "menu_main.h"

sfFloatRect menu_UiRectsMain[5];
char* menu_UiTexts[5];
int menu_MainSel = 2;

void m_main_Init() {
	menu_UiRectsMain[0] = FloatRect(300.f, 687.5f, 200.f, 75.f);
	menu_UiRectsMain[1] = FloatRect(525.f, 662.5f, 250.f, 125.f);
	menu_UiRectsMain[2] = FloatRect(800.f, 637.5f, 320.f, 175.f);
	menu_UiRectsMain[3] = FloatRect(1145.f, 662.5f, 250.f, 125.f);
	menu_UiRectsMain[4] = FloatRect(1420.f, 687.5f, 200.f, 75.f);
	menu_UiTexts[0] = "CREDITS";
	menu_UiTexts[1] = "OPTIONS";
	menu_UiTexts[2] = "START";
	menu_UiTexts[3] = "CONTROLS";
	menu_UiTexts[4] = "QUIT";
}

void m_main_Update() {
	gp_Dir dir = gp_StickDirOnce(0, GP_STICK_LEFT);
	if (dir == GP_DIR_IDLE) dir = gp_StickDirOnce(0, GP_STICK_DPAD);

	if ((kb_TestPress(sfKeyLeft) || dir == GP_DIR_LEFT) && menu_MainSel > 0) menu_MainSel--;
	if ((kb_TestPress(sfKeyRight) || dir == GP_DIR_RIGHT) && menu_MainSel < 4) menu_MainSel++;

	if (kb_TestPress(sfKeySpace) || gp_TestPress(0, GP_BUTTON_A)) {
		switch (menu_MainSel) {
			case 0: menu_SetSubstate(MENU_CREDITS); break;
			case 1: menu_SetSubstate(MENU_OPTIONS); break;
			case 2: menu_SetSubstate(MENU_SELECT); break;
			case 3: menu_SetSubstate(MENU_CONTROLS); break;
			case 4:
				sav_Save(); 
				gs_ChangeState(GS_EXIT);
				break;
		}
	}
}

void m_main_Render() {
	menu_RenderLogo(0.f);

	for (int i = 0; i < 5; i++) {
		sfFloatRect frame = menu_UiRectsMain[i];
		sfColor clr = i == menu_MainSel ? sfWhite : Color3(64);
		if (i == menu_MainSel) frame.top -= 25.f;
		if (i == menu_MainSel) frame = floatRect_Expand(frame, 15.f);
		va_DrawRectangle(VA_TRI, NULL, floatRect_Expand(frame, 3.f), ColorA(0, 0, 0, 224));
		va_DrawFrame(NULL, frame, clr);

		for (int j = 0; j < 3; j++) {
			sfVector2f textPos = Vector2f(frame.left + frame.width * .5f, frame.top + frame.height * .5f - 10.f + j);
			clr.a = 255 - j * 82;
			vt_DrawText(textPos, menu_UiTexts[i], 20 + 4 * (i % 2) + 8 * (i == 2), TXT_CENTER, clr);
		}
	}
}

void m_main_Unload() {

}
