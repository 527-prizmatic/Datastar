#include "menu.h"

float menu_TimerGlobal = 0.f;

void menu_Init() {
	snd_Preload(SND_MUS, "far.ogg", "far");
	tex_Preload("logo_datastar.png", "logo");
	m_bg_Init();
	m_main_Init();
	m_options_Init();
	m_cred_Init();
	m_ctrl_Init();
	menu_SetSubstate(MENU_MAIN);
}

void menu_Update() {
	if (snd_GetMusicState() != sfPlaying) mus_Play("far");
	menu_TimerGlobal += getDeltaTime();
	m_bg_Update();

	switch (menu_Substate) {
		case MENU_MAIN: m_main_Update(); break;
		case MENU_SELECT: break;
		case MENU_OPTIONS: m_options_Update(); break;
		case MENU_CONTROLS: m_ctrl_Update(); break;
		case MENU_CREDITS: m_cred_Update();  break;
	}
}

void menu_Render() {
	va_DrawScreenBorders();
	rq_Draw(RQ_SPRITE, NULL, Vector2f(960.f - 10.f, 190.f + sin(menu_TimerGlobal * .5f) * 20.f), "logo", RQ_TEX_NORECT, Vector2f(783.f, 0.f), 0.f, RQ_SCALE(.6f), sfWhite);
	m_bg_Render();

	switch (menu_Substate) {
		case MENU_MAIN: m_main_Render(); break;
		case MENU_SELECT: break;
		case MENU_OPTIONS: m_options_Render(); break;
		case MENU_CONTROLS: m_ctrl_Render(); break;
		case MENU_CREDITS: m_cred_Render(); break;
	}
}

void menu_Unload() {
	snd_Unload("far");
	tex_Unload("logo");
	m_bg_Unload();
	m_main_Unload();
	m_cred_Unload();
	m_ctrl_Unload();
	m_options_Unload();
}

void menu_SetSubstate(MenuSubstate _s) { menu_Substate = _s; }