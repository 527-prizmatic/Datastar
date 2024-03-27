#include "walls.h"

void wall_Init() {

}

void wall_Update() {

}

void wall_Render() {
	sfVector2f wall[13];
	for (int j = 0; j < 8; j++) {
		for (int i = 0; i <= 12; i++) {
			wall[i].x = (int)(game_GetScrollX() - 200.f + 200.f * i) / 200 * 200;
			wall[i].y = 100.f + sin(wall[i].x * .2f) * 50.f - j * 15.f;
		}
		va_DrawPolygon(VA_LINE, NULL, 13, wall, sfFalse, ColorA(255, 255, 255, max(255 - 40 * j, 0)));
	}

	for (int j = 0; j < 8; j++) {
		for (int i = 0; i <= 12; i++) {
			wall[i].x = (int)(game_GetScrollX() - 200.f + 200.f * i) / 200 * 200;
			wall[i].y = 980.f + sin(wall[i].x * .2f + 500.f) * 50.f + j * 15.f;
		}
		va_DrawPolygon(VA_LINE, NULL, 13, wall, sfFalse, ColorA(255, 255, 255, max(255 - 40 * j, 0)));
	}
}

void wall_Unload() {

}