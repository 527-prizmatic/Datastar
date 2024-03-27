#include "score.h"

int score = 0;
char* txt_Score;

void score_Init() {
	score = 0;
	txt_Score = calloc(12, sizeof(char));
}

void score_Update() {
	sprintf(txt_Score, "%7d", score);
}

void score_Render() {
	vt_DrawText(Vector2f(1895.f, 25.f), txt_Score, 25, TXT_RIGHT, sfWhite);
}

void score_Unload() {
	free(txt_Score);
}

void score_Add(int _score) {
	score += _score;
}