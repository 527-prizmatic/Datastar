/// The Shockwave is a large, brutal Pulse with six modular arms.
/// Each arm has its own individual health pool, and they protect a sensitive core.
/// When all arms are broken, the core discards them and starts roaming around the arena.
/// The core will phase out of view, attempting to land on the player, sending a wave of projectiles on landing and staying stunned for a few seconds.
/// Function prefix: en_shockwave_

#pragma once
#include "../tools.h"
#include "../vectors.h"
#include "../va_tools.h"
#include "../enemy.h"

void en_Shockwave(sfVector2f _pos);
struct EnData* en_shockwave_Update(struct EnData* _en);
void en_shockwave_OnHit(struct EnData* _en, struct PlayerBullet* _plb);
void en_shockwave_OnKill(struct EnData* _en);
void en_shockwave_Render(struct EnData* _en);
int en_shockwave_Value();