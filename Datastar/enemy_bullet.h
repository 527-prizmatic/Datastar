/// Functions related to manipulating the enemy projectile buffer.
/// Function prefix: enb_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "va_tools.h"
#include "player.h"
#include "enemy.h"
#include "sfx.h"

typedef enum EnbType {
	ENB_NORMAL
	// Some more will come here later
} EnbType;

typedef struct EnemyBullet {
	struct EnemyBullet* prev;
	struct EnemyBullet* next;
	enum EnbType type;
	sfVector2f pos;
	sfVector2f oldPos[3]; // FOR LATER, FOR COMPUTING AFTERIMAGES
	sfVector2f spd;
	float lifetime;
	float angle;
	sfColor clr;
	sfFloatRect aabb;
} EnemyBullet;
EnemyBullet* enb_Sentinel;

void enb_Init();

void enb_New(EnbType _type, sfVector2f _pos, sfVector2f _spd, sfColor _clr);

void enb_Add(EnemyBullet* _enb);

void enb_Update();

void enb_Render();

EnemyBullet* enb_PopPtr(EnemyBullet* _enb);

void enb_ClearBuffer();

void enb_Unload();