/// Functions related to the player entity, its controls and its rendering.
/// Function prefix: plr_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "va_tools.h"
#include "keyboard.h"
#include "game.h"
#include "player_bullet.h"
#include "models.h"

typedef struct {
	sfVector2f pos;
	sfVector2f spd;
	int hp;
	int hp_max;
	float rot;
	float fireTimer;
	float inv_frames;
} PlrPlayer;
PlrPlayer plr_Player;

void plr_Init();

void plr_Update();

void plr_Render();

void plr_Unload();

void plr_Control();
sfBool plr_Collisions();