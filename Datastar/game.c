#include "game.h"

float init_TimerGlobal;

void game_Init() {
	model_Init();
	game_View = sfView_createFromRect(FloatRect(0.f, 0.f, 1920.f, 1080.f));

	plr_Init();
	en_Init();
	plb_Init();

	init_TimerGlobal = 5.f;
}

void game_Update() {
	init_TimerGlobal += getDeltaTime();
	sfView_move(game_View, Vector2f(100.f * getDeltaTime(), 0.f));
	plr_Update();
	if (plr_Player.hp == 0) return;
	en_Update();
	plb_Update();

	if (init_TimerGlobal >= 5.f) {
		init_TimerGlobal = 0.f;
		for (int i = 1; i < 7; i++) if (RAND_BOOL) en_New(EN_WALL, Vector2f(game_GetScrollX() + 2000.f, i * 135.f + 67.5f));
	}
}

void game_Render() {
	w_SetView(game_View);

	plr_Render();
	en_Render();
	plb_Render();
	wall_Render();
	ptc_Render();

	w_ResetView();

	for (int i = 0; i < plr_Player.hp; i++) {
		sfVector2f hpUiPos[4];
		hpUiPos[0] = Vector2f(40.f + i * 50.f, 20.f);
		hpUiPos[1] = Vector2f(85.f + i * 50.f, 20.f);
		hpUiPos[2] = Vector2f(65.f + i * 50.f, 40.f);
		hpUiPos[3] = Vector2f(20.f + i * 50.f, 40.f);
		va_DrawPolygon(VA_TRI, NULL, 4, hpUiPos, sfTrue, Color(0, 128, 64));
	}

	for (int i = 0; i < plr_Player.hp_max; i++) {
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

	vt_DrawText(Vector2f(25.f, 1030.f), "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789", 25, TXT_LEFT, sfWhite);
}

void game_Unload() {
	plr_Unload();
	en_Unload();
	plb_Unload();
}

float game_GetScrollX() { return sfView_getCenter(game_View).x - 960.f; }

sfBool game_IsOnScreen(sfVector2f _pos) {
	if (_pos.x < game_GetScrollX() - 25.f) return sfFalse;
	else if (_pos.x > game_GetScrollX() + 1945.f) return sfFalse;
	if (_pos.y < -25.f) return sfFalse;
	else if (_pos.y > 1105.f) return sfFalse;
	return sfTrue;
}