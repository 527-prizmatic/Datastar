/// Manages functions related to the engine's demo.
/// Function prefix: demo_

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

void demo_Init();
void demo_Update();
void demo_Render();
void demo_Unload();