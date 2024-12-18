#include "enemy_bullet.h"

void enb_Init() {
	enb_Sentinel = malloc(sizeof(EnemyBullet));
	if (!enb_Sentinel) return;
	memset(enb_Sentinel, 0, sizeof(EnemyBullet));
}

void enb_New(EnbType _type, sfVector2f _pos, sfVector2f _spd, sfColor _clr) {
	EnemyBullet* new = malloc(sizeof(EnemyBullet));
	if (!new) return;

	new->type = _type;
	new->pos = _pos;
	new->spd = _spd;
	new->oldPos[0] = _pos;
	new->oldPos[1] = _pos;
	new->oldPos[2] = _pos;
	new->lifetime = 15.f;
	new->angle = RANDF(0.f, 360.f);
	new->clr = _clr;
	new->aabb = FloatRect_FromCenter(new->pos, 10.f, 10.f);
	
	enb_Add(new);
}

void enb_Add(EnemyBullet* _enb) {
	EnemyBullet* n = enb_Sentinel->next;
	enb_Sentinel->next = _enb;
	_enb->prev = enb_Sentinel;
	_enb->next = n;
	if (n != NULL) n->prev = _enb;
}

void enb_Update() {
	EnemyBullet* itr = enb_Sentinel->next;
	while (itr != NULL) {
		itr->pos = v_Add(itr->pos, v_Mul(itr->spd, getDeltaTime()));
		itr->aabb = FloatRect_FromCenter(itr->pos, 10.f, 10.f);
		itr->angle -= 720.f * getDeltaTime();
		itr->lifetime -= getDeltaTime();

		if (RANDF(0.f, 1.f) < .1f) ptc_CreateParticle(PTC_SHARD, itr->pos, NULLVECTF, 2.f, PTC_GRAV_NONE, NULL, RANDF(0.f, 3.f), 3, itp_Color(clrDGray, itr->clr, RANDF(0.f, 1.f), itp_Linear));

		if (itr->lifetime <= 0.f || !game_IsOnScreen(itr->pos)) itr = enb_PopPtr(itr);
		else itr = itr->next;
	}
}

void enb_Render() {
	EnemyBullet* itr = enb_Sentinel->next;
	while (itr != NULL) {
		va_DrawPolygonStar(VA_LINE, NULL, 4, itr->pos, 15.f, itr->angle, (fmod(itr->lifetime, .1f) < .05f) ? sfWhite : itr->clr);
		if (RENDER_HITBOXES) va_DrawFrame(NULL, itr->aabb, sfCyan);
		itr = itr->next;
	}
}

EnemyBullet* enb_PopPtr(EnemyBullet* _enb) {
	EnemyBullet* p = _enb->prev;
	EnemyBullet* n = _enb->next;

	p->next = n;
	if (n != NULL) n->prev = p;
	free(_enb);
	return n;
}

void enb_ClearBuffer() {
	EnemyBullet* itr = enb_Sentinel->next;
	while (itr != NULL) itr = enb_PopPtr(itr);
	log_LogStr(LOG_INFO, "Enemy projectile buffer cleared", sfTrue, sfTrue);
}

void enb_Unload() {
	enb_ClearBuffer();
	free(enb_Sentinel);
}