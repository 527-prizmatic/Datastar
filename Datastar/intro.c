#include "intro.h"

float intro_TimerGlobal = 0.f;
float intro_TimerShader = 0.f;

char* intro_TxtPressStart;

void intro_Init() {
	snd_Preload(SND_MUS, "origin.ogg", "origin");
	tex_Preload("logo_datastar.png", "logo");
	tex_Preload("intro_screens\\1.png", "intro_1");
	tex_Preload("intro_screens\\2.png", "intro_2");
	tex_Preload("intro_screens\\3.png", "intro_3");
	tex_Preload("intro_screens\\4.png", "intro_4");

	intro_TxtPressStart = calloc(0, 25 * sizeof(char));
}

void intro_Update() {
	if (snd_GetMusicState() != sfPlaying) mus_Play("origin");
	intro_TimerGlobal += getDeltaTime();

	if ((kb_TestPress(sfKeySpace) || gp_TestPress(0, GP_BUTTON_A)) && intro_TimerGlobal < 24.f) {
		intro_TimerGlobal = 24.f;
		mus_SetPos("origin", 24.f);
	}
	if ((kb_TestPressAnyKey() || gp_TestPressAny()) && intro_TimerGlobal >= 25.5f) {
		menu_SetSubstate(MENU_MAIN);
		gs_ChangeState(GS_MENU);
	}
}

void intro_Render() {
	va_DrawScreenBorders();

	if (intro_TimerGlobal <= 6.f) {
		rq_Draw(RQ_SPRITE, NULL, Vector2f(960.f, 200.f), "intro_1", RQ_TEX_NORECT, Vector2f(375.f, 0.f), 0.f, RQ_SCALE_DEFAULT, RQ_SPRCLR_NONE);

		vt_DrawText(Vector2f(960.f, 770.f), "THE YEAR IS 204X,", 20, TXT_CENTER, sfWhite);
		vt_DrawText(Vector2f(960.f, 800.f), "AND CRYPTOCURRENCY HAS SUPPLANTED", 20, TXT_CENTER, sfWhite);
		vt_DrawText(Vector2f(960.f, 830.f), "ALL OTHER FORMS OF ECONOMY.", 20, TXT_CENTER, sfWhite);
	}
	else if (intro_TimerGlobal <= 12.f) {
		rq_Draw(RQ_SPRITE, NULL, Vector2f(960.f, 200.f), "intro_2", RQ_TEX_NORECT, Vector2f(375.f, 0.f), 0.f, RQ_SCALE_DEFAULT, RQ_SPRCLR_NONE);

		vt_DrawText(Vector2f(960.f, 770.f), "THE BLOCKCHAIN HAS BECOME A BATTLEFIELD", 20, TXT_CENTER, sfWhite);
		vt_DrawText(Vector2f(960.f, 800.f), "INFESTED WITH RAVENOUS PROSPECTORS", 20, TXT_CENTER, sfWhite);
		vt_DrawText(Vector2f(960.f, 830.f), "LOOKING TO MINE VALUABLE CURRENCIES.", 20, TXT_CENTER, sfWhite);

	}
	else if (intro_TimerGlobal <= 18.f) {
		rq_Draw(RQ_SPRITE, NULL, Vector2f(960.f, 200.f), "intro_3", RQ_TEX_NORECT, Vector2f(375.f, 0.f), 0.f, RQ_SCALE_DEFAULT, RQ_SPRCLR_NONE);

		vt_DrawText(Vector2f(960.f, 770.f), "ONLY THE HARDIEST DATAMINERS", 20, TXT_CENTER, sfWhite);
		vt_DrawText(Vector2f(960.f, 800.f), "DARE TRY THEIR LUCK AT THE", 20, TXT_CENTER, sfWhite);
		vt_DrawText(Vector2f(960.f, 830.f), "MOST VALUABLE OF THEM ALL...", 20, TXT_CENTER, sfWhite);
	}
	else if (intro_TimerGlobal <= 24.f) {
		rq_Draw(RQ_SPRITE, NULL, Vector2f(960.f, 200.f), "intro_4", RQ_TEX_NORECT, Vector2f(375.f, 0.f), 0.f, RQ_SCALE_DEFAULT, RQ_SPRCLR_NONE);
		vt_DrawText(Vector2f(960.f, 790.f), "THE DATASTAR.", 40, TXT_CENTER, sfWhite);
	}
	else {
		rq_Draw(RQ_SPRITE, NULL, Vector2f(960.f, 175.f), "logo", RQ_TEX_NORECT, Vector2f(783.f, 0.f), 0.f, RQ_SCALE_DEFAULT, RQ_SPRCLR_NONE);
		vt_DrawText(Vector2f(960.f, 862.5f), "PRESS ANY KEY TO BEGIN", 25, TXT_CENTER, sfWhite);
	}

	if (intro_TimerGlobal >= 22.f && intro_TimerGlobal <= 26.f) {
		if (intro_TimerGlobal <= 24.f) intro_TimerShader = pow2(.5f * clamp(intro_TimerGlobal - 22.f, 0.f, 2.f));
		else intro_TimerShader = 1.f - pow2(.5f * clamp(intro_TimerGlobal - 24.f, 0.f, 2.f));

		rq_Draw(RQ_RECTANGLE, NULL, NULLVECTF, Vector2f(1920.f, 1080.f), NULLVECTF, ColorA(255, 255, 255, 255 * intro_TimerShader), 0.f, RQ_SCALE_DEFAULT);
	}
}

void intro_Unload() {
	snd_Unload("origin");
	tex_Unload("logo");
	free(intro_TxtPressStart);
}
