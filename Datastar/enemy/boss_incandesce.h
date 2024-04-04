/// The Incandesce is a colossal meteor able to summon large waves of Glimmers and Flares.
/// It is completely impervious to player projectiles, so the only solution is to wait for it to exhaust itself.
/// At the end of each attack cycle, it attempts a direct attack, letting itself fall from the sky and damaging itself a bit more in the impact.
/// Function prefix: en_incandesce_

#pragma once
#include "../tools.h"
#include "../vectors.h"
#include "../va_tools.h"
#include "../enemy.h"
#include "../waves/level_3.h"

void en_Incandesce(sfVector2f _pos);
struct EnData* en_incandesce_Update(struct EnData* _en);
void en_incandesce_OnHit(struct EnData* _en, struct PlayerBullet* _plb);
void en_incandesce_OnKill(struct EnData* _en);
void en_incandesce_Render(struct EnData* _en);
int en_incandesce_Value();