#include "intro.h"

float intro_TimerGlobal = 0.f;
float intro_TimerShader = 0.f;

char* intro_TxtPressStart;

void intro_Init() {
	snd_Preload(SND_MUS, "origin.ogg", "origin");
	tex_Preload("logo_datastar.png", "logo");

	intro_TxtPressStart = calloc(0, 25 * sizeof(char));
}

void intro_Update() {
	if (snd_GetMusicState() != sfPlaying) mus_Play("origin");
	intro_TimerGlobal += getDeltaTime();

	if (kb_TestPressAnyKey() && intro_TimerGlobal >= 25.5f) gs_ChangeState(GS_MENU);

	/// DEBUG KEYBIND, DELETE ME LATER
	if (kb_TestPress(sfKeyE)) {
		intro_TimerGlobal = 21.f;
		mus_SetPos("origin", 21.f);
	}
}

void intro_Render() {
	va_DrawScreenBorders();

	if (intro_TimerGlobal <= 6.f) {
		vt_DrawText(Vector2f(960.f, 517.5f), "INTRO 1", 20, TXT_CENTER, sfWhite);
	}
	else if (intro_TimerGlobal <= 12.f) {
		vt_DrawText(Vector2f(960.f, 517.5f), "INTRO 2", 20, TXT_CENTER, sfWhite);
	}
	else if (intro_TimerGlobal <= 18.f) {
		vt_DrawText(Vector2f(960.f, 517.5f), "INTRO 3", 20, TXT_CENTER, sfWhite);
	}
	else if (intro_TimerGlobal <= 24.f) {
		vt_DrawText(Vector2f(960.f, 517.5f), "INTRO 4", 20, TXT_CENTER, sfWhite);
	}
	// Fade to white between these two phases
	else {
		rq_Draw(RQ_SPRITE, NULL, Vector2f(960.f, 175.f), "logo", RQ_TEX_NORECT, Vector2f(783.f, 0.f), 0.f, RQ_SCALE_DEFAULT, RQ_SPRCLR_NONE);
		// Have some more UI components flash into existence after the BGM's first bar
		for (int i = 0; i < 3; i++) vt_DrawText(Vector2f(960.f, 862.5f + i), "PRESS ANY KEY TO BEGIN", 25, TXT_CENTER, sfWhite);
	}
	if (intro_TimerGlobal >= 22.f && intro_TimerGlobal <= 26.f) {
		if (intro_TimerGlobal <= 24.f) intro_TimerShader = pow2(.5f * clamp(intro_TimerGlobal - 22.f, 0.f, 2.f));
		else intro_TimerShader = 1.f - pow2(.5f * clamp(intro_TimerGlobal - 24.f, 0.f, 2.f));

		rq_Draw(RQ_RECTANGLE, NULL, NULLVECTF, Vector2f(1920.f, 1080.f), NULLVECTF, ColorA(255, 255, 255, 255 * intro_TimerShader), 0.f, RQ_SCALE_DEFAULT);
	}

/*	if (intro_TimerGlobal >= 27.5f) {
		int chars = min(23, (int)((intro_TimerGlobal - 27.5f) * 15.f));
		strncpy(intro_TxtPressStart, "PRESS ANY KEY TO BEGIN", chars);
		vt_DrawText(Vector2f(960.f, 850.f), intro_TxtPressStart, 25, TXT_CENTER, sfWhite);
	}*/
}

void intro_Unload() {
	snd_Unload("origin");
	tex_Unload("logo");
	free(intro_TxtPressStart);
}
