#include "streak.h"

void en_Streak(sfVector2f _pos, sfBool _dir) {
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

	new->dataSt.dir = _dir;
	new->dataSt.spd_mul = 1.f;

	en_Add(new);
}

struct EnData* en_streak_Update(struct EnData* _en) {
	if (_en->dataSt.dir == 1) _en->spd = Vector2f(0.f, 600.f);
	else _en->spd = Vector2f(0.f, -600.f);
	_en->pos = v_Add(_en->pos, v_Mul(_en->spd, getDeltaTime() * _en->dataSt.spd_mul));
	if (_en->pos.y <= 130.f) _en->dataSt.dir = 1;
	if (_en->pos.y >= 950.f) _en->dataSt.dir = 0;
	_en->aabb = FloatRect_FromCenter(_en->pos, 60.f, 60.f);

	return _en;
}

void en_streak_OnHit(struct EnData* _en, struct PlayerBullet* _plb) {
	_en->hp--;
	_en->dataSt.spd_mul -= .25f;
}

void en_streak_OnKill(struct EnData* _en) { }

void en_streak_Render(struct EnData* _en) {
	sfColor colorBase = (fmod(_en->timer_blink, .1f) > .05f) ? sfWhite : _en->clr;

	va_DrawPolygonReg(VA_LINE, NULL, 4, _en->pos, 30.f, 0.f, colorBase);
}


int en_streak_Value() { return 500; }