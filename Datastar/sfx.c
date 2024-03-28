#include "sfx.h"

void sfx_PlayerPropeller() {
	PtcSystem* propellerPtc = ptc_CreateSystem(-1.f, .25f, 1, 1.f, 5.f, -100.f, -80.f, PTC_GRAV_NONE, NULL);
	ptc_SetType(propellerPtc, PTC_SHARD, 1.f, 5.f, 3, 3, Color3(128), sfWhite);
	ptc_SetShape(propellerPtc, PTCS_POINT, v_Add(plr_Player.pos, Vector2f(-15.f, 0.f)));
}

void sfx_PlayerFire() {
	PtcSystem* firePtc = ptc_CreateSystem(-1.f, .5f, 5, 5.f, 15.f, plr_Player.rot - 20.f, plr_Player.rot + 20.f, PTC_GRAV_NONE, NULL);
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