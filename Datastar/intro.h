/// Manages functions related to the GS_INTRO gamestate.
/// Function prefix: intro_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "state_manager.h"
#include "texture_manager.h"
#include "sound_manager.h"
#include "shader_manager.h"

void intro_Init();
void intro_Update();
void intro_Render();
void intro_Unload();