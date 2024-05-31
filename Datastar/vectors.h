/// (C) 2024 The Prizmanager
/// Author - J.Sebastien Toussaint
/// 
/// Library for vector arithmetics.
/// Function prefix: v_

#pragma once
#include "tools.h"

#define PI 3.1415926535
#define D2R_FACTOR (PI / 180.) /// Multiply an angle in degrees by this to convert it to radians
#define R2D_FACTOR (180. / PI) /// Multiply an angle in radians by this to convert it to degrees

#define D2R(x) x * (D2R_FACTOR) /// Converts a degree angle to radians
#define R2D(x) x * (R2D_FACTOR) /// Converts a radian angle to degrees

#define REC2POL(v) Vector2f(v_Mag(v), v_AngAbsR(v)) /// Converts Cartesian coordinates to polar coordinates
#define POL2REC(v) Vector2f((float)v.x * cosf(v.y), (float)v.x * sinf(v.y)) /// Converts polar coordinates to Cartesian coordinates

#define V2F(v) (Vector2f((float)v.x, (float)v.y)) /// Converts any 2D vector to a sfVector2f
#define V2I(v) (Vector2i((int)v.x, (int)v.y)) /// Converts any 2D vector to a sfVector2i
#define V2U(v) (Vector2u((unsigned int)v.x, (unsigned int)v.y)) /// Converts any 2D vector to a sfVector2u

/// Computes the sum of two vectors.
sfVector2f v_Add(sfVector2f _a, sfVector2f _b);

/// Compute the difference between two vectors, subtracting _b to _a.
sfVector2f v_Sub(sfVector2f _a, sfVector2f _b);

/// Multiplies a vector by a constant. Only affects its magnitude, not its direction.
sfVector2f v_Mul(sfVector2f _a, float _x);

/// Computes the dot product between two vectors.
double v_Dot(sfVector2f _a, sfVector2f _b);

/// Computes a vector's magnitude.
double v_Mag(sfVector2f _a);

/// Computes a vector's squared magnitude.
/// Functionally similar to v_Mag(), but skipping the square root allows for slight optimizations.
double v_Mag2(sfVector2f _a);

/// Normalizes a vector. Returns a null vector if the input vector is a null vector.
sfVector2f v_Nmlz(sfVector2f _a);

/// Sets a vector's magnitude to the given value.
sfVector2f v_SetMag(sfVector2f _a, float _m);

/// Computes the angle between two vectors, in radians.
float v_AngRelR(sfVector2f _a, sfVector2f _b);

/// Computes a vector's angle relatively to the trigonometric unit vector, in radians.
float v_AngAbsR(sfVector2f _a);

/// Computes the angle between two vectors, in degrees.
float v_AngRelD(sfVector2f _a, sfVector2f _b);

/// Computes a vector's angle relatively to the trigonometric unit vector, in degrees.
float v_AngAbsD(sfVector2f _a);

/// Rotates a vector by the given angle in radians.
sfVector2f v_RotateR(sfVector2f _a, float _angle);

/// Rotates a vector by the given angle in degrees.
sfVector2f v_RotateD(sfVector2f _a, float _angle);

/// Performs axial symmetry on a vector along the Y axis, inverting its X coordinate.
sfVector2f v_MirrorX(sfVector2f _v);

/// Performs axial symmetry on a vector along the X axis, inverting its Y coordinate.
sfVector2f v_MirrorY(sfVector2f _v);

/// Rotates a vector by 180 degrees.
sfVector2f v_Flip(sfVector2f _v);

/// Converts a floating-point vector to integer.
sfVector2i v_FtoI(sfVector2f _v);

/// Converts an integer vector to floating-point.
sfVector2f v_ItoF(sfVector2i _v);