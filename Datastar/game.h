/// Manages functions related to the GS_GAME gamestate.
/// Function prefix: game_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "texture_manager.h"
#include "sound_manager.h"
#include "particle_manager.h"
#include "gamepad.h"
#include "state_manager.h"
#include "shader_manager.h"
#include "va_tools.h"
#include "va_text.h"

#include "player.h"
#include "walls.h"
#include "enemy.h"
#include "waves.h"
#include "score.h"
#include "hud.h"
#include "sfx.h"

sfView* game_View;
sfVector2f game_ViewPos;
char game_LastLevelUnlocked;

void game_Init();
void game_Update();
void game_Render();
void game_Unload();

float game_GetScrollX();

sfBool game_IsOnScreen(sfVector2f _pos);
sfBool game_GetBeatFlag();
void game_LoadLevel(int _lvl);
int game_GetLevel();
float Beats(int _i);
float Bars(int _i);

void game_SetScrollSpeed(float _target, float _time);
float game_GetScrollSpeed();
float game_GetTime();

void game_InitLevel();
void game_UpdateLevel();
void game_UnloadLevel();