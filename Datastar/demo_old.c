#include "demo.h"

float posX;
float rot;

PtcSystem* ptcsTestPoint;
PtcSystem* ptcsTestCircle;
PtcSystem* ptcsTestRectangle;
PtcSystem* ptcsTestLine;
PtcSystem* ptcsTestCatsmile;
PtcSystem* ptcsTestShard;

sfVertexArray* va;

void demo_Init() {
	posX = -100.f;
	rot = 0.f;

	tex_Preload("ufoRed.png", "ufo_red");
	tex_Preload("ufoGreen.png", "ufo_green");
	tex_Preload("ufoBlue.png", "ufo_blue");
	tex_Preload("mycelium.png", "mycelium");
	tex_Preload("bruh.png", "bruh");
	tex_Preload("poyo.png", "poyo");
	tex_Preload("catsmile.png", "cat");
	tex_Preload("trolfaec.png", "trolfaec");

	snd_Preload(SND_MUS, "bonk.wav", "bonk");
	snd_Preload(SND_MUS, "et_cybertruck.wav", "CYBERTRUCK");
	snd_Preload(SND_SND, "boom.wav", "boom");
	snd_Preload(SND_SND, "pickup.wav", "plop");

	shd_Preload(NULL, "example.frag", "ex");

	ptcsTestPoint = ptc_CreateSystem(5.f, 5.f, 100, 1.f, 2.f, 0.f, 30.f, PTC_GRAV_NONE, NULL);
	ptc_SetType(ptcsTestPoint, PTC_CIRCLE, 2.f, 4.f, sfWhite, sfBlack);
	ptc_SetShape(ptcsTestPoint, PTCS_POINT, Vector2f(560.f, 540.f));

	ptcsTestCircle = ptc_CreateSystem(-1.f, 10.f, 10000, 0.f, 0.f, 0.f, 0.f, PTC_GRAV_NONE, NULL);
	ptc_SetType(ptcsTestCircle, PTC_CIRCLE, 2.f, 4.f, sfMagenta, sfRed);
	ptc_SetShape(ptcsTestCircle, PTCS_CIRCLE, Vector2f(1460.f, 540.f), 150.f);

	ptcsTestRectangle = ptc_CreateSystem(20.f, 1.f, 100, 0.f, 0.f, 0.f, 0.f, PTC_GRAV_UP_SLOW, NULL);
	ptc_SetType(ptcsTestRectangle, PTC_CIRCLE, 2.f, 4.f, sfBlue, sfGreen);
	ptc_SetShape(ptcsTestRectangle, PTCS_RECTANGLE, Vector2f(830.f, 140.f), Vector2f(990.f, 290.f));

	ptcsTestLine = ptc_CreateSystem(5.f, 5.f, 1000, 0.f, 1.f, 0.f, 360.f, PTC_GRAV_SLOW, NULL);
	ptc_SetType(ptcsTestLine, PTC_CIRCLE, 2.f, 4.f, sfRed, sfBlack);
	ptc_SetShape(ptcsTestLine, PTCS_LINE, Vector2f(630.f, 740.f), Vector2f(1090.f, 950.f));

	ptcsTestCatsmile = ptc_CreateSystem(10.f, .5f, 25, 10.f, 10.f, -45.f, 45.f, PTC_GRAV_DEFAULT, NULL);
	ptc_SetType(ptcsTestCatsmile, PTC_SPRITE, "cat", .25f, 1.f, -120.f, 120.f);
	ptc_SetShape(ptcsTestCatsmile, PTCS_POINT, Vector2f(960.f, 540.f));

	ptcsTestShard = ptc_CreateSystem(5.f, 5.f, 100, 0.f, 1.f, 0.f, 360.f, PTC_GRAV_NONE, NULL);
	ptc_SetType(ptcsTestShard, PTC_SHARD, 2.f, 7.f, 3, 3, sfWhite, sfBlue);
	ptc_SetShape(ptcsTestShard, PTCS_POINT, Vector2f(1260.f, 740.f));

	/*	ptcsTestCatsmile = ptc_CreateSystem(10.f, 2.f, 25, 5.f, 5.f, 0.f, 360.f, PTC_GRAV_NONE, NULL);
		ptc_SetType(ptcsTestCatsmile, PTC_SPRITE, "trolfaec", .5f, 2.f, -120.f, 120.f);
		ptc_SetShape(ptcsTestCatsmile, PTCS_POINT, Vector2f(960.f, 540.f));*/

	va = sfVertexArray_create();
	sfVertexArray_setPrimitiveType(va, sfLineStrip);
	sfVertexArray_append(va, Vertex(Vector2f(100.f, 100.f), sfWhite));
	sfVertexArray_append(va, Vertex(Vector2f(1820.f, 100.f), sfWhite));
	sfVertexArray_append(va, Vertex(Vector2f(1820.f, 980.f), sfWhite));
	sfVertexArray_append(va, Vertex(Vector2f(100.f, 980.f), sfWhite));
	sfVertexArray_append(va, Vertex(Vector2f(101.f, 101.f), sfWhite));
	sfVertexArray_append(va, Vertex(Vector2f(1819.f, 101.f), sfWhite));
	sfVertexArray_append(va, Vertex(Vector2f(1819.f, 979.f), sfWhite));
	sfVertexArray_append(va, Vertex(Vector2f(101.f, 979.f), sfWhite));
	sfVertexArray_append(va, Vertex(Vector2f(102.f, 101.f), sfWhite));
	sfVertexArray_append(va, Vertex(Vector2f(1818.f, 101.f), sfWhite));
	sfVertexArray_append(va, Vertex(Vector2f(1818.f, 978.f), sfWhite));
	sfVertexArray_append(va, Vertex(Vector2f(102.f, 978.f), sfWhite));
	sfVertexArray_append(va, Vertex(Vector2f(100.f, 100.f), sfWhite));
}

void demo_Update() {
	rot += 4.f;
	posX += 6.f;
	if (kb_TestHold(sfKeyE)) posX -= 3.f;
	if (kb_TestRelease(sfKeyE)) posX += 30.f;

	if (kb_TestPress(sfKeyD)) gs_ChangeState(GS_GAME);

	if (snd_GetMusicState() == SND_PLAYING) {
	}
	else {
		if (kb_TestPress(sfKeyNum1)) mus_Play("bonk");
		if (kb_TestPress(sfKeyNum2)) mus_Play("CYBERTRUCK");
	}

	if (kb_TestPress(sfKeyNum5)) mus_FadeOut();

	if (kb_TestPress(sfKeyNum3)) snd_Play("boom");
	if (kb_TestPress(sfKeyNum4)) snd_Play("plop");

	ptc_SetPositionPC(ptcsTestPoint, v_Add(ptcsTestPoint->pos, Vector2f(100.f * getDeltaTime(), 0.f)));
	ptc_SetPositionRL(ptcsTestLine, v_Add(ptcsTestLine->pos1, Vector2f(0.f, 40.f * getDeltaTime())), v_Add(ptcsTestLine->pos2, Vector2f(0.f, -40.f * getDeltaTime())));
}

void demo_Render() {
	static float offsetX = 0.f;
	static float offsetY = 0.f;
	static float rot = 0.f;
	if (!w_IsPaused()) {
		offsetX = fmodf(offsetX + 2., 128.f);
		offsetY = fmodf(offsetY + .8, 128.f);
		//	rot = fmodf(rot + 90.f * getDeltaTime(), 360.f);
	}


	for (int i = -1; i <= 1920 / 128 + 1; i++) {
		for (int j = -1; j <= 1080 / 128 + 1; j++) {
			rq_Draw(RQ_SPRITE, NULL, Vector2f(i * 128.f + offsetX, j * 128.f + offsetY), "mycelium", RQ_TEX_NORECT, Vector2f(45.f, 45.f), rot, RQ_SCALE_DEFAULT, RQ_SPRCLR_NONE);
		}
	}

	rq_Draw(RQ_CIRCLE, NULL, Vector2f(100.f, 200.f), 50.f, NULLVECTF, sfWhite, RQ_SCALE_DEFAULT);
	rq_Draw(RQ_CIRCLE, NULL, Vector2f(500.f, 700.f), 80.f, NULLVECTF, sfYellow, RQ_SCALE_DEFAULT);
	rq_Draw(RQ_RECTANGLE, NULL, Vector2f(1200.f, 200.f), Vector2f(200.f, 20.f), NULLVECTF, sfGreen, 20.f, RQ_SCALE_DEFAULT);

	rq_Draw(RQ_SPRITE, shd_FetchState("ex"), Vector2f(posX - 000.f, 590.f), "poyo", RQ_TEX_NORECT, Vector2f(45.f, 45.f), rot - 144., RQ_SCALE_DEFAULT, RQ_SPRCLR_NONE);
	rq_Draw(RQ_SPRITE, NULL, Vector2f(posX - 100.f, 490.f), "cat", RQ_TEX_NORECT, Vector2f(45.f, 45.f), rot - 72., RQ_SCALE_DEFAULT, RQ_SPRCLR_NONE);
	rq_Draw(RQ_SPRITE, shd_FetchState("ex"), Vector2f(posX - 200.f, 840.f), "poyo", RQ_TEX_NORECT, Vector2f(45.f, 45.f), rot, RQ_SCALE_DEFAULT, RQ_SPRCLR_NONE);
	rq_Draw(RQ_SPRITE, NULL, Vector2f(posX - 300.f, 340.f), "bruh", RQ_TEX_NORECT, Vector2f(45.f, 45.f), rot + 72., RQ_SCALE_DEFAULT, RQ_SPRCLR_NONE);
	rq_Draw(RQ_SPRITE, NULL, Vector2f(posX - 400.f, 640.f), "cat", RQ_TEX_NORECT, Vector2f(45.f, 45.f), rot + 144., RQ_SCALE_DEFAULT, RQ_SPRCLR_NONE);

	rq_Draw(RQ_CIRCLE, NULL, v_Add(Vector2f(500.f, 500.f), gp_StickState(0, GP_STICK_LEFT)), 20.f, NULLVECTF, sfRed, RQ_SCALE_DEFAULT);
	rq_Draw(RQ_CIRCLE, NULL, v_Add(Vector2f(500.f, 500.f), gp_StickState(1, GP_STICK_LEFT)), 20.f, NULLVECTF, sfMagenta, RQ_SCALE_DEFAULT);
	rq_Draw(RQ_CIRCLE, NULL, Vector2f(500.f, 500.f), 20.f, NULLVECTF, sfRed, RQ_SCALE_DEFAULT);

	rq_Draw(RQ_VA, shd_FetchState("ex"), va);
}

void demo_Unload() {

}