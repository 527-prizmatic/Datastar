#include "pulse.h"

#define FLARE_SPD 50.f

void en_Flare(sfVector2f _pos) {
	EnData* new = malloc(sizeof(EnData));
	if (!new) {
		log_LogStr(LOG_ERROR, "Enemy creation error: insufficient memory", sfTrue, sfTrue);
		return;
	}

	new->type = EN_FLARE;
	new->clr = Color(160, 192, 240);
	new->pos = Vector2f(_pos.x + FLARE_SPD * Bars(4), _pos.y - FLARE_SPD * Bars(4));
	new->spd = Vector2f(-FLARE_SPD, FLARE_SPD);
	new->lifetime = 0.f;
	new->timer_blink = 0.f;
	new->hp_max = 1;
	new->hp = new->hp_max;
	new->drop = PWR_NONE;

	new->dataGl.pos_target = _pos;
	new->dataGl.rot = 0.f;

	en_Add(new);
}

struct EnData* en_flare_Update(struct EnData* _en) {
	_en->dataGl.rot += 60.f * getDeltaTime();
	_en->pos = v_Add(_en->pos, v_Mul(_en->spd, getDeltaTime()));

	sfColor clrTrail = _en->clr;
	clrTrail.a = itp_Float(0.f, 255.f, clamp(_en->lifetime / Bars(2), 0.f, 1.f), itp_Linear);
	sfx_EnemyFlareTrail(_en->pos, clrTrail);

	if (_en->lifetime > Bars(4)) {
		if (v_Mag2(v_Sub(plr_Player.pos, _en->pos)) < 62500.f) plr_Hit();

		for (int i = 0; i < 16; i++) enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 400.f), 22.5f * i), _en->clr);
		sfx_EnemyFlareWaves(_en->pos, _en->clr);
		return en_PopPtr(_en);
	}

	return _en;
}

void en_flare_Render(struct EnData* _en) {
	sfColor colorBase = _en->clr;
	sfColor colorBlink = (fmod(fabs(_en->lifetime), .15f) > .075f) ? sfWhite : _en->clr;

	colorBase.a = itp_Float(0.f, 255.f, clamp(_en->lifetime / Bars(2), 0.f, 1.f), itp_Linear);
	colorBlink.a = itp_Float(0.f, 255.f, clamp(_en->lifetime / Bars(2), 0.f, 1.f), itp_Linear);

	/// For the Flare's body
	va_DrawPolygonReg(VA_LINE, NULL, 5, _en->pos, 90.f, _en->dataGl.rot, colorBase);
	va_DrawPolygonReg(VA_LINE, NULL, 5, _en->pos, 81.f, _en->dataGl.rot, colorBase);

	/// For the warning circle
	colorBase.a = 96;
	colorBlink.a = 12;
	va_DrawCircle(VA_LINE, NULL, _en->dataGl.pos_target, 250.f, colorBase);
	va_DrawCircle(VA_TRI, NULL, _en->dataGl.pos_target, itp_Float(0.f, 250.f, clamp(_en->lifetime / Bars(4), 0.f, 1.f), itp_Square), colorBlink);
}

int en_flare_Value() { return 0; }