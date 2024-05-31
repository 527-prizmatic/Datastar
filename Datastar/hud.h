/// Displaying useful info about the current state of the game.
/// Function prefix: hud_

#pragma once
#include "tools.h"
#include "va_tools.h"
#include "player.h"

void hud_Init();
void hud_Unload();

void hud_DrawInfoTime(int _beats, int _waves);
void hud_DrawInfoFrameRate();
void hud_DrawHealth(int _hp);
void hud_DrawMaxHealth(int _hp_max);