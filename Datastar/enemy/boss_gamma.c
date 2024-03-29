#include "boss_gamma.h"

void en_Gamma(sfVector2f _pos) {
	EnData* new = malloc(sizeof(EnData));
	if (!new) {
		log_LogStr(LOG_ERROR, "Enemy creation error: insufficient memory", sfTrue, sfTrue);
		return;
	}

	new->type = EN_BOSS_GAMMA;
	new->clr = Color(255, 128, 64);
	new->pos = _pos;
	new->spd = NULLVECTF;
	new->lifetime = 0.f;
	new->timer_blink = 0.f;
	new->hp_max = 200;
	new->hp = new->hp_max;

	new->dataGm.rot = 0.f;
	new->dataGm.posOrigin = _pos;
	new->dataGm.phase = 1;
	new->dataGm.timer_shots = 0.f;

	en_Add(new);
}

struct EnData* en_gamma_Update(struct EnData* _en) {
	_en->pos.x = itp_Float(_en->dataGm.posOrigin.x, 1820.f, clamp(_en->lifetime, 0.f, 5.f) * .2f, itp_Smoother) + game_GetScrollX();
	_en->dataGm.rot += 75.f * getDeltaTime();
	_en->aabb = FloatRect_FromCenter(_en->pos, 440.f, 440.f);
	if (_en->dataGm.timer_shots > 0.f) _en->dataGm.timer_shots -= getDeltaTime();

	if (game_GetBeatFlag() && _en->lifetime >= Beats(1) + .1f) {
		switch (_en->dataGm.phase) {
		case 1:
			enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(-400.f, 0.f), -sinf(_en->lifetime) * 30.f), _en->clr);
			enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(-400.f, 0.f), sinf(_en->lifetime) * 30.f), _en->clr);
			break;
		case 2:
			enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(-500.f, 0.f), -sinf(_en->lifetime + 2.f) * 40.f), _en->clr);
			enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(-500.f, 0.f), sinf(_en->lifetime + 2.f) * 40.f), _en->clr);
			break;
		case 3:
			enb_New(ENB_NORMAL, _en->pos, Vector2f(-400.f, 0.f), _en->clr);
			enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(-400.f, 0.f), -sinf(_en->lifetime) * 20.f), _en->clr);
			enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(-400.f, 0.f), sinf(_en->lifetime) * 20.f), _en->clr);
			break;
		case 4:
			enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(-400.f, 0.f), -40.f), _en->clr);
			enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(-400.f, 0.f), -20.f), _en->clr);
			enb_New(ENB_NORMAL, _en->pos, Vector2f(-400.f, 0.f), _en->clr);
			enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(-400.f, 0.f), 20.f), _en->clr);
			enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(-400.f, 0.f), 40.f), _en->clr);
			break;
		}
		sfx_EnemyFire(_en->pos, Vector2f(-400.f, 0.f), _en->clr);
	}

	if (_en->dataGm.timer_shots <= 0.f) {
		switch (_en->dataGm.phase) {
		case 1: break;
		case 2:
			enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(-350.f, 0.f), -sinf(_en->lifetime) * 20.f), _en->clr);
			enb_New(ENB_NORMAL, _en->pos, Vector2f(-400.f, 0.f), _en->clr);
			enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(-350.f, 0.f), sinf(_en->lifetime) * 20.f), _en->clr);
			_en->dataGm.timer_shots = .667f;
			break;
		case 3:
			enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(-400.f, 0.f), v_AngAbsD(v_Sub(_en->pos, plr_Player.pos))), _en->clr);
			_en->dataGm.timer_shots = .5f;
			break;
		case 4:
			enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(-200.f, 0.f), v_AngAbsD(v_Sub(_en->pos, plr_Player.pos)) - 30.f), _en->clr);
			enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(-200.f, 0.f), v_AngAbsD(v_Sub(_en->pos, plr_Player.pos)) + 30.f), _en->clr);
			_en->dataGm.timer_shots = .333f;
			break;

		}
	}

	return _en;
}

void en_gamma_OnHit(struct EnData* _en, struct PlayerBullet* _plb) {
	_en->hp--;
	if (_en->hp > _en->hp_max / 4 * 3) _en->dataGm.phase = 1;
	else if (_en->hp > _en->hp_max / 2) _en->dataGm.phase = 2;
	else if (_en->hp > _en->hp_max / 4) _en->dataGm.phase = 3;
	else _en->dataGm.phase = 4;
}

void en_gamma_OnKill(struct EnData* _en) {
	game_SetScrollSpeed(5000.f, Bars(2));
}

void en_gamma_Render(struct EnData* _en) {
	sfColor colorBase = (fmod(_en->timer_blink, .1f) > .05f) ? sfWhite : _en->clr;

	if (_en->dataGm.phase <= 1) va_DrawPolygonStar(VA_LINE, NULL, 4, _en->pos, 190.f, _en->dataGm.rot, colorBase);
	if (_en->dataGm.phase <= 2) va_DrawPolygonStar(VA_LINE, NULL, 4, _en->pos, 140.f, _en->dataGm.rot, colorBase);
	if (_en->dataGm.phase <= 3) va_DrawPolygonStar(VA_LINE, NULL, 4, _en->pos, 90.f, _en->dataGm.rot, colorBase);
	va_DrawPolygonStar(VA_LINE, NULL, 4, _en->pos, 240.f, _en->dataGm.rot, sfWhite);

	sfFloatRect rect = FloatRect_FromCenter(Vector2f(960.f + game_GetScrollX(), 1020.f), 1000.f, 15.f);
	rect.width = itp_Float(0.f, 1000.f, clamp(_en->lifetime, 0.f, Beats(2)) / Beats(2), itp_Smoother);
	float w = rect.width;
	va_DrawRectangle(VA_LINE, NULL, rect, sfWhite);
	colorBase.a = 128;
	rect.width = itp_Float(0.f, w, _en->hp / (float)_en->hp_max, itp_Linear);
	va_DrawRectangle(VA_TRI, NULL, rect, colorBase);
	va_DrawLine(NULL, Vector2f(710.f + game_GetScrollX(), 1015.f), Vector2f(710.f + game_GetScrollX(), 1025.f), sfWhite);
	va_DrawLine(NULL, Vector2f(960.f + game_GetScrollX(), 1015.f), Vector2f(960.f + game_GetScrollX(), 1025.f), sfWhite);
	va_DrawLine(NULL, Vector2f(1210.f + game_GetScrollX(), 1015.f), Vector2f(1210.f + game_GetScrollX(), 1025.f), sfWhite);
	vt_DrawText(Vector2f(960.f + game_GetScrollX(), 965.f), "GAMMA", 25, TXT_CENTER, ColorA(255, 255, 255, itp_Float(0, 255, clamp(_en->lifetime, 0.f, Beats(1)) / Beats(1), itp_Smoother)));
}

int en_gamma_Value() { return 10000; }