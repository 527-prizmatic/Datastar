/// The Spark is a simple enemy that shoots three projectiles in sync with the BGM's off beats.
/// It stays static at the right edge of the screen and disappears after 4 bars.
/// Function prefix: en_spark_

#pragma once
#include "../tools.h"
#include "../vectors.h"
#include "../va_tools.h"
#include "../enemy.h"

void en_Spark(sfVector2f _pos);
struct EnData* en_spark_Update(struct EnData* _en);
void en_spark_OnHit(struct EnData* _en, struct PlayerBullet* _plb);
void en_spark_OnKill(struct EnData* _en);
void en_spark_Render(struct EnData* _en);
int en_spark_Value();