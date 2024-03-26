/// Manages functions related to the GS_MENU gamestate.
/// Function prefix: menu_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "state_manager.h"
#include "texture_manager.h"
#include "sound_manager.h"
#include "shader_manager.h"

void menu_Init();
void menu_Update();
void menu_Render();
void menu_Unload();