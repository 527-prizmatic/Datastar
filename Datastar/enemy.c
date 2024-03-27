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

	/// initialization of type-relevant data
	if (_type == EN_WALL) {
		new->spd = NULLVECTF;
		new->hp_max = 3;
		new->aabb = FloatRect(_pos.x - 67.5f, _pos.y - 67.5f, 135.f, 135.f);
		new->clr = Color3(64);
	}
	else if (_type == EN_SPARK) {
		new->spd = NULLVECTF;
		new->hp_max = 2;
		new->dataS.beatCounter = 0;
		new->dataS.rot = 0.f;
		new->dataS.posOrigin = _pos;
		new->dataS.posOrigin.x -= game_GetScrollX();
//		new->clr = itp_Color(Color(0, 128, 255), Color(255, 0, 128), rand_unit(2), itp_Linear);
		new->clr = itp_Color(Color(128, 0, 255), Color(255, 0, 128), rand_unit(2), itp_Linear);
//		new->clr = Color(255, 0, 128);
	}
	else if (_type == EN_DART) {
		new->spd = Vector2f(300.f, 0.f);
		new->hp_max = 1;
		new->aabb = FloatRect(_pos.x - 67.5f, _pos.y - 67.5f, 135.f, 135.f);
		new->clr = Color(255, 192, 0);
		new->dataD.beatCounter = -1;
		for (int i = 0; i < 5; i++) new->dataD.posOld[i] = _pos;
		new->dataD.timerTrail = 0.f;
	}

	/// Initialization of generic data
	new->type = _type;
	new->pos = _pos;
	new->lifetime = 0.f;

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
		itr->lifetime += getDeltaTime();

		if (itr->type == EN_SPARK) {
			if (itr->hp == 2) {
				itr->pos.x = itp_Float(itr->dataS.posOrigin.x, 1770.f, clamp(itr->lifetime, 0.f, 1.f), itp_Smoother) + game_GetScrollX();
				if (game_GetBeatFlag()) itr->dataS.beatCounter++;
				if (itr->dataS.beatCounter == 2 && itr->hp == 2) {
					itr->dataS.beatCounter = -1;
					//				enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-500.f, 0.f), -20.f));
					enb_New(ENB_NORMAL, itr->pos, Vector2f(-500.f, 0.f), itr->clr);
					//				enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-500.f, 0.f), 20.f));
				}
				itr->dataS.rot += 360.f * getDeltaTime();
			}
			else {
				itr->pos.x += 400.f * getDeltaTime();
				itr->dataS.rot += 180.f * getDeltaTime();
			}

			itr->aabb = FloatRect(itr->pos.x - 40.f, itr->pos.y - 40.f, 80.f, 80.f);
		}

		else if (itr->type == EN_DART) {
			itr->pos = v_Add(itr->pos, v_Mul(itr->spd, getDeltaTime()));
			if (game_GetBeatFlag())
				itr->dataD.beatCounter++;
			if (itr->dataD.beatCounter >= 4) {
				itr->spd.x -= 1200.f * getDeltaTime();

				itr->dataD.timerTrail += getDeltaTime();
				if (itr->dataD.timerTrail >= .035f) {
					itr->dataD.timerTrail -= .035f;
					for (int i = 4; i > 0; i--) itr->dataD.posOld[i] = itr->dataD.posOld[i - 1];
					itr->dataD.posOld[0] = itr->pos;
				}
			}
			else for (int i = 0; i < 5; i++) itr->dataD.posOld[i] = itr->pos;

			itr->aabb = FloatRect(itr->pos.x - 30.f, itr->pos.y - 40.f, 60.f, 80.f);
		}

		PlayerBullet* itrB = plb_Sentinel->next;
		while (itrB != NULL) {
			sfBool flagDestroy = sfFalse;
			if (sfFloatRect_contains(&(itr->aabb), itrB->pos.x, itrB->pos.y)) {
				flagDestroy = sfTrue;
				itr->hp--;
				if (itr->type == EN_SPARK && itr->hp == 1) score_Add(en_GetValue(itr->type));
			}

			if (flagDestroy) {
				PtcSystem* ptc = ptc_CreateSystem(-1.f, .5f, 10, 5.f, 15.f, 60.f - v_AngAbsD(itrB->spd), 120.f - v_AngAbsD(itrB->spd), PTC_GRAV_NONE, NULL);
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
			score_Add(en_GetValue(itr->type));
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

			if (itr->hp <= 2) va_DrawPolygonStar(VA_LINE, NULL, 4, itr->pos, 35, 45.f, itr->clr);
			if (itr->hp <= 1) va_DrawPolygonStar(VA_LINE, NULL, 4, itr->pos, 70, 45.f, itr->clr);
		}
		else if (itr->type == EN_SPARK) {
			va_DrawPolygonStar(VA_LINE, NULL, 4, itr->pos, 40.f, itr->dataS.rot, sfWhite);
			if (itr->hp == 2) va_DrawPolygonStar(VA_LINE, NULL, 4, itr->pos, 40.f, itr->dataS.rot * .667f, itr->clr);
		}
		else if (itr->type == EN_DART) {
			sfColor clr = itr->clr;

			if (itr->dataD.beatCounter >= 4) {
				for (int i = 0; i < 5; i++) {
					va_DrawPolygonReg(VA_LINE, NULL, 3, itr->dataD.posOld[i], 30.f, 30.f, clr);
					clr.a -= 50;
				}
			}
			else {
				float i = itp_Float(0.f, 20.f, itr->lifetime / (4.f * (60.f / wave_GetTempo(game_GetLevel()))), itp_Square);
				sfFloatRect rFill = FloatRect(game_GetScrollX(), itr->pos.y - i, 1920.f, 2.f * i);
				clr.a = 16;
				va_DrawRectangle(VA_TRI, NULL, rFill, clr);
			}
			clr.a = itp_Float(128, 0, clamp(itr->lifetime - 3.f, 0.f, 1.f), itp_Linear);
			va_DrawRectangle(VA_LINE, NULL, FloatRect(game_GetScrollX(), itr->pos.y - 20.f, 1920.f, 40.f), clr);
		}


		va_DrawFrame(NULL, itr->aabb, sfGreen);
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
		case EN_WALL: return 100;
		case EN_SPARK: return 200;
		case EN_DART: return 750;
		default: return 100;
	}
}