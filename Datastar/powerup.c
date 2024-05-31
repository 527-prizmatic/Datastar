#include "powerup.h"

char* pwr_TxtRender;

void pwr_Init() {
	pwr_Sentinel = malloc(sizeof(PwrData));
	if (!pwr_Sentinel) return;
	pwr_Sentinel->prev = NULL;
	pwr_Sentinel->next = NULL;
	pwr_Sentinel->pos = NULLVECTF;
	pwr_Sentinel->type = PWR_NONE;
	pwr_Sentinel->lifetime = 0.f;
	pwr_Sentinel->aabb = FloatRect(0.f, 0.f, 0.f, 0.f);

	pwr_TxtRender = calloc(20, sizeof(char));
}

void pwr_New(sfVector2f _pos, PwrType _type) {
	PwrData* new = malloc(sizeof(PwrData));
	if (!new) return;

	if (_type == PWR_NONE) return;

	new->type = _type;
	new->pos = _pos;
	new->lifetime = 0.f;
	new->ptc = sfx_PowerupParticle(_pos, _type);
	new->spd = POL2REC(Vector2f(25.f, RANDF(0.f, 2.f * (float)PI)));

	PwrData* n = pwr_Sentinel->next;
	pwr_Sentinel->next = new;
	new->prev = pwr_Sentinel;
	new->next = n;
	if (n != NULL) n->prev = new;
}

void pwr_Update() {
	PwrData* itr = pwr_Sentinel->next;
	while (itr != NULL) {
		itr->lifetime += getDeltaTime();
		itr->pos = v_Add(itr->pos, v_Mul(itr->spd, getDeltaTime()));
		itr->aabb = FloatRect_FromCenter(itr->pos, 40.f, 40.f);
		ptc_SetPositionPC(itr->ptc, itr->pos);

		if (col_RectRect(itr->aabb, plr_Player.aabb)) {
			switch (itr->type) {
				case PWR_HP: plr_HealOne(); break;
				case PWR_POWER: plr_IncreaseBullets(1); break;
				case PWR_SCORE: score_Add(2500); sfx_ScoreNew(itr->pos, 2500); break;
				default: break;
			}
			itr = pwr_PopPtr(itr);
		}

		else if (itr->pos.x < game_GetScrollX() - 100.f) itr = pwr_PopPtr(itr);
		else itr = itr->next;
	}
}

void pwr_Render() {
	PwrData* itr = pwr_Sentinel->next;
	while (itr != NULL) {
		switch (itr->type) {
		case PWR_HP: pwr_RenderHp(itr->pos, itr->lifetime * 120.f); break;
			case PWR_POWER: pwr_RenderPower(itr->pos); break;
			case PWR_SCORE: pwr_RenderScore(itr->pos); break;
			default: break;
		}

		if (ARGS_RENDER_HITBOXES) va_DrawFrame(NULL, itr->aabb, sfMagenta);
		itr = itr->next;
	}

}

PwrData* pwr_PopPtr(PwrData* _pwr) {
	if (_pwr->ptc) ptc_DestroySystem(_pwr->ptc);

	PwrData* p = _pwr->prev;
	PwrData* n = _pwr->next;

	p->next = n;
	if (n != NULL) n->prev = p;
	free(_pwr);
	return n;
}

void pwr_ClearBuffer() {
	PwrData* itr = pwr_Sentinel->next;
	while (itr != NULL) itr = pwr_PopPtr(itr);

	free(pwr_Sentinel);
	free(pwr_TxtRender);
}

void pwr_RenderHp(sfVector2f _pos, float _angle) {
	if (ARGS_PIZZA_MODE) {
		sfColor clrDough = Color(255, 208, 64);
		sfColor clrCrust = Color(128, 64, 32);
		sfColor clrPepperoni = Color(208, 64, 64);

		sfVector2f vCrust[10];
		vCrust[0] = v_Add(_pos, v_RotateD(Vector2f(0.f, -25.f), -45.f));
		vCrust[1] = v_Add(_pos, v_RotateD(Vector2f(0.f, -25.f), -22.f));
		vCrust[2] = v_Add(_pos, v_RotateD(Vector2f(0.f, -25.f), 0.f));
		vCrust[3] = v_Add(_pos, v_RotateD(Vector2f(0.f, -25.f), 22.f));
		vCrust[4] = v_Add(_pos, v_RotateD(Vector2f(0.f, -25.f), 45.f));
		vCrust[5] = v_Add(_pos, v_RotateD(Vector2f(0.f, -28.f), 42.f));
		vCrust[6] = v_Add(_pos, v_RotateD(Vector2f(0.f, -28.f), 21.f));
		vCrust[7] = v_Add(_pos, v_RotateD(Vector2f(0.f, -28.f), 0.f));
		vCrust[8] = v_Add(_pos, v_RotateD(Vector2f(0.f, -28.f), -21.f));
		vCrust[9] = v_Add(_pos, v_RotateD(Vector2f(0.f, -28.f), -42.f));
		va_DrawPolygon(VA_LINE, NULL, 10, vCrust, sfTrue, clrCrust);

		sfVector2f vDough[6];
		vDough[0] = v_Add(_pos, Vector2f(0.f, 25.f));
		vDough[1] = v_Add(_pos, v_RotateD(Vector2f(0.f, -24.f), 45.f));
		vDough[2] = v_Add(_pos, v_RotateD(Vector2f(0.f, -24.f), 22.f));
		vDough[3] = v_Add(_pos, v_RotateD(Vector2f(0.f, -24.f), 0.f));
		vDough[4] = v_Add(_pos, v_RotateD(Vector2f(0.f, -24.f), -22.f));
		vDough[5] = v_Add(_pos, v_RotateD(Vector2f(0.f, -24.f), -45.f));
		va_DrawPolygon(VA_LINE, NULL, 6, vDough, sfTrue, clrDough);

		va_DrawPolygonReg(VA_LINE, NULL, 6, v_Add(_pos, Vector2f(-7.f, -14.f)), 4.f, 0.f, clrPepperoni);
		va_DrawPolygonReg(VA_LINE, NULL, 6, v_Add(_pos, Vector2f(6.f, -7.f)), 4.f, 0.f, clrPepperoni);
		va_DrawPolygonReg(VA_LINE, NULL, 6, v_Add(_pos, Vector2f(-2.f, 3.f)), 4.f, 0.f, clrPepperoni);
	}
	else {
		sfColor clr = Color(0, 64, 192);
		sfVector2f v[12];
		float rds = 30.f;
		for (int k = 0; k < 2; k++) {
			for (int i = 0; i < 4; i++) {
				v[i * 3]     = v_Add(_pos, v_RotateD(Vector2f(rds, 0.f), 15.f + i * 90.f));
				v[i * 3 + 1] = v_Add(_pos, v_RotateD(Vector2f(rds * .4f, 0.f), 45.f + i * 90.f));
				v[i * 3 + 2] = v_Add(_pos, v_RotateD(Vector2f(rds, 0.f), 75.f + i * 90.f));
			}
			va_DrawPolygon(VA_LINE, NULL, 12, v, sfTrue, clr);
			rds *= .75f;
		}
	}
}

void pwr_RenderPower(sfVector2f _pos) {
	sfColor clr = Color(192, 0, 0);
	sfVector2f v[5];

	_pos.y -= 15.f;
	for (int i = 0; i < 3; i++) {
		v[0] = v_Add(_pos, Vector2f((i == 1 ? 5.f : -5.f) + -15.f, 5.f));
		v[1] = v_Add(_pos, Vector2f((i == 1 ? 5.f : -5.f) + -15.f, -5.f));
		v[2] = v_Add(_pos, Vector2f((i == 1 ? 5.f : -5.f) + 10.f, -5.f));
		v[3] = v_Add(_pos, Vector2f((i == 1 ? 5.f : -5.f) + 20.f, 0.f));
		v[4] = v_Add(_pos, Vector2f((i == 1 ? 5.f : -5.f) + 10.f, 5.f));
		va_DrawPolygon(VA_LINE, NULL, 5, v, sfTrue, clr);

		_pos.y += 15.f;
	}
}

void pwr_RenderScore(sfVector2f _pos) {
	sfColor clr = Color(0, 160, 64);

	va_DrawPolygonReg(VA_LINE, NULL, 6, _pos, 25.f, 30.f, clr);
	va_DrawPolygonReg(VA_LINE, NULL, 6, _pos, 22.f, 30.f, clr);
	va_DrawPolygonReg(VA_LINE, NULL, 4, _pos, 12.f, 45.f, clr);
	va_DrawLine(NULL, v_Sub(_pos, Vector2f(8.f, -8.f)), v_Sub(_pos, Vector2f(-8.f, 8.f)), clr);
}