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
	new->hp_max = 60;
	new->hp = new->hp_max;
	new->drop = PWR_NONE;

	for (int i = 0; i < 6; i++) {
		new->dataSw.hp_arm[i] = 25;
		new->dataSw.hp_max_arm[i] = new->dataSw.hp_arm[i];
		new->dataSw.timers_blink[i] = 0.f;
	}
	new->dataSw.rot = 0.f;
	new->dataSw.rot_spd = 40.f;
	new->dataSw.phase = 1;
	new->dataSw.beat_ctr = -1;
	new->dataSw.timer_shots_slow = 0.f;
	new->dataSw.pos_target = _pos;
	new->dataSw.lifetime_mod8 = 0.f;
	new->dataSw.flag_targeting = sfFalse;

	en_Add(new);
}

struct EnData* en_shockwave_Update(struct EnData* _en) {
	_en->dataSw.rot += _en->dataSw.rot_spd * getDeltaTime();
	_en->pos.x += game_GetScrollSpeed() * getDeltaTime();
	_en->dataSw.lifetime_mod8 += getDeltaTime();
	if (_en->dataSw.timer_shots_slow > 0.f) _en->dataSw.timer_shots_slow -= getDeltaTime();
	for (int i = 0; i < 6; i++) if (_en->dataSw.timers_blink[i] > 0.f) _en->dataSw.timers_blink[i] -= getDeltaTime();

	if (_en->dataSw.phase == 1) {
		_en->dataSw.pos_target.x += game_GetScrollSpeed() * getDeltaTime();
		if (_en->lifetime >= 0.f) _en->pos = v_Mul(v_Add(v_Mul(_en->pos, 3.f), _en->dataSw.pos_target), .25f);

		if (_en->dataSw.lifetime_mod8 >= Bars(8)) {
			_en->dataSw.lifetime_mod8 -= Bars(8);
			mus_SetPos("captain", Bars(40));

			char ctr = 0;
			for (int i = 0; i < 6; i++) if (_en->dataSw.hp_arm[i] == 0) ctr++;
			if (ctr == 6) {
				_en->dataSw.phase = 2;
				_en->dataSw.lifetime_mod8 -= Bars(2);
				game_SetScrollSpeed(-200.f, Bars(1));
			}
		}

		if (game_GetBeatFlag()) {
			_en->dataSw.beat_ctr++;
			for (int i = 0; i < 6; i++) if (_en->dataSw.hp_arm[i] != 0) enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 750.f), _en->dataSw.rot + 60.f * (i - 1)), _en->clr);
			if (_en->dataSw.beat_ctr % 2 == 0) {
				for (int i = 0; i < 6; i++) {
					if (_en->dataSw.hp_arm[i] == 0) {
						for (int j = 0; j < 3; j++) enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 250.f), _en->dataSw.rot + 60.f * (i - 1) + 7.5f * (j - 1)), _en->clr);
					}
				}
			}
			if (_en->dataSw.beat_ctr % 8 == 0) {
				for (int i = 0; i < 30; i++) enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 100.f), _en->dataSw.rot + 12.f * i), _en->clr);
			}
		}

		_en->aabb = FloatRect_FromCenter(_en->pos, 300.f, 300.f);
	}
	else {
		float lt = _en->dataSw.lifetime_mod8;
		if (lt >= Bars(4)) {
			_en->dataSw.lifetime_mod8 -= Bars(4);
			en_Pulse(Vector2f(game_GetScrollX() +  200.f, 340.f), Beats(3));
			en_Pulse(Vector2f(game_GetScrollX() + 1760.f, 740.f), Beats(4));
			en_Pulse(Vector2f(game_GetScrollX() + 1760.f, 190.f), Beats(5));
			en_Pulse(Vector2f(game_GetScrollX() +  200.f, 790.f), Beats(6));
		}

		if (game_GetBeatFlag()) {
			_en->dataSw.beat_ctr++;
			if (_en->dataSw.beat_ctr % 32 == 0) mus_SetPos("captain", Bars(40));
		}

		if (lt < Bars(1)) {
			_en->aabb = FloatRect(-1.f, -1.f, 0.f, 0.f);
			_en->dataSw.pos_target.y = -200.f;
			_en->dataSw.pos_target.x += game_GetScrollSpeed() * getDeltaTime();
			_en->pos.x += game_GetScrollSpeed() * getDeltaTime();
			_en->pos = v_Mul(v_Add(_en->pos, _en->dataSw.pos_target), .5f);
		}
		else if (lt < Bars(2)) {
			_en->aabb = FloatRect(-1.f, -1.f, 0.f, 0.f);
			_en->dataSw.flag_targeting = sfTrue;

			if (_en->dataSw.pos_target.y <= 0.f) _en->dataSw.pos_target = plr_Player.pos;
			else {
				sfVector2f v = v_Sub(plr_Player.pos, _en->dataSw.pos_target);
				v = v_SetMag(v, 200.f * getDeltaTime());
				_en->dataSw.pos_target = v_Add(_en->dataSw.pos_target, v);
				_en->dataSw.pos_target.x += game_GetScrollSpeed() * getDeltaTime();
				_en->pos.x = _en->dataSw.pos_target.x;
			}
		}
		else {
			_en->aabb = FloatRect_FromCenter(_en->pos, 100.f, 100.f);

			if (_en->dataSw.flag_targeting) {
				_en->pos = v_Mul(v_Add(_en->pos, _en->dataSw.pos_target), .5f);
				if (v_Mag2(v_Sub(_en->pos, _en->dataSw.pos_target)) < 100.f && v_Mag2(v_Sub(_en->pos, _en->dataSw.pos_target)) > 1.f) {
					sfx_EnemyShockwaveWaves(_en->pos, _en->clr);
					_en->pos = _en->dataSw.pos_target;
					if (v_Mag2(v_Sub(plr_Player.pos, _en->pos)) < 100000.f) plr_Hit();
					for (int i = 0; i < 24; i++) {
						enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 300.f), _en->dataSw.rot + 15.f * i), _en->clr);
						enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 250.f), _en->dataSw.rot + 15.f * i + 4.f), _en->clr);
						enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 200.f), _en->dataSw.rot + 15.f * i + 8.f), _en->clr);
					}
					_en->dataSw.flag_targeting = sfFalse;
				}
			}
			_en->pos.x -= game_GetScrollSpeed() * getDeltaTime();
		}
	}
	/// Second AI cycle (4 bars):
	/// Flies upwards on bar 1 (do a trail)
	/// Shadow appears on bar 2
	/// Lands on bar 3, explosion of bullets
	/// Inert till end of bar 4
	/// Rinse and repeat

	return _en;
}
void en_shockwave_OnHit(struct EnData* _en, struct PlayerBullet* _plb) {
	if (_en->dataSw.phase == 1) {
		_en->timer_blink = 0.f;

		int hpArmSum = 0;
		for (int i = 0; i < 6; i++) hpArmSum += _en->dataSw.hp_arm[i];
		if (hpArmSum) {
			while (1) {
				int i = RAND(0, 5);
				if (_en->dataSw.hp_arm[i] != 0) {
					_en->dataSw.hp_arm[i]--;
					_en->dataSw.timers_blink[i] = .4f;
					if (_en->dataSw.hp_arm[i] == 0) _en->dataSw.rot_spd += 20.f;
					break;
				}
			}
		}
	}
	else _en->hp--;
}

void en_shockwave_OnKill(struct EnData* _en) {
	sfx_EnemyBossDeath(_en->pos, _en->clr);
	lv2_End();
}

void en_shockwave_Render(struct EnData* _en) {
	sfColor colorBase = _en->clr;
	sfColor colorBlink = (fmod(_en->timer_blink, .1f) > .05f) ? sfWhite : _en->clr;
	sfColor colorFlicker = (fmod(_en->lifetime, .2f) > .1f) ? sfWhite : _en->clr;

	if (_en->lifetime < 0.f) {
		colorBase.a = 128;
		colorBlink.a = 32;
		va_DrawPolygonStar(VA_LINE, NULL, 6, _en->dataSw.pos_target, 160.f, _en->dataSw.rot * 4.f, colorBase);
		va_DrawPolygonStar(VA_TRI, NULL, 6, _en->dataSw.pos_target, itp_Float(160.f, 0.f, clamp(-_en->lifetime / Beats(2), 0.f, 1.f), itp_InvSquare), _en->dataSw.rot * 4.f, colorBlink);
	}
	else {
		if (_en->dataSw.phase == 1) {
			float rds = 60.f;
			for (int i = 0; i < 3; i++) {
				va_DrawPolygonReg(VA_LINE, NULL, 6, _en->pos, rds, _en->dataSw.rot + 30.f, colorBase);
				rds -= 20.f;
			}
			for (int i = 0; i < 6; i++) {
				if (_en->dataSw.hp_arm[i] != 0) {
					sfColor clr = (fmod(_en->dataSw.timers_blink[i], .1f) > .05f) ? sfWhite : clrDGray;
					sfVector2f v[5] = { 0 };
					v[0] = v_Add(_en->pos, v_RotateD(Vector2f(120.f, 0.f), i * 60.f + _en->dataSw.rot + 60.f));
					v[1] = v_Add(_en->pos, v_RotateD(Vector2f(210.f, 0.f), i * 60.f + _en->dataSw.rot + 30.f));
					v[2] = v_Add(_en->pos, v_RotateD(Vector2f(120.f, 0.f), i * 60.f + _en->dataSw.rot));
					v[3] = v_Add(_en->pos, v_RotateD(Vector2f(60.f, 0.f), i * 60.f + _en->dataSw.rot));
					v[4] = v_Add(_en->pos, v_RotateD(Vector2f(60.f, 0.f), i * 60.f + _en->dataSw.rot + 60.f));
					va_DrawPolygon(VA_LINE, NULL, 5, v, sfTrue, clr);
				}
			}
		}
		else {
			float lt = _en->dataSw.lifetime_mod8;

			if (!(lt > Bars(1) && lt < Bars(2))) {
				float rds = 60.f;
				for (int i = 0; i < 3; i++) {
					va_DrawPolygonReg(VA_LINE, NULL, 6, _en->pos, rds, _en->dataSw.rot + 30.f, colorBase);
					rds -= 20.f;
				}
			}

			if (lt < Bars(2)) {
				va_DrawPolygonStar(VA_LINE, NULL, 6, _en->dataSw.pos_target, 160.f, _en->dataSw.rot, colorBase);
				va_DrawPolygonStar(VA_TRI, NULL, 6, _en->dataSw.pos_target, itp_Float(0.f, 160.f, clamp((lt - Bars(1)) / Bars(1), 0.f, 1.f), itp_Square), _en->dataSw.rot, colorFlicker);
				if (lt > Bars(1)) va_DrawCircle(VA_LINE, NULL, _en->dataSw.pos_target, 300.f, colorFlicker);
			}
		}
	}

	sfFloatRect rectRed = FloatRect_FromCenter(Vector2f(710.f + game_GetScrollX(), 1020.f), 500.f, 15.f);
	rectRed.width = itp_Float(0.f, 500.f, clamp(_en->lifetime, 0.f, Beats(1)) / Beats(1), itp_Smoother);
	float w = rectRed.width;
	colorBlink.a = 128;
	va_DrawRectangle(VA_LINE, NULL, rectRed, sfWhite);
	rectRed.width = itp_Float(0.f, w, _en->hp / (float)_en->hp_max, itp_Linear);
	va_DrawRectangle(VA_TRI, NULL, rectRed, colorBlink);
	rectRed.width = w;
	va_DrawRectangle(VA_LINE, NULL, rectRed, sfWhite);

	float timers = 0;
	for (int i = 0; i < 6; i++) timers += _en->dataSw.timers_blink[i];
	sfColor clrGray = (fmod(timers, .1f) > .05f) ? sfWhite : clrDGray;
	sfFloatRect rectGray = FloatRect_FromCenter(Vector2f(1210.f + game_GetScrollX(), 1020.f), 500.f, 15.f);
	rectGray.width = itp_Float(0.f, 500.f, clamp(_en->lifetime - Beats(1), 0.f, Beats(1)) / Beats(1), itp_Smoother);
	float w2 = rectGray.width;
	colorBlink.a = 128;
	int hp_sum = 0;
	for (int i = 0; i < 6; i++) hp_sum += _en->dataSw.hp_arm[i];
	rectGray.width = itp_Float(0.f, w2, hp_sum / (_en->dataSw.hp_max_arm[0] * 6.f), itp_Linear);
	va_DrawRectangle(VA_TRI, NULL, rectGray, clrGray);
	rectGray.width = w2;
	va_DrawRectangle(VA_LINE, NULL, rectGray, sfWhite);

	va_DrawLine(NULL, Vector2f(960.f + game_GetScrollX(), 1015.f), Vector2f(960.f + game_GetScrollX(), 1025.f), sfWhite);
	vt_DrawText(Vector2f(960.f + game_GetScrollX(), 965.f), "SHOCKWAVE", 25, TXT_CENTER, ColorA(255, 255, 255, itp_Float(0, 255, clamp(_en->lifetime, 0.f, Beats(1)) / Beats(1), itp_Smoother)));
}

int en_shockwave_Value() { return 10000; }