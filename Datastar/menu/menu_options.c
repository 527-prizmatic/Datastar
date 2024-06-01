#include "menu_options.h"

char menu_OptionsSel = 0;
char menu_ChangingVolMus = 0;
char menu_ChangingVolSnd = 0;
char menu_ChangingFps = 0;
enum { MENU_FPS_10, MENU_FPS_20, MENU_FPS_30, MENU_FPS_40, MENU_FPS_60, MENU_FPS_120, MENU_FPS_INF } menu_FpsSel;
char menu_TextFps[4];

void m_options_Init() {
	menu_OptionsSel = 0;
	menu_ChangingVolMus = 0;
	menu_ChangingVolSnd = 0;
	menu_ChangingFps = 0;
}

void m_options_Update() {
	gp_Dir dir = gp_StickDirOnce(0, GP_STICK_LEFT);
	if (dir == GP_DIR_IDLE) dir = gp_StickDirOnce(0, GP_STICK_DPAD);

	gp_Dir dirHold = gp_StickDir(0, GP_STICK_LEFT);
	if (dirHold == GP_DIR_IDLE) dir = gp_StickDir(0, GP_STICK_DPAD);

	if (window.framerate == 10u) menu_FpsSel = MENU_FPS_10;
	if (window.framerate == 20u) menu_FpsSel = MENU_FPS_20;
	else if (window.framerate == 30u) menu_FpsSel = MENU_FPS_30;
	else if (window.framerate == 40u) menu_FpsSel = MENU_FPS_40;
	else if (window.framerate == 60u) menu_FpsSel = MENU_FPS_60;
	else if (window.framerate == 120u) menu_FpsSel = MENU_FPS_120;
	else if (window.framerate == 10000u) menu_FpsSel = MENU_FPS_INF;
	else {
		window.framerate = 60u;
		menu_FpsSel = MENU_FPS_60;
	}

	if (kb_TestHold(sfKeyRight) || dirHold == GP_DIR_RIGHT) {
		if (menu_ChangingVolMus) vol_SetMus(min(100.f, vol_GetMus() + 50.f * getDeltaTime()));
		else if (menu_ChangingVolSnd) vol_SetSnd(min(100.f, vol_GetSnd() + 50.f * getDeltaTime()));
	}

	if (kb_TestHold(sfKeyLeft) || dirHold == GP_DIR_LEFT) {
		if (menu_ChangingVolMus) vol_SetMus(max(0.f, vol_GetMus() - 50.f * getDeltaTime()));
		else if (menu_ChangingVolSnd) vol_SetSnd(max(0.f, vol_GetSnd() - 50.f * getDeltaTime()));
	}

	if (menu_ChangingFps) {
		if ((kb_TestPress(sfKeyRight) || dir == GP_DIR_RIGHT) && menu_FpsSel < MENU_FPS_INF) menu_FpsSel++;
		if ((kb_TestPress(sfKeyLeft) || dir == GP_DIR_LEFT) && menu_FpsSel > MENU_FPS_20) menu_FpsSel--;
	}

	if (!menu_ChangingVolMus && !menu_ChangingVolSnd && !menu_ChangingFps) {
		if ((kb_TestPress(sfKeyRight) || dir == GP_DIR_RIGHT) && menu_OptionsSel != 4) menu_OptionsSel++;
		if ((kb_TestPress(sfKeyLeft) || dir == GP_DIR_LEFT) && menu_OptionsSel != 0) menu_OptionsSel--;

		if (gp_TestPress(0, GP_BUTTON_B)) {
			sav_Save();
			menu_SetSubstate(MENU_MAIN);
		}
	}

	if (kb_TestPress(sfKeySpace) || gp_TestPress(0, GP_BUTTON_A)) {
		if (menu_OptionsSel == 0) menu_ChangingVolMus = !menu_ChangingVolMus;
		if (menu_OptionsSel == 1) menu_ChangingVolSnd = !menu_ChangingVolSnd;
		if (menu_OptionsSel == 2) w_ToggleFS();
		if (menu_OptionsSel == 3) menu_ChangingFps = !menu_ChangingFps;
		if (menu_OptionsSel == 4) {
			sav_Save();
			menu_SetSubstate(MENU_MAIN);
		}
	}

	switch (menu_FpsSel) {
		case MENU_FPS_10: window.framerate = 10u; break;
		case MENU_FPS_20: window.framerate = 20u; break;
		case MENU_FPS_30: window.framerate = 30u; break;
		case MENU_FPS_40: window.framerate = 40u; break;
		case MENU_FPS_60: window.framerate = 60u; break;
		case MENU_FPS_120: window.framerate = 120u; break;
		case MENU_FPS_INF: window.framerate = 10000u; break;
		default: window.framerate = 60u; break;
	}
}

void m_options_Render() {
	menu_RenderLogo(0.f);

	sfColor colors[5] = { clrDGray, clrDGray, clrDGray, clrDGray, clrDGray };
	colors[menu_OptionsSel] = sfWhite;
	vt_DrawText(Vector2f(360.f, 700.f), "MUSIC VOL.", 22, TXT_CENTER, menu_ChangingVolMus ? clrDGray : colors[0]);
	vt_DrawText(Vector2f(660.f, 700.f), "SFX VOL.", 22, TXT_CENTER, colors[1]);
	vt_DrawText(Vector2f(960.f, 700.f), "FULLSCREEN", 22, TXT_CENTER, colors[2]);
	vt_DrawText(Vector2f(960.f, 735.f), w_IsFullscreen() ? "YES" : "NO", 22, TXT_CENTER, colors[2]);
	vt_DrawText(Vector2f(1260.f, 700.f), "TARGET FPS", 22, TXT_CENTER, colors[3]);
	vt_DrawText(Vector2f(1560.f, 700.f), "DONE", 22, TXT_CENTER, colors[4]);

	if (menu_FpsSel == MENU_FPS_INF) sprintf(menu_TextFps, "INF");
	else sprintf(menu_TextFps, "%d", window.framerate);
	vt_DrawText(Vector2f(1260.f, 735.f), menu_TextFps, 22, TXT_CENTER, menu_ChangingFps ? colors[3] : clrDGray);
	
	va_DrawRectangle(VA_LINE, NULL, FloatRect_FromCenter(Vector2f(360.f, 755.f), 240.f, 10.f), menu_ChangingVolMus ? colors[0] : clrDGray);
	va_DrawRectangle(VA_LINE, NULL, FloatRect_FromCenter(Vector2f(itp_Float(245.f, 475.f, vol_GetMus() / 100.f, itp_Linear), 755.f), 20.f, 20.f), menu_ChangingVolMus ? colors[0] : clrDGray);
	
	va_DrawRectangle(VA_LINE, NULL, FloatRect_FromCenter(Vector2f(660.f, 755.f), 240.f, 10.f), menu_ChangingVolSnd ? colors[1] : clrDGray);
	va_DrawRectangle(VA_LINE, NULL, FloatRect_FromCenter(Vector2f(itp_Float(545.f, 775.f, vol_GetSnd() / 100.f, itp_Linear), 755.f), 20.f, 20.f), menu_ChangingVolSnd ? colors[1] : clrDGray);
}

void m_options_Unload() {

}
