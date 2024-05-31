#include "tools.h"
#include "window_manager.h"
#include "state_manager.h"
#include "logger.h"

void claHandler(int argc, char** argv) {
	ARGS_RENDER_HITBOXES = sfFalse;
	ARGS_DOUBLE_RENDER = sfFalse;
	ARGS_PIZZA_MODE = sfFalse;
	ARGS_ENABLE_LOGGING = sfFalse;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-hitboxes")) ARGS_RENDER_HITBOXES = sfTrue;
		if (strcmp(argv[i], "-double-render")) ARGS_DOUBLE_RENDER = sfTrue;
		if (strcmp(argv[i], "-pizza")) ARGS_PIZZA_MODE = sfTrue;
		if (strcmp(argv[i], "-log")) ARGS_ENABLE_LOGGING = sfTrue;
	}
}

int main(int argc, char** argv) {
	claHandler(argc, argv);


	ShowWindow(GetConsoleWindow(), 0);
	initTools();
	w_Init("Datastar", sfVideoMode_getDesktopMode(), 60);
	log_Init(LOG_INFO | LOG_WARN | LOG_ERROR | LOG_FATAL);
	w_Create();

	while (!w_IsClosed()) {
		gs_Init();

		w_Update();
		kb_Update();
		gp_Update();
		gs_Update();

		w_RenderStart();
		gs_Render();
		w_RenderEnd();
	}

	tex_ClearBuffer();
	snd_ClearBuffer();
	ptc_Clear();
	log_Conclude();
}