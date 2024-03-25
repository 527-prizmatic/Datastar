/// VA-based text rendering API.
/// Function prefix: vt_

#pragma once
#include "tools.h"
#include "vectors.h"
#include "va_tools.h"
#include "window_manager.h"

/// Draws the given piece of text on the screen via vertex arrays.
/// \param _pos - Position of the text
/// \param _msg - String to display
/// \param _size - Text size, in pixels
/// \param _align - Text alignment. Note that TXT_CENTER and TXT_RIGHT does not work quite correctly with multi-line text.
/// \param _clr - Text color
void vt_DrawText(sfVector2f _pos, char* _msg, int _size, WTxtAlign _align, sfColor _clr);

void vt_DrawChar(sfVector2f _pos, char _char, int _size, sfColor _clr);

void vt_DrawCharA(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharB(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharC(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharD(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharE(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharF(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharG(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharH(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharI(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharJ(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharK(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharL(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharM(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharN(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharO(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharP(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharQ(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharR(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharS(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharT(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharU(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharV(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharW(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharX(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharY(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawCharZ(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawChar0(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawChar1(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawChar2(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawChar3(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawChar4(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawChar5(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawChar6(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawChar7(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawChar8(sfVector2f _pos, int _size, sfColor _clr);
void vt_DrawChar9(sfVector2f _pos, int _size, sfColor _clr);