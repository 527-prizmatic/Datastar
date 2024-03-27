#include "level_1.h"

void wave_Level_1(int _wave_num) {
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
		wave_CreateWall(1);
		wave_CreateWall(6);
		break;

	case 11:
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 840.f));
		wave_CreateWall(2);
		wave_CreateWall(5);
		break;

	case 12: case 14:
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 440.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 640.f));
		break;

	case 15: wave_CreateWallBarrier();
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2000.f, 140.f));
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2000.f, 940.f));

	case 13:
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 180.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 900.f));
		wave_CreateWallBarrier();
		break;

	case 16:
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 240.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 390.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 540.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 690.f));
		en_New(EN_SPARK, Vector2f(game_GetScrollX() + 2000.f, 840.f));
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2000.f, 240.f));
		en_New(EN_DART, Vector2f(game_GetScrollX() + 2000.f, 840.f));
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

	default: break;
	}
}