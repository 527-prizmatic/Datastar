#include "savefile.h"

void sav_Save() {
	sav_AssembleData();

	FILE* f = fopen(PATH_SAVEFILE, "wb");
	if (!f) {
		log_LogStr(LOG_WARN, "Saving error - unable to open savefile", sfTrue, sfTrue);
		return;
	}
	fwrite(&sav_Data, sizeof(SaveData), 1, f);
	log_LogStr(LOG_WARN, "Data saving to savefile complete", sfTrue, sfTrue);
	fclose(f);
}

void sav_Load() {
	FILE* f = fopen(PATH_SAVEFILE, "rb");
	if (!f) {
		log_LogStr(LOG_WARN, "No savefile found, loading default data.", sfTrue, sfTrue);
		sav_LoadDefault();
		sav_Save();
		return;
	}
	fread(&sav_Data, sizeof(SaveData), 1, f);
	sav_AssignData();
	log_LogStr(LOG_WARN, "Data loading from savefile complete", sfTrue, sfTrue);
	fclose(f);
}

void sav_LoadDefault() {
	sav_Data.vol_master = 100.f;
	sav_Data.vol_mus = 100.f;
	sav_Data.vol_sfx = 100.f;
	sav_Data.fullscreen = 0;
	sav_Data.controls = ctrl_GetDefaults();

	sav_AssignData();
}

void sav_AssembleData() {
	sav_Data.vol_master = vol_GetMaster();
	sav_Data.vol_mus = vol_GetMus();
	sav_Data.vol_sfx = vol_GetSnd();
	sav_Data.fullscreen = w_IsFullscreen();
	sav_Data.controls = ctrl;
}

void sav_AssignData() {
	vol_SetMaster(sav_Data.vol_master);
	vol_SetMus(sav_Data.vol_mus);
	vol_SetSnd(sav_Data.vol_sfx);
	w_SetFS(sav_Data.fullscreen);
	ctrl = sav_Data.controls;
}