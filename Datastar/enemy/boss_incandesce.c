#include "boss_incandesce.h"

void spawnGlimmer(int _x, int _y, float _delay);
void spawnGlimmerColumn(int _x, float _delay);
void spawnGlimmerRow(int _y, float _delay);

void en_Incandesce(sfVector2f _pos) {
	EnData* new = malloc(sizeof(EnData));
	if (!new) {
		log_LogStr(LOG_ERROR, "Enemy creation error: insufficient memory", sfTrue, sfTrue);
		return;
	}

	new->type = EN_BOSS_INCANDESCE;
	new->clr = Color(255, 96, 128);
	new->pos = Vector2f(_pos.x, _pos.y - 75.f * Bars(4));
	new->spd = Vector2f(0.f, 75.f);
	new->lifetime = -Bars(4);
	new->timer_blink = 0.f;
	new->hp_max = 3;
	new->hp = new->hp_max;
	new->drop = PWR_NONE;

	new->dataIc.rot = 0.f;
	new->dataIc.rot_spd = 90.f;
	new->dataIc.clr_osc = .5f;
	new->dataIc.clr_osc_spd = 0.f;
	new->dataIc.pos_target = _pos;
	new->dataIc.entrance = sfTrue;
	new->dataIc.beat_ctr = -1;
	new->dataIc.timer_cycle = 0.f;
	new->dataIc.timer_fire = 0.f;
	new->dataIc.fire_dir = 0.f;

	new->Update = en_incandesce_Update;
	new->OnHit  = en_incandesce_OnHit;
	new->OnKill = en_incandesce_OnKill;
	new->Render = en_incandesce_Render;
	new->Value  = en_incandesce_Value;

	en_Add(new);
}

struct EnData* en_incandesce_Update(struct EnData* _en) {
	_en->dataIc.rot += _en->dataIc.rot_spd * getDeltaTime();
	_en->dataIc.clr_osc = sinf(_en->lifetime * PI * _en->dataIc.clr_osc_spd) * .5f + .5f;
	_en->clr = itp_Color(Color(192, 128, 255), Color(128, 255, 224), _en->dataIc.clr_osc, itp_Linear);

	if (_en->lifetime < Bars(4)) _en->dataIc.clr_osc_spd = itp_Float(0.f, 5.f, max(0.f, _en->lifetime / Bars(4)), itp_Quartic);
	else if (_en->dataIc.timer_cycle > Bars(7)) _en->dataIc.clr_osc_spd = itp_Float(0.f, 5.f, max(0.f, (_en->dataIc.timer_cycle - Bars(7)) / Bars(4)), itp_Quartic);
	else _en->dataIc.clr_osc_spd = 1.f / (float)PI;

	_en->pos = v_Add(_en->pos, v_Mul(_en->spd, getDeltaTime()));

	if (_en->lifetime > 0.f && _en->dataIc.entrance) {
		_en->dataIc.entrance = sfFalse;
		_en->pos = _en->dataIc.pos_target;
		_en->spd = NULLVECTF;
		_en->dataIc.rot_spd = 0.f;

		if (v_Mag2(v_Sub(plr_Player.pos, _en->pos)) < 90000.f) plr_Hit();
		for (int i = 0; i < 16; i++) enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 250.f), 22.5f * i       ), _en->clr);
		for (int i = 0; i < 16; i++) enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 200.f), 22.5f * i + 7.5f), _en->clr);
		for (int i = 0; i < 16; i++) enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 150.f), 22.5f * i + 15.f), _en->clr);
		sfx_EnemyFlareWaves(_en->pos, _en->clr);
	}

	if (_en->lifetime > Bars(3) && _en->lifetime < Bars(4)) {
		_en->pos.y = itp_Float(350.f, -350.f, clamp((_en->lifetime - Bars(3)) / Bars(1), 0.f, 1.f), itp_Square);
		_en->dataIc.rot_spd = itp_Float(0.f, 360.f, clamp((_en->lifetime - Bars(3)) / Bars(1), 0.f, 1.f), itp_Square);
	}

	else if (_en->dataIc.timer_cycle > Bars(7) + Beats(2)) {
		_en->pos.y = itp_Float(540.f, -350.f, clamp((_en->dataIc.timer_cycle - (Bars(7) + Beats(2))) / Beats(2), 0.f, 1.f), itp_Square);
		_en->dataIc.rot_spd = itp_Float(0.f, 360.f, clamp((_en->dataIc.timer_cycle - (Bars(7) + Beats(2))) / Beats(2), 0.f, 1.f), itp_Square);
	}

	/// Computing AI cycles
	if (_en->lifetime > Bars(4) - .1f) {
		_en->dataIc.timer_cycle += getDeltaTime();
		if (game_GetBeatFlag()) {
			_en->dataIc.beat_ctr = (_en->dataIc.beat_ctr + 1) % 32;

			char beat = _en->dataIc.beat_ctr;
			float hb = Beats(1) * .5f; // Half a beat

			if (beat == 0) {
				_en->dataIc.timer_cycle = 0.f;
//				mus_SetPos("glow", Bars(36));
				spawnGlimmerColumn(0, 0.f);
				spawnGlimmerColumn(15, 0.f);

				spawnGlimmerColumn(1, hb);
				spawnGlimmerColumn(14, hb);
			}

			if (beat == 1) {
				spawnGlimmerColumn(2, 0.f);
				spawnGlimmerColumn(13, 0.f);

				spawnGlimmerColumn(3, hb);
				spawnGlimmerColumn(12, hb);
			}

			if (beat == 2) {
				spawnGlimmerColumn(7, 0.f);
				spawnGlimmerColumn(8, 0.f);

				spawnGlimmerColumn(6, hb);
				spawnGlimmerColumn(9, hb);
			}

			if (beat == 3) spawnGlimmerRow(4, 0.f);
			if (beat == 4) spawnGlimmerRow(7, 0.f);

			if (beat == 6) {
				spawnGlimmerColumn(5, 0.f);
				spawnGlimmerColumn(10, hb);
			}

			if (beat >= 7 && beat <= 10) {
				spawnGlimmerRow(17 - beat, 0.f);
			}

			if (beat == 8) lv3_SetGlimmerSpawn(1);

			if (beat >= 12 && beat <= 15) {
				for (int i = 0; i < 24; i++) enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 250.f), 15.f * i + _en->dataIc.rot), _en->clr);

				spawnGlimmerColumn(beat - 12, 0.f);
				spawnGlimmerColumn(27 - beat, 0.f);
			}

			if (beat == 12) en_Flare(Vector2f(game_GetScrollX() + 960.f, 540.f), Bars(1));

			if (beat == 16) lv3_SetGlimmerSpawn(2);

			if (beat >= 15 && beat <= 22) {
				spawnGlimmerColumn((beat - 15) * 2    , 0.f);
				spawnGlimmerColumn((beat - 15) * 2 + 1, 0.f);
			}

			if (beat == 24) {
				_en->dataIc.pos_target = Vector2f(game_GetScrollX() + 960.f, 540.f);
				_en->pos = v_Sub(_en->dataIc.pos_target, Vector2f(0.f, 300.f * Bars(1)));
				_en->spd = Vector2f(0.f, 300.f);
				_en->dataIc.rot_spd = 360.f;
				lv3_SetGlimmerSpawn(0);
			}

			if (beat == 28) {
				_en->pos = _en->dataIc.pos_target;
				_en->spd = NULLVECTF;
				_en->dataIc.rot_spd = 0.f;

				if (v_Mag2(v_Sub(plr_Player.pos, _en->pos)) < 90000.f) plr_Hit();
				for (int i = 0; i < 16; i++) enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 250.f), 22.5f * i), _en->clr);
				for (int i = 0; i < 16; i++) enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 200.f), 22.5f * i + 7.5f), _en->clr);
				for (int i = 0; i < 16; i++) enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 150.f), 22.5f * i + 15.f), _en->clr);
				sfx_EnemyIncandesceShatter(_en->pos, Color(192, 128, 255), Color(128, 255, 224));
				_en->hp--;
				_en->timer_blink = 2.f;
				_en->dataIc.clr_osc = .5f;
				_en->dataIc.clr_osc_spd = 0.f;
			}
		}

		float t = _en->dataIc.timer_cycle;

		if (t > Beats(6) && t < Beats(7)) {
			_en->pos.y = itp_Float(-350.f, 100.f, clamp((t - Beats(6)) / Beats(1), 0.f, 1.f), itp_Smoother);
			_en->dataIc.timer_fire = 0.f;
		}

		if (t > Beats(7) && t < Beats(8)) {
			_en->dataIc.timer_fire += getDeltaTime();
			if (_en->dataIc.timer_fire > .1f) {
				_en->dataIc.timer_fire = 0.f;
				enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 1000.f), -45.f), _en->clr);
				enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 1000.f),   0.f), _en->clr);
				enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 1000.f),  45.f), _en->clr);
			}
		}

		for (int i = 0; i < 2; i++) {
			if (t > Beats(8 + i * 2) && t < Beats(9 + i * 2)) {
				_en->dataIc.timer_fire = 0.f;
				_en->dataIc.fire_dir = v_AngAbsD(v_Sub(_en->pos, plr_Player.pos)) + 90.f;
			}

			if (t > Beats(9 + i * 2) && t < Beats(10 + i * 2)) {
				_en->dataIc.timer_fire += getDeltaTime();
				if (_en->dataIc.timer_fire > .1f) {
					_en->dataIc.timer_fire = 0.f;
					enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(0.f, 1000.f), _en->dataIc.fire_dir), _en->clr);
				}
			}
		}

		if (t > Beats(19) && t < Beats(20)) {
			_en->pos.y = itp_Float(100.f, -350.f, clamp((t - Beats(19)) / Beats(1), 0.f, 1.f), itp_Smoother);
		}
	}
	
	_en->aabb = FloatRect_FromCenter(_en->pos, 200.f, 200.f);
	return _en;
}
void en_incandesce_OnHit(struct EnData* _en, struct PlayerBullet* _plb) { }

void en_incandesce_OnKill(struct EnData* _en) {
	sfx_EnemyBossDeath(_en->pos, _en->clr);
	lv3_End();
}

void en_incandesce_Render(struct EnData* _en) {
	sfColor colorBase = _en->clr;
	sfColor colorBlink = (fmod(_en->timer_blink, .1f) > .05f) ? sfWhite : _en->clr;
	sfColor colorFlicker = (fmod(_en->lifetime, .2f) > .1f) ? sfWhite : _en->clr;

	float t = _en->dataIc.timer_cycle;

	for (int i = 0; i < 5; i++) {
		va_DrawPolygonReg(VA_LINE, NULL, 5, _en->pos, 125.f - 8.f * i, _en->dataIc.rot, _en->clr);
		_en->clr.a -= 55;
	}

	if (_en->hp != 1) {
		for (int i = 0; i < 5; i++) {
			if ((i == 0 || i == 2) && _en->hp == 2) continue;
			float rot = 72.f * i + _en->dataIc.rot + 36.f;
			sfVector2f v[3] = { 0 };
			v[0] = v_Add(_en->pos, v_RotateD(Vector2f(0.f, -109.f), rot - 7.f));
			v[1] = v_Add(_en->pos, v_RotateD(Vector2f(0.f, -109.f), rot + 7.f));
			v[2] = v_Add(_en->pos, v_RotateD(Vector2f(0.f, -235.f + (70.f * (_en->hp == 2))), rot));
			va_DrawPolygon(VA_LINE, NULL, 3, v, sfTrue, sfWhite);
		}
	}

	if (_en->lifetime < 0.f) {
		colorBase.a = 96;
		colorBlink.a = 24;
		va_DrawCircle(VA_LINE, NULL, _en->dataIc.pos_target, 300.f, colorBase);
		va_DrawCircle(VA_TRI, NULL, _en->dataIc.pos_target, itp_Float(300.f, 0.f, clamp((-_en->lifetime) / Bars(4), 0.f, 1.f), itp_InvSquare), colorBlink);
	}

	if (t > Bars(6) && t < Bars(7)) {
		colorBase.a = 96;
		colorBlink.a = 24;
		va_DrawCircle(VA_LINE, NULL, _en->dataIc.pos_target, 300.f, colorBase);
		va_DrawCircle(VA_TRI, NULL, _en->dataIc.pos_target, itp_Float(0.f, 300.f, clamp((_en->dataIc.timer_cycle - Bars(6)) / Bars(1), 0.f, 1.f), itp_InvSquare), colorBlink);
	}

	if (t > Beats(6) && t < Beats(7)) {
		va_DrawLine(NULL, _en->pos, v_Add(_en->pos, Vector2f(-1500.f, 1500.f)), colorFlicker);
		va_DrawLine(NULL, _en->pos, v_Add(_en->pos, Vector2f(    0.f, 1500.f)), colorFlicker);
		va_DrawLine(NULL, _en->pos, v_Add(_en->pos, Vector2f( 1500.f, 1500.f)), colorFlicker);
	}

	if (t > Beats(8) && t < Beats(9) || t > Beats(10) && t < Beats(11)) {
		va_DrawLine(NULL, _en->pos, v_Add(_en->pos, v_RotateD(Vector2f(0.f, 1500.f), _en->dataIc.fire_dir)), colorFlicker);
	}

	sfFloatRect rect = FloatRect_FromCenter(Vector2f(960.f + game_GetScrollX(), 1020.f), 1000.f, 15.f);
	rect.width = itp_Float(0.f, 1000.f, clamp(_en->lifetime, 0.f, Beats(2)) / Beats(2), itp_Smoother);
	float w = rect.width;
	colorBlink.a = 128;
	rect.width = itp_Float(0.f, w, _en->hp / (float)_en->hp_max, itp_Linear);
	va_DrawRectangle(VA_TRI, NULL, rect, colorBlink);
	rect.width = w;
	va_DrawRectangle(VA_LINE, NULL, rect, sfWhite);

	va_DrawLine(NULL, Vector2f(793.f + game_GetScrollX(), 1015.f), Vector2f(793.f + game_GetScrollX(), 1025.f), sfWhite);
	va_DrawLine(NULL, Vector2f(1127.f + game_GetScrollX(), 1015.f), Vector2f(1127.f + game_GetScrollX(), 1025.f), sfWhite);
	vt_DrawText(Vector2f(960.f + game_GetScrollX(), 965.f), "INCANDESCE", 25, TXT_CENTER, ColorA(255, 255, 255, (int)itp_Float(0, 255, clamp(_en->lifetime, 0.f, Beats(1)) / Beats(1), itp_Smoother)));
}

int en_incandesce_Value() { return 10000; }

void spawnGlimmer(int _x, int _y, float _delay) {
	float x = _x * 120.f + 60.f + game_GetScrollX();
	float y = _y * 100.f - 10.f;

	en_Glimmer(Vector2f(x, y), Beats(1), _delay);
}

void spawnGlimmerColumn(int _x, float _delay) {
	for (int i = 1; i <= 10; i++) spawnGlimmer(_x, i, _delay);
}

void spawnGlimmerRow(int _y, float _delay) {
	for (int i = 0; i <= 15; i++) spawnGlimmer(i, _y, _delay);
}