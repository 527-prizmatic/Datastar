/// The Dart's brief appearance is telegraphed with a beam of light streaking across the screen.
/// It zips from right to left at a very high speed.
/// Function prefix: en_dart_

#pragma once
#include "../tools.h"
#include "../vectors.h"
#include "../va_tools.h"
#include "../enemy.h"

void en_Dart(sfVector2f _pos, enum PwrType _drop);
struct EnData* en_dart_Update(struct EnData* _en);
void en_dart_OnHit(struct EnData* _en, struct PlayerBullet* _plb);
void en_dart_OnKill(struct EnData* _en);
void en_dart_Render(struct EnData* _en);
int en_dart_Value();