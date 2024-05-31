#include "tools.h"


/// === TIME UTILITIES === ///

sfTime t;
sfClock* clockGame;

void initTools() {
	srand((unsigned int)time(NULL));
	seedRNGs((UL)time(NULL));
	clockGame = sfClock_create();
	clrDGray = Color3(96);
}

void restartClock() {
	t = sfClock_restart(clockGame);
	for (int i = 9; i > 0; i--) dtLatestList[i] = dtLatestList[i - 1];
	dtLatestList[0] = getDeltaTime();
}

float getDeltaTime() {
	return sfTime_asSeconds(t);
}

float getDtAverage() {
	float t = 0.f;
	for (int i = 0; i < 10; i++) t += dtLatestList[i];
	return t * .1f;
}

/// === CONSTRUCTORS === ///

sfVector2f Vector2f(float _x, float _y) { return (sfVector2f) { _x, _y }; }
sfVector2i Vector2i(int _x, int _y) { return (sfVector2i) { _x, _y }; }
sfVector2u Vector2u(unsigned int _x, unsigned int _y) { return (sfVector2u) { _x, _y }; }

sfIntRect IntRect(int _left, int _top, int _width, int _height) { return (sfIntRect) { _left, _top, _width, _height }; }
sfFloatRect FloatRect(float _left, float _top, float _width, float _height) { return (sfFloatRect) { _left, _top, _width, _height }; }

sfColor Color(int _r, int _g, int _b) { return (sfColor) { _r, _g, _b, 255 }; }
sfColor Color3(int _c) { return (sfColor) { _c, _c, _c, 255 }; }
sfColor ColorA(int _r, int _g, int _b, int _a) { return (sfColor) { _r, _g, _b, _a }; }

sfVertex Vertex(sfVector2f _pos, sfColor _clr) { return (sfVertex) { _pos, _clr, NULLVECTF }; }
sfTime Time(float _s) { return (sfTime) { _s * 1e6f }; }
sfTimeSpan TimeSpan(float _start, float _duration) { return (sfTimeSpan) { Time(_start), Time(_duration) }; }


/// === QUICK MATH === ///

float pow2(float _a) { return _a * _a; }
float pow3(float _a) { return _a * _a * _a; }
float pow4(float _a) { return _a * _a * _a * _a; }

float powi(float _a, int _exp) {
	if (_exp == 1) return _a;
	else return _a * powi(_a, _exp - 1);
}

float clamp(float _x, float _lower, float _upper) {
	if (_x <= _lower) return _lower;
	if (_x >= _upper) return _upper;
	return _x;
}


/// === RANDOMIZERS === ///

UL seed_rng = 0;

void seedRNGs(UL _seed) { seed_rng = _seed; }

UL rng32() {
	UL res = 0;
	res |= (rand() << 1 | (rand() & 1));
	res <<= 16;
	res |= (rand() << 1 | (rand() & 1));
	return res;
}

ULL rng64() {
	ULL res = 0;
	res |= rng32();
	res <<= 32;
	res |= rng32();
	return res;
}

double rand_unit(int _d) {
	double x = rng32();
	x /= (double)UL_LIMIT;
	x *= (int)pow(10.f, _d);
	x /= pow(10.f, _d);
	return x;
}


/// === MISC === ///

void claHandler(int argc, char** argv) {
	ARGS_DEBUG_KEYS = sfFalse;
	ARGS_RENDER_HITBOXES = sfFalse;
	ARGS_DOUBLE_RENDER = sfFalse;
	ARGS_PIZZA_MODE = sfFalse;
	ARGS_ENABLE_LOGGING = sfFalse;

	for (int i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-debug")) ARGS_DEBUG_KEYS = sfTrue;
		if (strcmp(argv[i], "-hitboxes")) ARGS_RENDER_HITBOXES = sfTrue;
		if (strcmp(argv[i], "-double-render")) ARGS_DOUBLE_RENDER = sfTrue;
		if (strcmp(argv[i], "-pizza")) ARGS_PIZZA_MODE = sfTrue;
		if (strcmp(argv[i], "-log")) ARGS_ENABLE_LOGGING = sfTrue;
	}
}

sfFloatRect floatRect_Contract(sfFloatRect _r, float _val) { return FloatRect(_r.left + _val, _r.top + _val, _r.width - 2.f * _val, _r.height - 2.f * _val); }
sfFloatRect floatRect_Expand(sfFloatRect _r, float _val) { return FloatRect(_r.left - _val, _r.top - _val, _r.width + 2.f * _val, _r.height + 2.f * _val); }
sfFloatRect FloatRect_FromCenter(sfVector2f _c, float _w, float _h) { return FloatRect(_c.x - _w * .5f, _c.y - _h * .5f, _w, _h); }
