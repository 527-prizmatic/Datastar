#include "va_text.h"

/// Fetches exact vertex coordinates in a 3x3 matrix with the given origin and character size.
/// \param _id - The id of the requested vertex, as follows:
/// \param 0 1 2
/// \param 3 4 5
/// \param 6 7 8
/// \param _pos - Origin position
/// \param _size - Character size
sfVector2f vt_GetVertex(char _id, sfVector2f _pos, int _size);

void vt_DrawText(sfVector2f _pos, char* _msg, int _size, WTxtAlign _align, sfColor _clr) {
	if (_align == TXT_CENTER) {
		_pos.x -= (strlen(_msg) * _size * 1.25f - _size * .25f) * .5f;
	}
	else if (_align == TXT_RIGHT) {
		_pos.x -= strlen(_msg) * _size * 1.25f - _size * .25f;
	}

	sfVector2f posTemp = _pos;
	for (int i = 0; i < strlen(_msg); i++) {
		if (_msg[i] == '\n') {
			posTemp.x = _pos.x;
			posTemp.y += _size * 1.25f;
		}
		else {
			vt_DrawChar(posTemp, _msg[i], _size, _clr);
			posTemp.x += _size * 1.25f;
		}
	}
}

void vt_DrawChar(sfVector2f _pos, char _char, int _size, sfColor _clr) {
	sfColor clrBase = _clr;
	for (int i = 0; i < 5; i++) {
		switch (_char) {
			case ' ': break;
			case 'A':	vt_DrawCharA(_pos, _size, _clr); break;
			case 'B':	vt_DrawCharB(_pos, _size, _clr); break;
			case 'C':	vt_DrawCharC(_pos, _size, _clr); break;
			case 'D':	vt_DrawCharD(_pos, _size, _clr); break;
			case 'E':	vt_DrawCharE(_pos, _size, _clr); break;
			case 'F':	vt_DrawCharF(_pos, _size, _clr); break;
			case 'G':	vt_DrawCharG(_pos, _size, _clr); break;
			case 'H':	vt_DrawCharH(_pos, _size, _clr); break;
			case 'I':	vt_DrawCharI(_pos, _size, _clr); break;
			case 'J':	vt_DrawCharJ(_pos, _size, _clr); break;
			case 'K':	vt_DrawCharK(_pos, _size, _clr); break;
			case 'L':	vt_DrawCharL(_pos, _size, _clr); break;
			case 'M':	vt_DrawCharM(_pos, _size, _clr); break;
			case 'N':	vt_DrawCharN(_pos, _size, _clr); break;
			case 'O':	vt_DrawCharO(_pos, _size, _clr); break;
			case 'P':	vt_DrawCharP(_pos, _size, _clr); break;
			case 'Q':	vt_DrawCharQ(_pos, _size, _clr); break;
			case 'R':	vt_DrawCharR(_pos, _size, _clr); break;
			case 'S':	vt_DrawCharS(_pos, _size, _clr); break;
			case 'T':	vt_DrawCharT(_pos, _size, _clr); break;
			case 'U':	vt_DrawCharU(_pos, _size, _clr); break;
			case 'V':	vt_DrawCharV(_pos, _size, _clr); break;
			case 'W':	vt_DrawCharW(_pos, _size, _clr); break;
			case 'X':	vt_DrawCharX(_pos, _size, _clr); break;
			case 'Y':	vt_DrawCharY(_pos, _size, _clr); break;
			case 'Z':	vt_DrawCharZ(_pos, _size, _clr); break;
			case '0':	vt_DrawChar0(_pos, _size, _clr); break;
			case '1':	vt_DrawChar1(_pos, _size, _clr); break;
			case '2':	vt_DrawChar2(_pos, _size, _clr); break;
			case '3':	vt_DrawChar3(_pos, _size, _clr); break;
			case '4':	vt_DrawChar4(_pos, _size, _clr); break;
			case '5':	vt_DrawChar5(_pos, _size, _clr); break;
			case '6':	vt_DrawChar6(_pos, _size, _clr); break;
			case '7':	vt_DrawChar7(_pos, _size, _clr); break;
			case '8':	vt_DrawChar8(_pos, _size, _clr); break;
			case '9':	vt_DrawChar9(_pos, _size, _clr); break;
			case '.':	vt_DrawCharDot(_pos, _size, _clr); break;
			case ',':	vt_DrawCharComma(_pos, _size, _clr); break;
			case '-':	vt_DrawCharHyphen(_pos, _size, _clr); break;
			case '\'':	vt_DrawCharApostrophe(_pos, _size, _clr); break;
			case '&':	vt_DrawCharAmpersand(_pos, _size, _clr); break;
			case '!':	vt_DrawCharBang(_pos, _size, _clr); break;
			case '(':	vt_DrawCharLBracket(_pos, _size, _clr); break;
			case ')':	vt_DrawCharRBracket(_pos, _size, _clr); break;
		}
		_pos.y++;
		_clr.a = clrBase.a * itp_Float(0.f, 1.f, (5.f - i) / 5.f, itp_Square);
	}
}

void vt_DrawCharA(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vt_GetVertex(6, _pos, _size);
	v[1] = vt_GetVertex(0, _pos, _size);
	v[2] = vt_GetVertex(2, _pos, _size);
	v[3] = vt_GetVertex(8, _pos, _size);
	v[4] = vt_GetVertex(5, _pos, _size);
	v[5] = vt_GetVertex(3, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 6, v, sfFalse, _clr);
}

void vt_DrawCharB(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vt_GetVertex(6, _pos, _size);
	v[1] = vt_GetVertex(0, _pos, _size);
	v[2] = vt_GetVertex(2, _pos, _size);
	v[3] = vt_GetVertex(4, _pos, _size);
	v[4] = vt_GetVertex(8, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 5, v, sfTrue, _clr);
}

void vt_DrawCharC(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vt_GetVertex(2, _pos, _size);
	v[1] = vt_GetVertex(0, _pos, _size);
	v[2] = vt_GetVertex(6, _pos, _size);
	v[3] = vt_GetVertex(8, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 4, v, sfFalse, _clr);
}

void vt_DrawCharD(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vt_GetVertex(0, _pos, _size);
	v[1] = vt_GetVertex(1, _pos, _size);
	v[2] = vt_GetVertex(5, _pos, _size);
	v[3] = vt_GetVertex(8, _pos, _size);
	v[4] = vt_GetVertex(6, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 5, v, sfTrue, _clr);
}

void vt_DrawCharE(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[7];
	v[0] = vt_GetVertex(2, _pos, _size);
	v[1] = vt_GetVertex(0, _pos, _size);
	v[2] = vt_GetVertex(3, _pos, _size);
	v[3] = vt_GetVertex(4, _pos, _size);
	v[4] = vt_GetVertex(3, _pos, _size);
	v[5] = vt_GetVertex(6, _pos, _size);
	v[6] = vt_GetVertex(8, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 7, v, sfFalse, _clr);
}

void vt_DrawCharF(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vt_GetVertex(2, _pos, _size);
	v[1] = vt_GetVertex(0, _pos, _size);
	v[2] = vt_GetVertex(3, _pos, _size);
	v[3] = vt_GetVertex(4, _pos, _size);
	v[4] = vt_GetVertex(3, _pos, _size);
	v[5] = vt_GetVertex(6, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 6, v, sfFalse, _clr);
}

void vt_DrawCharG(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vt_GetVertex(2, _pos, _size);
	v[1] = vt_GetVertex(0, _pos, _size);
	v[2] = vt_GetVertex(6, _pos, _size);
	v[3] = vt_GetVertex(8, _pos, _size);
	v[4] = vt_GetVertex(5, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 5, v, sfFalse, _clr);
}

void vt_DrawCharH(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vt_GetVertex(0, _pos, _size);
	v[1] = vt_GetVertex(6, _pos, _size);
	v[2] = vt_GetVertex(3, _pos, _size);
	v[3] = vt_GetVertex(5, _pos, _size);
	v[4] = vt_GetVertex(2, _pos, _size);
	v[5] = vt_GetVertex(8, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 6, v, sfFalse, _clr);
}

void vt_DrawCharI(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vt_GetVertex(0, _pos, _size);
	v[1] = vt_GetVertex(2, _pos, _size);
	v[2] = vt_GetVertex(1, _pos, _size);
	v[3] = vt_GetVertex(7, _pos, _size);
	v[4] = vt_GetVertex(6, _pos, _size);
	v[5] = vt_GetVertex(8, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 6, v, sfFalse, _clr);
}

void vt_DrawCharJ(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[3];
	v[0] = vt_GetVertex(2, _pos, _size);
	v[1] = vt_GetVertex(8, _pos, _size);
	v[2] = vt_GetVertex(6, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 3, v, sfFalse, _clr);
}

void vt_DrawCharK(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vt_GetVertex(0, _pos, _size);
	v[1] = vt_GetVertex(6, _pos, _size);
	v[2] = vt_GetVertex(2, _pos, _size);
	v[3] = vt_GetVertex(4, _pos, _size);
	v[4] = vt_GetVertex(8, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 5, v, sfFalse, _clr);
}

void vt_DrawCharL(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[3];
	v[0] = vt_GetVertex(0, _pos, _size);
	v[1] = vt_GetVertex(6, _pos, _size);
	v[2] = vt_GetVertex(8, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 3, v, sfFalse, _clr);
}

void vt_DrawCharM(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vt_GetVertex(6, _pos, _size);
	v[1] = vt_GetVertex(0, _pos, _size);
	v[2] = vt_GetVertex(4, _pos, _size);
	v[3] = vt_GetVertex(2, _pos, _size);
	v[4] = vt_GetVertex(8, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 5, v, sfFalse, _clr);
}

void vt_DrawCharN(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = vt_GetVertex(6, _pos, _size);
	v[1] = vt_GetVertex(0, _pos, _size);
	v[2] = vt_GetVertex(8, _pos, _size);
	v[3] = vt_GetVertex(2, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 4, v, sfFalse, _clr);
}

void vt_DrawCharO(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = vt_GetVertex(0, _pos, _size);
	v[1] = vt_GetVertex(6, _pos, _size);
	v[2] = vt_GetVertex(8, _pos, _size);
	v[3] = vt_GetVertex(2, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 4, v, sfTrue, _clr);
}

void vt_DrawCharP(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vt_GetVertex(6, _pos, _size);
	v[1] = vt_GetVertex(0, _pos, _size);
	v[2] = vt_GetVertex(2, _pos, _size);
	v[3] = vt_GetVertex(5, _pos, _size);
	v[4] = vt_GetVertex(3, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 5, v, sfFalse, _clr);
}

void vt_DrawCharQ(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vt_GetVertex(8, _pos, _size);
	v[1] = vt_GetVertex(6, _pos, _size);
	v[2] = vt_GetVertex(0, _pos, _size);
	v[3] = vt_GetVertex(2, _pos, _size);
	v[4] = vt_GetVertex(8, _pos, _size);
	v[5] = vt_GetVertex(4, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 6, v, sfFalse, _clr);
}

void vt_DrawCharR(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vt_GetVertex(6, _pos, _size);
	v[1] = vt_GetVertex(0, _pos, _size);
	v[2] = vt_GetVertex(2, _pos, _size);
	v[3] = vt_GetVertex(4, _pos, _size);
	v[4] = vt_GetVertex(8, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 5, v, sfFalse, _clr);
}

void vt_DrawCharS(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = vt_GetVertex(2, _pos, _size);
	v[1] = vt_GetVertex(0, _pos, _size);
	v[2] = vt_GetVertex(8, _pos, _size);
	v[3] = vt_GetVertex(6, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 4, v, sfFalse, _clr);
}

void vt_DrawCharT(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vt_GetVertex(0, _pos, _size);
	v[1] = vt_GetVertex(2, _pos, _size);
	v[2] = vt_GetVertex(1, _pos, _size);
	v[3] = vt_GetVertex(7, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 4, v, sfFalse, _clr);
}

void vt_DrawCharU(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = vt_GetVertex(0, _pos, _size);
	v[1] = vt_GetVertex(6, _pos, _size);
	v[2] = vt_GetVertex(8, _pos, _size);
	v[3] = vt_GetVertex(2, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 4, v, sfFalse, _clr);
}

void vt_DrawCharV(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vt_GetVertex(0, _pos, _size);
	v[1] = vt_GetVertex(3, _pos, _size);
	v[2] = vt_GetVertex(7, _pos, _size);
	v[3] = vt_GetVertex(5, _pos, _size);
	v[4] = vt_GetVertex(2, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 5, v, sfFalse, _clr);
}

void vt_DrawCharW(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vt_GetVertex(0, _pos, _size);
	v[1] = vt_GetVertex(6, _pos, _size);
	v[2] = vt_GetVertex(4, _pos, _size);
	v[3] = vt_GetVertex(8, _pos, _size);
	v[4] = vt_GetVertex(2, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 5, v, sfFalse, _clr);
}

void vt_DrawCharX(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vt_GetVertex(0, _pos, _size);
	v[1] = vt_GetVertex(8, _pos, _size);
	v[2] = vt_GetVertex(4, _pos, _size);
	v[3] = vt_GetVertex(6, _pos, _size);
	v[4] = vt_GetVertex(2, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 5, v, sfFalse, _clr);
}

void vt_DrawCharY(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = vt_GetVertex(0, _pos, _size);
	v[1] = vt_GetVertex(4, _pos, _size);
	v[2] = vt_GetVertex(2, _pos, _size);
	v[3] = vt_GetVertex(6, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 4, v, sfFalse, _clr);
}

void vt_DrawCharZ(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = vt_GetVertex(0, _pos, _size);
	v[1] = vt_GetVertex(2, _pos, _size);
	v[2] = vt_GetVertex(6, _pos, _size);
	v[3] = vt_GetVertex(8, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 4, v, sfFalse, _clr);
}

void vt_DrawChar0(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vt_GetVertex(0, _pos, _size);
	v[1] = vt_GetVertex(2, _pos, _size);
	v[2] = vt_GetVertex(8, _pos, _size);
	v[3] = vt_GetVertex(6, _pos, _size);
	v[4] = vt_GetVertex(0, _pos, _size);
	v[5] = vt_GetVertex(8, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 6, v, sfFalse, _clr);
}

void vt_DrawChar1(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[2];
	v[0] = vt_GetVertex(2, _pos, _size);
	v[1] = vt_GetVertex(8, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 2, v, sfFalse, _clr);
}

void vt_DrawChar2(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vt_GetVertex(0, _pos, _size);
	v[1] = vt_GetVertex(2, _pos, _size);
	v[2] = vt_GetVertex(5, _pos, _size);
	v[3] = vt_GetVertex(3, _pos, _size);
	v[4] = vt_GetVertex(6, _pos, _size);
	v[5] = vt_GetVertex(8, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 6, v, sfFalse, _clr);
}

void vt_DrawChar3(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[7];
	v[0] = vt_GetVertex(0, _pos, _size);
	v[1] = vt_GetVertex(2, _pos, _size);
	v[2] = vt_GetVertex(5, _pos, _size);
	v[3] = vt_GetVertex(4, _pos, _size);
	v[4] = vt_GetVertex(5, _pos, _size);
	v[5] = vt_GetVertex(8, _pos, _size);
	v[6] = vt_GetVertex(6, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 7, v, sfFalse, _clr);
}

void vt_DrawChar4(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[5];
	v[0] = vt_GetVertex(0, _pos, _size);
	v[1] = vt_GetVertex(3, _pos, _size);
	v[2] = vt_GetVertex(5, _pos, _size);
	v[3] = vt_GetVertex(2, _pos, _size);
	v[4] = vt_GetVertex(8, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 5, v, sfFalse, _clr);
}

void vt_DrawChar5(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vt_GetVertex(2, _pos, _size);
	v[1] = vt_GetVertex(0, _pos, _size);
	v[2] = vt_GetVertex(3, _pos, _size);
	v[3] = vt_GetVertex(5, _pos, _size);
	v[4] = vt_GetVertex(8, _pos, _size);
	v[5] = vt_GetVertex(6, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 6, v, sfFalse, _clr);
}

void vt_DrawChar6(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vt_GetVertex(2, _pos, _size);
	v[1] = vt_GetVertex(0, _pos, _size);
	v[2] = vt_GetVertex(6, _pos, _size);
	v[3] = vt_GetVertex(8, _pos, _size);
	v[4] = vt_GetVertex(5, _pos, _size);
	v[5] = vt_GetVertex(3, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 6, v, sfFalse, _clr);
}

void vt_DrawChar7(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[3];
	v[0] = vt_GetVertex(0, _pos, _size);
	v[1] = vt_GetVertex(2, _pos, _size);
	v[2] = vt_GetVertex(8, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 3, v, sfFalse, _clr);
}

void vt_DrawChar8(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[7];
	v[0] = vt_GetVertex(3, _pos, _size);
	v[1] = vt_GetVertex(0, _pos, _size);
	v[2] = vt_GetVertex(2, _pos, _size);
	v[3] = vt_GetVertex(8, _pos, _size);
	v[4] = vt_GetVertex(6, _pos, _size);
	v[5] = vt_GetVertex(3, _pos, _size);
	v[6] = vt_GetVertex(5, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 7, v, sfFalse, _clr);
}

void vt_DrawChar9(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[6];
	v[0] = vt_GetVertex(5, _pos, _size);
	v[1] = vt_GetVertex(3, _pos, _size);
	v[2] = vt_GetVertex(0, _pos, _size);
	v[3] = vt_GetVertex(2, _pos, _size);
	v[4] = vt_GetVertex(8, _pos, _size);
	v[5] = vt_GetVertex(6, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 6, v, sfFalse, _clr);
}

void vt_DrawCharDot(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = v_Add(_pos, Vector2f(_size * .375f, _size));
	v[1] = v_Add(_pos, Vector2f(_size * .375f, _size * .75f));
	v[2] = v_Add(_pos, Vector2f(_size * .625f, _size * .75f));
	v[3] = v_Add(_pos, Vector2f(_size * .625f, _size));
	va_DrawPolygon(VA_LINE, "text", 4, v, sfTrue, _clr);
}

void vt_DrawCharComma(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[2];
	v[0] = v_Add(_pos, Vector2f(_size * .25f, _size));
	v[1] = v_Add(_pos, Vector2f(_size * .5f, _size * .75f));
	va_DrawPolygon(VA_LINE, "text", 2, v, sfFalse, _clr);
}

void vt_DrawCharHyphen(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[2];
	v[0] = vt_GetVertex(3, _pos, _size);
	v[1] = vt_GetVertex(5, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 2, v, sfFalse, _clr);
}

void vt_DrawCharApostrophe(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[2];
	v[0] = vt_GetVertex(1, _pos, _size);
	v[1] = vt_GetVertex(4, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 2, v, sfFalse, _clr);
}

void vt_DrawCharAmpersand(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[8];
	v[0] = vt_GetVertex(7, _pos, _size);
	v[1] = vt_GetVertex(1, _pos, _size);
	v[2] = vt_GetVertex(0, _pos, _size);
	v[3] = vt_GetVertex(3, _pos, _size);
	v[4] = vt_GetVertex(5, _pos, _size);
	v[5] = vt_GetVertex(3, _pos, _size);
	v[6] = vt_GetVertex(6, _pos, _size);
	v[7] = vt_GetVertex(8, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 8, v, sfFalse, _clr);
}

void vt_DrawCharBang(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = v_Add(_pos, Vector2f(_size * .375f, _size));
	v[1] = v_Add(_pos, Vector2f(_size * .375f, _size * .75f));
	v[2] = v_Add(_pos, Vector2f(_size * .625f, _size * .75f));
	v[3] = v_Add(_pos, Vector2f(_size * .625f, _size));
	va_DrawPolygon(VA_LINE, "text", 4, v, sfTrue, _clr);

	sfVector2f v2[2];
	v2[0] = vt_GetVertex(1, _pos, _size);
	v2[1] = vt_GetVertex(4, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 2, v2, sfTrue, _clr);
}

void vt_DrawCharLBracket(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = vt_GetVertex(2, _pos, _size);
	v[1] = vt_GetVertex(1, _pos, _size);
	v[2] = vt_GetVertex(7, _pos, _size);
	v[3] = vt_GetVertex(8, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 4, v, sfFalse, _clr);
}

void vt_DrawCharRBracket(sfVector2f _pos, int _size, sfColor _clr) {
	sfVector2f v[4];
	v[0] = vt_GetVertex(0, _pos, _size);
	v[1] = vt_GetVertex(1, _pos, _size);
	v[2] = vt_GetVertex(7, _pos, _size);
	v[3] = vt_GetVertex(6, _pos, _size);
	va_DrawPolygon(VA_LINE, "text", 4, v, sfFalse, _clr);
}

sfVector2f vt_GetVertex(char _id, sfVector2f _pos, int _size) {
	return v_Add(_pos, Vector2f((_id % 3) * (_size * .5f), (int)(_id / 3) * (_size * .5f)));
}