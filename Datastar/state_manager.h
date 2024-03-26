/// (C) 2024 The Prizmanager
/// Author - J.Sebastien Toussaint
/// 
/// Various functions for handling state-dependent behavior.
/// Function prefix: gs_

#pragma once
#include "tools.h"
#include "window_manager.h"
#include "texture_manager.h"
#include "sound_manager.h"
#include "particle_manager.h"
#include "shader_manager.h"
#include "keyboard.h"
#include "gamepad.h"
#include "va_tools.h"

#include "demo.h"
#include "init.h"
#include "intro.h"
#include "menu.h"
#include "level_select.h"
#include "game.h"

typedef enum {
	GS_ALL = -1,
	GS_INIT = 0,
	GS_INTRO = 1,
	GS_MENU = 2,
	GS_SELECT = 3,
	GS_GAME = 4,
	GS_EXIT = 5
} GameState;
GameState gs_state;

float gs_TimerGlobal;

static sfBool gs_FirstInit = sfTrue; /// Used to request initialization of the resource engine
static sfBool gs_InitPass = sfFalse; /// Used to fire a round of resource init

void gs_Init();

void gs_Update();

void gs_Render();

void gs_Unload();

void gs_ChangeState(GameState _gs);