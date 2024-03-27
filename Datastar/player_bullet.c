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
	new->spd = Vector2f(1200.f, 0.f);
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
		itr->lifetime -= getDeltaTime();


		if (itr->lifetime <= 0.f || !game_IsOnScreen(itr->pos)) itr = plb_PopPtr(itr);
		else itr = itr->next;
	}
}

void plb_Render() {
	PlayerBullet* itr = plb_Sentinel->next;
	while (itr != NULL) {
		va_DrawPolygonReg(VA_LINE, NULL, 3, itr->pos, 7.f, 90.f - v_AngAbsD(itr->spd), sfWhite);
		sfColor clr = sfWhite;
		for (int i = 0; i < 25; i++) {
			clr.a = itp_Float(0.f, 255.f, 1.f - i / 25.f, itp_Cube);
			va_DrawPolygonReg(VA_LINE, NULL, 3, v_Sub(itr->pos, Vector2f(i * 3.f, 0.f)), 7.f, 90.f - v_AngAbsD(itr->spd), clr);
		}
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