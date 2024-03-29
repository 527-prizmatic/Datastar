/// Savefile handling and I/O.
/// Function prefix: sav_

#pragma once
#include "tools.h"
#include "logger.h"
#include "sound_manager.h"
#include "window_manager.h"
#include "controls.h"

/// Container for save data
typedef struct {
	/// Config
	float vol_master;
	float vol_mus;
	float vol_sfx;
	char fullscreen;
	CtrlMap controls;

	/// Game data
} SaveData;
SaveData sav_Data;

void sav_Save();
void sav_Load();
void sav_LoadDefault();
void sav_AssembleData();
void sav_AssignData();