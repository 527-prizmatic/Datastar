#include "level_2.h"

sfBool lv2_Complete = sfFalse;
float lv2_TimerGlobal = 0.f;
float lv2_TimerCompleted = 0.f;

void lv2_Init() {
	snd_Preload(SND_MUS, "captain_valentine.wav", "captain");

}

void lv2_Update() {
	if (snd_GetMusicState() == SND_STOPPED) mus_FadeIn("captain");
	lv2_TimerGlobal += getDeltaTime();
	if (lv2_Complete) {
		mus_FadeOut();
		if (ISZERO(lv2_TimerCompleted)) game_SetScrollSpeed(5000.f, Bars(2));
		lv2_TimerCompleted += getDeltaTime();
		if (lv2_TimerCompleted >= Bars(2)) {
			gs_ChangeState(GS_MENU);
			if (score_Best[0] < score_Get()) score_Best[0] = score_Get();
			game_LastLevelUnlocked = 3;
			sav_Save();
		}
	}
}

void lv2_Unload() {
	snd_Unload("captain");
}

void lv2_End() { lv2_Complete = sfTrue; }

void lv2_SpawnWaves(int _wave_num) {
	switch (_wave_num) {
	case 0: break;
	case 1:	break;
	case 2: break;
	case 3:
		en_Pulse(Vector2f(game_GetScrollX() + 1360.f, 540.f), Beats(2));
		break;

	case 4:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 240.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 840.f), PWR_NONE);
		break;
	
	case 6:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 390.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 690.f), PWR_NONE);
		break;

	case 7:
		en_Pulse(Vector2f(game_GetScrollX() + 1360.f, 540.f), Beats(2));
		en_Pulse(Vector2f(game_GetScrollX() + 1560.f, 240.f), Beats(4));
		en_Pulse(Vector2f(game_GetScrollX() + 1560.f, 840.f), Beats(6));
		break;

	case 8:
		wave_CreateWallBarrier();
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 740.f), PWR_NONE);
		en_Pulse(Vector2f(game_GetScrollX() + 1560.f, 240.f), Beats(4));
		en_Pulse(Vector2f(game_GetScrollX() + 1560.f, 840.f), Beats(6));
		break;

	case 9:
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 340.f), PWR_SCORE);
		en_Pulse(Vector2f(game_GetScrollX() + 1360.f, 240.f), Beats(4));
		en_Pulse(Vector2f(game_GetScrollX() + 1760.f, 840.f), Beats(6));
		break;

	case 10:
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 640.f), PWR_NONE);
		en_Pulse(Vector2f(game_GetScrollX() + 1360.f, 840.f), Beats(4));
		en_Pulse(Vector2f(game_GetScrollX() + 1760.f, 240.f), Beats(6));
		break;

	case 11:
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 440.f), PWR_NONE);
		en_Pulse(Vector2f(game_GetScrollX() + 1360.f, 540.f), Beats(4));
		break;

	case 12:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 240.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 540.f), PWR_POWER);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 840.f), PWR_NONE);
	//	en_Dart(Vector2f(game_GetScrollX() + 2000.f, 540.f), PWR_SCORE);
		break;

	case 14:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 390.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 690.f), PWR_NONE);
		break;

	case 15: 
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 290.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 790.f), PWR_NONE);
		en_Pulse(Vector2f(game_GetScrollX() + 400.f, 240.f), Beats(3));
		en_Pulse(Vector2f(game_GetScrollX() + 400.f, 540.f), Beats(3));
		en_Pulse(Vector2f(game_GetScrollX() + 400.f, 840.f), Beats(3));
		en_Pulse(Vector2f(game_GetScrollX() + 1560.f, 140.f), Beats(4));
		en_Pulse(Vector2f(game_GetScrollX() + 1560.f, 940.f), Beats(6));
		break;

	case 16:
		wave_CreateWallBarrier();
		en_Dart(Vector2f(game_GetScrollX() + 2600.f, 360.f), PWR_SCORE);
		en_Dart(Vector2f(game_GetScrollX() + 2400.f, 420.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2200.f, 480.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 540.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2200.f, 600.f), PWR_HP);
		en_Dart(Vector2f(game_GetScrollX() + 2400.f, 660.f), PWR_NONE);
		en_Dart(Vector2f(game_GetScrollX() + 2600.f, 720.f), PWR_NONE);
		en_Pulse(Vector2f(game_GetScrollX() + 1560.f, 340.f), Beats(4));
		en_Pulse(Vector2f(game_GetScrollX() + 1560.f, 740.f), Beats(6));
		break;

	case 17:
		wave_CreateWall(1);
		wave_CreateWall(2);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 240.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 540.f), PWR_NONE);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 840.f), PWR_NONE);
		en_Pulse(Vector2f(game_GetScrollX() + 1560.f, 140.f), Beats(4));
		en_Pulse(Vector2f(game_GetScrollX() + 1560.f, 840.f), Beats(6));
		break;

	case 18:
		wave_CreateWall(3);
		wave_CreateWall(4);
		en_Pulse(Vector2f(game_GetScrollX() + 1560.f, 340.f), Beats(4));
		en_Pulse(Vector2f(game_GetScrollX() + 1560.f, 740.f), Beats(5));
		en_Pulse(Vector2f(game_GetScrollX() + 1560.f, 190.f), Beats(6));
		en_Pulse(Vector2f(game_GetScrollX() + 1560.f, 790.f), Beats(7));
		break;

	case 19:
		wave_CreateWall(5);
		wave_CreateWall(6);
		break;

	case 20:
		wave_CreateWallBarrier();
		en_Dart(Vector2f(game_GetScrollX() + 2400.f, 540.f), PWR_NONE);
		en_Streak(Vector2f(game_GetScrollX() + 2200.f, 540.f), 0, PWR_SCORE);
		en_Streak(Vector2f(game_GetScrollX() + 2300.f, 540.f), 1, PWR_NONE);
		break;

	case 21:
		en_Dart(Vector2f(game_GetScrollX() + 2400.f, 780.f), PWR_NONE);
//		en_Streak(Vector2f(game_GetScrollX() + 2200.f, 540.f), 1, PWR_NONE);
//		en_Streak(Vector2f(game_GetScrollX() + 2300.f, 540.f), 0, PWR_NONE);
		en_Pulse(Vector2f(game_GetScrollX() + 1760.f, 240.f), Beats(4));
		en_Pulse(Vector2f(game_GetScrollX() + 1760.f, 840.f), Beats(6));
		break;

	case 22:
		en_Dart(Vector2f(game_GetScrollX() + 2400.f, 300.f), PWR_NONE);
		en_Streak(Vector2f(game_GetScrollX() + 2200.f, 540.f), 0, PWR_NONE);
		en_Streak(Vector2f(game_GetScrollX() + 2300.f, 540.f), 1, PWR_NONE);
		en_Pulse(Vector2f(game_GetScrollX() + 1760.f, 240.f), Beats(4));
		en_Pulse(Vector2f(game_GetScrollX() + 1760.f, 840.f), Beats(6));
		break;

	case 23:
		en_Dart(Vector2f(game_GetScrollX() + 2400.f, 300.f), PWR_NONE);
//		en_Streak(Vector2f(game_GetScrollX() + 2200.f, 540.f), 0, PWR_NONE);
//		en_Streak(Vector2f(game_GetScrollX() + 2300.f, 540.f), 1, PWR_NONE);
		en_Pulse(Vector2f(game_GetScrollX() + 1760.f, 240.f), Beats(4));
		en_Pulse(Vector2f(game_GetScrollX() + 1760.f, 840.f), Beats(6));
		break;

	default: break;
	}
}