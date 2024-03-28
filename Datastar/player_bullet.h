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

typedef struct {
	float dummy;
} PlbDataNormal;

typedef struct {
	struct EnData* target;
	float timer_turn;
	sfVector2f trail[25];
	float timer_trail;
} PlbDataHoming;

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

void plb_Init();

void plb_New(PlbType _type, sfVector2f _pos, float _angle);

void plb_Add(PlayerBullet* _plb);

void plb_Update();

void plb_Render();

PlayerBullet* plb_PopPtr(PlayerBullet* _plb);

void plb_ClearBuffer();

void plb_Unload();