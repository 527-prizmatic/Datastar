#include "init.h"

float init_TimerGlobal = 0.f;

sfVector2f init_LogoCap_RandomPos[13]; /// Randomized starting positions for the logo's VA - the cap
sfVector2f init_LogoCap_RandomSpd[13]; /// Randomized starting speeds for the logo's VA - the cap
sfVector2f init_LogoCap_Star[13];	   /// Intermediary positions for the logo's VA to morph into a Datastar - the cap
sfVector2f init_LogoCap_Final[13];	   /// Final positions to reveal the school's logo - the cap
sfVector2f init_LogoCap[13];		   /// Current positions for the logo's VA - the cap

sfVector2f init_LogoG_RandomPos[17];   /// Randomized starting positions for the logo's VA - the G
sfVector2f init_LogoG_RandomSpd[17];   /// Randomized starting speeds for the logo's VA - the G
sfVector2f init_LogoG_Star[17];		   /// Intermediary positions for the logo's VA to morph into a Datastar - the G
sfVector2f init_LogoG_Final[17];	   /// Final positions to reveal the school's logo - the G
sfVector2f init_LogoG[17];			   /// Current positions for the logo's VA - the G

sfVector2f init_LogoA_RandomPos[14];   /// Randomized starting positions for the logo's VA - the A
sfVector2f init_LogoA_RandomSpd[14];   /// Randomized starting speeds for the logo's VA - the A
sfVector2f init_LogoA_Star[14];		   /// Intermediary positions for the logo's VA to morph into a Datastar - the A
sfVector2f init_LogoA_Final[14];	   /// Final positions to reveal the school's logo - the A
sfVector2f init_LogoA[14];			   /// Current positions for the logo's VA - the A


void init_InitLogoMorph();

VtnVaText* txtDiscl[5], *txtFlash[4];

void init_Init() {
	init_InitLogoMorph();

	txtDiscl[0] = vtn_Text("THIS GAME IS A WORK OF FICTION.", 28, TXT_CENTER);
	txtDiscl[1] = vtn_Text("ANY RESEMBLANCE TO ACTUAL EVENTS OR LOCALES", 28, TXT_CENTER);
	txtDiscl[2] = vtn_Text("OR PERSONS, LIVING OR DECEASED,", 28, TXT_CENTER);
	txtDiscl[3] = vtn_Text("WOULD BE ENTIRELY COINCIDENTAL.", 28, TXT_CENTER);
	txtDiscl[4] = vtn_Text("ALL RIGHTS RESERVED.", 28, TXT_CENTER);

	txtFlash[0] = vtn_Text("THIS VIDEO GAME CONTAINS BRIGHT COLORS", 28, TXT_CENTER);
	txtFlash[1] = vtn_Text("AND FLASHING LIGHTS WHICH MAY CAUSE DISCOMFORT", 28, TXT_CENTER);
	txtFlash[2] = vtn_Text("OR TRIGGER SEIZURES FOR SENSITIVE PEOPLE.", 28, TXT_CENTER);
	txtFlash[3] = vtn_Text("REMEMBER TO TAKE FREQUENT BREAKS!", 28, TXT_CENTER);
}

void init_Update() {
	init_TimerGlobal += getDeltaTime();

	for (int i = 0; i < 13; i++) init_LogoCap_RandomPos[i] = v_Add(init_LogoCap_RandomPos[i], v_Mul(init_LogoCap_RandomSpd[i], getDeltaTime()));
	for (int i = 0; i < 17; i++) init_LogoG_RandomPos[i]   = v_Add(init_LogoG_RandomPos[i], v_Mul(init_LogoG_RandomSpd[i], getDeltaTime()));
	for (int i = 0; i < 14; i++) init_LogoA_RandomPos[i]   = v_Add(init_LogoA_RandomPos[i], v_Mul(init_LogoA_RandomSpd[i], getDeltaTime()));

	if (init_TimerGlobal < 13.f) {
		for (int i = 0; i < 13; i++) init_LogoCap[i] = init_LogoCap_RandomPos[i];
		for (int i = 0; i < 17; i++) init_LogoG[i]   = init_LogoG_RandomPos[i];
		for (int i = 0; i < 14; i++) init_LogoA[i]   = init_LogoA_RandomPos[i];
	}
	else if (init_TimerGlobal >= 13.f && init_TimerGlobal < 14.5f) {
		float time = (init_TimerGlobal - 13.f) / 1.5f;
		for (int i = 0; i < 13; i++) init_LogoCap[i] = itp_Vector2f(init_LogoCap_RandomPos[i], init_LogoCap_Star[i], time, itp_Smoothester);
		for (int i = 0; i < 17; i++) init_LogoG[i]   = itp_Vector2f(init_LogoG_RandomPos[i],   init_LogoG_Star[i],   time, itp_Smoothester);
		for (int i = 0; i < 14; i++) init_LogoA[i]   = itp_Vector2f(init_LogoA_RandomPos[i],   init_LogoA_Star[i],   time, itp_Smoothester);
	}
	else if (init_TimerGlobal >= 14.5f && init_TimerGlobal < 15.f) {
		for (int i = 0; i < 13; i++) init_LogoCap[i] = init_LogoCap_Star[i];
		for (int i = 0; i < 17; i++) init_LogoG[i] = init_LogoG_Star[i];
		for (int i = 0; i < 14; i++) init_LogoA[i] = init_LogoA_Star[i];
	}
	else if (init_TimerGlobal >= 15.f && init_TimerGlobal < 16.5f) {
		float time = (init_TimerGlobal - 15.f) / 1.5f;
		for (int i = 0; i < 13; i++) init_LogoCap[i] = itp_Vector2f(init_LogoCap_Star[i], init_LogoCap_Final[i], time, itp_Smoothester);
		for (int i = 0; i < 17; i++) init_LogoG[i]   = itp_Vector2f(init_LogoG_Star[i],   init_LogoG_Final[i],   time, itp_Smoothester);
		for (int i = 0; i < 14; i++) init_LogoA[i]   = itp_Vector2f(init_LogoA_Star[i],   init_LogoA_Final[i],   time, itp_Smoothester);
	}
	else {
		for (int i = 0; i < 13; i++) init_LogoCap[i] = init_LogoCap_Final[i];
		for (int i = 0; i < 17; i++) init_LogoG[i]   = init_LogoG_Final[i];
		for (int i = 0; i < 14; i++) init_LogoA[i]   = init_LogoA_Final[i];
	}
}

void init_Render() {
	va_DrawScreenBorders();

	if (init_TimerGlobal <= 10.f) {
		for (int i = 0; i < 5; i++) {
			vtn_Draw(txtDiscl[i], Vector2f(960.f, 437.5f + 35.f * i), ColorA(255, 255, 255, clamp((4.f - fabs(init_TimerGlobal - (4.f + .5f * i))) * 64.f, 0.f, 255.f)));
		}

		if (kb_TestPress(sfKeySpace) || gp_TestPress(0, GP_BUTTON_A)) init_TimerGlobal = 10.f;
	}
	else if (init_TimerGlobal <= 20.f) {
		sfColor clr = ColorA(255, 255, 255, clamp((5.f - fabs(init_TimerGlobal - 15.f)) * 64.f, 0.f, 255.f));

		va_DrawPolygon(VA_LINE, NULL, 13, init_LogoCap, sfTrue, clr);
		va_DrawPolygon(VA_LINE, NULL, 17, init_LogoG,   sfTrue, clr);
		va_DrawPolygon(VA_LINE, NULL, 14, init_LogoA,   sfTrue, clr);

		if ((kb_TestPress(sfKeySpace) || gp_TestPress(0, GP_BUTTON_A)) && init_TimerGlobal < 18.f) init_TimerGlobal = 18.f;
	}
	else if (init_TimerGlobal <= 30.f) {
		for (int i = 0; i < 4; i++) {
			vtn_Draw(txtFlash[i], Vector2f(960.f, 475.f + 35.f * i), ColorA(255, 255, 255, clamp((4.f - fabs(init_TimerGlobal - (24.f + .5f * i))) * 64.f, 0.f, 255.f)));
		}
		if (kb_TestPress(sfKeySpace) || gp_TestPress(0, GP_BUTTON_A)) init_TimerGlobal = 30.f;
	}
	else gs_ChangeState(GS_INTRO);
}

void init_Unload() {
	for (int i = 0; i < 5; i++) vtn_DestroyText(txtDiscl[i]);
	for (int i = 0; i < 4; i++) vtn_DestroyText(txtFlash[i]);
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
	init_LogoG_Final[6]  = Vector2f( 871.f, 623.f);
	init_LogoG_Final[7]  = Vector2f( 927.f, 651.f);
	init_LogoG_Final[8]  = Vector2f( 927.f, 593.f);
	init_LogoG_Final[9]  = Vector2f( 879.f, 593.f);
	init_LogoG_Final[10]  = Vector2f( 879.f, 564.f);
	init_LogoG_Final[11] = Vector2f( 956.f, 564.f);
	init_LogoG_Final[12] = Vector2f( 956.f, 710.f);
	init_LogoG_Final[13] = Vector2f( 841.f, 639.f);
	init_LogoG_Final[14] = Vector2f( 841.f, 550.f);
	init_LogoG_Final[15] = Vector2f( 864.f, 527.f);
	init_LogoG_Final[16] = Vector2f( 849.f, 512.f);


	init_LogoA_Star[0]  = Vector2f( 760.f, 540.f);
	init_LogoA_Star[1]  = Vector2f( 810.f, 455.f);
	init_LogoA_Star[2]  = Vector2f( 860.f, 370.f);
	init_LogoA_Star[3]  = Vector2f( 910.f, 370.f);
	init_LogoA_Star[4]  = Vector2f(1010.f, 370.f);
	init_LogoA_Star[5]  = Vector2f(1060.f, 370.f);
	init_LogoA_Star[6]  = Vector2f(1110.f, 455.f);
	init_LogoA_Star[7]  = Vector2f(1160.f, 540.f);
	init_LogoA_Star[8]  = Vector2f(1110.f, 625.f);
	init_LogoA_Star[9]  = Vector2f(1060.f, 710.f);
	init_LogoA_Star[10] = Vector2f(1010.f, 710.f);
	init_LogoA_Star[11] = Vector2f( 910.f, 710.f);
	init_LogoA_Star[12] = Vector2f( 860.f, 710.f);
	init_LogoA_Star[13] = Vector2f( 810.f, 625.f);

	init_LogoA_Final[0]  = Vector2f( 967.f, 445.f);
	init_LogoA_Final[1]  = Vector2f(1082.f, 500.f);
	init_LogoA_Final[2]  = Vector2f(1082.f, 639.f);
	init_LogoA_Final[3]  = Vector2f(1028.f, 673.f);
	init_LogoA_Final[4]  = Vector2f(1028.f, 635.f);
	init_LogoA_Final[5]  = Vector2f(1052.f, 623.f);
	init_LogoA_Final[6]  = Vector2f(1052.f, 516.f);
	init_LogoA_Final[7]  = Vector2f( 996.f, 493.f);
	init_LogoA_Final[8]  = Vector2f( 996.f, 564.f);
	init_LogoA_Final[9]  = Vector2f(1044.f, 564.f);
	init_LogoA_Final[10] = Vector2f(1044.f, 593.f);
	init_LogoA_Final[11] = Vector2f( 996.f, 593.f);
	init_LogoA_Final[12] = Vector2f( 996.f, 692.f);
	init_LogoA_Final[13] = Vector2f( 967.f, 710.f);

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