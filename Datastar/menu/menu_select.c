#include "menu_select.h"

#define NYI 3

float menu_TimerSelectGlobal = 0.f, menu_TimerSelectRotate = 0.f;
sfBool menu_LeavingSelect = sfFalse;
char menu_SelectLevel = 0;
char* menu_TextScore;
float menu_LevelPosY[7];

void m_select_Init() {
	menu_TimerSelectGlobal = 0.f;
	menu_TimerSelectRotate = 0.f;
	menu_LeavingSelect = sfFalse;
	menu_TextScore = calloc(30, sizeof(char));
	for (int i = 0; i < 7; i++) menu_LevelPosY[i] = RANDF(350.f, 900.f);
}

void m_select_Update() {
	menu_TimerSelectRotate += getDeltaTime();
	if (!menu_LeavingSelect) {
		menu_TimerSelectGlobal += getDeltaTime();

		if (kb_TestPress(sfKeyRight) && menu_SelectLevel < 6 && menu_SelectLevel < game_LastLevelUnlocked - 1) menu_SelectLevel++;
		else if (kb_TestPress(sfKeyLeft) && menu_SelectLevel > 0) menu_SelectLevel--;

		if (kb_TestPress(sfKeyEscape)) {
			menu_LeavingSelect = sfTrue;
			menu_TimerSelectGlobal = 2.f;
		}

		if (kb_TestPress(sfKeySpace) && (menu_SelectLevel < NYI)) {
			game_LoadLevel(menu_SelectLevel + 1);
			gs_ChangeState(GS_GAME);
		}
	}
	else {
		menu_TimerSelectGlobal -= getDeltaTime();
		if (menu_TimerSelectGlobal <= 0.f) menu_SetSubstate(MENU_MAIN);
	}
}

void m_select_Render() {
	menu_RenderLogo(itp_Float(0.f, -600.f, clamp(menu_TimerSelectGlobal * .5f, 0.f, 1.f), itp_Smoother));
	float a = itp_Float(0.f, 255.f, clamp(menu_TimerSelectGlobal * .667f - .5f, 0.f, 1.f), itp_Linear);

	sfColor clrW = sfWhite;
	clrW.a = a;
	float offX = (menu_SelectLevel) * 400.f;
	static float offXReal = 0.f;
	offXReal = (offXReal * 7.f + offX) * .125f;

	sfVector2f levelPos[7];
	for (int i = 0; i < 7; i++) levelPos[i] = Vector2f(960.f + 400.f * i - offXReal, menu_LevelPosY[i]);

	for (int i = 0; i < 7; i++) {
		sfColor clr = game_LastLevelUnlocked > i ? sfWhite : clrDGray;
		if (i < game_LastLevelUnlocked - 1) clr = Color(96, 224, 255);
		if (i >= NYI) clr = sfRed;
		clr.a = a;
		float size = 30.f + ((i == menu_SelectLevel) * 30.f);
		va_DrawPolygonStar(VA_LINE, NULL, 4, levelPos[i], size, 0.f, clr);
		size *= .5f;
		va_DrawPolygonStar(VA_LINE, NULL, 4, levelPos[i], size, 0.f, clr);
	}

	sfColor clrSel = sfWhite;
	clrSel.a = a;
	va_DrawPolygonReg(VA_LINE, NULL, 6, levelPos[menu_SelectLevel], 80.f, menu_TimerSelectRotate * 120.f, clrSel);
	va_DrawPolygonReg(VA_LINE, NULL, 6, levelPos[menu_SelectLevel], 85.f, menu_TimerSelectRotate * 120.f, clrSel);


	for (int i = 0; i < 6; i++) {
		if (i >= game_LastLevelUnlocked - 1) break;
		sfVector2f v = v_Mul(v_Sub(levelPos[i + 1], levelPos[i]), .2f);
		va_DrawLine(NULL, v_Add(v, levelPos[i]), v_Add(v_Mul(v, 4.f), levelPos[i]), clrW);
	}

	char* title;
	switch (menu_SelectLevel) {
		case 0: title = "ODE TO THE FUTURE"; break;
		case 1: title = "CAPTAIN VALENTINE"; break;
		case 2: title = "SOFT GLOW"; break;
		default: title = "NOT YET IMPLEMENTED"; break;
	}
	sprintf(menu_TextScore, "BEST SCORE - %d", score_Best[menu_SelectLevel]);
	sfColor clrR = sfRed;
	clrR.a = a;

	vt_DrawText(Vector2f(960.f, 175.f), title, 30, TXT_CENTER, menu_SelectLevel < NYI ? clrW : clrR);
	vt_DrawText(Vector2f(960.f, 220.f), menu_TextScore, 20, TXT_CENTER, menu_SelectLevel < NYI ? clrW : clrR);
}

void m_select_Unload() {
	free(menu_TextScore);
}
