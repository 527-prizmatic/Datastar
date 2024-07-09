/// VA-based text rendering API.
/// Function prefix: vt_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "va_tools.h"
#include "window_manager.h"

typedef struct VtnVaText {
	sfRenderTexture* rt;
} VtnVaText;

VtnVaText* vtn_Text(char* _msg, int _size, enum WTxtAlign _align);
void vtn_Draw(VtnVaText* _txt, sfVector2f _pos, sfColor _clr);
void vtn_DestroyText(VtnVaText* _vt);

/// Draws the given piece of text on the screen via vertex arrays.
/// \param _pos - Position of the text
/// \param _msg - String to display
/// \param _size - Text size, in pixels
/// \param _align - Text alignment. Note that TXT_CENTER and TXT_RIGHT do not work quite correctly with multi-line text.
/// \param _clr - Text color
void vtn_DrawText(sfRenderTexture* _rt, sfVector2f _pos, char* _msg, int _ll, int _size, enum WTxtAlign _align, sfColor _clr);

void vtn_DrawChar(sfRenderTexture* _rt, sfVector2f _pos, char _char, int _size, sfColor _clr);

void vtn_DrawCharA(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharB(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharC(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharD(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharE(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharF(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharG(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharH(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharI(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharJ(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharK(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharL(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharM(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharN(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharO(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharP(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharQ(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharR(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharS(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharT(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharU(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharV(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharW(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharX(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharY(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharZ(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawChar0(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawChar1(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawChar2(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawChar3(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawChar4(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawChar5(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawChar6(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawChar7(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawChar8(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawChar9(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharDot(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharComma(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharHyphen(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharApostrophe(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharAmpersand(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharBang(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharLBracket(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharRBracket(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);
void vtn_DrawCharSlash(sfRenderTexture* _rt, sfVector2f _pos, int _size, sfColor _clr);