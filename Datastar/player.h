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
#include "collisions.h"
#include "controls.h"

float plr_TimerDeath;

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
	sfBool hit;
	float inv_frames;
	sfFloatRect aabb;
	sfBool invincible;
} PlrPlayer;
PlrPlayer plr_Player;

void plr_Init();
void plr_Update();
void plr_Render();
void plr_Unload();

/// User input handler
void plr_Control();

/// Computes collisions with various world objects.
sfBool plr_Collisions();

/// Adds one extra projectile to the player's fire.
void plr_IncreaseBullets(int _i);

/// Heals the player for 1 HP.
void plr_HealOne();

/// Makes the player invincible, or revokes that status.
void plr_Invincible(sfBool _inv);

/// Marks the player as having been hit and triggers related events.
/// For use in non-direct damage sources such as AoE effects.
void plr_Hit();