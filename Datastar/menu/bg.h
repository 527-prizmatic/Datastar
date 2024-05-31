/// Handles updating and rendering the main menu's background.
/// Function prefix: m_bg_

#pragma once
#include "..\tools.h"
#include "..\vectors.h"
#include "..\va_tools.h"
#include "..\window_manager.h"

typedef struct bg_Star {
	sfVector2f pos;
	float scroll_spd;
	float angle;
	float rot_spd;
	float size;
	float size_base;
} bg_Star;

void m_bg_Init();
void m_bg_Update();
void m_bg_Render();
void m_bg_Unload();