#include "dart.h"

void en_Dart(sfVector2f _pos, enum PwrType _drop) {
	EnData* new = malloc(sizeof(EnData));
	if (!new) {
		log_LogStr(LOG_ERROR, "Enemy creation error: insufficient memory", sfTrue, sfTrue);
		return;
	}

	new->type = EN_DART;
	new->clr = Color(255, 192, 0);
	new->pos = _pos;
	new->spd = NULLVECTF;
	new->lifetime = 0.f;
	new->timer_blink = 0.f;
	new->hp_max = 1;
	new->hp = new->hp_max;
	new->drop = _drop;

	for (int i = 0; i < 5; i++) new->dataDt.posOld[i] = _pos;
	new->dataDt.timerTrail = 0.f;

	en_Add(new);
}

struct EnData* en_dart_Update(struct EnData* _en) {
	_en->pos = v_Add(_en->pos, v_Mul(_en->spd, getDeltaTime()));
	if (_en->lifetime >= Beats(4)) {
		_en->spd.x -= 1200.f * getDeltaTime();

		_en->dataDt.timerTrail += getDeltaTime();
		if (_en->dataDt.timerTrail >= .035f) {
			_en->dataDt.timerTrail -= .035f;
			for (int i = 4; i > 0; i--) _en->dataDt.posOld[i] = _en->dataDt.posOld[i - 1];
			_en->dataDt.posOld[0] = _en->pos;
		}
		_en->aabb = FloatRect_FromCenter(_en->pos, 60.f, 80.f);
	}
	else {
		_en->spd.x = game_GetScrollSpeed();
		for (int i = 0; i < 5; i++) _en->dataDt.posOld[i] = _en->pos;
		_en->aabb = FloatRect(-1.f, -1.f, 0.f, 0.f);
	}

	return _en;
}

void en_dart_OnHit(struct EnData* _en, struct PlayerBullet* _plb) {
	_en->hp--;
}

void en_dart_OnKill(struct EnData* _en) { }

void en_dart_Render(struct EnData* _en) {
	sfColor colorBase = (fmod(_en->timer_blink, .1f) > .05f) ? sfWhite : _en->clr;
	sfColor clr = colorBase;
	float j = itp_Float(0.f, 1920.f, _en->lifetime / Beats(4), itp_Square);

	/// The Dart itself
	if (_en->lifetime >= Beats(4)) {
		for (int i = 0; i < 5; i++) {
			va_DrawPolygonReg(VA_LINE, NULL, 3, _en->dataDt.posOld[i], 30.f, 30.f, clr);
			clr.a -= 50;
		}
	}

	/// Warning beam
	else {
		float i = itp_Float(0.f, 15.f, _en->lifetime / Beats(4), itp_Square);
		sfFloatRect rFill = FloatRect(game_GetScrollX() + 1920.f - j, _en->pos.y - i, j, 2.f * i);
		clr.a = 12;
		va_DrawRectangle(VA_TRI, NULL, rFill, clr);
	}
	clr.a = itp_Float(48, 0, clamp(_en->lifetime - 3.f, 0.f, 1.f), itp_Linear);
	va_DrawRectangle(VA_LINE, NULL, FloatRect(game_GetScrollX() + 1920.f - j, _en->pos.y - 15.f, j, 30.f), clr);
}

int en_dart_Value() { return 750; }