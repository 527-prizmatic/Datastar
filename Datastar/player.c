#include "player.h"

sfVertexArray* plr_ModelShipTemp;

void plr_Init() {
	plr_Player.pos = Vector2f(960.f, 540.f);
	plr_Player.spd = NULLVECTF;
	plr_Player.hp = 3;
	plr_Player.hp_max = 6;
	plr_Player.rot = 0.f;
	plr_Player.fire_timer = 0.f;
	plr_Player.inv_frames = 0.f;
	plr_Player.bullet_count = 1;
	plr_Player.fire_mode = PLB_NORMAL;
	plr_Player.rof = 5.f;
	plr_Player.rot = 90.f;
	plr_Player.invincible = sfFalse;
}

void plr_Update() {
	if (plr_Player.fire_timer > 0.f) plr_Player.fire_timer -= getDeltaTime();
	if (plr_Player.inv_frames > 0.f) plr_Player.inv_frames -= getDeltaTime();
	plr_Control();

	if (plr_Collisions() && !plr_Player.invincible) {
		plr_Player.hp--;
		plr_Player.inv_frames = 3.f;
		sfx_PlayerHit();
	}
	
	if (plr_Player.hp <= 0) {
		gs_ChangeState(GS_MENU);
		return;
	}
	plr_Player.pos = v_Add(plr_Player.pos, v_Mul(plr_Player.spd, getDeltaTime()));
	plr_Player.aabb = FloatRect_FromCenter(plr_Player.pos, 32.f, 32.f);
}

void plr_Render() {
	plr_ModelShipTemp = sfVertexArray_copy(model_PlayerShip);
	va_SetPosition(plr_ModelShipTemp, plr_Player.pos);
	va_Rotate(plr_ModelShipTemp, plr_Player.rot);
	if (plr_Player.inv_frames > 0.f) va_SetColorOverride(plr_ModelShipTemp, itp_Color(sfWhite, sfRed, .5f - .5f * cos(plr_Player.inv_frames * 25.f), itp_Linear));
	sfRenderWindow_drawVertexArray(window.rw, plr_ModelShipTemp, NULL);
	if (RANDF(0.f, 1.f) < .25f) sfx_PlayerPropeller();
	if (plr_Player.invincible) {
		va_DrawCircle(VA_LINE, NULL, plr_Player.pos, 35.f, sfWhite);
		va_DrawCircle(VA_LINE, NULL, plr_Player.pos, 38.f, sfWhite);
	}
	if (RENDER_HITBOXES) va_DrawFrame(NULL, plr_Player.aabb, sfGreen);
}

void plr_Unload() {
	sfVertexArray_destroy(plr_ModelShipTemp);
}

void plr_Control() {
	/// Moving when pressing arrow keys
	if (kb_TestHold(ctrl_GetKey(KEY_UP))) plr_Player.acc.y = -1.f;
	else if (kb_TestHold(ctrl_GetKey(KEY_DOWN))) plr_Player.acc.y = 1.f;
	else plr_Player.acc.y = 0.f;

	if (kb_TestHold(ctrl_GetKey(KEY_LEFT))) plr_Player.acc.x = -1.f;
	else if (kb_TestHold(ctrl_GetKey(KEY_RIGHT))) plr_Player.acc.x = 1.f;
	else plr_Player.acc.x = 0.f;

	plr_Player.acc = v_Mul(plr_Player.acc, 3000.f);
	plr_Player.spd = v_Add(plr_Player.spd, v_Mul(plr_Player.acc, getDeltaTime()));
	plr_Player.spd.x += game_GetScrollSpeed() * .075f;
	plr_Player.spd = v_Mul(plr_Player.spd, pow(.01f, getDeltaTime()));
	plr_Player.spd.x -= 2.f * max(0.f, plr_Player.pos.x - (game_GetScrollX() + 1820.f));
	plr_Player.spd.x -= 2.f * min(0.f, plr_Player.pos.x - (game_GetScrollX() + 100.f));
	if (plr_Player.pos.y <= 99.f || plr_Player.pos.y >= 981.f) {
		plr_Player.acc.y *= -2.f;
		plr_Player.spd.y *= -2.f;
	}

	/// Firing while space is kept pressed
	if (kb_TestHold(ctrl_GetKey(KEY_FIRE)) && plr_Player.fire_timer <= 0.f && game_GetTime() > .5f) {
		plr_Player.fire_timer = 1.f / plr_Player.rof;
		for (int i = 0; i < plr_Player.bullet_count; i++) plb_New(plr_Player.fire_mode, v_Add(plr_Player.pos, v_RotateD(Vector2f(20.f, 0.f), plr_Player.rot - 90.f)), 4.f * i - 2.f * (plr_Player.bullet_count - 1.f));
		sfx_PlayerFire();
	}

	/// Changing fire modes upon hitting tab
	if (kb_TestPress(ctrl_GetKey(KEY_CHANGE))) {
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

void plr_HealOne() { if (plr_Player.hp < plr_Player.hp_max) plr_Player.hp++; }

void plr_Invincible(sfBool _inv) { plr_Player.invincible = _inv; }