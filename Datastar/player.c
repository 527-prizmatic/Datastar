#include "player.h"

sfVertexArray* plr_ModelShipTemp;

void plr_Init() {
	plr_Player.pos = Vector2f(960.f, 540.f);
	plr_Player.spd = NULLVECTF;
	plr_Player.hp = 3;
	plr_Player.hp_max = 3;
	plr_Player.rot = 0.f;
	plr_Player.fire_timer = 0.f;
	plr_Player.inv_frames = 0.f;
	plr_Player.bullet_count = 1;
	plr_Player.fire_mode = PLB_NORMAL;
	plr_Player.rof = 5.f;
}

void plr_Update() {
	if (plr_Player.fire_timer > 0.f) plr_Player.fire_timer -= getDeltaTime();
	plr_Control();
	if (plr_Collisions()) {
		plr_Player.hp--;
		plr_Player.inv_frames = 3.f;
		sfx_PlayerHit();
	}
	if (plr_Player.inv_frames > 0.f) plr_Player.inv_frames -= getDeltaTime();
	
	if (plr_Player.hp <= 0) {
		gs_ChangeState(GS_MENU);
		return;
	}
	plr_Player.pos = v_Add(plr_Player.pos, v_Mul(plr_Player.spd, getDeltaTime()));
	plr_Player.aabb = FloatRect_FromCenter(plr_Player.pos, 40.f, 40.f);
}

void plr_Render() {
	plr_ModelShipTemp = sfVertexArray_copy(model_PlayerShip);
//	sfVertexArray_getVertex(plr_ModelShipTemp, 2)->color = itp_Color(sfWhite, sfRed, plr_Player.fireTimer * 5.f, itp_InvSquare);
	va_SetPosition(plr_ModelShipTemp, plr_Player.pos);
	va_Rotate(plr_ModelShipTemp, plr_Player.rot);
	if (plr_Player.inv_frames > 0.f) va_SetColorOverride(plr_ModelShipTemp, itp_Color(sfWhite, sfRed, .5f - .5f * cos(plr_Player.inv_frames * 25.f), itp_Linear));
	sfRenderWindow_drawVertexArray(window.rw, plr_ModelShipTemp, NULL);
	if (RANDF(0.f, 1.f) < .25f) sfx_PlayerPropeller();
	if (RENDER_HITBOXES) va_DrawFrame(NULL, plr_Player.aabb, sfGreen);
}

void plr_Unload() {
	sfVertexArray_destroy(plr_ModelShipTemp);
}

void plr_Control() {
	/// Moving when pressing arrow keys
	if (kb_TestHold(sfKeyUp) || kb_TestHold(sfKeyW)) plr_Player.spd.y = -1.f;
	else if (kb_TestHold(sfKeyDown) || kb_TestHold(sfKeyS)) plr_Player.spd.y = 1.f;
	else plr_Player.spd.y = 0.f;
	if (kb_TestHold(sfKeyLeft) || kb_TestHold(sfKeyA)) plr_Player.spd.x = -1.f;
	else if (kb_TestHold(sfKeyRight) || kb_TestHold(sfKeyD)) plr_Player.spd.x = 1.f;
	else plr_Player.spd.x = 0.f;

	plr_Player.spd = v_SetMag(plr_Player.spd, 500.f);
	plr_Player.spd.x -= 2.f * max(0.f, plr_Player.pos.x - (game_GetScrollX() + 1720.f));
	plr_Player.spd.x -= 2.f * min(0.f, plr_Player.pos.x - (game_GetScrollX() + 300.f));
	plr_Player.spd.x += 100.f;
	if (plr_Player.pos.y <= 90.f) plr_Player.spd.y = max(0.f, plr_Player.spd.y);
	if (plr_Player.pos.y >= 990.f) plr_Player.spd.y = min(0.f, plr_Player.spd.y);
	plr_Player.rot = 90.f;

	/// Firing while space is kept pressed
	if (kb_TestHold(sfKeySpace) && plr_Player.fire_timer <= 0.f) {
		plr_Player.fire_timer = 1.f / plr_Player.rof;
		for (int i = 0; i < plr_Player.bullet_count; i++) plb_New(plr_Player.fire_mode, v_Add(plr_Player.pos, v_RotateD(Vector2f(20.f, 0.f), plr_Player.rot - 90.f)), 4.f * i - 2.f * (plr_Player.bullet_count - 1.f));
		sfx_PlayerFire();
	}

	/// Changing fire modes upon hitting tab
	if (kb_TestPress(sfKeyTab)) {
		if (plr_Player.fire_mode == PLB_NORMAL) {
			plr_Player.fire_mode = PLB_HOMING;
			plr_Player.rof = 3.f;
		}
		else if (plr_Player.fire_mode == PLB_HOMING) {
			plr_Player.fire_mode = PLB_NORMAL;
			plr_Player.rof = 5.f;
		}
	}
}

sfBool plr_Collisions() {
	if (plr_Player.inv_frames > 0.f) return sfFalse;
	if (plr_Player.pos.y <= 100.f || plr_Player.pos.y >= 980.f) return sfTrue;
//	sfFloatRect aabbPlr = floatRect_Expand(FloatRect(plr_Player.pos.x, plr_Player.pos.y, 0.f, 0.f), 20.f);

	EnData* en = en_Sentinel->next;
	while (en != NULL) {
		if (col_RectRect(en->aabb, plr_Player.aabb)) return sfTrue;
		en = en->next;
	}

	EnemyBullet* enb = enb_Sentinel->next;
	while (enb != NULL) {
		if (col_RectRect(enb->aabb, plr_Player.aabb)) {
			enb->lifetime = 0.f;
			return sfTrue;
		}
		enb = enb->next;
	}

	return sfFalse;
}

void plr_IncreaseBullets(int _i) { plr_Player.bullet_count += _i; }