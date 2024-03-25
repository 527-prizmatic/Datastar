#include "state_manager.h"

/// Technical function used for logging
char* gs_StateToString(GameState _gs);

void gs_Init() {
	if (gs_FirstInit) {
		gs_FirstInit = sfFalse;
		gs_InitPass = sfTrue;
		gs_state = GS_GAME;

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

		switch (gs_state) {
			case GS_INIT: break;
			case GS_INTRO: break;
			case GS_MENU: break;
			case GS_SELECT: break;
			case GS_GAME: game_Init(); break;
		}

		log_LogStr(LOG_INFO, "Initialization of game state", sfTrue, sfFalse);
		log_LogStr(LOG_INFO, gs_StateToString(gs_state), sfFalse, sfFalse);
		log_LogStr(LOG_INFO, "complete", sfFalse, sfTrue);
	}
}

void gs_Update() {
	snd_Update();
	if (!w_IsPaused()) {
		switch (gs_state) {
			case GS_INIT: break;
			case GS_INTRO: break;
			case GS_MENU: break;
			case GS_SELECT: break;
			case GS_GAME: game_Update(); break;
		}

		ptc_Update();
	}
}

void gs_Render() {
	switch (gs_state) {
		case GS_INIT: break;
		case GS_INTRO: break;
		case GS_MENU: break;
		case GS_SELECT: break;
		case GS_GAME: game_Render(); break;
	}
}

void gs_Unload() {
	log_LogStr(LOG_INFO, "Requested deinitialization of game state", sfTrue, sfFalse);
	log_LogStr(LOG_INFO, gs_StateToString(gs_state), sfFalse, sfTrue);

	ptc_Clear();

	switch (gs_state) {
		case GS_INIT: break;
		case GS_INTRO: break;
		case GS_MENU: break;
		case GS_SELECT: break;
		case GS_GAME: game_Unload(); break;
	}

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
		case GS_INIT: return "INIT";
		case GS_INTRO: return "INTRO";
		case GS_MENU: return "MENU";
		case GS_SELECT: return "SELECT";
		case GS_GAME: return "GAME";
		default: return "???";
	}
}