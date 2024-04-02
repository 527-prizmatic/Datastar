/// (C) 2024 The Prizmanager
/// Author - J.Sebastien Toussaint
/// 
/// Misc rendering functions.
/// Function prefix: w_

#pragma once
#include "tools.h"
#include "texture_manager.h"
#include "keyboard.h"
#include "logger.h"

/// Initializes the window handling API.
void w_Init(char* _title, sfVideoMode _mode, unsigned int _framerate);

/// Creates a new render window.
void w_Create();

/// Destroys the current render window.
void w_Destroy();

sfBool w_IsClosed();
sfBool w_IsFullscreen();
sfBool w_IsPaused();
sfBool w_HasFocus();
W_Window* w_Get();

/// Initiates the rendering phase and clears the contents of the render window.
void w_RenderStart();

/// Ends the rendering phase and displays the render window to screen.
void w_RenderEnd();

/// Toggles fullscreen.
void w_ToggleFS();

/// Sets fullscreen to the given value.
void w_SetFS(sfBool _fs);

/// Toggles pause.
void w_TogglePause();

/// Sets a new render view.
void w_SetView(sfView* _v);

/// Resets the window's render view.
void w_ResetView();

/// Computes tick updates for the render window.
void w_Update();

/// TODO MAKE AN ACTUAL MOUSE MANAGER FOR THOSE

/// Gets mouse position. Returns (-65536.f, -65536.f) if the render window doesn't have focus.
sfVector2f w_GetMousePos();

/// Tests whether the left mouse button has been clicked.
sfBool w_LeftClick();


/// === RENDERING QUERY MANAGER === ///
/// Function prefix: rq_

#define RQ_POS_CENTERED Vector2f(960.f, 540.f)

#define RQ_SCALE_DEFAULT Vector2f(1.f, 1.f)
#define RQ_SCALE_HALF Vector2f(.5f, .5f)
#define RQ_SCALE_DOUBLE Vector2f(2.f, 2.f)
#define RQ_SCALE_FLIP_H Vector2f(-1.f, 1.f)
#define RQ_SCALE_FLIP_V Vector2f(1.f, -1.f)
#define RQ_SCALE_ROTATE_180 Vector2f(-1.f, -1.f)
#define RQ_SCALE(x) Vector2f(x, x)

#define RQ_TEX_NORECT IntRect(-1, -1, -1, -1)

#define RQ_SPRCLR_NONE sfWhite

typedef enum {
	RQ_SPRITE = 1,
	RQ_CIRCLE = 2,
	RQ_RECTANGLE = 3,
	RQ_TEXT = 4,
	RQ_VA = 5
} RQType;

typedef enum {
	TXT_LEFT,
	TXT_CENTER,
	TXT_RIGHT
} WTxtAlign;

typedef struct {
	RQType type;
	sfVector2f pos;
	sfTexture* tex;
	sfIntRect texRect;
	sfVector2f origin;
	sfVector2f scale;
	float rot;
	sfColor clr;
} RQDataSpr;

typedef struct {
	RQType type;
	sfVector2f pos;
	float rds;
	sfVector2f origin;
	sfVector2f scale;
	sfColor fillClr;
} RQDataCrc;

typedef struct {
	RQType type;
	sfVector2f pos;
	sfVector2f dims;
	sfVector2f origin;
	sfVector2f scale;
	float rot;
	sfColor fillClr;
} RQDataRct;

typedef struct {
	RQType type;
	sfVector2f pos;
	sfFont* font;
	int size;
	sfColor clr;
	char* msg;
	WTxtAlign align;
} RQDataTxt;

typedef struct {
	sfRenderStates* rState;
	union {
		RQType type;
		RQDataSpr dataSp;
		RQDataCrc dataC;
		RQDataRct dataR;
		RQDataTxt dataT;
	};
} RQuery;

/// Initializes the render query engine.
void rq_Init();

/// This function allows to send a display query the game's rendering engine.
/// It takes as argument the type of query (i.e. the type of SFML object to render) followed by a variable number of arguments, specifying different properties of the rendered object.
/// \param For a RQ_SPRITE - Position (2D vector), texture ID (string), UVs (intRect), origin (2D vector), rotation (float), scale (2D vector), overlay color (color)
/// \param For a RQ_CIRCLE - Position (2D vector), radius (float), origin (2D vector), fill color (color), scale (2D vector)
/// \param For a RQ_RECTANGLE - Position (2D vector), dimensions (2D vector), origin (2D vector), fill color (color), rotation (float), scale (2D vector)
/// \param For a RQ_TEXT - Position (2D vector), font (font object), font size (int), text color (color), message (string), text alignment (WTxtAlign)
/// \param For a RQ_VA - Vertex array
void rq_Draw(RQType _type, sfRenderStates* _rs, ...);

/// Flushes a render query.
void rq_RenderQuery(RQuery _query);

/// Returns the bounding box of the last render query of the given type.
/// This needs some heavy refactoring, doing it that way makes no sense.
sfFloatRect rq_GetBB(RQType _type);