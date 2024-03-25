#include "tools.h"
#include "vectors.h"
#include "interpolation.h"
#include "window_manager.h"
#include "state_manager.h"
#include "logger.h"

int main(int argc, char** argv) {
	initTools();
	log_Init(LOG_INFO | LOG_WARN | LOG_ERROR | LOG_FATAL);
	w_Init("Prizmanager", sfVideoMode_getDesktopMode(), 60);

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

	log_Conclude();
}