/// Functions related to the player entity, its controls and its rendering.
/// Function prefix: plr_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "va_tools.h"
#include "keyboard.h"
#include "game.h"
#include "player_bullet.h"
#include "enemy_bullet.h"
#include "models.h"
#include "collisions.h"
#include "controls.h"

typedef struct {
	sfVector2f pos;
	sfVector2f spd;
	sfVector2f acc;
	int hp;
	int hp_max;
	float rot;
	float fire_timer;
	float rof;
	enum PlbType fire_mode;
	float bullet_count;
	float inv_frames;
	sfFloatRect aabb;
	sfBool invincible;
} PlrPlayer;
PlrPlayer plr_Player;

void plr_Init();
void plr_Update();
void plr_Render();
void plr_Unload();

void plr_Control();
sfBool plr_Collisions();
void plr_IncreaseBullets(int _i);
void plr_HealOne();
void plr_Invincible(sfBool _inv);