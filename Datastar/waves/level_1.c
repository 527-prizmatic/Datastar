#include "level_1.h"

void wave_Level_1(int _wave_num) {
	switch (_wave_num) {
	case 1:
		mus_SetLoop("future", TimeSpan(Bars(1), Beats(1)));
		wave_CreateWall(1);
		wave_CreateWall(6);
		break;

	case 2:
		mus_StopLoop("future");
		mus_SetPos("future", Bars(2));
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
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 390.f));
		break;

	case 9:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 690.f));
		break;

	case 10:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 240.f));
		wave_CreateWall(4);
		wave_CreateWall(5);
		wave_CreateWall(6);
		break;

	case 11:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 840.f));
		wave_CreateWall(1);
		wave_CreateWall(2);
		wave_CreateWall(3);
		break;

	case 12: case 14:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 440.f));
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 640.f));
		break;

	case 15:
		wave_CreateWallBarrier();
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 140.f));
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 940.f));

	case 13:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 180.f));
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 900.f));
		break;

	case 16:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 240.f));
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 390.f));
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 540.f));
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 690.f));
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 840.f));
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 240.f));
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 840.f));
//		plr_IncreaseBullets(1);
		break;

	case 17:
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 340.f));
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 740.f));
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 540.f));
		break;

	case 18:
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 440.f));
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 640.f));
		break;

	case 19:
		en_Dart(Vector2f(game_GetScrollX() + 3200.f, 150.f));
		en_Dart(Vector2f(game_GetScrollX() + 2800.f, 280.f));
		en_Dart(Vector2f(game_GetScrollX() + 2400.f, 410.f));
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 540.f));
		en_Dart(Vector2f(game_GetScrollX() + 2400.f, 670.f));
		en_Dart(Vector2f(game_GetScrollX() + 2800.f, 800.f));
		en_Dart(Vector2f(game_GetScrollX() + 3200.f, 930.f));
		break;

	case 20:
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 190.f));
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 540.f));
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 890.f));
		wave_CreateWall(3);
		wave_CreateWall(6);
		en_Streak(Vector2f(game_GetScrollX() + 2000.f, 540.f), 1);
		break;

	case 21:
		wave_CreateWall(1);
		wave_CreateWall(5);
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 140.f));
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 940.f));
		en_Streak(Vector2f(game_GetScrollX() + 2120.f, 770.f), 1);
		break;

	case 22:
		wave_CreateWall(2);
		wave_CreateWall(6);
		en_Dart(Vector2f(game_GetScrollX() + 2000.f, 340.f));
		en_Dart(Vector2f(game_GetScrollX() + 2500.f, 740.f));
		en_Streak(Vector2f(game_GetScrollX() + 2000.f, 240.f), 1);
		break;

	case 23:
		wave_CreateWall(2);
		wave_CreateWall(4);
		wave_CreateWall(5);
		en_Streak(Vector2f(game_GetScrollX() + 2000.f, 100.f), 1);
		en_Streak(Vector2f(game_GetScrollX() + 2000.f, 980.f), 1);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 540.f));
		break;

	case 24:
		en_Streak(Vector2f(game_GetScrollX() + 2000.f, 390.f), 1);
		en_Streak(Vector2f(game_GetScrollX() + 2120.f, 520.f), 0);
		en_Streak(Vector2f(game_GetScrollX() + 2240.f, 650.f), 1);
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 280.f));
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 430.f));
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 650.f));
		en_Spark(Vector2f(game_GetScrollX() + 2000.f, 800.f));
		break;

	case 28: case 29: case 30: case 31:
		wave_CreateWallBarrier();
		break;

	case 32:
		mus_SetLoop("future", TimeSpan(Bars(40), Bars(8)));
		en_Gamma(Vector2f(game_GetScrollX() + 2500.f, 540.f));
		game_SetScrollSpeed(400.f, Bars(2));
		break;

	default: break;
	}
}