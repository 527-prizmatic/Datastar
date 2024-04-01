/// The Pulse is a pretty simple kamikaze-style enemy.
/// It slides in from the top or bottom of the screen and explodes in a ring of projectiles.
/// It cannot be hit nor destroyed, you can only dodge.
/// Function prefix: en_pulse_

#pragma once
#include "../tools.h"
#include "../vectors.h"
#include "../va_tools.h"
#include "../enemy.h"

void en_Pulse(sfVector2f _pos, float _delay);
struct EnData* en_pulse_Update(struct EnData* _en);
void en_pulse_Render(struct EnData* _en);
int en_pulse_Value();