#include "level_1.h"

void wave_Level_1(int _wave_num) {
	float beatTime = 60.f / wave_GetTempo(1);

	switch (_wave_num) {
	case 1:
		wave_CreateWall(1);
		wave_CreateWall(6);
		break;

	case 2:
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
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 390.f));
		break;

	case 9:
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 690.f));
		break;

	case 10:
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 240.f));
		wave_CreateWall(4);
		wave_CreateWall(5);
		wave_CreateWall(6);
		break;

	case 11:
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 840.f));
		wave_CreateWall(1);
		wave_CreateWall(2);
		wave_CreateWall(3);
		break;

	case 12: case 14:
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 440.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 640.f));
		break;

	case 15:
		wave_CreateWallBarrier();
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2000.f, 140.f));
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2000.f, 940.f));

	case 13:
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 180.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 900.f));
		break;

	case 16:
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 240.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 390.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 540.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 690.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 840.f));
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2000.f, 240.f));
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2000.f, 840.f));
//		plr_IncreaseBullets(1);
		break;

	case 17:
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2000.f, 340.f));
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2000.f, 740.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 540.f));
		break;

	case 18:
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2000.f, 440.f));
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2000.f, 640.f));
		break;

	case 19:
		en_New(EN_DART, Vector2f(game_GetScrollX() + 3200.f, 150.f));
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2800.f, 280.f));
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2400.f, 410.f));
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2000.f, 540.f));
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2400.f, 670.f));
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2800.f, 800.f));
		en_New(EN_DART, Vector2f(game_GetScrollX() + 3200.f, 930.f));
		break;

	case 20:
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 190.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 540.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 890.f));
		wave_CreateWall(3);
		wave_CreateWall(6);
		en_New(EN_STREAK, Vector2f(game_GetScrollX() + 2000.f, 540.f));
		break;

	case 21:
		wave_CreateWall(1);
		wave_CreateWall(5);
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2000.f, 140.f));
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2000.f, 940.f));
		en_New(EN_STREAK, Vector2f(game_GetScrollX() + 2120.f, 770.f));
		break;

	case 22:
		wave_CreateWall(2);
		wave_CreateWall(6);
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2000.f, 340.f));
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2500.f, 740.f));
		en_New(EN_STREAK, Vector2f(game_GetScrollX() + 2000.f, 240.f));
		break;

	case 23:
		wave_CreateWall(2);
		wave_CreateWall(4);
		wave_CreateWall(5);
		en_New(EN_STREAK, Vector2f(game_GetScrollX() + 2000.f, 100.f));
		en_New(EN_STREAK, Vector2f(game_GetScrollX() + 2000.f, 980.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 540.f));
		break;

	case 24:
		en_New(EN_STREAK, Vector2f(game_GetScrollX() + 2000.f, 390.f));
		en_New(EN_STREAK, Vector2f(game_GetScrollX() + 2120.f, 520.f));
		en_New(EN_STREAK, Vector2f(game_GetScrollX() + 2240.f, 650.f));
		en_New(EN_STREAK, Vector2f(game_GetScrollX() + 2360.f, 780.f));
		en_New(EN_STREAK, Vector2f(game_GetScrollX() + 2480.f, 910.f));
//		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 180.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 280.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 380.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 700.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 800.f));
//		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 900.f));
		break;

	case 28: case 29: case 30: case 31:
		wave_CreateWallBarrier();
		break;

	case 32:
		sfMusic_setLoopPoints(mus_GetCurrentlyPlaying(), (sfTimeSpan) { (sfTime) { beatTime * 160000000.f }, (sfTime) { beatTime * 32000000.f } });
		en_New(EN_BOSS_GAMMA, Vector2f(game_GetScrollX() + 2500.f, 540.f));

		// Wave 32 - Boss of level 1 (giant spark)
		// Loop music around bars 41-48

		break;

	default: break;
	}
}