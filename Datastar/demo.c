#include "demo.h"

sfVector2f pol1[4];

sfVertexArray *ship, *shipTemp;

void demo_Init() {
	pol1[0] = Vector2f(100.f, 200.f);
	pol1[1] = Vector2f(200.f, 400.f);
	pol1[2] = Vector2f(400.f, 150.f); 
	pol1[3] = Vector2f(600.f, 400.f);

	ship = sfVertexArray_create();
	shipTemp = sfVertexArray_create();
	sfVertexArray_setPrimitiveType(ship, sfLineStrip);
	sfVertexArray_append(ship, Vertex(Vector2f(0.f, 0.f), sfBlack));
	sfVertexArray_append(ship, Vertex(v_RotateD(Vector2f(0.f, 20.f), 110.f), sfWhite));
	sfVertexArray_append(ship, Vertex(Vector2f(0.f, 40.f), sfWhite));
	sfVertexArray_append(ship, Vertex(v_RotateD(Vector2f(0.f, 20.f), -110.f), sfWhite));
	sfVertexArray_append(ship, Vertex(Vector2f(0.f, 0.f), sfBlack));
	shipTemp = sfVertexArray_copy(ship);
}

void demo_Update() {
	
}

void demo_Render() {
	static float angle = 0.f;
	angle += 60.f * getDeltaTime();

	static float v = 3;
	v += getDeltaTime();
	va_DrawRectangle(VA_LINE, NULL, FloatRect(100.f, 100.f, 1720.f, 880.f), sfRed);
	va_DrawPolygonReg(VA_LINE, NULL, (int)v, Vector2f(560.f, 540.f), 200.f, angle, sfGreen);
	va_DrawCircle(VA_LINE, NULL, Vector2f(1360.f, 540.f), 200.f, sfBlue);
	va_DrawPolygonReg(VA_LINE, NULL, 3, Vector2f(1360.f, 540.f), 200.f, angle, sfBlue);
	va_DrawPolygonReg(VA_LINE, NULL, 3, Vector2f(1360.f, 540.f), 200.f, angle + 180.f, sfBlue);
	va_DrawCircle(VA_LINE, NULL, Vector2f(1360.f, 540.f), 100.f, sfBlue);
	va_DrawPolygonReg(VA_LINE, NULL, 3, Vector2f(1360.f, 540.f), 100.f, angle + 90.f, sfBlue);
	va_DrawPolygonReg(VA_LINE, NULL, 3, Vector2f(1360.f, 540.f), 100.f, angle - 90.f, sfBlue);
	va_DrawCircle(VA_LINE, NULL, Vector2f(1360.f, 540.f), 50.f, sfBlue);
	va_DrawPolygonReg(VA_LINE, NULL, 3, Vector2f(1360.f, 540.f), 50.f, angle, sfBlue);
	va_DrawPolygonReg(VA_LINE, NULL, 3, Vector2f(1360.f, 540.f), 50.f, angle + 180.f, sfBlue);
	va_DrawCircle(VA_LINE, NULL, Vector2f(1360.f, 540.f), 25.f, sfBlue);

	va_DrawPolygon(VA_LINE, NULL, 4, pol1, sfTrue, sfYellow);

	va_SetPosition(shipTemp, Vector2f(500.f, 500.f));
	va_Rotate(shipTemp, 60.f * getDeltaTime());
	sfRenderWindow_drawVertexArray(window.rw, shipTemp, NULL);
}

void demo_Unload() {

}