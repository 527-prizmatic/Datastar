#include "tools.h"


/// === TIME UTILITIES === ///

sfTime t;
sfClock* clockGame;

void initTools() {
	srand((unsigned int)time(NULL));
	seedRNGs((UL)time(NULL));
	clockGame = sfClock_create();
}

void restartClock() {
	t = sfClock_restart(clockGame);
}

float getDeltaTime() {
	return sfTime_asSeconds(t);
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

/*
UL rng32() {
	static int ctr1 = 0;
	static int ctr2 = 0;
	ctr1 = (ctr1 += 1) % 120530929;
	ctr2 = (ctr2 += 1) % 664326991;

	UL x = seed_rng;
	x += 1;
	x %= UL_LIMIT;
	x ^= UL_LIMIT;
	x *= 0x10000001;
	x *= (x - 1);
	x += ctr1;
	x %= UL_LIMIT;
	x += ctr2;
	x %= UL_LIMIT;

	seed_rng = (UL)x;
	return x;
}
*/

double rand_unit(int _d) {
	double x = rng32();
	x /= (double)UL_LIMIT;
	x *= (int)pow(10.f, _d);
	x /= pow(10.f, _d);
	return x;
}