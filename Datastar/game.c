#include "game.h"

float game_TimerBeats = 0.f;
float game_BeatTime;
int game_Waves = 0;
int game_Beats = 1;
sfBool game_BeatFlag = sfFalse, game_WaveFlag = sfFalse;
char* game_TxtBeats, *game_TxtWaves;
int game_Level;
float game_TimerBg = 0.f;

void game_Init() {
	snd_Preload(SND_MUS, "ode_to_the_future.ogg", "future");
	shd_Preload(NULL, "grid.frag", "bg_grid");

	model_Init();
	game_View = sfView_createFromRect(FloatRect(0.f, 0.f, 1920.f, 1080.f));
	game_ViewPos = sfView_getCenter(game_View);

	plr_Init();
	en_Init();
	plb_Init();
	enb_Init();
	score_Init();

	game_TxtBeats = calloc(4, sizeof(char));
	game_TxtWaves = calloc(4, sizeof(char));
	game_LoadLevel(1);
	game_TimerBeats = 0.f;
	game_BeatTime = 60.f / wave_GetTempo(game_GetLevel());
	game_Waves = 0;
	game_Beats = 1;
}

void game_Update() {
	if (snd_GetMusicState() != sfPlaying) mus_Play("future");
	game_TimerBeats += getDeltaTime();
	game_TimerBg += getDeltaTime();
	game_ViewPos = v_Add(game_ViewPos, Vector2f(300.f * getDeltaTime(), 0.f));
	sfView_setCenter(game_View, game_ViewPos);
	plr_Update();
	if (plr_Player.hp == 0) return;
	en_Update();
	plb_Update();
	enb_Update();
	score_Update();

	game_BeatFlag = sfFalse;
	game_WaveFlag = sfFalse;
	if (game_TimerBeats >= game_BeatTime) {
		game_TimerBeats -= game_BeatTime;
		game_BeatFlag = sfTrue;
		if (game_Beats == 4) {
			game_Beats = 0;
			game_WaveFlag = sfTrue;
		}
		game_Beats++;
		sprintf(game_TxtBeats, "%d", game_Beats);
	}

	if (game_WaveFlag) {
		game_Waves++;
		wave_Generate(game_Level, game_Waves);
		sprintf(game_TxtWaves, "%d", game_Waves);
	}
}

void game_Render() {
	sfShader_setFloatUniform(shd_FetchShader("bg_grid"), "time", game_TimerBg);
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

//	vt_DrawText(Vector2f(25.f, 1030.f), "ABCDEFGHIJKLMNOPQRSTUVWXYZ 0123456789", 25, TXT_LEFT, sfWhite);
	vt_DrawText(Vector2f(25.f, 1030.f), game_TxtBeats, 25, TXT_LEFT, sfWhite);
	vt_DrawText(Vector2f(200.f, 1030.f), game_TxtWaves, 25, TXT_LEFT, sfWhite);
	score_Render();
}

void game_Unload() {
	plr_Unload();
	en_Unload();
	plb_Unload();
	enb_Unload();
	score_Unload();

	snd_Unload("future");
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

void game_LoadLevel(int _lvl) { game_Level = _lvl; }
int game_GetLevel() { return game_Level; }