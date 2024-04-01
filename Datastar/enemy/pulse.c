#include "pulse.h"

void en_Pulse(sfVector2f _pos, float _delay) {
	EnData* new = malloc(sizeof(EnData));
	if (!new) {
		log_LogStr(LOG_ERROR, "Enemy creation error: insufficient memory", sfTrue, sfTrue);
		return;
	}

	new->type = EN_PULSE;
	new->clr = Color(255, 32, 32);
	new->pos = Vector2f(_pos.x, _pos.y > 540.f ? 1180.f : 100.f);
	new->spd = NULLVECTF;
	new->lifetime = -_delay;
	new->timer_blink = 0.f;
	new->hp_max = 1;
	new->hp = new->hp_max;
	new->drop = PWR_NONE;

	for (int i = 0; i < 5; i++) new->dataPl.posOld[i] = new->pos;
	new->dataPl.timerTrail = 0.f;
	new->dataPl.pos_target = Vector2f(_pos.x, _pos.y);
	new->dataPl.rot = 0.f;

	en_Add(new);
}

struct EnData* en_pulse_Update(struct EnData* _en) {
	_en->dataPl.rot += 120.f * getDeltaTime();
	_en->dataPl.pos_target.x += game_GetScrollSpeed() * getDeltaTime();
	_en->pos.x += game_GetScrollSpeed() * getDeltaTime();

	if (_en->lifetime > 0.f) {
		_en->pos = v_Mul(v_Add(v_Mul(_en->pos, 7.f), _en->dataPl.pos_target), .125f);
		if (_en->lifetime > Beats(1)) {
			sfx_EnemyDeath(_en->pos, _en->clr);
			for (int i = 0; i < 8; i++) enb_New(ENB_NORMAL, v_Add(Vector2f(20.f, 0.f), _en->pos), v_RotateD(Vector2f(400.f, 0.f), 45.f * i /*+ 22.5f*/), _en->clr);
			return en_PopPtr(_en);
		}
	}

	return _en;
}

void en_pulse_Render(struct EnData* _en) {
	sfColor colorBase = _en->clr;
	sfColor colorBlink = (fmod(fabs(_en->lifetime), .1f) > .05f) ? sfWhite : _en->clr;

	if (_en->lifetime < 0.f && _en->lifetime > -Beats(2)) {
		colorBase.a = 128;
		colorBlink.a = 32;
		va_DrawPolygonStar(VA_LINE, NULL, 6, _en->dataPl.pos_target, 40.f, _en->dataPl.rot * 4.f, colorBase);
		va_DrawPolygonStar(VA_TRI, NULL, 6, _en->dataPl.pos_target, itp_Float(40.f, 0.f, clamp(-_en->lifetime / Beats(2), 0.f, 1.f), itp_InvSquare), _en->dataPl.rot * 4.f, colorBlink);
	}
	else if (_en->lifetime > 0.f) {
		va_DrawPolygonStar(VA_LINE, NULL, 6, _en->pos, 40.f, _en->dataPl.rot, colorBase);
		va_DrawPolygonStar(VA_LINE, NULL, 6, _en->pos, itp_Float(0.f, 80.f, clamp(_en->lifetime / Beats(1), 0.f, 1.f), itp_Cube), -_en->dataPl.rot, colorBlink);
	}

//	va_DrawPolygonStar(VA_LINE, NULL, 4, _en->pos, 40.f, _en->dataSp.rot, sfWhite);
//	if (_en->hp == 2) va_DrawPolygonStar(VA_LINE, NULL, 4, _en->pos, 40.f, _en->dataSp.rot * .667f, colorBase);
}

int en_pulse_Value() { return 0; }