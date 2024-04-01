#include "wall.h"

void en_Wall(sfVector2f _pos, int _hp_max, enum PwrType _drop) {
	EnData* new = malloc(sizeof(EnData));
	if (!new) {
		log_LogStr(LOG_ERROR, "Enemy creation error: insufficient memory", sfTrue, sfTrue);
		return;
	}

	new->type = EN_WALL;
	new->clr = Color3(64);
	new->pos = _pos;
	new->spd = NULLVECTF;
	new->aabb = FloatRect_FromCenter(_pos, 135.f, 135.f);
	new->lifetime = 0.f;
	new->timer_blink = 0.f;
	new->hp_max = _hp_max;
	new->hp = new->hp_max;
	new->drop = _drop;

	en_Add(new);
}

struct EnData* en_wall_Update(struct EnData* _en) {
	/// Walls have no AI and do nothing else than being hindrances whatsoever
	return _en;
}

void en_wall_OnHit(struct EnData* _en, struct PlayerBullet* _plb) {
	_en->hp--;
}

void en_wall_OnKill(struct EnData* _en) { }

void en_wall_Render(struct EnData* _en) {
	sfColor colorBase = (fmod(_en->timer_blink, .1f) > .05f) ? sfWhite : _en->clr;

	va_DrawRectangle(VA_LINE, NULL, _en->aabb, colorBase);
	va_DrawRectangle(VA_LINE, NULL, floatRect_Contract(_en->aabb, 5.f), colorBase);
	for (int i = 1; i < _en->hp; i++)va_DrawRectangle(VA_LINE, NULL, floatRect_Contract(_en->aabb, 15.f * i), colorBase);
}

int en_wall_Value() { return 100; }