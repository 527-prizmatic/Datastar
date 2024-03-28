/// Various collision-handling functions.
/// Function prefix: col_

#pragma once
#include "tools.h"
#include "vectors.h"

sfBool col_PointPoint(sfVector2f _a, sfVector2f _b);
sfBool col_PointCircle(sfVector2f _a, sfVector2f _center, float _rds);
sfBool col_PointRect(sfVector2f _a, sfFloatRect _rect);
sfBool col_PointLine(sfVector2f _p, sfVector2f _l1, sfVector2f _l2);
sfBool col_CircleCircle(sfVector2f _c1, float _r1, sfVector2f _c2, float _r2);
sfBool col_RectRect(sfFloatRect _rect1, sfFloatRect _rect2);