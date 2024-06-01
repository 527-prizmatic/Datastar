#include "interpolation.h"

#define ITP(a, b, t) ((b) - (a)) * t + a

/// === INTERPOLATORS === ///

float itp_Float(float _a, float _b, float _t, float _method(float _x)) {
	float itp = _method(_t);
	return ITP(_a, _b, itp);
}

sfVector2f itp_Vector2f(sfVector2f _a, sfVector2f _b, float _t, float _method(float _x)) {
	float itp = _method(_t);
	float x = ITP(_a.x, _b.x, itp);
	float y = ITP(_a.y, _b.y, itp);
	return Vector2f(x, y);
}

sfColor itp_Color(sfColor _a, sfColor _b, float _t, float _method(float _x)) {
	float itp = _method(_t);
	float r = ITP(_a.r, _b.r, itp);
	float g = ITP(_a.g, _b.g, itp);
	float b = ITP(_a.b, _b.b, itp);
	float a = ITP(_a.a, _b.a, itp);
	return ColorA((int)r, (int)g, (int)b, (int)a);
}

sfVector2f itp_Bilinear(sfVector2f _q11, sfVector2f _q12, sfVector2f _q21, sfVector2f _q22, float _v11, float _v12, float _v21, float _v22, float _x, float _y) {
	/// dæyum
	return NULLVECTF;
}


/// === INTERPOLATION METHODS === ///

float itp_Nearest(float _x) { return (_x >= .5f) ? 1.f : 0.f; }
float itp_Linear(float _x) { return clamp(_x, 0.f, 1.f); }
float itp_Square(float _x) { return clamp(pow2(_x), 0.f, 1.f); }
float itp_InvSquare(float _x) { return clamp(1.f - pow2(1.f - _x), 0.f, 1.f); }
float itp_InvCube(float _x) { return clamp(1.f - pow3(1.f - _x), 0.f, 1.f); }
float itp_InvQuartic(float _x) { return clamp(1.f - pow4(1.f - _x), 0.f, 1.f); }
float itp_Cube(float _x) { return clamp(pow3(_x), 0.f, 1.f); }
float itp_Quartic(float _x) { return clamp(pow4(_x), 0.f, 1.f); }
float itp_Smooth(float _x) { return clamp(pow2(_x) * (3 - 2 * _x), 0.f, 1.f); }
float itp_Smoother(float _x) { return clamp(pow3(_x) * ((6 * _x - 15) * _x + 10), 0.f, 1.f); }
float itp_Smoothest(float _x) { return clamp(pow4(_x) * (35.f + _x * (_x * (70.f - _x * 20.f) - 84.f)), 0.f, 1.f); }
float itp_Smoothester(float _x) { return clamp(powi(_x, 5) * (126.f + _x * (-420.f + _x * (540.f + _x * (-315.f + _x * 70.f)))), 0.f, 1.f); }