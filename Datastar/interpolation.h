/// (C) 2024 The Prizmanager
/// Author - J.Sebastien Toussaint
/// 
/// Contains a handful of interpolation functions, such as lerps, bilinears, bicubics, etc.
/// Function prefix: itp_

#pragma once
#include "tools.h"
#include "vectors.h"


/// === INTERPOLATORS === ///

/// Interpolates two float values by using the given method.
float itp_Float(float _a, float _b, float _t, float _method(float _x));

/// Interpolates two 2D vectors by using the given method.
sfVector2f itp_Vector2f(sfVector2f _a, sfVector2f _b, float _t, float _method(float _x));

/// Interpolates two colors by using the given method.
sfColor itp_Color(sfColor _a, sfColor _b, float _t, float _method(float _x));

/// Performs bilinear interpolation to calculate the value of a 2D field at the coordinates (_x , _y).
/// The four data points have to be specified in the following order: top left, top right, bottom left, bottom right.
sfVector2f itp_Bilinear(sfVector2f _q11, sfVector2f _q12, sfVector2f _q21, sfVector2f _q22, float _v11, float _v12, float _v21, float _v22, float _x, float _y);


/// === INTERPOLATION METHODS === ///

/// Nearest-neighbor interpolation. Returns 1 if the passed number is higher than 0.5, and 0 otherwise.
/// \return 1 if x >= 0.5;   0 if x < 0.5
float itp_Nearest(float _x);

/// Linear interpolation. Return values are clamped between 0 and 1.
/// \return x
float itp_Linear(float _x);

/// Square interpolation. Return values are clamped between 0 and 1.
/// \return x^2
float itp_Square(float _x);

/// Inverted square interpolation. Return values are clamped between 0 and 1.
/// \return 1 - ((1 - x)^2)
float itp_InvSquare(float _x);

/// Cubic interpolation. Return values are clamped between 0 and 1.
/// \return x^3
float itp_Cube(float _x);

/// Smoothstep function. Return values are clamped between 0 and 1.
/// \return 3x^2 - 2x^3
float itp_Smooth(float _x);

/// Smootherstep function. Return values are clamped between 0 and 1.
/// \return 6x^5 - 15x^4 + 10x^3
float itp_Smoother(float _x);

/// Third-order smoothstep function. Return values are clamped between 0 and 1.
/// \return -20x^7 + 70x^6 - 84x^5 + 35x^4
float itp_Smoothest(float _x);