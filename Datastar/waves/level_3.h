#pragma once
#include "..\waves.h"
#include "..\enemy.h"

void lv3_Init();
void lv3_Update();
void lv3_Unload();
void lv3_End();

void lv3_SpawnWaves(int _wave_num);

/// Reserved for level 3. Sets the amount of glimmers to be randomly spawned on each beat.
void lv3_SetGlimmerSpawn(int _i);