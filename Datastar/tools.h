/// (C) 2024 The Prizmanager
/// Author - J.Sebastien Toussaint
/// 
/// Generic library to make coding easier by providing shortcuts for commonly used functions and processes.

#pragma once
#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#include "SFML\Audio.h"
#include "SFML\Graphics.h"

#pragma warning (disable: 4090 4244)

#define E 1e-5 /// Reserved for floating-point error mitigation
#define UL_LIMIT 0xFFFFFFFF
#define ULL_LIMIT 0xFFFFFFFFFFFFFFFF
typedef unsigned long int UL;
typedef unsigned long long int ULL;

#define PATH_ASSETS			"..\\assets\\"
#define PATH_MUSICS			PATH_ASSETS"bgm\\"
#define PATH_LANGS			PATH_ASSETS"langs\\"
#define PATH_SOUNDS			PATH_ASSETS"sounds\\"
#define PATH_TEXTURES		PATH_ASSETS"textures\\"
#define PATH_SHADERS		PATH_ASSETS"shaders\\"
#define PATH_CONFIG			"..\\config\\"
#define PATH_LOGS			"..\\logs\\"
#define PATH_SAVES			""
#define PATH_SAVEFILE		PATH_SAVES"savefile.bin"

#define RENDER_HITBOXES		0
#define DOUBLE_RENDER		0
#define PIZZA_MODE			1

sfColor clrDGray;


/// === TIME UTILITIES === ///

/// Initializes various helper tools.
void initTools();

/// Restarts the internal clock for time-tracking purposes.
void restartClock();

/// \return Time elapsed since last restartClock() call
float getDeltaTime();


/// === CONSTRUCTORS === ///

sfVector2f Vector2f(float _x, float _y);
sfVector2i Vector2i(int _x, int _y);
sfVector2u Vector2u(unsigned int _x, unsigned int _y);

sfIntRect IntRect(int _left, int _top, int _width, int _height);
sfFloatRect FloatRect(float _left, float _top, float _width, float _height);

sfColor Color(int _r, int _g, int _b);
sfColor Color3(int _c);
sfColor ColorA(int _r, int _g, int _b, int _a);

sfVertex Vertex(sfVector2f _pos, sfColor _clr);
sfTime Time(float _s);
sfTimeSpan TimeSpan(float _start, float _duration);


/// === QUICK MATH === ///

#define FEQS(a, b) (fabs((a) - (b)) < E) /// Tests for equality between two floats. Comes packed with floating-point error mitigation.
#define ISZERO(a) ((a) < E && (a) > -E) /// Checks if a float is equal to zero. Comes packed with floating-point error mitigation.

/// Quick square function
float pow2(float _a);

/// Quick cube function
float pow3(float _a);

/// Quick quartic function
float pow4(float _a);

/// Recursive function for quickly calculating powers with integer exponents
float powi(float _a, int _exp);

/// Clamps a number between two bounds.
float clamp(float _x, float _lower, float _upper);

#define NULLVECTF Vector2f(0.f, 0.f) /// Zero vector, float
#define NULLVECTI Vector2i(0, 0) /// Zero vector, int
#define NULLVECTU Vector2u(0, 0) /// Zero vector, unsigned int
#define UNITVECTF Vector2f(1.f, 0.f) /// Trigonometric unit vector, float
#define UNITVECTI Vector2i(1, 0) /// Trigonometric unit vector, int
#define UNITVECTU Vector2u(1, 0) /// Trigonometric unit vector, unsigned int


/// === RANDOMIZERS === ///

void seedRNGs(UL _seed);

/// Generates a random 32-bit number.
UL rng32();

/// Generates a random 64-bit number.
ULL rng64();

#define RAND_Z(x) (rng32() % (int)((x) + 1)) /// Generates a random integer between 0 and x (both included)
#define RAND(x, y) (rng32() % (int)((y) - (x) + 1) + (x)) /// Generates a random integer between x and y (both included)
#define RAND_BOOL (rand() % 2) /// Generates either 0 or 1 randomly
#define RANDF(x, y) ((float)(RAND((x) * 1000.f, (y) * 1000.f)) / 1000.f) /// Generates a random float between x and y

/// Generates a random decimal number between 0 and 1 with the specified amount of decimals.
/// To circumvent the 16-bit limit of rand(), which would induce severe precision losses, a custom RNG is used.
double rand_unit(int _d);


/// === MISC === ///

sfFloatRect floatRect_Contract(sfFloatRect _r, float _val);
sfFloatRect floatRect_Expand(sfFloatRect _r, float _val);
sfFloatRect FloatRect_FromCenter(sfVector2f _c, float _w, float _h);