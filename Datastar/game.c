#include "game.h"

float game_TimerBeats = 0.f;
float game_TimerGlobal = 0.f;
float game_BeatTime;
int game_Waves = 0;
int game_Beats = 1;
sfBool game_BeatFlag = sfFalse, game_WaveFlag = sfFalse;
int game_Level;

float game_ScrollSpeed, game_ScrollSpeedOld, game_ScrollSpeedTarget;
float game_TimeCallSetSpeed, game_SpeedChangeTime;

float Beats(int _i) { return game_BeatTime * _i; }
float Bars(int _i) { return game_BeatTime * _i * 4.f; }

void game_Init() {
	shd_Preload(NULL, "grid.frag", "bg_grid");

	model_Init();
	game_View = sfView_createFromRect(FloatRect(0.f, 0.f, 1920.f, 1080.f));
	game_ViewPos = sfView_getCenter(game_View);

	plr_Init();
	en_Init();
	plb_Init();
	enb_Init();
	pwr_Init();
	score_Init();
	hud_Init();
	sfx_ScoreInit();

	game_TimerGlobal = 0.f;
	game_TimerBeats = 0.f;
	game_BeatTime = 60.f / wave_GetTempo(game_GetLevel());
	game_Waves = 30;
	game_Beats = 1;
	game_ScrollSpeed = 3000.f;
	game_ScrollSpeedOld = 3000.f;
	game_ScrollSpeedTarget = 300.f;
	game_TimeCallSetSpeed = 0.f;
	game_SpeedChangeTime = Beats(2);
}

void game_Update() {
	game_TimerBeats += getDeltaTime();
	game_TimerGlobal += getDeltaTime();

	if (game_TimeCallSetSpeed + game_SpeedChangeTime > game_TimerGlobal) {
		game_ScrollSpeed = itp_Float(game_ScrollSpeedOld, game_ScrollSpeedTarget, (game_TimerGlobal - game_TimeCallSetSpeed) / game_SpeedChangeTime, itp_Linear);
	}
	game_ViewPos = v_Add(game_ViewPos, Vector2f(game_ScrollSpeed * getDeltaTime(), 0.f));
	sfView_setCenter(game_View, game_ViewPos);

	game_UpdateLevel();
	if (gs_state == GS_MENU) return;

	plr_Update();
	if (plr_Player.hp == 0) return;
	en_Update();
	if (gs_state == GS_MENU) return;
	plb_Update();
	enb_Update();
	pwr_Update();
	score_Update();
	sfx_ScoreUpdate();

	game_BeatFlag = sfFalse;
	game_WaveFlag = sfFalse;
	if (game_TimerBeats >= Beats(1)) {
		game_TimerBeats -= Beats(1);
		game_BeatFlag = sfTrue;
		if (game_Beats == 4) {
			game_Beats = 0;
			game_WaveFlag = sfTrue;
		}
		game_Beats++;
	}

	if (game_WaveFlag) {
		game_Waves++;
		wave_Generate(game_Level, game_Waves);
	}

	if (kb_TestPress(sfKeyEscape)) gs_ChangeState(GS_MENU);
}

void game_Render() {
	sfShader_setFloatUniform(shd_FetchShader("bg_grid"), "time", game_TimerGlobal);
	for (int i = 0; i < 20; i++) va_DrawLine("bg_grid", Vector2f(i * 96.f, 0.f), Vector2f(i * 96.f, 1080.f), sfWhite);
	for (int i = 0; i < 12; i++) va_DrawLine("bg_grid", Vector2f(0.f, i * 96.f + 24.f), Vector2f(1920.f, i * 96.f + 24.f), sfWhite);

	if (plr_Player.inv_frames > 0.f) {
		sfVector2f shake = v_Mul(Vector2f(RANDF(-20.f, 20.f), RANDF(-20.f, 20.f)), itp_Float(0.f, 1.f, clamp(plr_Player.inv_frames * .5f - 1.f, 0.f, 1.f), itp_Linear));
		sfView_move(game_View, shake);
	}
	w_SetView(game_View);

	plr_Render();
	en_Render();
	plb_Render();
	enb_Render();
	pwr_Render();
	wall_Render();
	ptc_Render();
	sfx_ScoreRender();

	w_ResetView();
	hud_DrawHealth(plr_Player.hp);
	hud_DrawMaxHealth(plr_Player.hp_max);
	hud_DrawInfoTime(game_Beats, game_Waves);
	score_Render();
}

void game_Unload() {
	plr_Unload();
	en_Unload();
	plb_Unload();
	enb_Unload();
	pwr_ClearBuffer();
	score_Unload();
	hud_Unload();
	sfx_ScoreClearBuffer();

	game_UnloadLevel();

//	shd_Unload("bg_grid");
}

float game_GetScrollX() { return sfView_getCenter(game_View).x - 960.f; }

sfBool game_IsOnScreen(sfVector2f _pos) {
	if (_pos.x < game_GetScrollX() - 50.f) return sfFalse;
	else if (_pos.x > game_GetScrollX() + 1970.f) return sfFalse;
	if (_pos.y < -50.f) return sfFalse;
	else if (_pos.y > 1130.f) return sfFalse;
	return sfTrue;
}

sfBool game_GetBeatFlag() { return game_BeatFlag; }

void game_LoadLevel(int _lvl) {
	game_Level = _lvl;
	game_InitLevel();
}

int game_GetLevel() { return game_Level; }

void game_SetScrollSpeed(float _target, float _time) {
	game_TimeCallSetSpeed = game_TimerGlobal;
	game_SpeedChangeTime = _time;
	game_ScrollSpeedOld = game_ScrollSpeed;
	game_ScrollSpeedTarget = _target;
}

float game_GetScrollSpeed() { return game_ScrollSpeed; }

float game_GetTime() { return game_TimerGlobal; }

void game_InitLevel() {
	switch (game_Level) {
		case 1: lv1_Init(); break;
		case 2: lv2_Init(); break;
		default: break;
	}
}

void game_UpdateLevel() {
	switch (game_Level) {
		case 1: lv1_Update(); break;
		case 2: lv2_Update(); break;
		default: break;
	}
}

void game_UnloadLevel() {
	switch (game_Level) {
		case 1: lv1_Unload(); break;
		case 2: lv2_Unload(); break;
		default: break;
	}
}