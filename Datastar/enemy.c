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
		itr->lifetime += getDeltaTime();
		if (itr->timer_blink > 0.f) itr->timer_blink -= getDeltaTime();
		else itr->timer_blink = 0.f;

		/// AI updates
		switch (itr->type) {
			case EN_WALL: itr = en_wall_Update(itr); break;
			case EN_SPARK: itr = en_spark_Update(itr); break;
			case EN_DART: itr = en_dart_Update(itr); break;
			case EN_STREAK: itr = en_streak_Update(itr); break;
			case EN_BOSS_GAMMA: itr = en_gamma_Update(itr); break;
		}


		/// On-hit functions
		PlayerBullet* itrB = plb_Sentinel->next;
		while (itrB != NULL) {
			sfBool flagDestroy = sfFalse;
			if (col_RectRect(itrB->aabb, itr->aabb)) {
				flagDestroy = sfTrue;
				itr->timer_blink = .4f;
//				itr->hp--;
				sfx_ProjectileImpact(itr->pos, itrB->spd, itr->clr);

				switch (itr->type) {
					case EN_WALL: en_wall_OnHit(itr, itrB); break;
					case EN_SPARK: en_spark_OnHit(itr, itrB); break;
					case EN_DART: en_dart_OnHit(itr, itrB); break;
					case EN_STREAK: en_streak_OnHit(itr, itrB); break;
					case EN_BOSS_GAMMA: en_gamma_OnHit(itr, itrB); break;
				}
			}

			if (flagDestroy) itrB = plb_PopPtr(itrB);
			else itrB = itrB->next;
			if (itr->hp <= 0) break;
		}

		/// On-kill functions
		if (itr->hp <= 0) {
			sfx_EnemyDeath(itr->pos, itr->clr);
			score_Add(en_GetValue(itr->type));

			switch (itr->type) {
				case EN_WALL: en_wall_OnKill(itr); break;
				case EN_SPARK: en_spark_OnKill(itr); break;
				case EN_DART: en_dart_OnKill(itr); break;
				case EN_STREAK: en_streak_OnKill(itr); break;
				case EN_BOSS_GAMMA: en_gamma_OnKill(itr); break;
			}

			PlayerBullet* itrB = plb_Sentinel->next;
			while (itrB != NULL) {
				if (itrB->type == PLB_HOMING && itrB->dataH.target == itr) itrB->dataH.target = NULL;
				itrB = itrB->next;
			}

			itr = en_PopPtr(itr);
		}
		else if (itr->pos.x < game_GetScrollX() - 100.f) itr = en_PopPtr(itr);
		else itr = itr->next;
	}
}

void en_Render() {
	EnData* itr = en_Sentinel->next;
	while (itr != NULL) {
		switch (itr->type) {
			case EN_WALL: en_wall_Render(itr); break;
			case EN_SPARK: en_spark_Render(itr); break;
			case EN_DART: en_dart_Render(itr); break;
			case EN_STREAK: en_streak_Render(itr); break;
			case EN_BOSS_GAMMA: en_gamma_Render(itr); break;
		}

		if (RENDER_HITBOXES) va_DrawFrame(NULL, itr->aabb, sfGreen);
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

int en_GetValue(EnType _type) {
    switch (_type) {
		case EN_WALL: return en_wall_Value();
		case EN_SPARK: return en_spark_Value();
		case EN_DART: return en_dart_Value();
		case EN_STREAK: return en_streak_Value();
		case EN_BOSS_GAMMA: return en_gamma_Value();
		default: return 100;
	}
}