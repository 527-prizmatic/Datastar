#include "init.h"

float init_TimerGlobal = 0.f;

sfVector2f init_LogoCap_RandomPos[13];
sfVector2f init_LogoCap_RandomSpd[13];
sfVector2f init_LogoCap_Star[13];
sfVector2f init_LogoCap_Final[13];
sfVector2f init_LogoCap[13];

sfVector2f init_LogoG_RandomPos[17];
sfVector2f init_LogoG_RandomSpd[17];
sfVector2f init_LogoG_Star[17];
sfVector2f init_LogoG_Final[17];
sfVector2f init_LogoG[17];

sfVector2f init_LogoA_RandomPos[14];
sfVector2f init_LogoA_RandomSpd[14];
sfVector2f init_LogoA_Star[14];
sfVector2f init_LogoA_Final[14];
sfVector2f init_LogoA[14];


void init_InitLogoMorph();

void init_Init() {
	tex_Preload("ga.png", "ga");
	init_InitLogoMorph();
}

void init_Update() {
	init_TimerGlobal += getDeltaTime();
	//for (int i = 0; i < 6; i++) randomPos[i] = v_Add(randomPos[i], v_Mul(randomSpd[i], getDeltaTime()));

	for (int i = 0; i < 13; i++) init_LogoCap_RandomPos[i] = v_Add(init_LogoCap_RandomPos[i], v_Mul(init_LogoCap_RandomSpd[i], getDeltaTime()));
	for (int i = 0; i < 17; i++) init_LogoG_RandomPos[i] = v_Add(init_LogoG_RandomPos[i], v_Mul(init_LogoG_RandomSpd[i], getDeltaTime()));
	for (int i = 0; i < 14; i++) init_LogoA_RandomPos[i] = v_Add(init_LogoA_RandomPos[i], v_Mul(init_LogoA_RandomSpd[i], getDeltaTime()));



	if (init_TimerGlobal < 15.f) {
		for (int i = 0; i < 13; i++) init_LogoCap[i] = init_LogoCap_RandomPos[i];
		for (int i = 0; i < 17; i++) init_LogoG[i] = init_LogoG_RandomPos[i];
		for (int i = 0; i < 14; i++) init_LogoA[i] = init_LogoA_RandomPos[i];
	}
	else if (init_TimerGlobal >= 15.f && init_TimerGlobal < 16.5f) {
		float time = (init_TimerGlobal - 15.f) / 1.5f;
		for (int i = 0; i < 13; i++) init_LogoCap[i] = itp_Vector2f(init_LogoCap_RandomPos[i], init_LogoCap_Star[i], time, itp_Smoother);
		for (int i = 0; i < 17; i++) init_LogoG[i] = itp_Vector2f(init_LogoG_RandomPos[i], init_LogoG_Star[i], time, itp_Smoother);
		for (int i = 0; i < 14; i++) init_LogoA[i] = itp_Vector2f(init_LogoA_RandomPos[i], init_LogoA_Star[i], time, itp_Smoother);
	}
	else if (init_TimerGlobal >= 16.5f && init_TimerGlobal < 18.f) {
		float time = (init_TimerGlobal - 16.5f) / 1.5f;
		for (int i = 0; i < 13; i++) init_LogoCap[i] = itp_Vector2f(init_LogoCap_Star[i], init_LogoCap_Final[i], time, itp_Smoother);
		for (int i = 0; i < 17; i++) init_LogoG[i] = itp_Vector2f(init_LogoG_Star[i], init_LogoG_Final[i], time, itp_Smoother);
		for (int i = 0; i < 14; i++) init_LogoA[i] = itp_Vector2f(init_LogoA_Star[i], init_LogoA_Final[i], time, itp_Smoother);
	}
}

void init_Render() {
	va_DrawScreenBorders();

	if (init_TimerGlobal <= 12.f) {
		vt_DrawText(Vector2f(960.f, 437.5f), "THIS GAME IS A WORK OF FICTION.", 28, TXT_CENTER, ColorA(255, 255, 255, clamp((4.f - fabs(init_TimerGlobal - 4.f)) * 64.f, 0.f, 255.f)));
		vt_DrawText(Vector2f(960.f, 472.5f), "ANY RESEMBLANCE TO ACTUAL EVENTS OR LOCALES", 28, TXT_CENTER, ColorA(255, 255, 255, clamp((4.f - fabs(init_TimerGlobal - 5.f)) * 64.f, 0.f, 255.f)));
		vt_DrawText(Vector2f(960.f, 507.5f), "OR PERSONS, LIVING OR DEAD,", 28, TXT_CENTER, ColorA(255, 255, 255, clamp((4.f - fabs(init_TimerGlobal - 6.f)) * 64.f, 0.f, 255.f)));
		vt_DrawText(Vector2f(960.f, 542.5f), "WOULD BE ENTIRELY COINCIDENTAL.", 28, TXT_CENTER, ColorA(255, 255, 255, clamp((4.f - fabs(init_TimerGlobal - 7.f)) * 64.f, 0.f, 255.f)));
		vt_DrawText(Vector2f(960.f, 612.5f), "ALL RIGHTS RESERVED.", 28, TXT_CENTER, ColorA(255, 255, 255, clamp((4.f - fabs(init_TimerGlobal - 8.f)) * 64.f, 0.f, 255.f)));

		if (kb_TestPress(sfKeySpace)) init_TimerGlobal = 12.f;
	}
	else if (init_TimerGlobal <= 20.f) {

		va_DrawPolygon(VA_LINE, NULL, 13, init_LogoCap, sfTrue, ColorA(255, 255, 255, clamp((4.f - fabs(init_TimerGlobal - 16.f)) * 64.f, 0.f, 255.f)));
		va_DrawPolygon(VA_LINE, NULL, 17, init_LogoG, sfTrue, ColorA(255, 255, 255, clamp((4.f - fabs(init_TimerGlobal - 16.f)) * 64.f, 0.f, 255.f)));
//		va_DrawPolygon(VA_LINE, NULL, 14, init_LogoA, sfTrue, ColorA(255, 255, 255, clamp((4.f - fabs(init_TimerGlobal - 16.f)) * 64.f, 0.f, 255.f)));

		if (kb_TestPress(sfKeySpace)) init_TimerGlobal = 20.f;
	}
	else if (init_TimerGlobal <= 30.f) {
		for (int i = 0; i < 3; i++) {
			vt_DrawText(Vector2f(960.f, 493.5f + i), "THIS VIDEO GAME CONTAINS BRIGHT COLORS", 28, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((5.f - fabs(init_TimerGlobal - 25.f)) * 64.f, 0.f, 255.f)));
			vt_DrawText(Vector2f(960.f, 528.5f + i), "AND FLASHING LIGHTS WHICH MAY CAUSE DISCOMFORT", 28, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((5.f - fabs(init_TimerGlobal - 25.f)) * 64.f, 0.f, 255.f)));
			vt_DrawText(Vector2f(960.f, 563.5f + i), "OR TRIGGER SEIZURES FOR SENSITIVE PEOPLE.", 28, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((5.f - fabs(init_TimerGlobal - 25.f)) * 64.f, 0.f, 255.f)));
			vt_DrawText(Vector2f(960.f, 598.5f + i), "REMEMBER TO TAKE FREQUENT BREAKS!", 28, TXT_CENTER, ColorA(255, 255, 255, (3.f - i) / 3.f * clamp((5.f - fabs(init_TimerGlobal - 25.f)) * 64.f, 0.f, 255.f)));
		}
		if (kb_TestPress(sfKeySpace)) init_TimerGlobal = 30.f;
	}
	else gs_ChangeState(GS_INTRO);
}

void init_Unload() {
	tex_Unload("ga");
}

void init_InitLogoMorph() {
	init_LogoCap_Star[0]  = Vector2f( 900.f, 480.f);
	init_LogoCap_Star[1]  = Vector2f( 960.f, 480.f);
	init_LogoCap_Star[2]  = Vector2f(1020.f, 480.f);
	init_LogoCap_Star[3]  = Vector2f(1020.f, 540.f);
	init_LogoCap_Star[4]  = Vector2f(1020.f, 600.f);
	init_LogoCap_Star[5]  = Vector2f( 960.f, 600.f);
	init_LogoCap_Star[6]  = Vector2f( 900.f, 600.f);
	init_LogoCap_Star[7]  = Vector2f( 900.f, 540.f);
	init_LogoCap_Star[8]  = Vector2f( 900.f, 480.f);
	init_LogoCap_Star[9]  = Vector2f( 930.f, 510.f);
	init_LogoCap_Star[10] = Vector2f( 960.f, 540.f);
	init_LogoCap_Star[11] = Vector2f( 990.f, 570.f);
	init_LogoCap_Star[12] = Vector2f(1020.f, 600.f);

	init_LogoCap_Final[0]  = Vector2f( 816.f, 451.f);
	init_LogoCap_Final[1]  = Vector2f( 962.f, 368.f);
	init_LogoCap_Final[2]  = Vector2f(1104.f, 451.f);
	init_LogoCap_Final[3]  = Vector2f(1065.f, 479.f);
	init_LogoCap_Final[4]  = Vector2f( 962.f, 430.f);
	init_LogoCap_Final[5]  = Vector2f( 856.f, 479.f);
	init_LogoCap_Final[6]  = Vector2f( 839.f, 468.f);
	init_LogoCap_Final[7]  = Vector2f( 839.f, 515.f);
	init_LogoCap_Final[8]  = Vector2f( 851.f, 527.f);
	init_LogoCap_Final[9]  = Vector2f( 835.f, 542.f);
	init_LogoCap_Final[10] = Vector2f( 820.f, 527.f);
	init_LogoCap_Final[11] = Vector2f( 832.f, 515.f);
	init_LogoCap_Final[12] = Vector2f( 832.f, 463.f);


	init_LogoG_Star[0]  = Vector2f( 760.f, 540.f);
	init_LogoG_Star[1]  = Vector2f( 800.f, 540.f);
	init_LogoG_Star[2]  = Vector2f( 840.f, 470.f);
	init_LogoG_Star[3]  = Vector2f( 880.f, 400.f);
	init_LogoG_Star[4]  = Vector2f( 860.f, 370.f);
	init_LogoG_Star[5]  = Vector2f( 960.f, 370.f);
	init_LogoG_Star[6]  = Vector2f(1060.f, 370.f);
	init_LogoG_Star[7]  = Vector2f(1040.f, 400.f);
	init_LogoG_Star[8]  = Vector2f(1080.f, 470.f);
	init_LogoG_Star[9]  = Vector2f(1120.f, 540.f);
	init_LogoG_Star[10] = Vector2f(1160.f, 540.f);
	init_LogoG_Star[11] = Vector2f(1060.f, 710.f);
	init_LogoG_Star[12] = Vector2f(1040.f, 650.f);
	init_LogoG_Star[13] = Vector2f( 960.f, 650.f);
	init_LogoG_Star[14] = Vector2f( 900.f, 650.f);
	init_LogoG_Star[15] = Vector2f( 860.f, 710.f);
	init_LogoG_Star[16] = Vector2f( 810.f, 625.f);

	init_LogoG_Final[0]  = Vector2f( 849.f, 496.f);
	init_LogoG_Final[1]  = Vector2f( 956.f, 445.f);
	init_LogoG_Final[2]  = Vector2f( 956.f, 550.f);
	init_LogoG_Final[3]  = Vector2f( 927.f, 550.f);
	init_LogoG_Final[4]  = Vector2f( 927.f, 492.f);
	init_LogoG_Final[5]  = Vector2f( 871.f, 516.f);
	init_LogoG_Final[6]  = Vector2f( 871.f, 620.f);
	init_LogoG_Final[7]  = Vector2f( 927.f, 648.f);
	init_LogoG_Final[8]  = Vector2f( 927.f, 593.f);
	init_LogoG_Final[9]  = Vector2f( 879.f, 593.f);
	init_LogoG_Final[10]  = Vector2f( 879.f, 564.f);
	init_LogoG_Final[11] = Vector2f( 956.f, 564.f);
	init_LogoG_Final[12] = Vector2f( 956.f, 710.f);
	init_LogoG_Final[13] = Vector2f( 841.f, 639.f);
	init_LogoG_Final[14] = Vector2f( 841.f, 552.f);
	init_LogoG_Final[15] = Vector2f( 864.f, 527.f);
	init_LogoG_Final[16] = Vector2f( 849.f, 512.f);


	init_LogoA_Star[0]  = Vector2f( 900.f, 480.f);
	init_LogoA_Star[1]  = Vector2f( 960.f, 480.f);
	init_LogoA_Star[2]  = Vector2f(1020.f, 480.f);
	init_LogoA_Star[3]  = Vector2f(1020.f, 540.f);
	init_LogoA_Star[4]  = Vector2f(1020.f, 600.f);
	init_LogoA_Star[5]  = Vector2f( 960.f, 600.f);
	init_LogoA_Star[6]  = Vector2f( 900.f, 600.f);
	init_LogoA_Star[7]  = Vector2f( 900.f, 540.f);
	init_LogoA_Star[8]  = Vector2f( 900.f, 480.f);
	init_LogoA_Star[9]  = Vector2f( 930.f, 510.f);
	init_LogoA_Star[10] = Vector2f( 960.f, 540.f);
	init_LogoA_Star[11] = Vector2f( 990.f, 570.f);
	init_LogoA_Star[12] = Vector2f(1020.f, 600.f);
	init_LogoA_Star[13] = Vector2f(1020.f, 600.f);

	init_LogoA_Final[0]  = Vector2f( 816.f, 451.f);
	init_LogoA_Final[1]  = Vector2f( 962.f, 368.f);
	init_LogoA_Final[2]  = Vector2f(1104.f, 451.f);
	init_LogoA_Final[3]  = Vector2f(1065.f, 479.f);
	init_LogoA_Final[4]  = Vector2f( 962.f, 430.f);
	init_LogoA_Final[5]  = Vector2f( 856.f, 479.f);
	init_LogoA_Final[6]  = Vector2f( 839.f, 468.f);
	init_LogoA_Final[7]  = Vector2f( 839.f, 515.f);
	init_LogoA_Final[8]  = Vector2f( 851.f, 527.f);
	init_LogoA_Final[9]  = Vector2f( 835.f, 542.f);
	init_LogoA_Final[10] = Vector2f( 820.f, 527.f);
	init_LogoA_Final[11] = Vector2f( 832.f, 515.f);
	init_LogoA_Final[12] = Vector2f( 832.f, 463.f);
	init_LogoA_Final[13] = Vector2f( 832.f, 463.f);

	for (int i = 0; i < 13; i++) {
		init_LogoCap_RandomPos[i] = Vector2f(RANDF(700.f, 1180.f), RANDF(320.f, 760.f));
		init_LogoCap_RandomSpd[i] = Vector2f(RANDF(-30.f, 30.f), RANDF(-30.f, 30.f));
		init_LogoCap[i] = init_LogoCap_RandomPos[i];
	}

	for (int i = 0; i < 17; i++) {
		init_LogoG_RandomPos[i] = Vector2f(RANDF(700.f, 1180.f), RANDF(320.f, 760.f));
		init_LogoG_RandomSpd[i] = Vector2f(RANDF(-30.f, 30.f), RANDF(-30.f, 30.f));
		init_LogoG[i] = init_LogoG_RandomPos[i];
	}

	for (int i = 0; i < 14; i++) {
		init_LogoA_RandomPos[i] = Vector2f(RANDF(700.f, 1180.f), RANDF(320.f, 760.f));
		init_LogoA_RandomSpd[i] = Vector2f(RANDF(-30.f, 30.f), RANDF(-30.f, 30.f));
		init_LogoA[i] = init_LogoA_RandomPos[i];
	}
}