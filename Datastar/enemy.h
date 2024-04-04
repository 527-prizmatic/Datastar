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
#include "enemy/glimmer.h"
#include "enemy/flare.h"
#include "enemy/boss_gamma.h"
#include "enemy/boss_shockwave.h"
#include "enemy/boss_incandesce.h"

/// Enemy type list
typedef enum EnType {
	EN_WALL,
	EN_SPARK,
	EN_DART,
	EN_STREAK,
	EN_PULSE,
	EN_GLIMMER,
	EN_FLARE,

	EN_BOSS_GAMMA,
	EN_BOSS_SHOCKWAVE,
	EN_BOSS_INCANDESCE
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

typedef struct EnDataGlimmer {
	sfVector2f pos_target;
	float rot;
	float fall_time;
} EnDataGlimmer;


typedef struct EnDataGamma {
	sfVector2f posOrigin;
	float rot;
	char phase;
	float timer_shots_slow;
} EnDataGamma;

typedef struct EnDataShockwave {
	int hp_arm[6];
	int hp_max_arm[6];
	float timers_blink[6];
	sfVector2f pos_target;
	float rot;
	float rot_spd;
	char phase;
	char beat_ctr;
	float timer_shots_slow;
	float lifetime_mod8;
	sfBool flag_targeting;
} EnDataShockwave;

typedef struct EnDataIncandesce {
	float rot;
	float rot_spd;
	float clr_osc;
	float clr_osc_spd;
	sfVector2f pos_target;
	sfBool entrance;
	char beat_ctr;
	float timer_cycle;
	float timer_fire;
	float fire_dir;
} EnDataIncandesce;

/// Data structure for enemies
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
		struct EnDataGlimmer dataGl;


		struct EnDataGamma dataGm;
		struct EnDataShockwave dataSw;
		struct EnDataIncandesce dataIc;
	};
} EnData;
EnData* en_Sentinel;

/// Initializes the enemy buffer system.
void en_Init();

/// Adds a newly created enemy to the buffer.
void en_Add(EnData* _en);

/// Computes tick updates for enemies.
void en_Update();

/// Enemy renderer
void en_Render();

/// Removes a given element from the enemy buffer and frees up allocated memory.
/// Also returns the next element of the list.
EnData* en_PopPtr(EnData* _en);

/// Empties the enemy buffer.
void en_ClearBuffer();

/// Empties the enemy buffer and destroys all allocated resources.
void en_Unload();

/// Gets the score value of an enemy type.
int en_GetValue(EnType _type);