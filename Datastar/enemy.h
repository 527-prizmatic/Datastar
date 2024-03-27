/// Functions related to enemy handling.
/// Function prefix: en_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "va_tools.h"

#include "player_bullet.h"
#include "score.h"

typedef enum EnType {
	EN_WALL,
	EN_SPARK,
	EN_DART
} EnType;

typedef struct {
	float dummy;
} EnDataWall;

typedef struct {
	sfVector2f posOrigin;
	float rot;
	char beatCounter;
} EnDataSpark;

typedef struct {
	char beatCounter;
	sfVector2f posOld[5];
	float timerTrail;
} EnDataDart;

typedef struct EnData {
	struct EnData* prev;
	struct EnData* next;
	enum EnType type;
	sfColor clr;
	sfVector2f pos;
	sfVector2f spd;
	sfFloatRect aabb;
	float lifetime;

	int hp;
	int hp_max;

	union {
		EnDataWall dataW;
		EnDataSpark dataS;
		EnDataDart dataD;
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

int en_GetValue(EnType _type);