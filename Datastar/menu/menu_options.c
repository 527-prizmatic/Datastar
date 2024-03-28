#include "menu_options.h"

char menu_OptionsSel = 0;
char menu_ChangingVolMus = 0;
char menu_ChangingVolSnd = 0;

void m_options_Init() {
	menu_OptionsSel = 0;
}

void m_options_Update() {
	if (kb_TestHold(sfKeyRight)) {
		if (menu_ChangingVolMus) vol_SetMus(min(100.f, vol_GetMus() + 50.f * getDeltaTime()));
		else if (menu_ChangingVolSnd) vol_SetSnd(min(100.f, vol_GetSnd() + 50.f * getDeltaTime()));
	}

	if (kb_TestHold(sfKeyLeft)) {
		if (menu_ChangingVolMus) vol_SetMus(max(0.f, vol_GetMus() - 50.f * getDeltaTime()));
		else if (menu_ChangingVolSnd) vol_SetSnd(max(0.f, vol_GetSnd() - 50.f * getDeltaTime()));
	}

	if (!menu_ChangingVolMus && !menu_ChangingVolSnd) {
		if (kb_TestPress(sfKeyRight) && menu_OptionsSel != 3) menu_OptionsSel++;
		if (kb_TestPress(sfKeyLeft) && menu_OptionsSel != 0) menu_OptionsSel--;
	}

	if (kb_TestPress(sfKeySpace)) {
		if (menu_OptionsSel == 0) menu_ChangingVolMus = !menu_ChangingVolMus;
		if (menu_OptionsSel == 1) menu_ChangingVolSnd = !menu_ChangingVolSnd;
		if (menu_OptionsSel == 2) w_ToggleFS();
		if (menu_OptionsSel == 3) menu_SetSubstate(MENU_MAIN);
	}
}

void m_options_Render() {
	sfColor colors[4] = { Color3(96), Color3(96), Color3(96), Color3(96) };
	colors[menu_OptionsSel] = sfWhite;
	vt_DrawText(Vector2f(410.f, 700.f), "MUSIC VOL.", 25, TXT_CENTER, menu_ChangingVolMus ? Color3(96) : colors[0]);
	vt_DrawText(Vector2f(760.f, 700.f), "SFX VOL.", 25, TXT_CENTER, colors[1]);
	vt_DrawText(Vector2f(1160.f, 700.f), "FULLSCREEN", 25, TXT_CENTER, colors[2]);
	vt_DrawText(Vector2f(1160.f, 735.f), w_IsFullscreen() ? "YES" : "NO", 25, TXT_CENTER, colors[2]);
	vt_DrawText(Vector2f(1510.f, 700.f), "DONE", 25, TXT_CENTER, colors[3]);

	va_DrawRectangle(VA_LINE, NULL, FloatRect_FromCenter(Vector2f(410.f, 755.f), 300.f, 10.f), menu_ChangingVolMus ? colors[0] : Color3(96));
	va_DrawRectangle(VA_LINE, NULL, FloatRect_FromCenter(Vector2f(itp_Float(265.f, 555.f, vol_GetMus() / 100.f, itp_Linear), 755.f), 20.f, 20.f), menu_ChangingVolMus ? colors[0] : Color3(96));
	
	va_DrawRectangle(VA_LINE, NULL, FloatRect_FromCenter(Vector2f(760.f, 755.f), 300.f, 10.f), menu_ChangingVolSnd ? colors[1] : Color3(96));
	va_DrawRectangle(VA_LINE, NULL, FloatRect_FromCenter(Vector2f(itp_Float(615.f, 905.f, vol_GetSnd() / 100.f, itp_Linear), 755.f), 20.f, 20.f), menu_ChangingVolSnd ? colors[1] : Color3(96));
}

void m_options_Unload() {

}
