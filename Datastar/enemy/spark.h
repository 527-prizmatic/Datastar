/// The Spark is a simple enemy that shoots three projectiles in sync with the BGM's off beats.
/// It stays static at the right edge of the screen and disappears after 4 bars.
/// Function prefix: en_spark_

#pragma once
#include "../tools.h"
#include "../vectors.h"
#include "../va_tools.h"
#include "../enemy.h"

/// Creates a new Spark.
/// \param _pos - Absolute spawn position
/// \param _drop - What powerup the enemy drops on death
void en_Spark(sfVector2f _pos, enum PwrType _drop);

/// Computes tick updates for Sparks.
struct EnData* en_spark_Update(struct EnData* _en);

/// Spark's reaction to being hit
void en_spark_OnHit(struct EnData* _en, struct PlayerBullet* _plb);

/// Extra effects on a Spark's death
void en_spark_OnKill(struct EnData* _en);

/// Spark renderer
void en_spark_Render(struct EnData* _en);

/// \return Score value of a single Spark
int en_spark_Value();