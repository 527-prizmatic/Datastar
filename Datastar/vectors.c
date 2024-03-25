#include "vectors.h"

sfVector2f v_Add(sfVector2f _a, sfVector2f _b) { return Vector2f(_a.x + _b.x, _a.y + _b.y); }
sfVector2f v_Sub(sfVector2f _a, sfVector2f _b) { return Vector2f(_a.x - _b.x, _a.y - _b.y); }
sfVector2f v_Mul(sfVector2f _a, float _x) { return Vector2f(_a.x * _x, _a.y * _x); }

double v_Dot(sfVector2f _a, sfVector2f _b) { return _a.x * _b.x + _a.y * _b.y; }
double v_Mag(sfVector2f _a) { return sqrt(pow2(_a.x) + pow2(_a.y)); }
double v_Mag2(sfVector2f _a) { return pow2(_a.x) + pow2(_a.y); }

sfVector2f v_Nmlz(sfVector2f _a) {
	float n = v_Mag(_a);
	if (ISZERO(n)) return NULLVECTF;
	else return v_Mul(_a, 1.f / n);
}

sfVector2f v_SetMag(sfVector2f _a, float _m) {
	double n = v_Mag(_a);
	if (ISZERO(n)) return NULLVECTF;
	else return v_Mul(_a, _m / n);
}

float v_AngRelR(sfVector2f _a, sfVector2f _b) { return atan2f(_b.y, _b.x) - atan2f(_a.y, _a.x); }
float v_AngAbsR(sfVector2f _a) { return atan2f(_a.y, _a.x); }
float v_AngRelD(sfVector2f _a, sfVector2f _b) { return R2D(atan2f(_b.y, _b.x) - atan2f(_a.y, _a.x)); }
float v_AngAbsD(sfVector2f _a) { return R2D(atan2f(_a.y, _a.x)); }

sfVector2f v_RotateR(sfVector2f _a, float _angle) {
	sfVector2f v = REC2POL(_a);
	v.y += _angle;
	return POL2REC(v);
}

sfVector2f v_RotateD(sfVector2f _a, float _angle) {
	sfVector2f v = REC2POL(_a);
	v.y += D2R(_angle);
	return POL2REC(v);
}

sfVector2f v_MirrorX(sfVector2f _v) { return Vector2f(-_v.x, _v.y); }
sfVector2f v_MirrorY(sfVector2f _v) { return Vector2f(_v.x, -_v.y); }
sfVector2f v_Flip(sfVector2f _v) { return Vector2f(-_v.x, -_v.y); }

sfVector2i v_FtoI(sfVector2f _v) { return Vector2i((int)_v.x, (int)_v.y); }
sfVector2f v_ItoF(sfVector2i _v) { return Vector2f(_v.x, _v.y); }