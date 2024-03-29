/// The Wall is a static, sturdy enemy which poses little to no threat alone.
/// It is however able to shield other enemies from the player's bullets.
/// Function prefix: en_wall_

#pragma once
#include "../tools.h"
#include "../vectors.h"
#include "../va_tools.h"
#include "../enemy.h"

void en_Wall(sfVector2f _pos, int _hp_max);
struct EnData* en_wall_Update(struct EnData* _en);
void en_wall_OnHit(struct EnData* _en, struct PlayerBullet* _plb);
void en_wall_OnKill(struct EnData* _en);
void en_wall_Render(struct EnData* _en);
int en_wall_Value();