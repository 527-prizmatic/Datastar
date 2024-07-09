#include "va_text_neo.h"

/// Fetches exact vertex coordinates in a 3x3 matrix with the given origin and character size.
/// \param _id - The id of the requested vertex, as follows:
/// \param 0 1 2
/// \param 3 4 5
/// \param 6 7 8
/// \param _pos - Origin position
/// \param _size - Character size
sfVector2f vtn_GetVertex(char _id, sfVector2f _pos, int _size);


/// /////////////////// ///


sfSprite* vtn_Sprite;

void vtn_Init() {
	vtn_Sprite = sfSprite_create();
}

VtnVaText* vtn_Text(char* _msg, int _size, enum WTxtAlign _align) {
	VtnVaText* v = calloc(1, sizeof(VtnVaText));
	if (!v) return NULL;

	int c = 1;
	int linelen = 0;
	int longest = 0;
	for (int i = 0; i < strlen(_msg); i++) {
		if (_msg[i] == '\n') {
			c++;
			linelen = 0;
		}
		else {
			linelen++;
			if (linelen > longest) longest = linelen;
		}
	}

	char** lines = calloc(c, sizeof(char*));
	if (!lines) {
		free(v);
		return NULL;
	}
	for (int i = 0; i < c; i++) {
		lines[i] = calloc(longest + 1, sizeof(char));
		if (!lines[i]) {
			free(v);
			return NULL;
		}
	}

	int line = 0;
	int l = 0;
	for (int i = 0; i < strlen(_msg); i++) {
		lines[line][l] = _msg[i];
		if (_msg[i] == '\n') {
			lines[line][l] = 0;
			line++;
			l = 0;
		}
		else l++;
	}

	float mwidth = longest * _size * 1.25f - _size * .25f + 2.f;
	float mheight = c * _size * 1.25f - _size * .25f + 1.f;
	v->rt = sfRenderTexture_create(mwidth, mheight, sfFalse);
	sfRenderTexture_clear(v->rt, sfTransparent);
	for (int i = 0; i < c; i++) vtn_DrawText(v->rt, Vector2f(1.f, i * _size * 1.25f), lines[i], longest, _size, _align, sfWhite);

	for (int i = 0; i < c; i++) free(lines[i]);
	free(lines);
	return v;
}

void vtn_Draw(VtnVaText* _txt, sfVector2f _pos, sfColor _clr) {
	sfTexture* tex = sfRenderTexture_getTexture(_txt->rt);
	sfVector2f dims = Vector2f(sfTexture_getSize(tex).x, sfTexture_getSize(tex).y);
	dims.y = -dims.y;
	sfVector2f pos = v_Sub(_pos, v_Mul(dims, .5f));
	sfColor clr = _clr;
	sfSprite_setTexture(vtn_Sprite, tex, sfTrue);
	sfShader_setColorUniform(shd_FetchShader("text"), "clr", _clr);
	sfShader_setFloatUniform(shd_FetchShader("text"), "time", gs_TimerGlobal);

	for (int i = 0; i < 3; i++) {
		clr.a = _clr.a * (1.f - i * .333f);
		pos.y++;
		sfSprite_setPosition(vtn_Sprite, pos);
		sfSprite_setColor(vtn_Sprite, clr);
		sfSprite_setScale(vtn_Sprite, RQ_SCALE_FLIP_V);
		sfRenderWindow_drawSprite(window.rw, vtn_Sprite, NULL);
	}
}

void vtn_DestroyText(VtnVaText* _vt) {
	if (!_vt) return;
	if (_vt->rt) sfRenderTexture_destroy(_vt->rt);
	free(_vt);
}


/// /////////////////// ///


void vtn_DrawText(sfRenderTexture* _rt, sfVector2f _pos, char* _msg, int _ll, int _size, WTxtAlign _align, sfColor _clr) {
	float maxwidth = _ll * _size * 1.25f - _size * .25f;
	if (_align == TXT_CENTER) {
		_pos.x -= (strlen(_msg) * _size * 1.25f - _size * .25f) * .5f;
		_pos.x += maxwidth * .5f;
	}
	else if (_align == TXT_RIGHT) {
		_pos.x -= strlen(_msg) * _size * 1.25f - _size * .25f;
		_pos.x += maxwidth;
	}

	sfVector2f posTemp = _pos;
	for (int i = 0; i < strlen(_msg); i++) {
		if (_msg[i] == '\n') {
			posTemp.x = _pos.x;
			posTemp.y += _size * 1.25f;
		}
		else {
			vtn_DrawChar(_rt, posTemp, _msg[i], _size, _clr);
			posTemp.x += _size * 1.25f;
		}
	}
}

void vtn_DrawChar(sfRenderTexture* _rt, sfVector2f _pos, char _char, int _size, sfColor _clr) {
	sfColor clrBase = _clr;
	if (_char > 96) _char -= 32;

	switch (_char) {
		case ' ': break;
		case 'A':	vtn_DrawCharA(_rt, _pos, _size, _clr); break;
		case 'B':	vtn_DrawCharB(_rt, _pos, _size, _clr); break;
		case 'C':	vtn_DrawCharC(_rt, _pos, _size, _clr); break;
		case 'D':	vtn_DrawCharD(_rt, _pos, _size, _clr); break;
		case 'E':	vtn_DrawCharE(_rt, _pos, _size, _clr); break;
		case 'F':	vtn_DrawCharF(_rt, _pos, _size, _clr); break;
		case 'G':	vtn_DrawCharG(_rt, _pos, _size, _clr); break;
		case 'H':	vtn_DrawCharH(_rt, _pos, _size, _clr); break;
		case 'I':	vtn_DrawCharI(_rt, _pos, _size, _clr); break;
		case 'J':	vtn_DrawCharJ(_rt, _pos, _size, _clr); break;
		case 'K':	vtn_DrawCharK(_rt, _pos, _size, _clr); break;
		case 'L':	vtn_DrawCharL(_rt, _pos, _size, _clr); break;
		case 'M':	vtn_DrawCharM(_rt, _pos, _size, _clr); break;
		case 'N':	vtn_DrawCharN(_rt, _pos, _size, _clr); break;
		case 'O':	vtn_DrawCharO(_rt, _pos, _size, _clr); break;
		case 'P':	vtn_DrawCharP(_rt, _pos, _size, _clr); break;
		case 'Q':	vtn_DrawCharQ(_rt, _pos, _size, _clr); break;
		case 'R':	vtn_DrawCharR(_rt, _pos, _size, _clr); break;
		case 'S':	vtn_DrawCharS(_rt, _pos, _size, _clr); break;
		case 'T':	vtn_DrawCharT(_rt, _pos, _size, _clr); break;
		case 'U':	vtn_DrawCharU(_rt, _pos, _size, _clr); break;
		case 'V':	vtn_DrawCharV(_rt, _pos, _size, _clr); break;
		case 'W':	vtn_DrawCharW(_rt, _pos, _size, _clr); break;
		case 'X':	vtn_DrawCharX(_rt, _pos, _size, _clr); break;
		case 'Y':	vtn_DrawCharY(_rt, _pos, _size, _clr); break;
		case 'Z':	vtn_DrawCharZ(_rt, _pos, _size, _clr); break;
		case '0':	vtn_DrawChar0(_rt, _pos, _size, _clr); break;
		case '1':	vtn_DrawChar1(_rt, _pos, _size, _clr); break;
		case '2':	vtn_DrawChar2(_rt, _pos, _size, _clr); break;
		case '3':	vtn_DrawChar3(_rt, _pos, _size, _clr); break;
		case '4':	vtn_DrawChar4(_rt, _pos, _size, _clr); break;
		case '5':	vtn_DrawChar5(_rt, _pos, _size, _clr); break;
		case '6':	vtn_DrawChar6(_rt, _pos, _size, _clr); break;
		case '7':	vtn_DrawChar7(_rt, _pos, _size, _clr); break;
		case '8':	vtn_DrawChar8(_rt, _pos, _size, _clr); break;
		case '9':	vtn_DrawChar9(_rt, _pos, _size, _clr); break;
		case '.':	vtn_DrawCharDot(_rt, _pos, _size, _clr); break;
		case ',':	vtn_DrawCharComma(_rt, _pos, _size, _clr); break;
		case '-':	vtn_DrawCharHyphen(_rt, _pos, _size, _clr); break;
		case '\'':	vtn_DrawCharApostrophe(_rt, _pos, _size, _clr); break;
		case '&':	vtn_DrawCharAmpersand(_rt, _pos, _size, _clr); break;
		case '!':	vtn_DrawCharBang(_rt, _pos, _size, _clr); break;
		case '(':	vtn_DrawCharLBracket(_rt, _pos, _size, _clr); break;
		case ')':	vtn_DrawCharRBracket(_rt, _pos, _size, _clr); break;
		case '/':	vtn_DrawCharSlash(_rt, _pos, _size, _clr); break;
	}
}

void vtn_DrawCharA(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vtn_GetVertex(6, _pos, _size);
	v[1] = vtn_GetVertex(0, _pos, _size);
	v[2] = vtn_GetVertex(2, _pos, _size);
	v[3] = vtn_GetVertex(8, _pos, _size);
	v[4] = vtn_GetVertex(5, _pos, _size);
	v[5] = vtn_GetVertex(3, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 6, v, sfFalse, _clr);
}

void vtn_DrawCharB(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vtn_GetVertex(6, _pos, _size);
	v[1] = vtn_GetVertex(0, _pos, _size);
	v[2] = vtn_GetVertex(2, _pos, _size);
	v[3] = vtn_GetVertex(4, _pos, _size);
	v[4] = vtn_GetVertex(8, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 5, v, sfTrue, _clr);
}

void vtn_DrawCharC(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vtn_GetVertex(2, _pos, _size);
	v[1] = vtn_GetVertex(0, _pos, _size);
	v[2] = vtn_GetVertex(6, _pos, _size);
	v[3] = vtn_GetVertex(8, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 4, v, sfFalse, _clr);
}

void vtn_DrawCharD(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vtn_GetVertex(0, _pos, _size);
	v[1] = vtn_GetVertex(1, _pos, _size);
	v[2] = vtn_GetVertex(5, _pos, _size);
	v[3] = vtn_GetVertex(8, _pos, _size);
	v[4] = vtn_GetVertex(6, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 5, v, sfTrue, _clr);
}

void vtn_DrawCharE(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[7];
	v[0] = vtn_GetVertex(2, _pos, _size);
	v[1] = vtn_GetVertex(0, _pos, _size);
	v[2] = vtn_GetVertex(3, _pos, _size);
	v[3] = vtn_GetVertex(4, _pos, _size);
	v[4] = vtn_GetVertex(3, _pos, _size);
	v[5] = vtn_GetVertex(6, _pos, _size);
	v[6] = vtn_GetVertex(8, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 7, v, sfFalse, _clr);
}

void vtn_DrawCharF(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vtn_GetVertex(2, _pos, _size);
	v[1] = vtn_GetVertex(0, _pos, _size);
	v[2] = vtn_GetVertex(3, _pos, _size);
	v[3] = vtn_GetVertex(4, _pos, _size);
	v[4] = vtn_GetVertex(3, _pos, _size);
	v[5] = vtn_GetVertex(6, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 6, v, sfFalse, _clr);
}

void vtn_DrawCharG(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vtn_GetVertex(2, _pos, _size);
	v[1] = vtn_GetVertex(0, _pos, _size);
	v[2] = vtn_GetVertex(6, _pos, _size);
	v[3] = vtn_GetVertex(8, _pos, _size);
	v[4] = vtn_GetVertex(5, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 5, v, sfFalse, _clr);
}

void vtn_DrawCharH(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vtn_GetVertex(0, _pos, _size);
	v[1] = vtn_GetVertex(6, _pos, _size);
	v[2] = vtn_GetVertex(3, _pos, _size);
	v[3] = vtn_GetVertex(5, _pos, _size);
	v[4] = vtn_GetVertex(2, _pos, _size);
	v[5] = vtn_GetVertex(8, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 6, v, sfFalse, _clr);
}

void vtn_DrawCharI(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vtn_GetVertex(0, _pos, _size);
	v[1] = vtn_GetVertex(2, _pos, _size);
	v[2] = vtn_GetVertex(1, _pos, _size);
	v[3] = vtn_GetVertex(7, _pos, _size);
	v[4] = vtn_GetVertex(6, _pos, _size);
	v[5] = vtn_GetVertex(8, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 6, v, sfFalse, _clr);
}

void vtn_DrawCharJ(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[3];
	v[0] = vtn_GetVertex(2, _pos, _size);
	v[1] = vtn_GetVertex(8, _pos, _size);
	v[2] = vtn_GetVertex(6, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 3, v, sfFalse, _clr);
}

void vtn_DrawCharK(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vtn_GetVertex(0, _pos, _size);
	v[1] = vtn_GetVertex(6, _pos, _size);
	v[2] = vtn_GetVertex(2, _pos, _size);
	v[3] = vtn_GetVertex(4, _pos, _size);
	v[4] = vtn_GetVertex(8, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 5, v, sfFalse, _clr);
}

void vtn_DrawCharL(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[3];
	v[0] = vtn_GetVertex(0, _pos, _size);
	v[1] = vtn_GetVertex(6, _pos, _size);
	v[2] = vtn_GetVertex(8, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 3, v, sfFalse, _clr);
}

void vtn_DrawCharM(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vtn_GetVertex(6, _pos, _size);
	v[1] = vtn_GetVertex(0, _pos, _size);
	v[2] = vtn_GetVertex(4, _pos, _size);
	v[3] = vtn_GetVertex(2, _pos, _size);
	v[4] = vtn_GetVertex(8, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 5, v, sfFalse, _clr);
}

void vtn_DrawCharN(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = vtn_GetVertex(6, _pos, _size);
	v[1] = vtn_GetVertex(0, _pos, _size);
	v[2] = vtn_GetVertex(8, _pos, _size);
	v[3] = vtn_GetVertex(2, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 4, v, sfFalse, _clr);
}

void vtn_DrawCharO(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = vtn_GetVertex(0, _pos, _size);
	v[1] = vtn_GetVertex(6, _pos, _size);
	v[2] = vtn_GetVertex(8, _pos, _size);
	v[3] = vtn_GetVertex(2, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 4, v, sfTrue, _clr);
}

void vtn_DrawCharP(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vtn_GetVertex(6, _pos, _size);
	v[1] = vtn_GetVertex(0, _pos, _size);
	v[2] = vtn_GetVertex(2, _pos, _size);
	v[3] = vtn_GetVertex(5, _pos, _size);
	v[4] = vtn_GetVertex(3, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 5, v, sfFalse, _clr);
}

void vtn_DrawCharQ(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vtn_GetVertex(8, _pos, _size);
	v[1] = vtn_GetVertex(6, _pos, _size);
	v[2] = vtn_GetVertex(0, _pos, _size);
	v[3] = vtn_GetVertex(2, _pos, _size);
	v[4] = vtn_GetVertex(8, _pos, _size);
	v[5] = vtn_GetVertex(4, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 6, v, sfFalse, _clr);
}

void vtn_DrawCharR(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vtn_GetVertex(6, _pos, _size);
	v[1] = vtn_GetVertex(0, _pos, _size);
	v[2] = vtn_GetVertex(2, _pos, _size);
	v[3] = vtn_GetVertex(4, _pos, _size);
	v[4] = vtn_GetVertex(8, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 5, v, sfFalse, _clr);
}

void vtn_DrawCharS(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = vtn_GetVertex(2, _pos, _size);
	v[1] = vtn_GetVertex(0, _pos, _size);
	v[2] = vtn_GetVertex(8, _pos, _size);
	v[3] = vtn_GetVertex(6, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 4, v, sfFalse, _clr);
}

void vtn_DrawCharT(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vtn_GetVertex(0, _pos, _size);
	v[1] = vtn_GetVertex(2, _pos, _size);
	v[2] = vtn_GetVertex(1, _pos, _size);
	v[3] = vtn_GetVertex(7, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 4, v, sfFalse, _clr);
}

void vtn_DrawCharU(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = vtn_GetVertex(0, _pos, _size);
	v[1] = vtn_GetVertex(6, _pos, _size);
	v[2] = vtn_GetVertex(8, _pos, _size);
	v[3] = vtn_GetVertex(2, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 4, v, sfFalse, _clr);
}

void vtn_DrawCharV(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vtn_GetVertex(0, _pos, _size);
	v[1] = vtn_GetVertex(3, _pos, _size);
	v[2] = vtn_GetVertex(7, _pos, _size);
	v[3] = vtn_GetVertex(5, _pos, _size);
	v[4] = vtn_GetVertex(2, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 5, v, sfFalse, _clr);
}

void vtn_DrawCharW(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vtn_GetVertex(0, _pos, _size);
	v[1] = vtn_GetVertex(6, _pos, _size);
	v[2] = vtn_GetVertex(4, _pos, _size);
	v[3] = vtn_GetVertex(8, _pos, _size);
	v[4] = vtn_GetVertex(2, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 5, v, sfFalse, _clr);
}

void vtn_DrawCharX(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vtn_GetVertex(0, _pos, _size);
	v[1] = vtn_GetVertex(8, _pos, _size);
	v[2] = vtn_GetVertex(4, _pos, _size);
	v[3] = vtn_GetVertex(6, _pos, _size);
	v[4] = vtn_GetVertex(2, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 5, v, sfFalse, _clr);
}

void vtn_DrawCharY(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = vtn_GetVertex(0, _pos, _size);
	v[1] = vtn_GetVertex(4, _pos, _size);
	v[2] = vtn_GetVertex(2, _pos, _size);
	v[3] = vtn_GetVertex(6, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 4, v, sfFalse, _clr);
}

void vtn_DrawCharZ(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = vtn_GetVertex(0, _pos, _size);
	v[1] = vtn_GetVertex(2, _pos, _size);
	v[2] = vtn_GetVertex(6, _pos, _size);
	v[3] = vtn_GetVertex(8, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 4, v, sfFalse, _clr);
}

void vtn_DrawChar0(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vtn_GetVertex(0, _pos, _size);
	v[1] = vtn_GetVertex(2, _pos, _size);
	v[2] = vtn_GetVertex(8, _pos, _size);
	v[3] = vtn_GetVertex(6, _pos, _size);
	v[4] = vtn_GetVertex(0, _pos, _size);
	v[5] = vtn_GetVertex(8, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 6, v, sfFalse, _clr);
}

void vtn_DrawChar1(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[2];
	v[0] = vtn_GetVertex(2, _pos, _size);
	v[1] = vtn_GetVertex(8, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 2, v, sfFalse, _clr);
}

void vtn_DrawChar2(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vtn_GetVertex(0, _pos, _size);
	v[1] = vtn_GetVertex(2, _pos, _size);
	v[2] = vtn_GetVertex(5, _pos, _size);
	v[3] = vtn_GetVertex(3, _pos, _size);
	v[4] = vtn_GetVertex(6, _pos, _size);
	v[5] = vtn_GetVertex(8, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 6, v, sfFalse, _clr);
}

void vtn_DrawChar3(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[7];
	v[0] = vtn_GetVertex(0, _pos, _size);
	v[1] = vtn_GetVertex(2, _pos, _size);
	v[2] = vtn_GetVertex(5, _pos, _size);
	v[3] = vtn_GetVertex(4, _pos, _size);
	v[4] = vtn_GetVertex(5, _pos, _size);
	v[5] = vtn_GetVertex(8, _pos, _size);
	v[6] = vtn_GetVertex(6, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 7, v, sfFalse, _clr);
}

void vtn_DrawChar4(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vtn_GetVertex(0, _pos, _size);
	v[1] = vtn_GetVertex(3, _pos, _size);
	v[2] = vtn_GetVertex(5, _pos, _size);
	v[3] = vtn_GetVertex(2, _pos, _size);
	v[4] = vtn_GetVertex(8, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 5, v, sfFalse, _clr);
}

void vtn_DrawChar5(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vtn_GetVertex(2, _pos, _size);
	v[1] = vtn_GetVertex(0, _pos, _size);
	v[2] = vtn_GetVertex(3, _pos, _size);
	v[3] = vtn_GetVertex(5, _pos, _size);
	v[4] = vtn_GetVertex(8, _pos, _size);
	v[5] = vtn_GetVertex(6, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 6, v, sfFalse, _clr);
}

void vtn_DrawChar6(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vtn_GetVertex(2, _pos, _size);
	v[1] = vtn_GetVertex(0, _pos, _size);
	v[2] = vtn_GetVertex(6, _pos, _size);
	v[3] = vtn_GetVertex(8, _pos, _size);
	v[4] = vtn_GetVertex(5, _pos, _size);
	v[5] = vtn_GetVertex(3, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 6, v, sfFalse, _clr);
}

void vtn_DrawChar7(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[3];
	v[0] = vtn_GetVertex(0, _pos, _size);
	v[1] = vtn_GetVertex(2, _pos, _size);
	v[2] = vtn_GetVertex(8, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 3, v, sfFalse, _clr);
}

void vtn_DrawChar8(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[7];
	v[0] = vtn_GetVertex(3, _pos, _size);
	v[1] = vtn_GetVertex(0, _pos, _size);
	v[2] = vtn_GetVertex(2, _pos, _size);
	v[3] = vtn_GetVertex(8, _pos, _size);
	v[4] = vtn_GetVertex(6, _pos, _size);
	v[5] = vtn_GetVertex(3, _pos, _size);
	v[6] = vtn_GetVertex(5, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 7, v, sfFalse, _clr);
}

void vtn_DrawChar9(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vtn_GetVertex(5, _pos, _size);
	v[1] = vtn_GetVertex(3, _pos, _size);
	v[2] = vtn_GetVertex(0, _pos, _size);
	v[3] = vtn_GetVertex(2, _pos, _size);
	v[4] = vtn_GetVertex(8, _pos, _size);
	v[5] = vtn_GetVertex(6, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 6, v, sfFalse, _clr);
}

void vtn_DrawCharDot(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = v_Add(_pos, Vector2f(_size * .375f, _size));
	v[1] = v_Add(_pos, Vector2f(_size * .375f, _size * .75f));
	v[2] = v_Add(_pos, Vector2f(_size * .625f, _size * .75f));
	v[3] = v_Add(_pos, Vector2f(_size * .625f, _size));
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 4, v, sfTrue, _clr);
}

void vtn_DrawCharComma(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[2];
	v[0] = v_Add(_pos, Vector2f(_size * .25f, _size));
	v[1] = v_Add(_pos, Vector2f(_size * .5f, _size * .75f));
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 2, v, sfFalse, _clr);
}

void vtn_DrawCharHyphen(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[2];
	v[0] = vtn_GetVertex(3, _pos, _size);
	v[1] = vtn_GetVertex(5, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 2, v, sfFalse, _clr);
}

void vtn_DrawCharApostrophe(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[2];
	v[0] = vtn_GetVertex(1, _pos, _size);
	v[1] = vtn_GetVertex(4, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 2, v, sfFalse, _clr);
}

void vtn_DrawCharAmpersand(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[8];
	v[0] = vtn_GetVertex(7, _pos, _size);
	v[1] = vtn_GetVertex(1, _pos, _size);
	v[2] = vtn_GetVertex(0, _pos, _size);
	v[3] = vtn_GetVertex(3, _pos, _size);
	v[4] = vtn_GetVertex(5, _pos, _size);
	v[5] = vtn_GetVertex(3, _pos, _size);
	v[6] = vtn_GetVertex(6, _pos, _size);
	v[7] = vtn_GetVertex(8, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 8, v, sfFalse, _clr);
}

void vtn_DrawCharBang(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = v_Add(_pos, Vector2f(_size * .375f, _size));
	v[1] = v_Add(_pos, Vector2f(_size * .375f, _size * .75f));
	v[2] = v_Add(_pos, Vector2f(_size * .625f, _size * .75f));
	v[3] = v_Add(_pos, Vector2f(_size * .625f, _size));
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 4, v, sfTrue, _clr);

	sfVector2f v2[2];
	v2[0] = vtn_GetVertex(1, _pos, _size);
	v2[1] = vtn_GetVertex(4, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 2, v2, sfTrue, _clr);
}

void vtn_DrawCharLBracket(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = vtn_GetVertex(2, _pos, _size);
	v[1] = vtn_GetVertex(1, _pos, _size);
	v[2] = vtn_GetVertex(7, _pos, _size);
	v[3] = vtn_GetVertex(8, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 4, v, sfFalse, _clr);
}

void vtn_DrawCharRBracket(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = vtn_GetVertex(0, _pos, _size);
	v[1] = vtn_GetVertex(1, _pos, _size);
	v[2] = vtn_GetVertex(7, _pos, _size);
	v[3] = vtn_GetVertex(6, _pos, _size);
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 4, v, sfFalse, _clr);
}

void vtn_DrawCharSlash(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[2];
	v[0] = v_Add(_pos, Vector2f(_size * .25f, _size * .75f));
	v[1] = v_Add(_pos, Vector2f(_size * .75f, _size * .25f));
	va_DrawPolygonRt(_rt, VA_LINE, NULL, 2, v, sfFalse, _clr);
}

sfVector2f vtn_GetVertex(char _id, sfVector2f _pos, int _size) {
	return v_Add(_pos, Vector2f((_id % 3) * (_size * .5f), (int)(_id / 3) * (_size * .5f)));
}