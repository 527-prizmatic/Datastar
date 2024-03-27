/// Manages functions related to the GS_MENU gamestate.
/// Function prefix: menu_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "state_manager.h"
#include "texture_manager.h"
#include "sound_manager.h"
#include "shader_manager.h"
#include "window_manager.h"

#include "menu\bg.h"
#include "menu\menu_main.h"

typedef enum {
	MENU_MAIN = 0,
	MENU_SELECT = 1,
	MENU_OPTIONS = 2,
	MENU_CONTROLS = 3,
	MENU_CREDITS = 4
} MenuSubstate;
MenuSubstate menu_Substate;

void menu_Init();
void menu_Update();
void menu_Render();
void menu_Unload();

void menu_SetSubstate(MenuSubstate _s);