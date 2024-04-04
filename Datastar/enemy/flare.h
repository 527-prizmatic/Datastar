/// The Flare is essentially a much larger version of the Glimmer, only appearing for transitions.
/// Function prefix: en_flare_

#pragma once
#include "../tools.h"
#include "../vectors.h"
#include "../va_tools.h"
#include "../enemy.h"

/// Creates a new Flare.
/// \param _pos - Absolute spawn position
void en_Flare(sfVector2f _pos, float _lifetime);

/// Computes tick updates for Flares.
struct EnData* en_flare_Update(struct EnData* _en);

/// Flare renderer
void en_flare_Render(struct EnData* _en);

/// \return Score value of a single Flare
int en_flare_Value();