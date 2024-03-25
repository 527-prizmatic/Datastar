#include "walls.h"

void wall_Init() {

}

void wall_Update() {

}

void wall_Render() {
	sfVector2f wall[13];
	for (int i = 0; i <= 12; i++) {
		wall[i].x = (int)(game_GetScrollX() - 200.f + 200.f * i) / 200 * 200;
		wall[i].y = 100.f + sin(wall[i].x * .2f) * 30.f;
	}
	va_DrawPolygon(VA_LINE, NULL, 13, wall, sfFalse, sfWhite);

	for (int i = 0; i <= 12; i++) {
		wall[i].x = (int)(game_GetScrollX() - 200.f + 200.f * i) / 200 * 200;
		wall[i].y = 980.f + sin(wall[i].x * .2f + 500.f) * 30.f;
	}
	va_DrawPolygon(VA_LINE, NULL, 13, wall, sfFalse, sfWhite);
}

void wall_Unload() {

}