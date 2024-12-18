/// Functions related to the MENU_OPTIONS menu substate.
/// Function prefix: m_options_

#pragma once
#include "..\tools.h"
#include "..\vectors.h"
#include "..\va_tools.h"
#include "..\state_manager.h"
#include "..\savefile.h"

void m_options_Init();
void m_options_Update();
void m_options_Render();
void m_options_Unload();