/// Functions related to the MENU_SELECT menu substate.
/// Function prefix: m_select_

#pragma once
#include "..\tools.h"
#include "..\vectors.h"
#include "..\va_tools.h"
#include "..\state_manager.h"
#include "..\savefile.h"

void m_select_Init();
void m_select_Update();
void m_select_Render();
void m_select_Unload();