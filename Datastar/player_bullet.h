/// Functions related to manipulating the player projectile buffer.
/// Function prefix: plb_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "va_tools.h"
#include "player.h"
#include "sfx.h"

typedef enum PlbType {
	PLB_NORMAL,
	PLB_HOMING
	// Some more will come here later
} PlbType;

/// Extra data for bullet type PLB_NORMAL
/// Completely empty yet, but still exists in case it'd be needed later
typedef struct {
	float dummy;
} PlbDataNormal;

/// Extra data for bullet type PLB_HOMING
typedef struct {
	struct EnData* target;
	float timer_turn;
	sfVector2f trail[25];
	float timer_trail;
} PlbDataHoming;

/// Data structure for player bullets
typedef struct PlayerBullet {
	struct PlayerBullet* prev;
	struct PlayerBullet* next;
	enum PlbType type;
	sfVector2f pos;
	sfVector2f spd;
	float lifetime;
	sfFloatRect aabb;
	
	union {
		PlbDataNormal dataN;
		PlbDataHoming dataH;
	};
} PlayerBullet;
PlayerBullet* plb_Sentinel;

/// Initializes the player bullet system.
void plb_Init();

/// Creates a new player bullet.
/// Bullet speed is constant, so all the function takes is the starting position and the firing angle.
void plb_New(PlbType _type, sfVector2f _pos, float _angle);

/// Adds a new player bullet to the buffer.
void plb_Add(PlayerBullet* _plb);

/// Computes tick updates for player bullets.
void plb_Update();

/// Player bullet renderer
void plb_Render();

/// Removes an item from the player bullet buffer.
PlayerBullet* plb_PopPtr(PlayerBullet* _plb);

/// Empties the player bullet buffer.
void plb_ClearBuffer();

/// Unloads the player bullet buffer and frees up all allocated resources.
void plb_Unload();