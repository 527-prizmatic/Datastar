/// Functions related to tracking and displaying score in game.
/// Function prefix: score_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "va_tools.h"

void score_Init();
void score_Update();
void score_Render();
void score_Unload();
void score_Add(int _score);