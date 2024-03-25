#include "va_tools.h"

sfVertexArray* va_va;


/// === LOCAL HELPER FUNCTIONS === ///

void va_Clear() { sfVertexArray_clear(va_va); }
void va_AddPoint(sfVector2f _pos, sfColor _clr) { sfVertexArray_append(va_va, Vertex(_pos, _clr)); }
void va_Draw(sfRenderStates* _rstate) {
	sfRenderWindow_drawVertexArray(window.rw, va_va, _rstate);
}

void va_SetType(VaTypes _type) {
	switch (_type) {
		case VA_LINE: sfVertexArray_setPrimitiveType(va_va, sfLineStrip); break;
		case VA_TRI: sfVertexArray_setPrimitiveType(va_va, sfTriangleStrip); break;
		default: log_LogStr(LOG_ERROR, "Vertex array engine rendering error: unknown primitive type", sfTrue, sfTrue);
		case VA_POINT: sfVertexArray_setPrimitiveType(va_va, sfPoints); break;
	}
}


/// === CORE === ///

void va_Init() {
	va_va = sfVertexArray_create();
	if (!va_va) {
		log_LogStr(LOG_FATAL, "Vertex array engine initialization error: insufficient memory", sfTrue, sfTrue);
		return;
	}
}

void va_Unload() {
	sfVertexArray_destroy(va_va);
}


/// === QUICK RENDERING === ///

void va_DrawLine(char* _rstate_id, sfVector2f _a, sfVector2f _b, sfColor _clr) {
	sfRenderStates* rs = shd_FetchState(_rstate_id);
	va_Clear();
	va_SetType(sfLineStrip);

	va_AddPoint(_a, _clr);
	va_AddPoint(_b, _clr);

	va_Draw(rs);
}

void va_DrawRectangle(VaTypes _type, char* _rstate_id, sfFloatRect _r, sfColor _clr) {
	sfRenderStates* rs = shd_FetchState(_rstate_id);
	va_Clear();
	va_SetType(_type);

	va_AddPoint(Vector2f(_r.left, _r.top), _clr);
	va_AddPoint(Vector2f(_r.left + _r.width, _r.top), _clr);
	va_AddPoint(Vector2f(_r.left + _r.width, _r.top + _r.height), _clr);
	va_AddPoint(Vector2f(_r.left, _r.top + _r.height), _clr);
	va_AddPoint(Vector2f(_r.left, _r.top), _clr);

	va_Draw(rs);
}

void va_DrawPolygonReg(VaTypes _type, char* _rstate_id, int _v, sfVector2f _o, float _rds, float _angle, sfColor _clr) {
	if (_v < 3) {
		log_LogStr(LOG_ERROR, "Vertex array engine rendering error: attempting to render a polygon with too few vertices (", sfTrue, sfFalse);
		log_LogInt(LOG_ERROR, _v, sfFalse, sfFalse);
		log_LogStr(LOG_ERROR, ")", sfFalse, sfTrue);
		return;
	}
	sfRenderStates* rs = shd_FetchState(_rstate_id);
	va_Clear();
	va_SetType(_type);

	for (int i = 0; i <= _v; i++) va_AddPoint(v_Add(_o, v_RotateD(Vector2f(0.f, _rds), 180.f + _angle + (360.f / (float)_v) * i)), _clr);

	va_Draw(rs);
}

void va_DrawCircle(VaTypes _type, char* _rstate_id, sfVector2f _o, float _rds, sfColor _clr) {
	va_DrawPolygonReg(_type, _rstate_id, 50, _o, _rds, 0.f, _clr);
}

void va_DrawPolygon(VaTypes _type, char* _rstate_id, int _n, sfVector2f* _l, sfBool _closed, sfColor _clr) {
	sfRenderStates* rs = shd_FetchState(_rstate_id);
	va_Clear();
	va_SetType(_type);

	for (int i = 0; i < _n; i++) va_AddPoint(_l[i], _clr);
	if (_closed) va_AddPoint(_l[0], _clr);

	va_Draw(rs);
}


/// === TRANSFORMATIONS === ///

void va_Translate(sfVertexArray* _va, sfVector2f _vec) {
	size_t v = sfVertexArray_getVertexCount(_va);
	for (int i = 0; i < v; i++) sfVertexArray_getVertex(_va, i)->position = v_Add(sfVertexArray_getVertex(_va, i)->position, _vec);
}

void va_SetPosition(sfVertexArray* _va, sfVector2f _vec) {
	size_t v = sfVertexArray_getVertexCount(_va);
	sfFloatRect aabb = sfVertexArray_getBounds(_va);
	sfVector2f center = Vector2f(aabb.left + aabb.width * .5f, aabb.top + aabb.height * .5f);
	for (int i = 0; i < v; i++) {
		sfVertex* vp = sfVertexArray_getVertex(_va, i);
		sfVector2f posRel = v_Sub(vp->position, center);
		vp->position = v_Add(posRel, _vec);
	}
}

void va_Rotate(sfVertexArray* _va, float _angle) {
	size_t v = sfVertexArray_getVertexCount(_va);
	sfFloatRect aabb = sfVertexArray_getBounds(_va);
	sfVector2f center = Vector2f(aabb.left + aabb.width * .5f, aabb.top + aabb.height * .5f);
	for (int i = 0; i < v; i++) {
		sfVertex* vp = sfVertexArray_getVertex(_va, i);
		sfVector2f posRel = v_Sub(vp->position, center);
		vp->position = v_Add(center, v_RotateD(posRel, _angle));
	}
}