/// The Dart's brief appearance is telegraphed with a beam of light streaking across the screen.
/// It zips from right to left at a very high speed.
/// Function prefix: en_streak_

#pragma once
#include "../tools.h"
#include "../vectors.h"
#include "../va_tools.h"
#include "../enemy.h"

void en_Streak(sfVector2f _pos, sfBool _dir, enum PwrType _drop);
struct EnData* en_streak_Update(struct EnData* _en);
void en_streak_OnHit(struct EnData* _en, struct PlayerBullet* _plb);
void en_streak_OnKill(struct EnData* _en);
void en_streak_Render(struct EnData* _en);
int en_streak_Value();