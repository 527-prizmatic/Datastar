#include "boss_shockwave.h"

void en_Shockwave(sfVector2f _pos) {
	EnData* new = malloc(sizeof(EnData));
	if (!new) {
		log_LogStr(LOG_ERROR, "Enemy creation error: insufficient memory", sfTrue, sfTrue);
		return;
	}

	new->type = EN_BOSS_SHOCKWAVE;
	new->clr = Color(255, 96, 128);
	new->pos = v_Add(_pos, Vector2f(1000.f, 0.f));
	new->spd = NULLVECTF;
	new->lifetime = -Bars(1);
	new->timer_blink = 0.f;
	new->hp_max = 100;
	new->hp = new->hp_max;
	new->drop = PWR_NONE;

	for (int i = 0; i < 6; i++) {
		new->dataSw.hp_arm[i] = 25;
		new->dataSw.hp_max_arm[i] = new->dataSw.hp_arm[i];
		new->dataSw.timers_blink[i] = 0.f;
	}
	new->dataSw.rot = 0.f;
	new->dataSw.phase = 1;
	new->dataSw.beat_ctr = -1;
	new->dataSw.timer_shots_slow = 0.f;
	new->dataSw.pos_target = _pos;
	new->dataSw.lifetime_mod8 = 0.f;

	en_Add(new);
}

struct EnData* en_shockwave_Update(struct EnData* _en) {
	_en->dataSw.rot += 40.f * getDeltaTime();
	_en->pos.x += game_GetScrollSpeed() * getDeltaTime();
	if (_en->dataSw.timer_shots_slow > 0.f) _en->dataSw.timer_shots_slow -= getDeltaTime();
	for (int i = 0; i < 6; i++) if (_en->dataSw.timers_blink[i] > 0.f) _en->dataSw.timers_blink[i] -= getDeltaTime();

	if (_en->dataSw.phase == 1) {
		_en->dataSw.pos_target.x += game_GetScrollSpeed() * getDeltaTime();
		if (_en->lifetime >= 0.f) _en->pos = v_Mul(v_Add(v_Mul(_en->pos, 3.f), _en->dataSw.pos_target), .25f);

		_en->dataSw.lifetime_mod8 += getDeltaTime();
		if (_en->dataSw.lifetime_mod8 >= Bars(8)) {
			_en->dataSw.lifetime_mod8 -= Bars(8);

			char ctr = 0;
			for (int i = 0; i < 6; i++) if (_en->dataSw.hp_arm[i] == 0) ctr++;
			if (ctr == 6) _en->dataSw.phase = 2;
		}

		if (game_GetBeatFlag()) {
			_en->dataSw.beat_ctr++;
			for (int i = 0; i < 6; i++) if (_en->dataSw.hp_arm[i] != 0) enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 750.f), _en->dataSw.rot + 60.f * (i - 1)), _en->clr);
			if (_en->dataSw.beat_ctr % 2 == 0) {
				for (int i = 0; i < 6; i++) if (_en->dataSw.hp_arm[i] == 0) enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 250.f), _en->dataSw.rot + 60.f * (i - 1)), _en->clr);
			}
			if (_en->dataSw.beat_ctr % 8 == 0) {
				for (int i = 0; i < 24; i++) enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 150.f), _en->dataSw.rot + 15.f * (i - 1)), _en->clr);
			}
		}

		_en->aabb = FloatRect_FromCenter(_en->pos, 300.f, 300.f);
	}
	/// Second AI cycle (8 bars):
	/// Flies upwards on bar 1 (do a trail)
	/// Shadow appears on bar 3
	/// Lands on bar 5, explosion of bullets
	/// Inert till end of bar 8
	/// Rinse and repeat

	return _en;
}
void en_shockwave_OnHit(struct EnData* _en, struct PlayerBullet* _plb) {
	if (_en->dataSw.phase == 1) {
		_en->timer_blink = 0.f;
		float angle = fmod(690.f - v_AngAbsD(v_RotateD(v_Sub(_plb->pos, _en->pos), _en->dataSw.rot)), 360.f);

		/*for (int i = 0; i < 6; i++) {
			if (angle < 60.f * i) {
				if (_en->dataSw.hp_arm[i] != 0) {
					_en->dataSw.hp_arm[i]--;
					_en->dataSw.timers_blink[i] = .4f;
				}
				break;
			}
		}*/

		if (angle < 60.f) {
			if (_en->dataSw.hp_arm[0] != 0) {
				_en->dataSw.hp_arm[0]--;
				_en->dataSw.timers_blink[0] = .4f;
			}
		}
		else if (angle < 120.f) {
			if (_en->dataSw.hp_arm[1] != 0) {
				_en->dataSw.hp_arm[1]--;
				_en->dataSw.timers_blink[1] = .4f;
			}
		}
		else if (angle < 180.f) {
			if (_en->dataSw.hp_arm[2] != 0) {
				_en->dataSw.hp_arm[2]--;
				_en->dataSw.timers_blink[2] = .4f;
			}
		}
		else if (angle < 240.f) {
			if (_en->dataSw.hp_arm[3] != 0) {
				_en->dataSw.hp_arm[3]--;
				_en->dataSw.timers_blink[3] = .4f;
			}
		}
		else if (angle < 300.f) {
			if (_en->dataSw.hp_arm[4] != 0) {
				_en->dataSw.hp_arm[4]--;
				_en->dataSw.timers_blink[4] = .4f;
			}
		}
		else if (angle < 360.f) {
			if (_en->dataSw.hp_arm[5] != 0) {
				_en->dataSw.hp_arm[5]--;
				_en->dataSw.timers_blink[5] = .4f;
			}
		}
	}
	else _en->hp--;
}

void en_shockwave_OnKill(struct EnData* _en) {
	lv2_End();
}

void en_shockwave_Render(struct EnData* _en) {
	sfColor colorBase = _en->clr;
	sfColor colorBlink = (fmod(_en->timer_blink, .1f) > .05f) ? sfWhite : _en->clr;

	if (_en->lifetime < 0.f) {
		colorBase.a = 128;
		colorBlink.a = 32;
		va_DrawPolygonStar(VA_LINE, NULL, 6, _en->dataSw.pos_target, 160.f, _en->dataSw.rot * 4.f, colorBase);
		va_DrawPolygonStar(VA_TRI, NULL, 6, _en->dataSw.pos_target, itp_Float(160.f, 0.f, clamp(-_en->lifetime / Beats(2), 0.f, 1.f), itp_InvSquare), _en->dataSw.rot * 4.f, colorBlink);
	}
	else {
		float rds = 60.f;
		for (int i = 0; i < 3; i++) {
			va_DrawPolygonReg(VA_LINE, NULL, 6, _en->pos, rds, _en->dataSw.rot + 30.f, colorBase);
			rds -= 20.f;
		}
		for (int i = 0; i < 6; i++) {
			if (_en->dataSw.hp_arm[i] != 0) {
				sfColor clr = (fmod(_en->dataSw.timers_blink[i], .1f) > .05f) ? sfWhite : clrDGray;
				sfVector2f v[5];
				v[0] = v_Add(_en->pos, v_RotateD(Vector2f(120.f, 0.f), i * 60.f + _en->dataSw.rot + 60.f));
				v[1] = v_Add(_en->pos, v_RotateD(Vector2f(210.f, 0.f), i * 60.f + _en->dataSw.rot + 30.f));
				v[2] = v_Add(_en->pos, v_RotateD(Vector2f(120.f, 0.f), i * 60.f + _en->dataSw.rot       ));
				v[3] = v_Add(_en->pos, v_RotateD(Vector2f(60.f,  0.f), i * 60.f + _en->dataSw.rot       ));
				v[4] = v_Add(_en->pos, v_RotateD(Vector2f(60.f,  0.f), i * 60.f + _en->dataSw.rot + 60.f));
				va_DrawPolygon(VA_LINE, NULL, 5, v, sfTrue, clr);
			}
		}
	}

	sfFloatRect rect = FloatRect_FromCenter(Vector2f(960.f + game_GetScrollX(), 1020.f), 1000.f, 15.f);
	rect.width = itp_Float(0.f, 1000.f, clamp(_en->lifetime, 0.f, Beats(2)) / Beats(2), itp_Smoother);
	float w = rect.width;
	va_DrawRectangle(VA_LINE, NULL, rect, sfWhite);
	colorBase.a = 128;
	rect.width = itp_Float(0.f, w, _en->hp / (float)_en->hp_max, itp_Linear);
	va_DrawRectangle(VA_TRI, NULL, rect, colorBlink);
	va_DrawLine(NULL, Vector2f(710.f + game_GetScrollX(), 1015.f), Vector2f(710.f + game_GetScrollX(), 1025.f), sfWhite);
	va_DrawLine(NULL, Vector2f(960.f + game_GetScrollX(), 1015.f), Vector2f(960.f + game_GetScrollX(), 1025.f), sfWhite);
	va_DrawLine(NULL, Vector2f(1210.f + game_GetScrollX(), 1015.f), Vector2f(1210.f + game_GetScrollX(), 1025.f), sfWhite);
	vt_DrawText(Vector2f(960.f + game_GetScrollX(), 965.f), "SHOCKWAVE", 25, TXT_CENTER, ColorA(255, 255, 255, itp_Float(0, 255, clamp(_en->lifetime, 0.f, Beats(1)) / Beats(1), itp_Smoother)));
}

int en_shockwave_Value() { return 10000; }