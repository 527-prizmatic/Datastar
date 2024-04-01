#include "level_1.h"

sfBool lv1_Complete = sfFalse;
float lv1_TimerGlobal = 0.f;
float lv1_TimerCompleted = 0.f;

void lv1_Init() {
	snd_Preload(SND_MUS, "ode_to_the_future.wav", "future");

}

void lv1_Update() {
	if (snd_GetMusicState() == SND_STOPPED) mus_FadeIn("future");
	lv1_TimerGlobal += getDeltaTime();
	if (lv1_Complete) {
		mus_FadeOut();
		if (ISZERO(lv1_TimerCompleted)) game_SetScrollSpeed(5000.f, Bars(2));
		lv1_TimerCompleted += getDeltaTime();
		if (lv1_TimerCompleted >= Bars(2)) {
			gs_ChangeState(GS_MENU);
			if (score_Best[0] < score_Get()) score_Best[0] = score_Get();
			game_LastLevelUnlocked = 2;
			sav_Save();
		}
	}
}

void lv1_Unload() {
	snd_Unload("future");
}

void lv1_End() { lv1_Complete = sfTrue; }

void lv1_SpawnWaves(int _wave_num) {
	switch (_wave_num) {
	case 1:
//		mus_SetLoop("future", TimeSpan(Bars(1), Beats(1)));
		wave_CreateWall(1);
		wave_CreateWall(6);
		break;

	case 2:
//		mus_StopLoop("future");
//		mus_SetPos("future", Bars(2));
		wave_CreateWall(2);
		wave_CreateWall(5);
		break;

	case 3:
		wave_CreateWall(3);
		wave_CreateWall(4);
		break;

	case 4: case 5: case 6: case 7:
		wave_CreateWallBarrier();
		break;

	case 8:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 390.f), PWR_NONE);
		break;

	case 9:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 690.f), PWR_NONE);
		break;

	case 10:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 240.f), PWR_SCORE);
		wave_CreateWall(4);
		wave_CreateWall(5);
		wave_CreateWall(6);
		break;

	case 11:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 840.f), PWR_NONE);
		wave_CreateWall(1);
		wave_CreateWall(2);
		wave_CreateWall(3);
		break;

	case 12: case 14:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 440.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 640.f), PWR_NONE);
		break;

	case 15:
		wave_CreateWallBarrier();
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 140.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 940.f), PWR_NONE);

	case 13:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 180.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 900.f), PWR_NONE);
		break;

	case 16:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 240.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 390.f), PWR_SCORE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 540.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 690.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 840.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 240.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 840.f), PWR_NONE);
//		plr_IncreaseBullets(1);
		break;

	case 17:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 540.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 340.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 740.f), PWR_NONE);
		break;

	case 18:
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 440.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 640.f), PWR_NONE);
		break;

	case 19:
		en_Dart(Vector2f(game_GetScrollX() + 3200.f, 150.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2800.f, 280.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2400.f, 410.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 540.f), PWR_HP);
		en_Dart(Vector2f(game_GetScrollX() + 2400.f, 670.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2800.f, 800.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 3200.f, 930.f), PWR_NONE);
		break;

	case 20:
		wave_CreateWall(3);
		wave_CreateWall(6);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 190.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 540.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 890.f), PWR_NONE);
		en_Streak(Vector2f(game_GetScrollX() + 2000.f, 540.f), 1, PWR_SCORE);
		break;

	case 21:
		wave_CreateWall(1);
		wave_CreateWall(5);
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 140.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 940.f), PWR_NONE);
		en_Streak(Vector2f(game_GetScrollX() + 2120.f, 770.f), 1, PWR_NONE);
		break;

	case 22:
		wave_CreateWall(2);
		wave_CreateWall(6);
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 340.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2500.f, 740.f), PWR_NONE);
		en_Streak(Vector2f(game_GetScrollX() + 2000.f, 240.f), 1, PWR_NONE);
		break;

	case 23:
		wave_CreateWall(2);
		wave_CreateWall(4);
		wave_CreateWall(5);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 540.f), PWR_NONE);
		en_Streak(Vector2f(game_GetScrollX() + 2000.f, 150.f), 1, PWR_NONE);
		en_Streak(Vector2f(game_GetScrollX() + 2000.f, 930.f), 1, PWR_NONE);
		break;

	case 24:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 280.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 430.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 650.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 800.f), PWR_NONE);
		en_Streak(Vector2f(game_GetScrollX() + 2000.f, 390.f), 1, PWR_NONE);
		en_Streak(Vector2f(game_GetScrollX() + 2120.f, 520.f), 0, PWR_HP);
		en_Streak(Vector2f(game_GetScrollX() + 2240.f, 650.f), 1, PWR_NONE);
		break;

	case 28: case 29: case 30: case 31:
		wave_CreateWallBarrier();
		break;

	case 32:
		mus_SetLoop("future", TimeSpan(Bars(40), Bars(8)));
		en_Gamma(Vector2f(game_GetScrollX() + 2500.f, 540.f), PWR_NONE);
		game_SetScrollSpeed(400.f, Bars(2));
		break;

	default: break;
	}
}