/// Centralized handler for all SFXs and common particle effects.
/// Function prefix: sfx_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "va_tools.h"
#include "window_manager.h"
#include "particle_manager.h"

void sfx_PlayerPropeller();
void sfx_PlayerFire();
void sfx_PlayerHit();
void sfx_ProjectileImpact(sfVector2f _pos, sfVector2f _spd, sfColor _clr);
void sfx_EnemyFire(sfVector2f _pos, sfVector2f _dir, sfColor _clr);
void sfx_EnemyDeath(sfVector2f _pos, sfColor _clr);