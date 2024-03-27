#include "bg.h"

#define MENU_SHIPS_NUM 10
#define MENU_STARS_NUM 50
#define MENU_STARS_BG_NUM 500
float menu_TimerStarPulses = .6f;

sfVector2f menu_Ships[MENU_SHIPS_NUM];
float menu_ShipsSpeeds[MENU_SHIPS_NUM];
sfVector2f menu_Stars[MENU_STARS_NUM];
float menu_StarsRadius[MENU_STARS_NUM];
float menu_StarsAngles[MENU_STARS_NUM];
sfVector2f menu_StarsBackground[MENU_STARS_BG_NUM];
float menu_StarsBgRadius = 1.f;

void m_bg_Init() {
	for (int i = 0; i < MENU_STARS_NUM; i++) {
		menu_Stars[i] = Vector2f(RANDF(0.f, 1920.f), RANDF(0.f, 1080.f));
		menu_StarsRadius[i] = 4.f;
		menu_StarsAngles[i] = RANDF(0.f, 360.f);
	}

	for (int i = 0; i < MENU_STARS_BG_NUM; i++) menu_StarsBackground[i] = Vector2f(RANDF(0.f, 1920.f), RANDF(0.f, 1080.f));

	for (int i = 0; i < MENU_SHIPS_NUM; i++) {
		menu_Ships[i] = Vector2f(RANDF(-100000.f, 0.f), RANDF(0.f, 1080.f));
		menu_ShipsSpeeds[i] = RANDF(3500.f, 7500.f);
	}
}

void m_bg_Update() {
	menu_TimerStarPulses += getDeltaTime();

	if (menu_TimerStarPulses >= .75f) {
		menu_TimerStarPulses -= .75f;
		menu_StarsBgRadius = 2.5f;
		for (int i = 0; i < MENU_STARS_NUM; i++) if (RANDF(0.f, 1.f) < 0.1f) menu_StarsRadius[i] = RANDF(10.f, 16.f);
	}
	for (int i = 0; i < MENU_STARS_NUM; i++) {
		if (menu_StarsRadius[i] >= 4.f) menu_StarsRadius[i] -= getDeltaTime() * 10.f;
		menu_Stars[i].x -= 50.f * getDeltaTime();
		if (menu_Stars[i].x <= 0.f) menu_Stars[i] = Vector2f(1920.f, RANDF(0.f, 1080.f));
	}

	for (int i = 0; i < MENU_STARS_BG_NUM; i++) {
		menu_StarsBackground[i].x -= 20.f * getDeltaTime();
		if (menu_StarsBackground[i].x <= 0.f) menu_StarsBackground[i] = Vector2f(1920.f, RANDF(0.f, 1080.f));
	}
	if (menu_StarsBgRadius >= 1.f) {
		menu_StarsBgRadius -= getDeltaTime() * 2.f;
	}

	for (int i = 0; i < MENU_SHIPS_NUM; i++) {
		menu_Ships[i].x += menu_ShipsSpeeds[i] * getDeltaTime();
		if (menu_Ships[i].x >= 2500.f) {
			menu_Ships[i] = Vector2f(RANDF(-100000.f, 0.f), RANDF(0.f, 1080.f));
			menu_ShipsSpeeds[i] = RANDF(-3000.f, 6000.f);
		}
	}
}

void m_bg_Render() {
	for (int i = 0; i < MENU_SHIPS_NUM; i++) va_DrawLine(NULL, menu_Ships[i], v_Add(menu_Ships[i], Vector2f(menu_ShipsSpeeds[i] * .1f, 0.f)), Color3(128));
	for (int i = 0; i < MENU_STARS_NUM; i++) va_DrawPolygonStar(VA_LINE, NULL, 4, menu_Stars[i], menu_StarsRadius[i], menu_StarsAngles[i], sfWhite);
	for (int i = 0; i < MENU_STARS_BG_NUM; i++) va_DrawPolygonStar(VA_LINE, NULL, 4, menu_StarsBackground[i], menu_StarsBgRadius, 0.f, sfWhite);

}

void m_bg_Unload() { }