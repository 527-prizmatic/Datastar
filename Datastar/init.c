#include "init.h"

float init_TimerGlobal = 0.f;

void init_Init() {
}

void init_Update() {
	init_TimerGlobal += getDeltaTime();
}

void init_Render() {
	va_DrawScreenBorders();

	if (init_TimerGlobal <= 12.f) {
		for (int i = 0; i < 3; i++) {
			vt_DrawText(Vector2f(960.f, 437.5f + i), "THIS GAME IS A WORK OF FICTION.", 28, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((4.f - fabs(init_TimerGlobal - 4.f)) * 64.f, 0.f, 255.f)));
			vt_DrawText(Vector2f(960.f, 472.5f + i), "ANY RESEMBLANCE TO ACTUAL EVENTS OR LOCALES", 28, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((4.f - fabs(init_TimerGlobal - 5.f)) * 64.f, 0.f, 255.f)));
			vt_DrawText(Vector2f(960.f, 507.5f + i), "OR PERSONS, LIVING OR DEAD,", 28, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((4.f - fabs(init_TimerGlobal - 6.f)) * 64.f, 0.f, 255.f)));
			vt_DrawText(Vector2f(960.f, 542.5f + i), "WOULD BE ENTIRELY COINCIDENTAL.", 28, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((4.f - fabs(init_TimerGlobal - 7.f)) * 64.f, 0.f, 255.f)));
			vt_DrawText(Vector2f(960.f, 612.5f + i), "ALL RIGHTS RESERVED.", 28, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((4.f - fabs(init_TimerGlobal - 8.f)) * 64.f, 0.f, 255.f)));
		}
		if (kb_TestPress(sfKeySpace)) init_TimerGlobal = 12.f;
	}
	else if (init_TimerGlobal <= 20.f) {
		for (int i = 0; i < 3; i++) {
			vt_DrawText(Vector2f(960.f, 528.5f + i), "GAME ACADEMY LOGO", 28, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((4.f - fabs(init_TimerGlobal - 16.f)) * 64.f, 0.f, 255.f)));
		}
		if (kb_TestPress(sfKeySpace)) init_TimerGlobal = 20.f;
	}
	else if (init_TimerGlobal <= 30.f) {
		for (int i = 0; i < 3; i++) {
			vt_DrawText(Vector2f(960.f, 528.5f + i), "EPILEPSY YADDI YADDA WRITE THIS OUT SOMEDAY", 28, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((5.f - fabs(init_TimerGlobal - 25.f)) * 64.f, 0.f, 255.f)));
		}
		if (kb_TestPress(sfKeySpace)) init_TimerGlobal = 30.f;
	}
	else gs_ChangeState(GS_INTRO);
}

void init_Unload() {

}