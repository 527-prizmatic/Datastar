#include "streak.h"

void en_Streak(sfVector2f _pos, sfBool _dir, enum PwrType _drop) {
	EnData* new = malloc(sizeof(EnData));
	if (!new) {
		log_LogStr(LOG_ERROR, "Enemy creation error: insufficient memory", sfTrue, sfTrue);
		return;
	}

	new->type = EN_STREAK;
	new->clr = Color(128, 224, 255);
	new->pos = _pos;
	new->spd = NULLVECTF;
	new->lifetime = 0.f;
	new->timer_blink = 0.f;
	new->hp_max = 3;
	new->hp = new->hp_max;
	new->drop = _drop;

	new->dataSt.dir = _dir;
	new->dataSt.spd_mul = 1.f;
	for (int i = 0; i < 5; i++) new->dataSt.posOld[i] = _pos;
	new->dataSt.timerTrail = 0.f;

	en_Add(new);
}

struct EnData* en_streak_Update(struct EnData* _en) {
	_en->spd = Vector2f(sin(_en->lifetime * 5.f) * 25.f, sin((_en->pos.y - 120.f) / 840.f * PI) * 800.f);
	if (_en->dataSt.dir == 0) _en->spd.y *= -1.f;

	_en->pos = v_Add(_en->pos, v_Mul(_en->spd, getDeltaTime() * _en->dataSt.spd_mul));
	if (_en->pos.y <= 135.f) _en->dataSt.dir = 1;
	if (_en->pos.y >= 945.f) _en->dataSt.dir = 0;
	_en->aabb = FloatRect_FromCenter(_en->pos, 60.f, 60.f);

	_en->dataSt.timerTrail += getDeltaTime();
	if (_en->dataSt.timerTrail >= .035f) {
		_en->dataSt.timerTrail -= .035f;
		for (int i = 4; i > 0; i--) _en->dataSt.posOld[i] = _en->dataSt.posOld[i - 1];
		_en->dataSt.posOld[0] = _en->pos;
	}

	return _en;
}

void en_streak_OnHit(struct EnData* _en, struct PlayerBullet* _plb) {
	_en->hp--;
	_en->dataSt.spd_mul -= .25f;
}

void en_streak_OnKill(struct EnData* _en) { }

void en_streak_Render(struct EnData* _en) {
	sfColor colorBase = (fmod(_en->timer_blink, .1f) > .05f) ? sfWhite : _en->clr;

	va_DrawPolygonStar(VA_LINE, NULL, 2, _en->pos, 45.f, 0.f, colorBase);
	va_DrawPolygonStar(VA_LINE, NULL, 2, _en->pos, 22.5f, 0.f, colorBase);
	colorBase.a -= 127;
	for (int i = 0; i < 5; i++) {
		va_DrawPolygonStar(VA_LINE, NULL, 2, _en->dataSt.posOld[i], 45.f, 0.f, colorBase);
		va_DrawPolygonStar(VA_LINE, NULL, 2, _en->dataSt.posOld[i], 22.5f, 0.f, colorBase);
		colorBase.a -= 25;
	}
}


int en_streak_Value() { return 500; }