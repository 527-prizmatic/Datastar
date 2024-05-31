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
		EnData* enp = itr;
		itr = itr->Update(itr);
		if (itr != enp) continue;


		/// On-hit functions
		if (itr->lifetime > Beats(1)) {
			PlayerBullet* itrB = plb_Sentinel->next;
			while (itrB != NULL) {
				sfBool flagDestroy = sfFalse;
				if (col_RectRect(itrB->aabb, itr->aabb)) {
					flagDestroy = sfTrue;
					if (itr->type != EN_BOSS_INCANDESCE) itr->timer_blink = .4f;
					sfx_ProjectileImpact(itrB->pos, itrB->spd, itr->clr);
					itr->OnHit(itr, itrB);
				}

				if (flagDestroy) itrB = plb_PopPtr(itrB);
				else itrB = itrB->next;
				if (itr->hp <= 0) break;
			}
		}

		/// On-kill functions
		if (itr->hp <= 0) {
			sfx_EnemyDeath(itr->pos, itr->clr);
			score_Add(itr->Value());
			sfx_ScoreNew(itr->pos, itr->Value());
			if (itr->drop != PWR_NONE) pwr_New(itr->pos, itr->drop);
			itr->OnKill(itr);
			if (gs_state == GS_MENU) return;

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
		itr->Render(itr);

		if (ARGS_RENDER_HITBOXES) va_DrawFrame(NULL, itr->aabb, sfRed);
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