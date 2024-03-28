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
		new->aabb = FloatRect_FromCenter(_pos, 135.f, 135.f);
		new->clr = Color3(64);
	}
	else if (_type == EN_SPARK) {
		new->spd = NULLVECTF;
		new->hp_max = 2;
		new->dataSp.beatCounter = 0;
		new->dataSp.rot = 0.f;
		new->dataSp.posOrigin = _pos;
		new->dataSp.posOrigin.x -= game_GetScrollX();
//		new->clr = itp_Color(Color(0, 128, 255), Color(255, 0, 128), rand_unit(2), itp_Linear);
		new->clr = itp_Color(Color(128, 0, 255), Color(255, 0, 128), rand_unit(2), itp_Linear);
//		new->clr = Color(255, 0, 128);
	}
	else if (_type == EN_DART) {
		new->spd = Vector2f(300.f, 0.f);
		new->hp_max = 1;
		new->clr = Color(255, 192, 0);
		new->dataDt.beatCounter = -1;
		for (int i = 0; i < 5; i++) new->dataDt.posOld[i] = _pos;
		new->dataDt.timerTrail = 0.f;
	}
	else if (_type == EN_STREAK) {
		new->spd = NULLVECTF;
		new->hp_max = 3;
		new->clr = Color(128, 224, 255);
	}

	else if (_type == EN_BOSS_GAMMA) {
		new->spd = NULLVECTF;
		new->hp_max = 200;
		new->clr = Color(255, 128, 64);
		new->dataGm.rot = 0.f;
		new->dataGm.posOrigin = _pos;
		new->dataGm.phase = 1;
		new->dataGm.beatCounter = -2;
		new->dataGm.timer_shots = 0.f;
	}

	/// Initialization of generic data
	new->type = _type;
	new->pos = _pos;
	new->lifetime = 0.f;
	new->timer_blink = 0.f;

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
		if (itr->timer_blink > 0.f) itr->timer_blink -= getDeltaTime();
		else itr->timer_blink = 0.f;

		if (itr->type == EN_SPARK) {
			if (itr->hp == 2) {
				itr->pos.x = itp_Float(itr->dataSp.posOrigin.x, 1770.f, clamp(itr->lifetime, 0.f, 1.f), itp_Smoother) + game_GetScrollX();
				if (game_GetBeatFlag()) itr->dataSp.beatCounter++;
				if (itr->dataSp.beatCounter == 2 && itr->hp == 2) {
					itr->dataSp.beatCounter = 0;
					enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-500.f, 0.f), -30.f), itr->clr);
					enb_New(ENB_NORMAL, itr->pos, Vector2f(-500.f, 0.f), itr->clr);
					enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-500.f, 0.f), 30.f), itr->clr);
					sfx_EnemyFire(itr->pos, Vector2f(-500.f, 0.f), itr->clr);
				}
				itr->dataSp.rot += 360.f * getDeltaTime();
			}
			else {
				itr->pos.x += 400.f * getDeltaTime();
				itr->dataSp.rot += 180.f * getDeltaTime();
			}

			itr->aabb = FloatRect_FromCenter(itr->pos, 80.f, 80.f);
		}

		else if (itr->type == EN_DART) {
			itr->pos = v_Add(itr->pos, v_Mul(itr->spd, getDeltaTime()));
			if (game_GetBeatFlag())
				itr->dataDt.beatCounter++;
			if (itr->dataDt.beatCounter >= 4) {
				itr->spd.x -= 1200.f * getDeltaTime();

				itr->dataDt.timerTrail += getDeltaTime();
				if (itr->dataDt.timerTrail >= .035f) {
					itr->dataDt.timerTrail -= .035f;
					for (int i = 4; i > 0; i--) itr->dataDt.posOld[i] = itr->dataDt.posOld[i - 1];
					itr->dataDt.posOld[0] = itr->pos;
				}
			}
			else for (int i = 0; i < 5; i++) itr->dataDt.posOld[i] = itr->pos;

			itr->aabb = FloatRect_FromCenter(itr->pos, 60.f, 80.f);
		}

		else if (itr->type == EN_STREAK) {
			if (itr->dataSt.dir == 1) itr->spd = Vector2f(0.f, 500.f);
			else itr->spd = Vector2f(0.f, -500.f);
			itr->pos = v_Add(itr->pos, v_Mul(itr->spd, getDeltaTime()));
			if (itr->pos.y <= 130.f) itr->dataSt.dir = 1;
			if (itr->pos.y >= 950.f) itr->dataSt.dir = 0;
			itr->aabb = FloatRect_FromCenter(itr->pos, 60.f, 60.f);
		}

		else if (itr->type == EN_BOSS_GAMMA) {
			itr->pos.x = itp_Float(itr->dataGm.posOrigin.x, 1820.f, clamp(itr->lifetime, 0.f, 5.f) * .2f, itp_Smoother) + game_GetScrollX();
			itr->dataGm.rot += 75.f * getDeltaTime();
			itr->aabb = FloatRect_FromCenter(itr->pos, 440.f, 440.f);
			if (itr->dataGm.timer_shots > 0.f) itr->dataGm.timer_shots -= getDeltaTime();

			if (itr->hp > itr->hp_max / 4 * 3) itr->dataGm.phase = 1;
			else if (itr->hp > itr->hp_max / 2) itr->dataGm.phase = 2;
			else if (itr->hp > itr->hp_max / 4) itr->dataGm.phase = 3;
			else itr->dataGm.phase = 4;

			if (game_GetBeatFlag()) itr->dataGm.beatCounter++;
			if (itr->dataGm.beatCounter == 1) {
				itr->dataGm.beatCounter = 0;
				switch (itr->dataGm.phase) {
					case 1:
						enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-500.f, 0.f), -sinf(itr->lifetime) * 30.f), itr->clr);
						enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-500.f, 0.f), sinf(itr->lifetime) * 30.f), itr->clr);
						break;
					case 2:
						enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-400.f, 0.f), -sinf(itr->lifetime + 2.f) * 40.f), itr->clr);
						enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-400.f, 0.f), sinf(itr->lifetime + 2.f) * 40.f), itr->clr);
						break;
					case 3:
						enb_New(ENB_NORMAL, itr->pos, Vector2f(-500.f, 0.f), itr->clr);
						enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-500.f, 0.f), -sinf(itr->lifetime) * 20.f), itr->clr);
						enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-500.f, 0.f), sinf(itr->lifetime) * 20.f), itr->clr);
						break;
					case 4:
						enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-500.f, 0.f), -60.f), itr->clr);
				//		enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-500.f, 0.f), -sinf(itr->lifetime) * 40.f), itr->clr);
						enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-500.f, 0.f), -20.f), itr->clr);
						enb_New(ENB_NORMAL, itr->pos, Vector2f(-500.f, 0.f), itr->clr);
						enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-500.f, 0.f), 20.f), itr->clr);
				//		enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-500.f, 0.f), sinf(itr->lifetime) * 40.f), itr->clr);
						enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-500.f, 0.f), 60.f), itr->clr);
						break;
				}
				sfx_EnemyFire(itr->pos, Vector2f(-500.f, 0.f), itr->clr);
			}

			if (itr->dataGm.timer_shots <= 0.f) {
				switch (itr->dataGm.phase) {
					case 1: break;
					case 2:
						enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-450.f, 0.f), -sinf(itr->lifetime) * 20.f), itr->clr);
						enb_New(ENB_NORMAL, itr->pos, Vector2f(-500.f, 0.f), itr->clr);
						enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-450.f, 0.f), sinf(itr->lifetime) * 20.f), itr->clr);
						itr->dataGm.timer_shots = .667f;
						break;
					case 3:
						enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-500.f, 0.f), v_AngAbsD(v_Sub(itr->pos, plr_Player.pos))), itr->clr);
						itr->dataGm.timer_shots = .5f;
						break;
					case 4:
						enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-300.f, 0.f), v_AngAbsD(v_Sub(itr->pos, plr_Player.pos)) - 30.f), itr->clr);
						enb_New(ENB_NORMAL, itr->pos, v_RotateD(Vector2f(-300.f, 0.f), v_AngAbsD(v_Sub(itr->pos, plr_Player.pos)) + 30.f), itr->clr);
						itr->dataGm.timer_shots = .333f;
						break;

				}
			}
		}

		PlayerBullet* itrB = plb_Sentinel->next;
		while (itrB != NULL) {
			sfBool flagDestroy = sfFalse;
			if (col_RectRect(itrB->aabb, itr->aabb)) {
				flagDestroy = sfTrue;
				itr->hp--;
				itr->timer_blink = .4f;
				if (itr->type == EN_SPARK && itr->hp == 1) score_Add(en_GetValue(itr->type));
			}

			if (flagDestroy) {
				sfx_ProjectileImpact(itr->pos, itrB->spd, itr->clr);
				itrB = plb_PopPtr(itrB);
			}
			else itrB = itrB->next;
			if (itr->hp <= 0) break;
		}

		if (itr->hp <= 0) {
			sfx_EnemyDeath(itr->pos, itr->clr);
			score_Add(en_GetValue(itr->type));

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
		sfColor colorBase = (fmod(itr->timer_blink, .1f) > .05f) ? sfWhite : itr->clr;

		if (itr->type == EN_WALL) {
			va_DrawRectangle(VA_LINE, NULL, itr->aabb, itr->clr);
			va_DrawRectangle(VA_LINE, NULL, floatRect_Contract(itr->aabb, 5.f), colorBase);

			if (itr->hp <= 2) va_DrawPolygonStar(VA_LINE, NULL, 4, itr->pos, 35, 45.f, colorBase);
			if (itr->hp <= 1) va_DrawPolygonStar(VA_LINE, NULL, 4, itr->pos, 70, 45.f, colorBase);
		}
		else if (itr->type == EN_SPARK) {
			va_DrawPolygonStar(VA_LINE, NULL, 4, itr->pos, 40.f, itr->dataSp.rot, sfWhite);
			if (itr->hp == 2) va_DrawPolygonStar(VA_LINE, NULL, 4, itr->pos, 40.f, itr->dataSp.rot * .667f, colorBase);
		}
		else if (itr->type == EN_DART) {
			sfColor clr = colorBase;

			float j = itp_Float(0.f, 1920.f, itr->lifetime / (4.f * (60.f / wave_GetTempo(game_GetLevel()))), itp_Square);
			if (itr->dataDt.beatCounter >= 4) {
				for (int i = 0; i < 5; i++) {
					va_DrawPolygonReg(VA_LINE, NULL, 3, itr->dataDt.posOld[i], 30.f, 30.f, clr);
					clr.a -= 50;
				}
			}
			else {
				float i = itp_Float(0.f, 15.f, itr->lifetime / (4.f * (60.f / wave_GetTempo(game_GetLevel()))), itp_Square);
				sfFloatRect rFill = FloatRect(game_GetScrollX() + 1920.f - j, itr->pos.y - i, j, 2.f * i);
				clr.a = 12;
				va_DrawRectangle(VA_TRI, NULL, rFill, clr);
			}
			clr.a = itp_Float(48, 0, clamp(itr->lifetime - 3.f, 0.f, 1.f), itp_Linear);
			va_DrawRectangle(VA_LINE, NULL, FloatRect(game_GetScrollX() + 1920.f - j, itr->pos.y - 15.f, j, 30.f), clr);
		}
		else if (itr->type == EN_STREAK) {
			va_DrawPolygonReg(VA_LINE, NULL, 4, itr->pos, 30.f, 0.f, colorBase);
		}
		else if (itr->type == EN_BOSS_GAMMA) {
			if (itr->dataGm.phase <= 1) va_DrawPolygonStar(VA_LINE, NULL, 4, itr->pos, 190.f, itr->dataGm.rot, colorBase);
			if (itr->dataGm.phase <= 2) va_DrawPolygonStar(VA_LINE, NULL, 4, itr->pos, 140.f, itr->dataGm.rot, colorBase);
			if (itr->dataGm.phase <= 3) va_DrawPolygonStar(VA_LINE, NULL, 4, itr->pos, 90.f, itr->dataGm.rot, colorBase);
			va_DrawPolygonStar(VA_LINE, NULL, 4, itr->pos, 240.f, itr->dataGm.rot, sfWhite);
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
		case EN_WALL: return 100;
		case EN_SPARK: return 200;
		case EN_DART: return 750;
		case EN_STREAK: return 500;
		case EN_BOSS_GAMMA: return 10000;
		default: return 100;
	}
}