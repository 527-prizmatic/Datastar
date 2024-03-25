/// Functions related to manipulating the player projectile buffer.
/// Function prefix: plb_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "va_tools.h"
#include "player.h"

typedef enum PlbType {
	PLB_NORMAL
	// Some more will come here later
} PlbType;

typedef struct PlayerBullet {
	struct PlayerBullet* prev;
	struct PlayerBullet* next;
	enum PlbType type;
	sfVector2f pos;
	sfVector2f oldPos[3]; // FOR LATER, FOR COMPUTING AFTERIMAGES
	sfVector2f spd;
	float lifetime;
} PlayerBullet;
PlayerBullet* plb_Sentinel;

void plb_Init();

void plb_New(PlbType _type, sfVector2f _pos);

void plb_Add(PlayerBullet* _plb);

void plb_Update();

void plb_Render();

PlayerBullet* plb_PopPtr(PlayerBullet* _plb);

void plb_ClearBuffer();

void plb_Unload();