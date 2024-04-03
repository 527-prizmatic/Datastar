/// The invincible Glimmer slowly plummets down from the top of the screen.
/// It explodes upon impact with the ground, dealing damage to everything in a small AoE around itself.
/// Function prefix: en_glimmer_

#pragma once
#include "../tools.h"
#include "../vectors.h"
#include "../va_tools.h"
#include "../enemy.h"

/// Creates a new Glimmer.
/// \param _pos - Absolute spawn position
void en_Glimmer(sfVector2f _pos);

/// Computes tick updates for Glimmers.
struct EnData* en_glimmer_Update(struct EnData* _en);

///  Glimmer renderer
void en_glimmer_Render(struct EnData* _en);

/// \return Score value of a single Glimmer
int en_glimmer_Value();