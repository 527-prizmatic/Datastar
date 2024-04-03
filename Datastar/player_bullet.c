#include "player_bullet.h"

sfVertexArray* plb_VAHomingTrail;

void plb_Init() {
	plb_Sentinel = malloc(sizeof(PlayerBullet));
	if (!plb_Sentinel) return;
	memset(plb_Sentinel, 0, sizeof(PlayerBullet));

	plb_VAHomingTrail = sfVertexArray_create();
	sfVertexArray_setPrimitiveType(plb_VAHomingTrail, sfLineStrip);
}

void plb_New(PlbType _type, sfVector2f _pos, float _angle) {
	PlayerBullet* new = malloc(sizeof(PlayerBullet));
	if (!new) return;

	new->type = _type;
	new->pos = _pos;
	new->spd = v_RotateD(Vector2f(1200.f, 0.f), _angle);
	new->lifetime = 3.f;
	new->aabb = FloatRect_FromCenter(new->pos, 10.f, 10.f);

	if (_type == PLB_HOMING) {
		new->dataH.timer_turn = 0.f;
		for (int i = 0; i < 25; i++) new->dataH.trail[i] = _pos;
		new->dataH.timer_trail = 0.f;
		new->dataH.target = NULL;
	}
	
	plb_Add(new);
}

void plb_Add(PlayerBullet* _plb) {
	PlayerBullet* n = plb_Sentinel->next;
	plb_Sentinel->next = _plb;
	_plb->prev = plb_Sentinel;
	_plb->next = n;
	if (n != NULL) n->prev = _plb;
}

void plb_Update() {
	PlayerBullet* itr = plb_Sentinel->next;
	while (itr != NULL) {
		itr->pos = v_Add(itr->pos, v_Mul(itr->spd, getDeltaTime()));
		itr->aabb = FloatRect_FromCenter(itr->pos, 10.f, 10.f);
		itr->lifetime -= getDeltaTime();

		if (itr->type == PLB_HOMING) {
			if (itr->dataH.target == NULL) {
				EnData* target = NULL;
				float closestDist = 1.e9f;
				EnData* itrE = en_Sentinel->next;
				while (itrE != NULL) {
					if (itrE->type != EN_WALL && itrE->type != EN_PULSE && itrE->type != EN_GLIMMER && itrE->type != EN_FLARE && itrE->pos.x >= plr_Player.pos.x) {
						float dist = v_Mag2(v_Sub(itrE->pos, itr->pos));
						if (closestDist > dist) {
							closestDist = dist;
							target = itrE;
						}
					}
					itrE = itrE->next;
				}
				itr->dataH.target = target;
			}

			itr->dataH.timer_trail += getDeltaTime();
			if (itr->dataH.timer_trail >= .01f) {
				itr->dataH.timer_trail -= .01f;
				for (int i = 24; i > 0; i--) itr->dataH.trail[i] = itr->dataH.trail[i - 1];
				itr->dataH.trail[0] = itr->pos;
			}

			itr->dataH.timer_turn += getDeltaTime();
			if (itr->dataH.timer_turn >= .333f) {
				itr->dataH.timer_turn -= RANDF(.2f, .4f);
				if (itr->dataH.target != NULL) {
					sfVector2f posDiff = v_Sub(itr->dataH.target->pos, itr->pos);
						 if (posDiff.x <= 0.f && fabs(posDiff.y) <= fabs(posDiff.x)) itr->spd = Vector2f(-1200.f, 0.f);
					else if (posDiff.x >= 0.f && fabs(posDiff.y) <= fabs(posDiff.x)) itr->spd = Vector2f(1200.f, 0.f);
					else if (posDiff.y <= 0.f && fabs(posDiff.x) <= fabs(posDiff.y)) itr->spd = Vector2f(0.f, -1200.f);
					else if (posDiff.y >= 0.f && fabs(posDiff.x) <= fabs(posDiff.y)) itr->spd = Vector2f(0.f, 1200.f);
				}
			}

			if (itr->dataH.target) if (itr->dataH.target->pos.x < plr_Player.pos.x) itr->dataH.target = NULL;
		}

		if (itr->lifetime <= 0.f || !game_IsOnScreen(itr->pos)) itr = plb_PopPtr(itr);
		else itr = itr->next;
	}
}

void plb_Render() {
	PlayerBullet* itr = plb_Sentinel->next;
	while (itr != NULL) {
		va_DrawPolygonReg(VA_LINE, NULL, 3, itr->pos, 7.f, v_AngAbsD(itr->spd) + 90.f, sfWhite);
		sfColor clr = sfWhite;
		if (itr->type == PLB_NORMAL) {
			for (int i = 0; i < 25; i++) {
				clr.a = itp_Float(0.f, 255.f, 1.f - i / 25.f, itp_Cube);
				va_DrawPolygonReg(VA_LINE, NULL, 3, v_Sub(itr->pos, Vector2f(i * 3.f, 0.f)), 7.f, v_AngAbsD(itr->spd) + 90.f, clr);
			}
		}
		else if (itr->type == PLB_HOMING) {
			sfVertexArray_clear(plb_VAHomingTrail);
			for (int i = 0; i < 25; i++) sfVertexArray_append(plb_VAHomingTrail, Vertex(itr->dataH.trail[i], ColorA(255, 255, 255, 200 - 8 * i)));
			rq_Draw(RQ_VA, NULL, plb_VAHomingTrail);
		}
		if (RENDER_HITBOXES) va_DrawFrame(NULL, itr->aabb, sfCyan);
		itr = itr->next;
	}
}

PlayerBullet* plb_PopPtr(PlayerBullet* _plb) {
	PlayerBullet* p = _plb->prev;
	PlayerBullet* n = _plb->next;

	p->next = n;
	if (n != NULL) n->prev = p;
	free(_plb);
	return n;
}

void plb_ClearBuffer() {
	PlayerBullet* itr = plb_Sentinel->next;
	while (itr != NULL) itr = plb_PopPtr(itr);
	log_LogStr(LOG_INFO, "Player projectile buffer cleared", sfTrue, sfTrue);
}

void plb_Unload() {
	plb_ClearBuffer();
	free(plb_Sentinel);
	sfVertexArray_destroy(plb_VAHomingTrail);
}