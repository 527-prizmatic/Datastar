/// The Gamma is essentially a giant Spark, firing bullets in various patterns.
/// It has 4 phases which it transitions between at different stages of its health.
/// Function prefix: en_gamma_

#pragma once
#include "../tools.h"
#include "../vectors.h"
#include "../va_tools.h"
#include "../enemy.h"

/// Creates a new Gamma boss.
/// \param _pos - Absolute spawn position
/// \param _drop - What powerup the enemy drops on death
void en_Gamma(sfVector2f _pos, enum PwrType _drop);

/// Compute tick updates for Gammas.
struct EnData* en_gamma_Update(struct EnData* _en);

/// Gamma's reaction to being hit
void en_gamma_OnHit(struct EnData* _en, struct PlayerBullet* _plb);

/// Extra effects on a Gamma's death
void en_gamma_OnKill(struct EnData* _en);

/// Gamma renderer
void en_gamma_Render(struct EnData* _en);

/// \return Score value of a single Gamma
int en_gamma_Value();