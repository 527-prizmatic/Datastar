/// Functions handling wave generation.
/// Function prefix: wave_

#pragma once
#include "enemy.h"
#include "game.h"

#include "waves\level_1.h"
#include "waves\level_2.h"
#include "waves\level_3.h"

/// Spawns a set of enemies corresponding to each wave of the given level.
void wave_Generate(int _lvl, int _wave_num);

/// Fetches the tempo for the given level.
float wave_GetTempo(int _lvl);

/// Spawns a single Wall enemy. Used as a shortcut to avoid having to compute individual positions by hand.
void wave_CreateWall(int _slot);

/// Spawns a continuous barrier of Wall enemies.
void wave_CreateWallBarrier();