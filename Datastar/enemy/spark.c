#include "spark.h"

void en_Spark(sfVector2f _pos) {
	EnData* new = malloc(sizeof(EnData));
	if (!new) {
		log_LogStr(LOG_ERROR, "Enemy creation error: insufficient memory", sfTrue, sfTrue);
		return;
	}

	new->type = EN_SPARK;
	new->clr = itp_Color(Color(128, 0, 255), Color(255, 0, 128), rand_unit(2), itp_Linear);
	new->pos = _pos;
	new->spd = NULLVECTF;
	new->lifetime = 0.f;
	new->timer_blink = 0.f;
	new->hp_max = 2;
	new->hp = new->hp_max;

	new->dataSp.posOrigin = Vector2f(_pos.x - game_GetScrollX(), _pos.y);
	new->dataSp.rot = 0.f;
	new->dataSp.beatCounter = 0;

	en_Add(new);
}

struct EnData* en_spark_Update(struct EnData* _en) {
	if (_en->hp == 2) {
		/// Lifetime under 4 bars: enter field of vision
		if (_en->lifetime < Bars(4)) _en->pos.x = itp_Float(_en->dataSp.posOrigin.x, 1770.f, clamp(_en->lifetime, 0.f, Beats(1)), itp_Smoother) + game_GetScrollX();

		/// Lifetime just above 4 bars: retreat
		else if (_en->lifetime < Bars(4) + Beats(1)) {
			float retreat = Bars(4) + Beats(1) - _en->lifetime;
			_en->pos.x = itp_Float(_en->dataSp.posOrigin.x, 1770.f, clamp(retreat / Beats(1), 0.f, 1.f), itp_Smoother) + game_GetScrollX();
		}

		/// Lifetime above 4 bars and 1 beat (end of retreat): destroy
		else return en_PopPtr(_en);

		if (game_GetBeatFlag()) _en->dataSp.beatCounter++;

		if (_en->dataSp.beatCounter == 2) {
			_en->dataSp.beatCounter = 0;
			enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(-500.f, 0.f), -35.f), _en->clr);
			enb_New(ENB_NORMAL, _en->pos, Vector2f(-500.f, 0.f), _en->clr);
			enb_New(ENB_NORMAL, _en->pos, v_RotateD(Vector2f(-500.f, 0.f), 35.f), _en->clr);
			sfx_EnemyFire(_en->pos, Vector2f(-500.f, 0.f), _en->clr);
		}
		_en->dataSp.rot += 360.f * getDeltaTime();
	}
	else {
		_en->pos.x += 400.f * getDeltaTime();
		_en->dataSp.rot += 180.f * getDeltaTime();
	}

	_en->aabb = FloatRect_FromCenter(_en->pos, 80.f, 80.f);
	return _en;
}

void en_spark_OnHit(struct EnData* _en, struct PlayerBullet* _plb) {
	_en->hp--;
	if (_en->hp == 1) score_Add(en_GetValue(_en->type));
}

void en_spark_OnKill(struct EnData* _en) {

}

void en_spark_Render(struct EnData* _en) {
	sfColor colorBase = (fmod(_en->timer_blink, .1f) > .05f) ? sfWhite : _en->clr;

	va_DrawPolygonStar(VA_LINE, NULL, 4, _en->pos, 40.f, _en->dataSp.rot, sfWhite);
	if (_en->hp == 2) va_DrawPolygonStar(VA_LINE, NULL, 4, _en->pos, 40.f, _en->dataSp.rot * .667f, colorBase);
}

int en_spark_Value() { return 200; }