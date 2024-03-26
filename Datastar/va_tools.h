/// (C) 2024 The Prizmanager
/// Author - J.Sebastien Toussaint
/// 
/// A suite of tools to assist in manipulating vertex arrays and using them to render basic shapes such as polygons and lines.
/// Function prefix: va_

#pragma once
#include "tools.h"
#include "logger.h"
#include "tools.h"
#include "window_manager.h"
#include "shader_manager.h"
#include "state_manager.h"

typedef enum {
	VA_POINT,
	VA_LINE,
	VA_TRI
} VaTypes;


/// === CORE === ///

/// Initializes the vertex array engine.
void va_Init();

/// Unloads the vertex array engine and frees up all allocated memory.
void va_Unload();


/// === QUICK RENDERING === ///
/// A few functions allowing to render simple shapes. Do not use for more complex objects or if you would like to use transformation functions.

/// Draws a line between two points.
/// \param _type - Primitive type
/// \param _rstate_id - A string literal containing the ID of the render state to be applied. leave NULL for no shader.
/// \param _a, _b - Points
/// \param _clr - Color of the rectangle to display
void va_DrawLine(char* _rstate_id, sfVector2f _a, sfVector2f _b, sfColor _clr);

/// Draws an axis-aligned rectangle.
/// \param _type - Primitive type
/// \param _rstate_id - A string literal containing the ID of the render state to be applied. leave NULL for no shader.
/// \param _r - Bounds of the rectangle to display
/// \param _clr - Color of the rectangle to display
void va_DrawRectangle(VaTypes _type, char* _rstate_id, sfFloatRect _r, sfColor _clr);

/// Draws a regular polygon.
/// \param _type - Primitive type
/// \param _rstate_id - A string literal containing the ID of the render state to be applied. leave NULL for no shader.
/// \param _v - Number of vertices
/// \param _o - Center position
/// \param _rds - Polygon radius
/// \param _angle - Angle in degrees. If given 0, the first vertex drawn will be facing straight up.
/// \param _clr - Color of the polygon to display
void va_DrawPolygonReg(VaTypes _type, char* _rstate_id, int _v, sfVector2f _o, float _rds, float _angle, sfColor _clr);

/// Draws a star polygon.
/// \param _type - Primitive type
/// \param _rstate_id - A string literal containing the ID of the render state to be applied. leave NULL for no shader.
/// \param _v - Number of vertices
/// \param _o - Center position
/// \param _rds - Polygon radius
/// \param _angle - Angle in degrees. If given 0, the first vertex drawn will be facing straight up.
/// \param _clr - Color of the polygon to display
void va_DrawPolygonStar(VaTypes _type, char* _rstate_id, int _v, sfVector2f _o, float _rds, float _angle, sfColor _clr);

/// Draws a circle. To keep things simple enough, the shape will simply be approximated as a 50-vertex regular polygon (a bit more than the SFML's default 30).
/// \param _type - Primitive type
/// \param _rstate_id - A string literal containing the ID of the render state to be applied. leave NULL for no shader.
/// \param _o - Center position
/// \param _rds - Circle radius
/// \param _clr - Color of the polygon to display
void va_DrawCircle(VaTypes _type, char* _rstate_id, sfVector2f _o, float _rds, sfColor _clr);

/// Draws a broken line between the given list of points.
/// \param _type - Primitive type
/// \param _rstate_id - A string literal containing the ID of the render state to be applied. leave NULL for no shader.
/// \param _n - How many points in the given list should be displayed
/// \param _l - An array of sfVector2f data
/// \param _closed - Whether the shape should be closed
/// \param _clr - Color of the polygon to display
void va_DrawPolygon(VaTypes _type, char* _rstate_id, int _n, sfVector2f* _l, sfBool _closed, sfColor _clr);

/// Draws a double frame constituted of two rectangles.
/// \param _rstate_id - A string literal containing the ID of the render state to be applied. leave NULL for no shader.
/// \param _r - Bounds of the innermost rectangle. The second one is rendered with a 3-pixel offset outwards in all directions.
/// \param _clr - Color of the frame
void va_DrawFrame(char* _rstate_id, sfFloatRect _r, sfColor _clr);

/// Draws a preset frame around the screen's edges.
void va_DrawScreenBorders();


/// === TRANSFORMATIONS === ///
/// A set of functions allowing to perform various transformations (translation, rotation, etc.) on vertex arrays.
/// All transformation functions consider a vertex array's origin is the center of its bounding box.

void va_Translate(sfVertexArray* _va, sfVector2f _vec);

void va_SetPosition(sfVertexArray* _va, sfVector2f _vec);

void va_Rotate(sfVertexArray* _va, float _angle);

void va_SetColorOverride(sfVertexArray* _va, sfColor _clr);