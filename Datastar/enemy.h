/// Functions related to enemy handling.
/// Function prefix: en_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "va_tools.h"

#include "player_bullet.h"

typedef enum EnType {
	EN_WALL
} EnType;

typedef struct {
	float dummy;
} EnDataWall;

typedef struct EnData {
	struct EnData* prev;
	struct EnData* next;
	enum EnType type;
	sfColor clr;
	sfVector2f pos;
	sfVector2f spd;
	sfFloatRect aabb;

	int hp;
	int hp_max;

	union {
		EnDataWall dataW;
	};
} EnData;
EnData* en_Sentinel;

void en_Init();

void en_New(EnType _type, sfVector2f _pos);

void en_Add(EnData* _en);

void en_Update();

void en_Render();

EnData* en_PopPtr(EnData* _en);

void en_ClearBuffer();

void en_Unload();