#include "player.h"

sfVertexArray* plr_ModelShipTemp;

void plr_ParticlePropeller();
void plr_ParticleFire();
void plr_ParticleHit();

void plr_Init() {
	plr_Player.pos = Vector2f(960.f, 540.f);
	plr_Player.spd = NULLVECTF;
	plr_Player.hp = 3;
	plr_Player.hp_max = 3;
	plr_Player.rot = 0.f;
	plr_Player.fireTimer = 0.f;
	plr_Player.inv_frames = 0.f;
}

void plr_Update() {
	if (plr_Player.fireTimer > 0.f) plr_Player.fireTimer -= getDeltaTime();
	plr_Control();
	if (plr_Collisions()) {
		plr_Player.hp--;
		plr_Player.inv_frames = 3.f;
		plr_ParticleHit();
	}
	if (plr_Player.inv_frames > 0.f) plr_Player.inv_frames -= getDeltaTime();
	
	if (plr_Player.hp <= 0) {
		gs_ChangeState(GS_MENU);
		return;
	}
	plr_Player.pos = v_Add(plr_Player.pos, v_Mul(plr_Player.spd, getDeltaTime()));
}

void plr_Render() {
	plr_ModelShipTemp = sfVertexArray_copy(model_PlayerShip);
//	sfVertexArray_getVertex(plr_ModelShipTemp, 2)->color = itp_Color(sfWhite, sfRed, plr_Player.fireTimer * 5.f, itp_InvSquare);
	va_SetPosition(plr_ModelShipTemp, plr_Player.pos);
	va_Rotate(plr_ModelShipTemp, plr_Player.rot);
	if (plr_Player.inv_frames > 0.f) va_SetColorOverride(plr_ModelShipTemp, itp_Color(sfWhite, sfRed, .5f - .5f * cos(plr_Player.inv_frames * 25.f), itp_Linear));
	sfRenderWindow_drawVertexArray(window.rw, plr_ModelShipTemp, NULL);
	if (RANDF(0.f, 1.f) < .25f) plr_ParticlePropeller();
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

	plr_Player.spd = v_SetMag(plr_Player.spd, 500.f);
	plr_Player.spd.x -= 2.f * max(0.f, plr_Player.pos.x - (game_GetScrollX() + 1720.f));
	plr_Player.spd.x -= 2.f * min(0.f, plr_Player.pos.x - (game_GetScrollX() + 300.f));
	plr_Player.spd.x += 100.f;
	plr_Player.rot = 90.f;

	if (kb_TestHold(sfKeySpace) && plr_Player.fireTimer <= 0.f) {
		plr_Player.fireTimer = .2f;
		plb_New(PLB_NORMAL, v_Add(plr_Player.pos, v_RotateD(Vector2f(20.f, 0.f), plr_Player.rot - 90.f)));
		plr_ParticleFire();
	}
}

sfBool plr_Collisions() {
	if (plr_Player.inv_frames > 0.f) return sfFalse;
	if (plr_Player.pos.y <= 100.f || plr_Player.pos.y >= 980.f) return sfTrue;
//	sfFloatRect aabbPlr = floatRect_Expand(FloatRect(plr_Player.pos.x, plr_Player.pos.y, 0.f, 0.f), 20.f);

	EnData* en = en_Sentinel->next;
	while (en != NULL) {
		if (sfFloatRect_contains(&(en->aabb), plr_Player.pos.x, plr_Player.pos.y)) return sfTrue;
		en = en->next;
	}

	EnemyBullet* enb = enb_Sentinel->next;
	while (enb != NULL) {
		if (v_Mag2(v_Sub(plr_Player.pos, enb->pos)) < 625.f) {
			enb->lifetime = 0.f;
			return sfTrue;
		}
		enb = enb->next;
	}

	return sfFalse;
}

void plr_ParticlePropeller() {
	PtcSystem* propellerPtc = ptc_CreateSystem(-1.f, .25f, 1, 1.f, 5.f, -100.f, -80.f, PTC_GRAV_NONE, NULL);
	ptc_SetType(propellerPtc, PTC_SHARD, 1.f, 5.f, 3, 3, Color3(128), sfWhite);
	ptc_SetShape(propellerPtc, PTCS_POINT, v_Add(plr_Player.pos, Vector2f(-15.f, 0.f)));
}

void plr_ParticleFire() {
	PtcSystem* firePtc = ptc_CreateSystem(-1.f, .5f, 5, 5.f, 15.f, plr_Player.rot - 20.f, plr_Player.rot + 20.f, PTC_GRAV_NONE, NULL);
	ptc_SetType(firePtc, PTC_SHARD, 2.f, 5.f, 3, 3, sfWhite, sfWhite);
	ptc_SetShape(firePtc, PTCS_POINT, v_Add(plr_Player.pos, v_RotateD(Vector2f(20.f, 0.f), plr_Player.rot - 90.f)));
}

void plr_ParticleHit() {
	PtcSystem* firePtc = ptc_CreateSystem(-1.f, 3.f, 250, 0.f, 15.f, 0.f, 360.f, PTC_GRAV_NONE, NULL);
	ptc_SetType(firePtc, PTC_SHARD, .5f, 4.f, 3, 3, sfWhite, sfRed);
	ptc_SetShape(firePtc, PTCS_POINT, plr_Player.pos);
}