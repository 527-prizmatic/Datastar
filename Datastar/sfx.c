#include "sfx.h"

char* sfx_TexScoreRender;

void sfx_ScoreInit() {
	sfx_ScoreSentinel = malloc(sizeof(SfxScore));
	if (!sfx_ScoreSentinel) return;

	sfx_ScoreSentinel->prev = NULL;
	sfx_ScoreSentinel->next = NULL;
	sfx_ScoreSentinel->pos = NULLVECTF;
	sfx_ScoreSentinel->val = 0;
	sfx_ScoreSentinel->lifetime = 0.f;

	sfx_TexScoreRender = calloc(10, sizeof(char));
}

void sfx_ScoreNew(sfVector2f _pos, int _val) {
	SfxScore* new = malloc(sizeof(SfxScore));
	if (!new) return;

	new->pos = _pos;
	new->val = _val;
	new->lifetime = .5f;

	SfxScore* n = sfx_ScoreSentinel->next;
	sfx_ScoreSentinel->next = new;
	new->prev = sfx_ScoreSentinel;
	new->next = n;
	if (n != NULL) n->prev = new;
}

void sfx_ScoreUpdate() {
	SfxScore* itr = sfx_ScoreSentinel->next;
	while (itr != NULL) {
		itr->lifetime -= getDeltaTime();
		if (itr->lifetime <= 0.f) itr = sfx_ScorePopPtr(itr);
		else {
			itr->pos.y -= 250.f * getDeltaTime();
			itr = itr->next;
		}
	}
}

void sfx_ScoreRender() {
	SfxScore* itr = sfx_ScoreSentinel->next;
	while (itr != NULL) {
		sprintf(sfx_TexScoreRender, "%d", itr->val);
		sfColor clr = ColorA(255, 255, 255, itp_Float(0.f, 255.f, clamp(itr->lifetime * 4.f, 0.f, 1.f), itp_Linear));
		vt_DrawText(itr->pos, sfx_TexScoreRender, 20, TXT_CENTER, clr);
		itr = itr->next;
	}
}

SfxScore* sfx_ScorePopPtr(SfxScore* _sfx) {
	SfxScore* p = _sfx->prev;
	SfxScore* n = _sfx->next;

	p->next = n;
	if (n != NULL) n->prev = p;
	free(_sfx);
	return n;
}

void sfx_ScoreClearBuffer() {
	SfxScore* itr = sfx_ScoreSentinel->next;
	while (itr != NULL) itr = sfx_ScorePopPtr(itr);
	free(sfx_ScoreSentinel);
	free(sfx_TexScoreRender);
}


void sfx_PlayerPropeller() {
	PtcSystem* propellerPtc = ptc_CreateSystem(-1.f, .25f, 1, 1.f, 5.f, -100.f, -80.f, PTC_GRAV_NONE, NULL);
	ptc_SetType(propellerPtc, PTC_SHARD, 1.f, 5.f, 3, 3, Color3(128), sfWhite);
	ptc_SetShape(propellerPtc, PTCS_POINT, v_Add(plr_Player.pos, Vector2f(-15.f, 0.f)));
}

void sfx_PlayerFire() {
	PtcSystem* firePtc = ptc_CreateSystem(-1.f, .333f, 5, 10.f, 20.f, plr_Player.rot - 20.f, plr_Player.rot + 20.f, PTC_GRAV_NONE, NULL);
	ptc_SetType(firePtc, PTC_SHARD, 2.f, 5.f, 3, 3, sfWhite, sfWhite);
	ptc_SetShape(firePtc, PTCS_POINT, v_Add(plr_Player.pos, v_RotateD(Vector2f(20.f, 0.f), plr_Player.rot - 90.f)));
}

void sfx_PlayerHit() {
	PtcSystem* firePtc = ptc_CreateSystem(-1.f, 3.f, 250, 0.f, 15.f, 0.f, 360.f, PTC_GRAV_NONE, NULL);
	ptc_SetType(firePtc, PTC_SHARD, .5f, 4.f, 3, 3, sfWhite, sfRed);
	ptc_SetShape(firePtc, PTCS_POINT, plr_Player.pos);
}

void sfx_ProjectileImpact(sfVector2f _pos, sfVector2f _spd, sfColor _clr) {
	PtcSystem* ptc = ptc_CreateSystem(-1.f, .5f, 10, 5.f, 15.f, 60.f - v_AngAbsD(_spd), 120.f - v_AngAbsD(_spd), PTC_GRAV_NONE, NULL);
	ptc_SetType(ptc, PTC_SHARD, 2.f, 5.f, 3, 3, sfWhite, _clr);
	ptc_SetShape(ptc, PTCS_POINT, _pos);
}

void sfx_EnemyFire(sfVector2f _pos, sfVector2f _dir, sfColor _clr) {
	PtcSystem* firePtc = ptc_CreateSystem(-1.f, .5f, 5, 5.f, 15.f, v_AngAbsD(_dir) + 70.f, v_AngAbsD(_dir) + 110.f, PTC_GRAV_NONE, NULL);
	ptc_SetType(firePtc, PTC_SHARD, 2.f, 5.f, 3, 3, sfWhite, _clr);
	ptc_SetShape(firePtc, PTCS_POINT, _pos);
}

void sfx_EnemyDeath(sfVector2f _pos, sfColor _clr) {
	PtcSystem* ptc = ptc_CreateSystem(-1.f, 1.f, 75, 2.f, 8.f, 0.f, 360.f, PTC_GRAV_NONE, NULL);
	ptc_SetType(ptc, PTC_SHARD, 1.f, 6.f, 3, 3, sfWhite, _clr);
	ptc_SetShape(ptc, PTCS_CIRCLE, _pos, 20.f);
}

void sfx_EnemyBossDeath(sfVector2f _pos, sfColor _clr) {
	PtcSystem* ptc = ptc_CreateSystem(-1.f, 5.f, 500, 2.f, 16.f, 0.f, 360.f, PTC_GRAV_NONE, NULL);
	ptc_SetType(ptc, PTC_SHARD, 1.f, 6.f, 3, 3, sfWhite, _clr);
	ptc_SetShape(ptc, PTCS_CIRCLE, _pos, 20.f);
}

PtcSystem* sfx_PowerupParticle(sfVector2f _pos, enum PwrType _type) {
	sfColor clr;
	switch (_type) {
		case PWR_HP: clr = PIZZA_MODE ? Color(255, 208, 64) : Color(0, 64, 192); break;
		case PWR_POWER: clr = Color(192, 0, 0); break;
		case PWR_SCORE: clr = Color(0, 160, 64); break;
		default: break;
	}

	PtcSystem* ptc = ptc_CreateSystem(100000.f, 2.f, 25, 1.f, 5.f, 0.f, 360.f, PTC_GRAV_NONE, NULL);
	ptc_SetType(ptc, PTC_SHARD, 1.f, 5.f, 3, 3, sfWhite, clr);
	ptc_SetShape(ptc, PTCS_POINT, _pos);
	return ptc;
}