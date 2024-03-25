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
#include "particle_manager.h"
#include "va_text.h"

#include "player.h"
#include "walls.h"
#include "enemy.h"

sfView* game_View;

void game_Init();
void game_Update();
void game_Render();
void game_Unload();

float game_GetScrollX();

sfBool game_IsOnScreen(sfVector2f _pos);