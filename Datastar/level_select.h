/// Manages functions related to the GS_SELECT gamestate.
/// Function prefix: msel_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "state_manager.h"
#include "texture_manager.h"
#include "sound_manager.h"
#include "shader_manager.h"

void msel_Init();
void msel_Update();
void msel_Render();
void msel_Unload();