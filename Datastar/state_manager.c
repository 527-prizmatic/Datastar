#include "state_manager.h"

/// Technical function used for logging
char* gs_StateToString(GameState _gs);

void gs_Init() {
	/// This is done only once on startup
	if (gs_FirstInit) {
		gs_FirstInit = sfFalse;
		gs_InitPass = sfTrue;
		gs_state = GS_MENU;
		gs_TimerGlobal = 0.f;

		tex_Init();
		snd_Init();
		shd_Init();
		ptc_Init();
		va_Init();
		kb_Enable();
		gp_Enable();
		restartClock();
		sav_Load();
		log_LogStr(LOG_INFO, "Preinit complete", sfTrue, sfTrue);
	}

	/// This is done each time a new gamestate change is requested via the function gs_ChangeState()
	if (gs_InitPass) {
		gs_InitPass = sfFalse;

		switch (gs_state) {
			case GS_INIT: init_Init(); break;
			case GS_INTRO: intro_Init(); break;
			case GS_MENU: menu_Init(); break;
			case GS_GAME: game_Init(); break;
		}

		log_LogStr(LOG_INFO, "Initialization of game state", sfTrue, sfFalse);
		log_LogStr(LOG_INFO, gs_StateToString(gs_state), sfFalse, sfFalse);
		log_LogStr(LOG_INFO, "complete", sfFalse, sfTrue);
	}
}

void gs_Update() {
	gs_TimerGlobal += getDeltaTime();

	snd_Update();
	if (!w_IsPaused()) {
		switch (gs_state) {
			case GS_INIT: init_Update(); break;
			case GS_INTRO: intro_Update(); break;
			case GS_MENU: menu_Update(); break;
			case GS_GAME: game_Update(); break;
		}

		ptc_Update();
	}
}

void gs_Render() {
	switch (gs_state) {
		case GS_INIT: init_Render(); break;
		case GS_INTRO: intro_Render(); break;
		case GS_MENU: menu_Render(); break;
		case GS_GAME: game_Render(); break;
	}
}

void gs_Unload() {
	log_LogStr(LOG_INFO, "Requested deinitialization of game state", sfTrue, sfFalse);
	log_LogStr(LOG_INFO, gs_StateToString(gs_state), sfFalse, sfTrue);

	switch (gs_state) {
		case GS_INIT: init_Unload(); break;
		case GS_INTRO: intro_Unload(); break;
		case GS_MENU: menu_Unload(); break;
		case GS_GAME: game_Unload(); break;
	}

	ptc_Clear();

	log_LogStr(LOG_INFO, "Deinitialization of game state", sfTrue, sfFalse);
	log_LogStr(LOG_INFO, gs_StateToString(gs_state), sfFalse, sfFalse);
	log_LogStr(LOG_INFO, "complete", sfFalse, sfTrue);
}

void gs_ChangeState(GameState _gs) {
	log_LogStr(LOG_INFO, "Requested game state change from", sfTrue, sfFalse);
	log_LogStr(LOG_INFO, gs_StateToString(gs_state), sfFalse, sfFalse);
	log_LogStr(LOG_INFO, "to", sfFalse, sfFalse);
	log_LogStr(LOG_INFO, gs_StateToString(_gs), sfFalse, sfTrue);

	mus_Stop();
	gs_Unload();
	if (_gs == GS_EXIT) {
		w_Destroy();
		return;
	}
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
		case GS_GAME: return "GAME";
		case GS_EXIT: return "EXIT";
		default: return "???";
	}
}