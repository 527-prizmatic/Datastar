/// Manages functions related to the GS_INIT gamestate.
/// Function prefix: init_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "state_manager.h"
#include "texture_manager.h"
#include "sound_manager.h"
#include "shader_manager.h"

#include "va_text_neo.h"

void init_Init();
void init_Update();
void init_Render();
void init_Unload();