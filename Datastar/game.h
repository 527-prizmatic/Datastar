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
#include "va_text_neo.h"

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

/// \return Time (in seconds) corresponding to the requested number of beats, factoring in the current track's tempo
float Beats(int _i);

/// \return Time (in seconds) corresponding to the requested number of bars, factoring in the current track's tempo
float Bars(int _i);

/// Sets the current camera scroll speed.
/// \param _target - Desired scrolling speed, in pixels/second
/// \param _time - Time (in seconds) over which the camera will accelerate or decelerate
void game_SetScrollSpeed(float _target, float _time);

/// \return Current camera scroll speed
float game_GetScrollSpeed();

/// \return Camera's X position
float game_GetScrollX();

/// \return Whether the given position is visible on the camera
sfBool game_IsOnScreen(sfVector2f _pos);

/// \return sfTrue on each of the music's beats, factoring in the current track's tempo
/// \return sfFalse the rest of the time
sfBool game_GetBeatFlag();

/// Initializes the requested level and preloads corresponding resources.
void game_LoadLevel(int _lvl);

/// Gets the current level.
int game_GetLevel();

/// \return Time spent within this level
float game_GetTime();