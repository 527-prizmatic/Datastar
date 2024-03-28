#include "init.h"

float init_TimerGlobal = 0.f;

void init_Init() {
	tex_Preload("ga.png", "ga");
}

void init_Update() {
	init_TimerGlobal += getDeltaTime();
}

void init_Render() {
	va_DrawScreenBorders();

	if (init_TimerGlobal <= 12.f) {
		vt_DrawText(Vector2f(960.f, 437.5f), "THIS GAME IS A WORK OF FICTION.", 28, TXT_CENTER, ColorA(255, 255, 255, clamp((4.f - fabs(init_TimerGlobal - 4.f)) * 64.f, 0.f, 255.f)));
		vt_DrawText(Vector2f(960.f, 472.5f), "ANY RESEMBLANCE TO ACTUAL EVENTS OR LOCALES", 28, TXT_CENTER, ColorA(255, 255, 255, clamp((4.f - fabs(init_TimerGlobal - 5.f)) * 64.f, 0.f, 255.f)));
		vt_DrawText(Vector2f(960.f, 507.5f), "OR PERSONS, LIVING OR DEAD,", 28, TXT_CENTER, ColorA(255, 255, 255, clamp((4.f - fabs(init_TimerGlobal - 6.f)) * 64.f, 0.f, 255.f)));
		vt_DrawText(Vector2f(960.f, 542.5f), "WOULD BE ENTIRELY COINCIDENTAL.", 28, TXT_CENTER, ColorA(255, 255, 255, clamp((4.f - fabs(init_TimerGlobal - 7.f)) * 64.f, 0.f, 255.f)));
		vt_DrawText(Vector2f(960.f, 612.5f), "ALL RIGHTS RESERVED.", 28, TXT_CENTER, ColorA(255, 255, 255, clamp((4.f - fabs(init_TimerGlobal - 8.f)) * 64.f, 0.f, 255.f)));

		if (kb_TestPress(sfKeySpace)) init_TimerGlobal = 12.f;
	}
	else if (init_TimerGlobal <= 20.f) {
		for (int i = 0; i < 3; i++) {
			//vt_DrawText(Vector2f(960.f, 528.5f + i), "GAME ACADEMY LOGO", 28, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((4.f - fabs(init_TimerGlobal - 16.f)) * 64.f, 0.f, 255.f)));
			rq_Draw(RQ_SPRITE, NULL, Vector2f(960.f, 540.f), "ga", RQ_TEX_NORECT, Vector2f(193.f, 230.f), 0.f, RQ_SCALE(.75f), ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((4.f - fabs(init_TimerGlobal - 16.f)) * 64.f, 0.f, 255.f)));
		}
		if (kb_TestPress(sfKeySpace)) init_TimerGlobal = 20.f;
	}
	else if (init_TimerGlobal <= 30.f) {
		for (int i = 0; i < 3; i++) {
			vt_DrawText(Vector2f(960.f, 493.5f + i), "THIS VIDEO GAME CONTAINS BRIGHT COLORS", 28, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((5.f - fabs(init_TimerGlobal - 25.f)) * 64.f, 0.f, 255.f)));
			vt_DrawText(Vector2f(960.f, 528.5f + i), "AND FLASHING LIGHTS WHICH MAY CAUSE DISCOMFORT", 28, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((5.f - fabs(init_TimerGlobal - 25.f)) * 64.f, 0.f, 255.f)));
			vt_DrawText(Vector2f(960.f, 563.5f + i), "OR TRIGGER SEIZURES FOR SENSITIVE PEOPLE.", 28, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((5.f - fabs(init_TimerGlobal - 25.f)) * 64.f, 0.f, 255.f)));
			vt_DrawText(Vector2f(960.f, 598.5f + i), "REMEMBER TO TAKE FREQUENT BREAKS!", 28, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((5.f - fabs(init_TimerGlobal - 25.f)) * 64.f, 0.f, 255.f)));
		}
		if (kb_TestPress(sfKeySpace)) init_TimerGlobal = 30.f;
	}
	else gs_ChangeState(GS_INTRO);
}

void init_Unload() {
	tex_Unload("ga");
}