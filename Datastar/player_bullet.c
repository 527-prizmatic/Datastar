#include "player_bullet.h"

void plb_Init() {
	plb_Sentinel = malloc(sizeof(PlayerBullet));
	if (!plb_Sentinel) return;
	memset(plb_Sentinel, 0, sizeof(PlayerBullet));
}

void plb_New(PlbType _type, sfVector2f _pos) {
	PlayerBullet* new = malloc(sizeof(PlayerBullet));
	if (!new) return;

	new->type = _type;
	new->pos = _pos;
	new->spd = Vector2f(500.f, 0.f);
	new->oldPos[0] = _pos;
	new->oldPos[1] = _pos;
	new->oldPos[2] = _pos;
	new->lifetime = 3.f;
	
	plb_Add(new);
}

void plb_Add(PlayerBullet* _plb) {
	PlayerBullet* n = plb_Sentinel->next;
	plb_Sentinel->next = _plb;
	_plb->prev = plb_Sentinel;
	_plb->next = n;
	if (n != NULL) n->prev = _plb;
}

void plb_Update() {
	PlayerBullet* itr = plb_Sentinel->next;
	while (itr != NULL) {
		itr->pos = v_Add(itr->pos, v_Mul(itr->spd, getDeltaTime()));

		if (itr->lifetime <= 0.f || !game_IsOnScreen(itr->pos)) itr = plb_PopPtr(itr);
		else itr = itr->next;
	}
}

void plb_Render() {
	PlayerBullet* itr = plb_Sentinel->next;
	while (itr != NULL) {
		va_DrawPolygonReg(VA_LINE, NULL, 3, itr->pos, 5.f, 90.f - v_AngAbsD(itr->spd), sfWhite);
		itr = itr->next;
	}
}

PlayerBullet* plb_PopPtr(PlayerBullet* _plb) {
	PlayerBullet* p = _plb->prev;
	PlayerBullet* n = _plb->next;

	p->next = n;
	if (n != NULL) n->prev = p;
	free(_plb);
	return n;
}

void plb_ClearBuffer() {
	PlayerBullet* itr = plb_Sentinel->next;
	while (itr != NULL) itr = plb_PopPtr(itr);
	log_LogStr(LOG_INFO, "Player projectile buffer cleared", sfTrue, sfTrue);
}

void plb_Unload() {
	plb_ClearBuffer();
	free(plb_Sentinel);
}