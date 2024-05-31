#include "hud.h"

char* hud_TxtBeats, * hud_TxtWaves, *hud_TxtFrameRate;

void hud_Init() {
	hud_TxtBeats = calloc(4, sizeof(char));
	hud_TxtWaves = calloc(4, sizeof(char));
	hud_TxtFrameRate = calloc(10, sizeof(char));
}

void hud_Unload() {
	free(hud_TxtBeats);
	free(hud_TxtWaves);
}

void hud_DrawInfoTime(int _beats, int _waves) {
	sprintf(hud_TxtBeats, "%d", _beats);
	sprintf(hud_TxtWaves, "%d", _waves);
	vt_DrawText(Vector2f(25.f, 1030.f), hud_TxtBeats, 25, TXT_LEFT, sfWhite);
	vt_DrawText(Vector2f(200.f, 1030.f), hud_TxtWaves, 25, TXT_LEFT, sfWhite);
}

void hud_DrawInfoFrameRate() {
	int fr = (int)(1.f / getDtAverage());
	sprintf(hud_TxtFrameRate, "FPS %3d", fr);
	vt_DrawText(Vector2f(1768.f, 1040.f), hud_TxtFrameRate, 15, TXT_LEFT, sfWhite);
}

void hud_DrawHealth(int _hp) {
	for (int i = 0; i < _hp; i++) {
		sfVector2f hpUiPos[4];
		hpUiPos[0] = Vector2f(40.f + i * 50.f, 20.f);
		hpUiPos[1] = Vector2f(85.f + i * 50.f, 20.f);
		hpUiPos[2] = Vector2f(65.f + i * 50.f, 40.f);
		hpUiPos[3] = Vector2f(20.f + i * 50.f, 40.f);
		va_DrawPolygon(VA_TRI, NULL, 4, hpUiPos, sfTrue, Color(0, 128, 64));
	}
}

void hud_DrawMaxHealth(int _hp_max) {
	for (int i = 0; i < _hp_max; i++) {
		sfVector2f hpUiPos[4];
		hpUiPos[0] = Vector2f(40.f + i * 50.f, 20.f);
		hpUiPos[1] = Vector2f(85.f + i * 50.f, 20.f);
		hpUiPos[2] = Vector2f(65.f + i * 50.f, 40.f);
		hpUiPos[3] = Vector2f(20.f + i * 50.f, 40.f);
		va_DrawPolygon(VA_LINE, NULL, 4, hpUiPos, sfTrue, sfWhite);
		hpUiPos[0] = Vector2f(41.f + i * 50.f, 20.f);
		hpUiPos[1] = Vector2f(84.f + i * 50.f, 20.f);
		hpUiPos[2] = Vector2f(64.f + i * 50.f, 40.f);
		hpUiPos[3] = Vector2f(21.f + i * 50.f, 40.f);
		va_DrawPolygon(VA_LINE, NULL, 4, hpUiPos, sfTrue, sfWhite);
	}
}