#include "menu_credits.h"

int menu_CreditsState = 0;

void m_cred_Init() {
	menu_CreditsState = 0;
}

void m_cred_Update() {
	if (kb_TestPress(sfKeySpace) || gp_TestPress(0, GP_BUTTON_A)) menu_CreditsState++;
	if (menu_CreditsState == 5 || gp_TestPress(0, GP_BUTTON_MENU)) {
		menu_CreditsState = 0;
		menu_SetSubstate(MENU_MAIN);
	}
}

void m_cred_Render() {
	menu_RenderLogo(0.f);

	vt_DrawText(Vector2f(960.f, 575.f), "DATASTAR", 50, TXT_CENTER, sfWhite);
	switch (menu_CreditsState) {
		case 0:
			vt_DrawText(Vector2f(960.f, 690.f), "PROGRAMMING, GRAPHICS & GAME DESIGN", 35, TXT_CENTER, sfWhite);
			vt_DrawText(Vector2f(960.f, 745.f), "TOUSSAINT JEAN-SEBASTIEN", 25, TXT_CENTER, sfWhite);
			break;
		case 1:
			vt_DrawText(Vector2f(960.f, 690.f), "PROFESSORS", 35, TXT_CENTER, sfWhite);
			vt_DrawText(Vector2f(960.f, 745.f), "FOURNIERE SEBASTIEN", 25, TXT_CENTER, sfWhite);
			vt_DrawText(Vector2f(960.f, 780.f), "GIRAULT TRISTAN", 25, TXT_CENTER, sfWhite);
			vt_DrawText(Vector2f(960.f, 815.f), "MONAGO JONATHAN", 25, TXT_CENTER, sfWhite);
			break;
		case 2:
			vt_DrawText(Vector2f(960.f, 690.f), "TESTERS", 35, TXT_CENTER, sfWhite);
			vt_DrawText(Vector2f(960.f, 745.f), "PSILOVANGTON", 25, TXT_CENTER, sfWhite);
			vt_DrawText(Vector2f(960.f, 780.f), "MORENO RAPHAEL", 25, TXT_CENTER, sfWhite);
			vt_DrawText(Vector2f(960.f, 815.f), "VALETTE EVAN", 25, TXT_CENTER, sfWhite);
			break;
		case 3:
			vt_DrawText(Vector2f(960.f, 690.f), "SPECIAL THANKS", 35, TXT_CENTER, sfWhite);
			vt_DrawText(Vector2f(960.f, 745.f), "VIVIER KEVIN", 25, TXT_CENTER, sfWhite);
			vt_DrawText(Vector2f(960.f, 780.f), "AND ALL GAME ACADEMY PERSONNEL", 25, TXT_CENTER, sfWhite);
			break;
		case 4:
			vt_DrawText(Vector2f(960.f, 690.f), "MUSIC", 35, TXT_CENTER, sfWhite);
			vt_DrawText(Vector2f(960.f, 745.f), "PSILOVANGTON", 25, TXT_CENTER, sfWhite);
			vt_DrawText(Vector2f(960.f, 785.f), "TRACKS FROM THEIR ALBUM", 15, TXT_CENTER, sfWhite);
			vt_DrawText(Vector2f(960.f, 815.f), "APERTURE", 25, TXT_CENTER, sfWhite);
			break;
		default: break;
	}
}

void m_cred_Unload() {

}
