#include "collisions.h"

sfBool col_PointPoint(sfVector2f _a, sfVector2f _b) {
	return col_CircleCircle(_a, 1.f, _b, 1.f);
}

sfBool col_PointCircle(sfVector2f _a, sfVector2f _center, float _rds) {
	return v_Mag2(v_Sub(_a, _center)) <= pow2(_rds);
}

sfBool col_PointRect(sfVector2f _a, sfFloatRect _rect) {
	return _a.x > _rect.left && _a.x < _rect.left + _rect.width && _a.y > _rect.top && _a.y < _rect.top + _rect.height;
}

sfBool col_PointLine(sfVector2f _p, sfVector2f _l1, sfVector2f _l2) {
	double dist = v_Mag(v_Add(v_Sub(_p, _l1), v_Sub(_p, _l2)));
	double line = v_Mag(v_Sub(_l2, _l1));
	return dist - line < .1f;
}

sfBool col_CircleCircle(sfVector2f _c1, float _r1, sfVector2f _c2, float _r2) {
	return v_Mag2(v_Sub(_c2, _c1)) <= pow2(_r1 + _r2);
}

sfBool col_RectRect(sfFloatRect _rect1, sfFloatRect _rect2) {
	return !(_rect1.left > _rect2.left + _rect2.width || _rect1.left + _rect1.width < _rect2.left || _rect1.top > _rect2.top + _rect2.height || _rect1.top + _rect1.height < _rect2.top);
}