#include "menu_main.h"

sfFloatRect menu_UiRectsMain[5];
VtnVaText* menu_UiTexts[5];
int menu_MainSel = 2;

void m_main_Init() {
	menu_UiRectsMain[0] = FloatRect(300.f, 687.5f, 200.f, 75.f);
	menu_UiRectsMain[1] = FloatRect(525.f, 662.5f, 250.f, 125.f);
	menu_UiRectsMain[2] = FloatRect(800.f, 637.5f, 320.f, 175.f);
	menu_UiRectsMain[3] = FloatRect(1145.f, 662.5f, 250.f, 125.f);
	menu_UiRectsMain[4] = FloatRect(1420.f, 687.5f, 200.f, 75.f);

	menu_UiTexts[0] = vtn_Text("CREDITS",	20, TXT_LEFT);
	menu_UiTexts[1] = vtn_Text("OPTIONS",	24, TXT_LEFT);
	menu_UiTexts[2] = vtn_Text("START",		28, TXT_LEFT);
	menu_UiTexts[3] = vtn_Text("CONTROLS",	24, TXT_LEFT);
	menu_UiTexts[4] = vtn_Text("QUIT",		20, TXT_LEFT);
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
		vtn_Draw(menu_UiTexts[i], Vector2f(frame.left + frame.width * .5f, frame.top + frame.height * .5f), clr);
	}
}

void m_main_Unload() {
	for (int i = 0; i < 5; i++) vtn_DestroyText(menu_UiTexts[i]);
}
