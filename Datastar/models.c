#include "models.h"

void model_Init_PlayerShip();

void model_Init() {
	model_Init_PlayerShip();
}

void model_Init_PlayerShip() {
	model_PlayerShip = sfVertexArray_create();
	sfVertexArray_setPrimitiveType(model_PlayerShip, sfLineStrip);
	sfVertexArray_append(model_PlayerShip, Vertex(Vector2f(0.f, 0.f), sfBlack));
	sfVertexArray_append(model_PlayerShip, Vertex(v_RotateD(Vector2f(0.f, -20.f), 110.f), sfWhite));
	sfVertexArray_append(model_PlayerShip, Vertex(Vector2f(0.f, -40.f), sfWhite));
	sfVertexArray_append(model_PlayerShip, Vertex(v_RotateD(Vector2f(0.f, -20.f), -110.f), sfWhite));
	sfVertexArray_append(model_PlayerShip, Vertex(Vector2f(0.f, 0.f), sfBlack));
}