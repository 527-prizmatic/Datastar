#include "state_manager.h"

/// Technical function used for logging
char* gs_StateToString(GameState _gs);

void gs_Init() {
	if (gs_FirstInit) {
		gs_FirstInit = sfFalse;
		gs_InitPass = sfTrue;

		tex_Init();
		snd_Init();
		shd_Init();
		ptc_Init();
		va_Init();
		kb_Enable();
		gp_Enable();
		restartClock();
		log_LogStr(LOG_INFO, "Preinit complete", sfTrue, sfTrue);
	}

	if (gs_InitPass) {
		gs_InitPass = sfFalse;

		demo_Init();

		log_LogStr(LOG_INFO, "Initialization of game state", sfTrue, sfFalse);
		log_LogStr(LOG_INFO, gs_StateToString(gs_state), sfFalse, sfFalse);
		log_LogStr(LOG_INFO, "complete", sfFalse, sfTrue);
	}
}

void gs_Update() {
	snd_Update();
	if (!w_IsPaused()) {
		demo_Update();
		ptc_Update();
	}
}

void gs_Render() {
	demo_Render();
	ptc_Render();
}

void gs_Unload() {
	log_LogStr(LOG_INFO, "Requested deinitialization of game state", sfTrue, sfFalse);
	log_LogStr(LOG_INFO, gs_StateToString(gs_state), sfFalse, sfTrue);

//	tex_ClearBuffer();
//	snd_ClearBuffer();
	ptc_Clear();

	demo_Unload();

	log_LogStr(LOG_INFO, "Deinitialization of game state", sfTrue, sfFalse);
	log_LogStr(LOG_INFO, gs_StateToString(gs_state), sfFalse, sfFalse);
	log_LogStr(LOG_INFO, "complete", sfFalse, sfTrue);
}

void gs_ChangeState(GameState _gs) {
	log_LogStr(LOG_INFO, "Requested game state change from", sfTrue, sfFalse);
	log_LogStr(LOG_INFO, gs_StateToString(gs_state), sfFalse, sfFalse);
	log_LogStr(LOG_INFO, "to", sfFalse, sfFalse);
	log_LogStr(LOG_INFO, gs_StateToString(_gs), sfFalse, sfTrue);

	gs_Unload();
	gs_state = _gs;
	gs_InitPass = sfTrue;
	gs_Init();
}

char* gs_StateToString(GameState _gs) {
	switch (_gs) {
		case GS_ALL: return "ALL";
		case GS_GAME: return "GAME";
		default: return "???";
	}
}