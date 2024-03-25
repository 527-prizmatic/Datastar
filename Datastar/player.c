#include "player.h"

sfVertexArray* plr_ModelShipTemp;

void plr_ParticleFire();

void plr_Init() {
	plr_Player.pos = Vector2f(960.f, 540.f);
	plr_Player.spd = NULLVECTF;
	plr_Player.hp = 3;
	plr_Player.hp_max = 3;
	plr_Player.rot = 0.f;
	plr_Player.fireTimer = 0.f;
}

void plr_Update() {
	if (plr_Player.fireTimer > 0.f) plr_Player.fireTimer -= getDeltaTime();
	plr_Control();
	
	plr_Player.pos = v_Add(plr_Player.pos, v_Mul(plr_Player.spd, getDeltaTime()));
}

void plr_Render() {
	plr_ModelShipTemp = sfVertexArray_copy(model_PlayerShip);
//	sfVertexArray_getVertex(plr_ModelShipTemp, 2)->color = itp_Color(sfWhite, sfRed, plr_Player.fireTimer * 5.f, itp_InvSquare);
	va_SetPosition(plr_ModelShipTemp, plr_Player.pos);
	va_Rotate(plr_ModelShipTemp, plr_Player.rot);
	sfRenderWindow_drawVertexArray(window.rw, plr_ModelShipTemp, NULL);
}

void plr_Unload() {
	sfVertexArray_destroy(plr_ModelShipTemp);
}

void plr_Control() {
	if (kb_TestHold(sfKeyUp)) plr_Player.spd.y = -1.f;
	else if (kb_TestHold(sfKeyDown)) plr_Player.spd.y = 1.f;
	else plr_Player.spd.y = 0.f;
	if (kb_TestHold(sfKeyLeft)) plr_Player.spd.x = -1.f;
	else if (kb_TestHold(sfKeyRight)) plr_Player.spd.x = 1.f;
	else plr_Player.spd.x = 0.f;

	plr_Player.spd = v_SetMag(plr_Player.spd, 400.f);
	plr_Player.spd.x -= 2.f * max(0.f, plr_Player.pos.x - (game_GetScrollX() + 1720.f));
	plr_Player.spd.x -= 2.f * min(0.f, plr_Player.pos.x - (game_GetScrollX() + 300.f));
//	plr_Player.rot = 90.f + R2D(REC2POL(plr_Player.spd).y);
	plr_Player.rot = 90.f;

	if (kb_TestHold(sfKeySpace) && plr_Player.fireTimer <= 0.f) {
		plr_Player.fireTimer = .2f;
		plb_New(PLB_NORMAL, v_Add(plr_Player.pos, v_RotateD(Vector2f(20.f, 0.f), plr_Player.rot - 90.f)));
		plr_ParticleFire();
	}
}

void plr_ParticleFire() {
	PtcSystem* firePtc = ptc_CreateSystem(-1.f, .5f, 5, 5.f, 15.f, plr_Player.rot - 20.f, plr_Player.rot + 20.f, PTC_GRAV_NONE, NULL);
	ptc_SetType(firePtc, PTC_SHARD, 2.f, 5.f, 3, 3, sfWhite, sfWhite);
	ptc_SetShape(firePtc, PTCS_POINT, v_Add(plr_Player.pos, v_RotateD(Vector2f(20.f, 0.f), plr_Player.rot - 90.f)));
}