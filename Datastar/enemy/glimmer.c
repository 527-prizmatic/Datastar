#include "pulse.h"

#define GLIMMER_SPD 75.f

void en_Glimmer(sfVector2f _pos, float _lifetime, float _delay) {
	EnData* new = malloc(sizeof(EnData));
	if (!new) {
		log_LogStr(LOG_ERROR, "Enemy creation error: insufficient memory", sfTrue, sfTrue);
		return;
	}

	float spd = GLIMMER_SPD * Bars(2) / _lifetime;

	new->type = EN_GLIMMER;
	new->clr = itp_Color(Color(192, 128, 255), Color(128, 255, 224), rand_unit(2), itp_Linear);
	new->pos = Vector2f(_pos.x + spd * _lifetime, _pos.y - spd * _lifetime);
	new->spd = Vector2f(-spd, spd);
	new->lifetime = -_delay;
	new->timer_blink = 0.f;
	new->hp_max = 1;
	new->hp = new->hp_max;
	new->drop = PWR_NONE;

	new->dataGl.pos_target = _pos;
	new->dataGl.rot = 0.f;
	new->dataGl.fall_time = _lifetime;

	new->Update = en_glimmer_Update;
	new->OnHit  = NULL;
	new->OnKill = NULL;
	new->Render = en_glimmer_Render;
	new->Value  = en_glimmer_Value;

	en_Add(new);
}

struct EnData* en_glimmer_Update(struct EnData* _en) {
	if (_en->lifetime >= 0.f) {
		_en->dataGl.rot += 60.f * getDeltaTime();
		_en->pos = v_Add(_en->pos, v_Mul(_en->spd, getDeltaTime()));

		if (RANDF(0.f, 1.f) < .333f && (_en->dataGl.fall_time > Bars(1) || RANDF(0.f, 1.f) < .2f)) {
			sfColor clrTrail = _en->clr;
			clrTrail.a = itp_Float(0.f, 255.f, clamp(_en->lifetime / (_en->dataGl.fall_time * .5f), 0.f, 1.f), itp_Linear);
			sfx_EnemyGlimmerTrail(_en->pos, clrTrail);
		}

		if (_en->lifetime > _en->dataGl.fall_time) {
			if (v_Mag2(v_Sub(plr_Player.pos, _en->pos)) < 5625.f) plr_Hit();

			sfx_EnemyGlimmerWaves(_en->pos, _en->clr, _en->dataGl.fall_time > Bars(1));
			return en_PopPtr(_en);
		}
	}

	return _en;
}

void en_glimmer_Render(struct EnData* _en) {
	sfColor colorBase = _en->clr;
	sfColor colorBlink = (fmod(fabs(_en->lifetime), .15f) > .075f) ? sfWhite : _en->clr;

	colorBase.a = itp_Float(0.f, 255.f, clamp(_en->lifetime / (_en->dataGl.fall_time * .5f), 0.f, 1.f), itp_Linear);

	/// For the Glimmer's body
	va_DrawPolygonReg(VA_LINE, NULL, 5, _en->pos, 30.f, _en->dataGl.rot, colorBase);
	va_DrawPolygonReg(VA_LINE, NULL, 5, _en->pos, 25.f, _en->dataGl.rot, colorBase);

	/// For the warning circle
	colorBase.a = 96;
	colorBlink.a = 24;
	va_DrawCircle(VA_LINE, NULL, _en->dataGl.pos_target, 75.f, colorBase);
	va_DrawCircle(VA_TRI, NULL, _en->dataGl.pos_target, itp_Float(0.f, 75.f, clamp(_en->lifetime / _en->dataGl.fall_time, 0.f, 1.f), itp_Square), colorBlink);
}

int en_glimmer_Value() { return 0; }