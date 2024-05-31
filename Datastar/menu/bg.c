#include "bg.h"

#define BG_MENU_SHIPS 10
#define BG_MENU_STARS 250
float menu_TimerStarPulses = .6f;

sfVector2f menu_Ships[BG_MENU_SHIPS];
float menu_ShipsSpeeds[BG_MENU_SHIPS];

bg_Star bg_StarList[BG_MENU_STARS] = { 0 };

void m_bg_Init() {
	for (int i = 0; i < BG_MENU_STARS; i++) {
		bg_StarList[i].size_base = RANDF(1.f, 6.f);
		bg_StarList[i].size = bg_StarList[i].size_base;
		bg_StarList[i].angle = RANDF(0.f, 360.f);
		bg_StarList[i].scroll_spd = RANDF(bg_StarList[i].size_base * 6.f, bg_StarList[i].size_base * 8.f) + 4.f;
		bg_StarList[i].pos = Vector2f(RANDF(0.f, 1920.f), RANDF(0.f, 1080.f));
	}

	for (int i = 0; i < BG_MENU_SHIPS; i++) {
		menu_Ships[i] = Vector2f(RANDF(-100000.f, 0.f), RANDF(0.f, 1080.f));
		menu_ShipsSpeeds[i] = RANDF(3500.f, 7500.f);
	}
}

void m_bg_Update() {
	menu_TimerStarPulses += getDeltaTime();

	if (menu_TimerStarPulses >= .75f) {
		menu_TimerStarPulses -= .75f;
		for (int i = 0; i < BG_MENU_STARS; i++) {
			bg_StarList[i].size *= RANDF(1.25f, 1.5f);
			if (RANDF(0.f, 1.f) < 0.1f && bg_StarList[i].size < bg_StarList[i].size_base * 1.5f) {
				bg_StarList[i].size *= RANDF(2.f, 3.f);
				bg_StarList[i].rot_spd = RANDF(60.f, 720.f);
			}
		}
	}

	for (int i = 0; i < BG_MENU_STARS; i++) {
		if (bg_StarList[i].size > bg_StarList[i].size_base) bg_StarList[i].size -= getDeltaTime() * bg_StarList[i].size_base * 2.f;
		if (bg_StarList[i].rot_spd > 0.f) bg_StarList[i].rot_spd *= pow(.25f, getDeltaTime());

		bg_StarList[i].pos.x -= bg_StarList[i].scroll_spd * getDeltaTime();
		bg_StarList[i].angle -= bg_StarList[i].rot_spd * getDeltaTime();

		if (bg_StarList[i].pos.x < -10.f) {
			bg_StarList[i].size_base = RANDF(1.f, 6.f);
			bg_StarList[i].size = bg_StarList[i].size_base;
			bg_StarList[i].angle = RANDF(0.f, 360.f);
			bg_StarList[i].scroll_spd = RANDF(bg_StarList[i].size_base * 6.f, bg_StarList[i].size_base * 8.f) + 4.f;
			bg_StarList[i].pos = Vector2f(2000.f, RANDF(0.f, 1080.f));
		}
	}

	for (int i = 0; i < BG_MENU_SHIPS; i++) {
		menu_Ships[i].x += menu_ShipsSpeeds[i] * getDeltaTime();
		if (menu_Ships[i].x >= 2500.f) {
			menu_Ships[i] = Vector2f(RANDF(-100000.f, 0.f), RANDF(0.f, 1080.f));
			menu_ShipsSpeeds[i] = RANDF(-3000.f, 6000.f);
		}
	}
}

void m_bg_Render() {
	for (int i = 0; i < BG_MENU_SHIPS; i++) va_DrawLine(NULL, menu_Ships[i], v_Add(menu_Ships[i], Vector2f(menu_ShipsSpeeds[i] * .1f, 0.f)), Color3(128));
	for (int i = 0; i < BG_MENU_STARS; i++) va_DrawPolygonStar(VA_LINE, NULL, 4, bg_StarList[i].pos, bg_StarList[i].size, bg_StarList[i].angle, sfWhite);

}

void m_bg_Unload() { }