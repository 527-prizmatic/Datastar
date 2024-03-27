#include "waves.h"

void wave_Generate(int _lvl, int _wave_num) {
	switch (_lvl) {
		case 1: wave_Level_1(_wave_num); break;
		default: break;
	}
}

float wave_GetTempo(int _lvl) {
	switch (_lvl) {
		case 1: return 80.f;
		default: return 120.f;
	}
}

void wave_CreateWall(int _slot) {
	en_New(EN_WALL, Vector2f(game_GetScrollX() + 2000.f, _slot * 135.f + 67.5f));
}

void wave_CreateWallBarrier() {
	for (int i = 1; i <= 6; i++) wave_CreateWall(i);
}