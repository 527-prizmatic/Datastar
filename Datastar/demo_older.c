#include "demo.h"

sfVertexArray* va;
sfVector2f center;

sfVector2f coordsLine[2];
sfVector2f coordsLineBase[2];

sfVector2f coordsSquareCast[4];
sfVector3f coordsSquare[4];
sfVector2f coordsSquareBase[4];

float angleZL;

void demo_Init() {
	va = sfVertexArray_create();
	sfVertexArray_setPrimitiveType(va, sfLineStrip);
	for (int i = 0; i < 2; i++) coordsLine[i] = NULLVECTF;
	coordsLineBase[0] = Vector2f(-100.f, 0.f);
	coordsLineBase[1] = Vector2f(100.f, 0.f);
	center = RQ_POS_CENTERED;
	angleZL = 0.f;
}

void demo_Update() {
	angleZL += 60.f * getDeltaTime();
	for (int i = 0; i < 2; i++) coordsLine[i] = v_Add(center, v_RotateD(coordsLineBase[i], angleZL));



	for (int i = 0; i < 4; i++) coordsSquareCast[i] = Vector2f(coordsSquare[i].x, coordsSquare[i].y);
}

void demo_Render() {
	sfVertexArray_clear(va);
	for (int i = 0; i < 3; i++) sfVertexArray_append(va, Vertex(coordsLine[i % 2], sfRed));
	sfRenderWindow_drawVertexArray(window.rw, va, NULL);

	sfVertexArray_clear(va);
	for (int i = 0; i < 5; i++) sfVertexArray_append(va, Vertex(coordsLine[i % 4], sfGreen));
	sfRenderWindow_drawVertexArray(window.rw, va, NULL);
}

void demo_Unload() {

}