/// Centralized handler for all SFXs and common particle effects.
/// Function prefix: sfx_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "va_tools.h"
#include "window_manager.h"
#include "particle_manager.h"
#include "powerup.h"

typedef struct SfxScore {
	struct SfxScore* prev;
	struct SfxScore* next;
	sfVector2f pos;
	int val;
	float lifetime;
} SfxScore;
SfxScore* sfx_ScoreSentinel;

void sfx_ScoreInit();
void sfx_ScoreNew(sfVector2f _pos, int _val);
void sfx_ScoreUpdate();
void sfx_ScoreRender();
SfxScore* sfx_ScorePopPtr(SfxScore* _sfx);
void sfx_ScoreClearBuffer();

void sfx_PlayerPropeller();
void sfx_PlayerFire();
void sfx_PlayerHit();
void sfx_ProjectileImpact(sfVector2f _pos, sfVector2f _spd, sfColor _clr);
void sfx_EnemyFire(sfVector2f _pos, sfVector2f _dir, sfColor _clr);
void sfx_EnemyDeath(sfVector2f _pos, sfColor _clr);
void sfx_EnemyBossDeath(sfVector2f _pos, sfColor _clr);
struct PtcSystem* sfx_PowerupParticle(sfVector2f _pos, enum PwrType _type);