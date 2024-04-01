/// Functions related to various types of boosts, be it score, health or overdrives.
/// Function prefix: pwr_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "va_tools.h"

#include "score.h"
#include "enemy.h"
#include "player.h"

typedef enum PwrType {
	PWR_NONE = 0,
	PWR_HP,
	PWR_POWER,
	PWR_OVERDRIVE,
	PWR_SCORE
} PwrType;

typedef struct PwrData {
	struct PwrData* prev;
	struct PwrData* next;
	PwrType type;
	sfVector2f pos;
	sfVector2f spd;
	float lifetime;
	sfFloatRect aabb;
	struct PtcSystem* ptc;
} PwrData;
PwrData* pwr_Sentinel;

void pwr_Init();
void pwr_New(sfVector2f _pos, PwrType _type);
void pwr_Update();
void pwr_Render();
PwrData* pwr_PopPtr(PwrData* _pwr);
void pwr_ClearBuffer();

void pwr_RenderHp(sfVector2f _pos, float _angle);
void pwr_RenderPower(sfVector2f _pos);
void pwr_RenderScore(sfVector2f _pos);