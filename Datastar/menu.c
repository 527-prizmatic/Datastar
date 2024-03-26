#include "menu.h"

#define MENU_STARS_NUM 50
#define MENU_STARS_BG_NUM 500

float menu_TimerGlobal = 0.f;
float menu_TimerStarPulses = .6f;

sfVector2f menu_Stars[MENU_STARS_NUM];
float menu_StarsRadius[MENU_STARS_NUM];
float menu_StarsAngles[MENU_STARS_NUM];
sfVector2f menu_StarsBackground[MENU_STARS_BG_NUM];
float menu_StarsBgRadius = 1.f;

sfFloatRect menu_UiRectsMain[5];
char* menu_UiTexts[5];
int menu_MainSel = 0;

void menu_Init() {
	snd_Preload(SND_MUS, "far.ogg", "far");
	tex_Preload("logo_datastar.png", "logo");

	for (int i = 0; i < MENU_STARS_NUM; i++) {
		menu_Stars[i] = Vector2f(RANDF(0.f, 1920.f), RANDF(0.f, 1080.f));
		menu_StarsRadius[i] = 4.f;
		menu_StarsAngles[i] = RANDF(0.f, 360.f);
	}
	for (int i = 0; i < MENU_STARS_BG_NUM; i++) menu_StarsBackground[i] = Vector2f(RANDF(0.f, 1920.f), RANDF(0.f, 1080.f));

	menu_UiRectsMain[0] = FloatRect(300.f, 687.5f, 200.f, 75.f);
	menu_UiRectsMain[1] = FloatRect(525.f, 662.5f, 250.f, 125.f);
	menu_UiRectsMain[2] = FloatRect(800.f, 637.5f, 320.f, 175.f);
	menu_UiRectsMain[3] = FloatRect(1145.f, 662.5f, 250.f, 125.f);
	menu_UiRectsMain[4] = FloatRect(1420.f, 687.5f, 200.f, 75.f);
	menu_UiTexts[0] = "CREDITS";
	menu_UiTexts[1] = "OPTIONS";
	menu_UiTexts[2] = "START";
	menu_UiTexts[3] = "CONTROLS";
	menu_UiTexts[4] = "QUIT";
}

void menu_Update() {
	if (snd_GetMusicState() != sfPlaying) mus_Play("far");
	menu_TimerGlobal += getDeltaTime();
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

	for (int i = 0; i < 5; i++) {
		if (sfFloatRect_contains(&menu_UiRectsMain[i], w_GetMousePos().x, w_GetMousePos().y)) menu_MainSel = i;
	}
	
	if (kb_TestPress(sfKeyLeft) && menu_MainSel > 0) menu_MainSel--;
	if (kb_TestPress(sfKeyRight) && menu_MainSel < 4) menu_MainSel++;

	if (kb_TestPress(sfKeySpace) || w_LeftClick()) {
		switch (menu_MainSel) {
		case 0: printf("credits\n"); break;
		case 1: printf("options\n"); break;
		case 2: gs_ChangeState(GS_GAME); break;
		case 3: printf("controls\n"); break;
		case 4: gs_ChangeState(GS_EXIT); break;
		}
	}
}

void menu_Render() {
	va_DrawScreenBorders();
	rq_Draw(RQ_SPRITE, NULL, Vector2f(960.f, 190.f + sin(menu_TimerGlobal * .5f) * 20.f), "logo", RQ_TEX_NORECT, Vector2f(783.f, 0.f), 0.f, RQ_SCALE(.6f), RQ_SPRCLR_NONE);

	for (int i = 0; i < MENU_STARS_NUM; i++) va_DrawPolygonStar(VA_LINE, NULL, 4, menu_Stars[i], menu_StarsRadius[i], menu_StarsAngles[i], sfWhite);
	for (int i = 0; i < MENU_STARS_BG_NUM; i++) va_DrawPolygonStar(VA_LINE, NULL, 4, menu_StarsBackground[i], menu_StarsBgRadius, 0.f, sfWhite);

	for (int i = 0; i < 5; i++) {
		sfFloatRect frame = menu_UiRectsMain[i];
		sfColor clr = i == menu_MainSel ? sfWhite : Color3(64);
		if (i == menu_MainSel) frame.top -= 25.f;
		if (i == menu_MainSel) frame = floatRect_Expand(frame, 15.f);
		va_DrawFrame(NULL, frame, clr);

		for (int j = 0; j < 3; j++) {
			sfVector2f textPos = Vector2f(frame.left + frame.width * .5f, frame.top + frame.height * .5f - 10.f + j);
			clr.a = 255 - j * 82;
			vt_DrawText(textPos, menu_UiTexts[i], 20 + 4 * (i % 2) + 8 * (i == 2), TXT_CENTER, clr);
		}
	}
}

void menu_Unload() {
	snd_Unload("far");
	tex_Unload("logo");
}