#include "enemy.h"

void en_Init() {
	en_Sentinel = malloc(sizeof(EnData));
	if (!en_Sentinel) {
		log_LogStr(LOG_FATAL, "Enemy buffer initialization error: insufficient memory", sfTrue, sfTrue);
		return;
	}

	memset(en_Sentinel, 0, sizeof(EnData));
	log_LogStr(LOG_INFO, "Enemy buffer initialized successfully", sfTrue, sfTrue);
}

void en_New(EnType _type, sfVector2f _pos) {
	EnData* new = malloc(sizeof(EnData));
	if (!new) {
		log_LogStr(LOG_FATAL, "Enemy creation error: insufficient memory", sfTrue, sfTrue);
		return;
	}

	/// Initialization of generic data
	new->type = _type;
	new->pos = _pos;

	/// initialization of type-relevant data
	if (new->type == EN_WALL) {
		new->spd = NULLVECTF;
		new->hp_max = 5;
		new->aabb = FloatRect(_pos.x - 67.5f, _pos.y - 67.5f, 135.F, 135.f);
		new->clr = Color3(64);
	}

	new->hp = new->hp_max;
	en_Add(new);
}

void en_Add(EnData* _en) {
	EnData* n = en_Sentinel->next;
	en_Sentinel->next = _en;
	_en->prev = en_Sentinel;
	_en->next = n;
	if (n != NULL) n->prev = _en;
}

void en_Update() {
	EnData* itr = en_Sentinel->next;
	while (itr != NULL) {
		PlayerBullet* itrB = plb_Sentinel->next;
		while (itrB != NULL) {
			sfBool flagDestroy = sfFalse;
			if (sfFloatRect_contains(&(itr->aabb), itrB->pos.x, itrB->pos.y)) {
				flagDestroy = sfTrue;
				itr->hp--;
			}

			if (flagDestroy) {
				PtcSystem* ptc = ptc_CreateSystem(-1.f, .5f, 10, 2.f, 8.f, 60.f - v_AngAbsD(itrB->spd), 120.f - v_AngAbsD(itrB->spd), PTC_GRAV_NONE, NULL);
				ptc_SetType(ptc, PTC_SHARD, 2.f, 5.f, 3, 3, sfWhite, itr->clr);
				ptc_SetShape(ptc, PTCS_POINT, itrB->pos);
				itrB = plb_PopPtr(itrB);
			}
			else itrB = itrB->next;
			if (itr->hp <= 0) break;
		}

		if (itr->hp <= 0) {
			PtcSystem* ptc = ptc_CreateSystem(-1.f, 1.f, 100, 2.f, 12.f, 0.f, 360.f, PTC_GRAV_NONE, NULL);
			ptc_SetType(ptc, PTC_SHARD, 2.f, 7.f, 3, 3, sfWhite, itr->clr);
			ptc_SetShape(ptc, PTCS_POINT, itr->pos, 20.f);
			itr = en_PopPtr(itr);
		}
		else if (itr->pos.x < game_GetScrollX() - 100.f) itr = en_PopPtr(itr);
		else itr = itr->next;
	}
}

void en_Render() {
	EnData* itr = en_Sentinel->next;
	while (itr != NULL) {
		if (itr->type == EN_WALL) {
			va_DrawRectangle(VA_LINE, NULL, itr->aabb, itr->clr);
			va_DrawRectangle(VA_LINE, NULL, floatRect_Contract(itr->aabb, 5.f), itr->clr);
		}

		itr = itr->next;
	}
}

EnData* en_PopPtr(EnData* _en) {
	EnData* p = _en->prev;
	EnData* n = _en->next;

	p->next = n;
	if (n != NULL) n->prev = p;
	free(_en);
	return n;
}

void en_ClearBuffer() {
	EnData* itr = en_Sentinel->next;
	while (itr != NULL) itr = en_PopPtr(itr);
	log_LogStr(LOG_INFO, "Enemy buffer cleared", sfTrue, sfTrue);
}

void en_Unload() {
	en_ClearBuffer();
	free(en_Sentinel);
}