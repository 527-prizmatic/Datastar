/// Functions related to enemy handling.
/// Function prefix: en_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "va_tools.h"

#include "player_bullet.h"
#include "score.h"
#include "sfx.h"
#include "powerup.h"

#include "enemy/wall.h"
#include "enemy/spark.h"
#include "enemy/dart.h"
#include "enemy/streak.h"
#include "enemy/pulse.h"
#include "enemy/boss_gamma.h"

typedef enum EnType {
	EN_WALL,
	EN_SPARK,
	EN_DART,
	EN_STREAK,
	EN_PULSE,

	EN_BOSS_GAMMA
} EnType;

typedef struct EnDataWall {
	float dummy;
} EnDataWall;

typedef struct EnDataSpark{
	sfVector2f posOrigin;
	float rot;
	char beatCounter;
} EnDataSpark;

typedef struct EnDataDart {
	sfVector2f posOld[5];
	float timerTrail;
} EnDataDart;

typedef struct EnDataStreak {
	sfVector2f posOld[5];
	float timerTrail;
	char dir;
	float spd_mul;
} EnDataStreak;

typedef struct EnDataPulse {
	sfVector2f posOld[5];
	float timerTrail;
	sfVector2f pos_target;
	float rot;
} EnDataPulse;

typedef struct EnDataGamma {
	sfVector2f posOrigin;
	float rot;
	char phase;
	float timer_shots;
} EnDataGamma;

typedef struct EnData {
	struct EnData* prev;
	struct EnData* next;
	enum EnType type;
	sfColor clr;
	sfVector2f pos;
	sfVector2f spd;
	sfFloatRect aabb;
	float lifetime;
	float timer_blink;
	int hp;
	int hp_max;
	enum PwrType drop;

	union {
		struct EnDataWall dataWl;
		struct EnDataSpark dataSp;
		struct EnDataDart dataDt;
		struct EnDataStreak dataSt;
		struct EnDataPulse dataPl;


		struct EnDataGamma dataGm;
	};
} EnData;
EnData* en_Sentinel;

void en_Init();

void en_Add(EnData* _en);

void en_Update();

void en_Render();

EnData* en_PopPtr(EnData* _en);

void en_ClearBuffer();

void en_Unload();

int en_GetValue(EnType _type);