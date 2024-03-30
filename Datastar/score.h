/// Functions related to tracking and displaying score in game.
/// Function prefix: score_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "va_tools.h"

int score_Best[7];

void score_Init();
void score_Update();
void score_Render();
void score_Unload();
void score_Add(int _score);
int score_Get();