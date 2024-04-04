#include "level_3.h"

sfBool lv3_Complete = sfFalse;
float lv3_TimerGlobal = 0.f;
float lv3_TimerCompleted = 0.f;

char lv3_SpawnGlimmers = 0;
sfBool lv3_Waiting;

/// Spawns a single Glimmer on a randomized grid position.
void lv3_spawnGlimmer();

void lv3_Init() {
	snd_Preload(SND_MUS, "soft_glow.wav", "glow");
	lv3_Complete = sfFalse;
	lv3_TimerGlobal = 0.f;
	lv3_TimerCompleted = 0.f;
	lv3_SpawnGlimmers = 0;
	lv3_Waiting = sfTrue;
}

void lv3_Update() {
	if (snd_GetMusicState() == SND_STOPPED) mus_FadeIn("glow");
	lv3_TimerGlobal += getDeltaTime();
	sfx_AmbientLv3();

	if (game_GetBeatFlag() && lv3_SpawnGlimmers) for (int i = 0; i < lv3_SpawnGlimmers; i++) lv3_spawnGlimmer();

	if (lv3_Complete) {
		plr_Invincible(sfTrue);
		mus_FadeOut();
		if (lv3_TimerCompleted > Beats(2) && lv3_Waiting) {
			lv3_Waiting = sfFalse;
			game_SetScrollSpeed(5000.f, Bars(2));
		}
		lv3_TimerCompleted += getDeltaTime();
		if (lv3_TimerCompleted >= Bars(2)) {
			gs_ChangeState(GS_MENU);
			if (score_Best[2] < score_Get()) score_Best[2] = score_Get();
			if (game_LastLevelUnlocked < 4) game_LastLevelUnlocked = 4;
			sav_Save();
		}
	}
}

void lv3_Unload() {
	snd_Unload("glow");
}

void lv3_End() { lv3_Complete = sfTrue; }

void lv3_SpawnWaves(int _wave_num) {
	switch (_wave_num) {
	case 0:
		wave_CreateWall(1);
		wave_CreateWall(3);
		break;

	case 1:
		wave_CreateWall(4);
		wave_CreateWall(5);
		break;

	case 2:
		wave_CreateWall(3);
		wave_CreateWall(5);
		lv3_SetGlimmerSpawn(1);
		break;

	case 3:
		wave_CreateWall(2);
		wave_CreateWall(6);
		break;

	case 7:
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 240.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2100.f, 390.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2200.f, 690.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2300.f, 840.f), PWR_NONE);
		break;

	case 9:
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 240.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2100.f, 390.f), PWR_SCORE);
		en_Dart(Vector2f(game_GetScrollX() + 2200.f, 690.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2300.f, 840.f), PWR_NONE);
		break;

	case 11:
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 240.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2100.f, 390.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2200.f, 690.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2300.f, 840.f), PWR_SCORE);
		break;

	case 12:
		wave_CreateWall(3);
		wave_CreateWall(4);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 340.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 540.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 740.f), PWR_NONE);
		break;

	case 13:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 440.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 240.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2100.f, 390.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2200.f, 690.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2300.f, 840.f), PWR_NONE);
		break;
	
	case 14:
		wave_CreateWall(1);
		wave_CreateWall(6);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 160.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 900.f), PWR_NONE);
		en_Streak(Vector2f(game_GetScrollX() + 2200.f, 540.f), 0, PWR_HP);
		en_Streak(Vector2f(game_GetScrollX() + 2300.f, 540.f), 1, PWR_NONE);
		break;

	case 15:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 640.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 240.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2100.f, 390.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2200.f, 690.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2300.f, 840.f), PWR_NONE);
		break;

	case 16:
		en_Flare(Vector2f(game_GetScrollX() + 3500.f, 540.f), Bars(4));
		break;

	case 17:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 640.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 240.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2100.f, 390.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2200.f, 690.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2300.f, 840.f), PWR_NONE);
		break;

	case 18:
		lv3_SetGlimmerSpawn(2);
		break;

	case 19:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 640.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 240.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2100.f, 390.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2200.f, 690.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2300.f, 840.f), PWR_NONE);
		en_Pulse(Vector2f(game_GetScrollX() + 1760.f, 240.f), Beats(4));
		en_Pulse(Vector2f(game_GetScrollX() + 1760.f, 840.f), Beats(6));
		break;

	case 20:
		wave_CreateWall(2);
		wave_CreateWall(5);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 440.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 640.f), PWR_NONE);
		en_Pulse(Vector2f(game_GetScrollX() + 1610.f, 240.f), Beats(4));
		en_Pulse(Vector2f(game_GetScrollX() + 1610.f, 840.f), Beats(6));
		break;

	case 21:
		wave_CreateWall(1);
		wave_CreateWall(6);
		en_Pulse(Vector2f(game_GetScrollX() + 1460.f, 240.f), Beats(4));
		en_Pulse(Vector2f(game_GetScrollX() + 1460.f, 840.f), Beats(6));
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 240.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2100.f, 390.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2200.f, 690.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2300.f, 840.f), PWR_NONE);
		break;

	case 22:
		en_Pulse(Vector2f(game_GetScrollX() + 1310.f, 240.f), Beats(4));
		en_Pulse(Vector2f(game_GetScrollX() + 1310.f, 840.f), Beats(6));
		en_Streak(Vector2f(game_GetScrollX() + 2200.f, 540.f), 0, PWR_NONE);
		en_Streak(Vector2f(game_GetScrollX() + 2300.f, 540.f), 1, PWR_NONE);
		lv3_SetGlimmerSpawn(3);
		break;

	case 23:
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 240.f), PWR_HP);
		en_Dart(Vector2f(game_GetScrollX() + 2100.f, 390.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2200.f, 690.f), PWR_POWER);
		en_Dart(Vector2f(game_GetScrollX() + 2300.f, 840.f), PWR_NONE);
		break;

	case 24:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 190.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 340.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 740.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 890.f), PWR_NONE);
		en_Flare(Vector2f(game_GetScrollX() + 3500.f, 540.f), Bars(4));
		break;

	case 25:
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 240.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2100.f, 390.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2200.f, 690.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2300.f, 840.f), PWR_NONE);
		break;

	case 26:
		lv3_SetGlimmerSpawn(4);
		game_SetScrollSpeed(0.f, Bars(2));
		break;

	case 27:
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 240.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2100.f, 390.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2200.f, 690.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2300.f, 840.f), PWR_NONE);
		break;

	case 28:
		en_Incandesce(Vector2f(game_GetScrollX() + 960.f, 350.f));
		break;
	
	case 30:
		lv3_SetGlimmerSpawn(2);
		break;

	case 32:
		lv3_SetGlimmerSpawn(1);
		break;

	case 34:
		lv3_SetGlimmerSpawn(0);
		break;

	case 36:
//		mus_SetLoop("glow", TimeSpan(Bars(36), Bars(8)));
		mus_SetPos("glow", Bars(36));
		break;

		/// Boss spawns on wave 28, falls from the sky over 4 bars, crashes down on wave 32
		/// Charges up power, begins all-out assault on wase 36
		/// Music loops around waves 36-44

	default: break;
	}
}

void lv3_spawnGlimmer() {
	float x = RAND(0, 32) * 100.f;
	float y = RAND(1, 10) * 100.f - 10.f;

	x += game_GetScrollX();
	x = 100.f * (int)(x / 100);

	en_Glimmer(Vector2f(x, y), Bars(2), 0.f);
}

void lv3_SetGlimmerSpawn(int _i) { lv3_SpawnGlimmers = _i; }