#include "init.h"

float timerStateInit;

void init_Init() {
	timerStateInit = 0.f;
}

void init_Update() {
	timerStateInit += getDeltaTime();
}

void init_Render() {
	va_DrawRectangle(VA_LINE, NULL, FloatRect(100.f, 100.f, 1720.f, 880.f), ColorA(255, 255, 255, clamp(timerStateInit * 64.f, 0.f, 255.f)));
	if (timerStateInit <= 12.f) {
		for (int i = 0; i < 3; i++) {
			vt_DrawText(Vector2f(960.f, 467.5f + i), "THIS GAME IS A WORK OF FICTION.", 20, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((4.f - fabs(timerStateInit - 4.f)) * 64.f, 0.f, 255.f)));
			vt_DrawText(Vector2f(960.f, 492.5f + i), "ANY RESEMBLANCE TO ACTUAL EVENTS OR LOCALES", 20, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((4.f - fabs(timerStateInit - 5.f)) * 64.f, 0.f, 255.f)));
			vt_DrawText(Vector2f(960.f, 517.5f + i), "OR PERSONS, LIVING OR DEAD,", 20, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((4.f - fabs(timerStateInit - 6.f)) * 64.f, 0.f, 255.f)));
			vt_DrawText(Vector2f(960.f, 542.5f + i), "WOULD BE ENTIRELY COINCIDENTAL.", 20, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((4.f - fabs(timerStateInit - 7.f)) * 64.f, 0.f, 255.f)));
			vt_DrawText(Vector2f(960.f, 592.5f + i), "(C) 2024 ALL RIGHTS RESERVED.", 20, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((4.f - fabs(timerStateInit - 8.f)) * 64.f, 0.f, 255.f)));
		}
		if (kb_TestPress(sfKeySpace)) timerStateInit = 12.f;
	}
	else if (timerStateInit <= 20.f) {
		for (int i = 0; i < 3; i++) {
			vt_DrawText(Vector2f(960.f, 517.5f + i), "GAME ACADEMY LOGO", 20, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((4.f - fabs(timerStateInit - 16.f)) * 64.f, 0.f, 255.f)));
		}
		if (kb_TestPress(sfKeySpace)) timerStateInit = 20.f;
	}
	else if (timerStateInit <= 30.f) {
		for (int i = 0; i < 3; i++) {
			vt_DrawText(Vector2f(960.f, 517.5f + i), "EPILEPSY YADDI YADDA WRITE THIS OUT SOMEDAY", 20, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((5.f - fabs(timerStateInit - 25.f)) * 64.f, 0.f, 255.f)));
		}
		if (kb_TestPress(sfKeySpace)) timerStateInit = 30.f;
	}
	else gs_ChangeState(GS_INTRO);
}

void init_Unload() {

}