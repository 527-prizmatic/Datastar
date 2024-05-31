#include "tools.h"
#include "window_manager.h"
#include "state_manager.h"
#include "logger.h"

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