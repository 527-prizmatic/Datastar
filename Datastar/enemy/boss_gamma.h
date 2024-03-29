/// The Gamma is essentially a giant Spark, firing bullets in various patterns.
/// It has 4 phases which it transitions between at different stages of its health.
/// Function prefix: en_gamma_

#pragma once
#include "../tools.h"
#include "../vectors.h"
#include "../va_tools.h"
#include "../enemy.h"

void en_Gamma(sfVector2f _pos);
struct EnData* en_gamma_Update(struct EnData* _en);
void en_gamma_OnHit(struct EnData* _en, struct PlayerBullet* _plb);
void en_gamma_OnKill(struct EnData* _en);
void en_gamma_Render(struct EnData* _en);
int en_gamma_Value();