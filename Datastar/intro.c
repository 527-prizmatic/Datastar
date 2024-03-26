#include "intro.h"

float timerStateIntro;

void intro_Init() {
	snd_Preload(SND_MUS, "origin.ogg", "origin");
	tex_Preload("logo_datastar.png", "logo");
	timerStateIntro = 0.f;
}

void intro_Update() {
	timerStateIntro += getDeltaTime();
}

void intro_Render() {
	if (snd_GetMusicState() != sfPlaying) mus_Play("origin");

	if (timerStateIntro <= 6.f) {
		vt_DrawText(Vector2f(960.f, 517.5f), "INTRO 1", 20, TXT_CENTER, sfWhite);
	}
	else if (timerStateIntro <= 12.f) {
		vt_DrawText(Vector2f(960.f, 517.5f), "INTRO 2", 20, TXT_CENTER, sfWhite);
	}
	else if (timerStateIntro <= 18.f) {
		vt_DrawText(Vector2f(960.f, 517.5f), "INTRO 3", 20, TXT_CENTER, sfWhite);
	}
	else if (timerStateIntro <= 24.f) {
		vt_DrawText(Vector2f(960.f, 517.5f), "INTRO 4", 20, TXT_CENTER, sfWhite);
	}
	// Fade to white between these two phases
	else {
		rq_Draw(RQ_SPRITE, NULL, Vector2f(960.f, 100.f), "logo", RQ_TEX_NORECT, Vector2f(783.f, 0.f), 0.f, RQ_SCALE_DEFAULT, RQ_SPRCLR_NONE);
		// Have some more UI components flash into existence after the BGM's first bar
	}
}

void intro_Unload() {
	snd_Unload("origin");
}
