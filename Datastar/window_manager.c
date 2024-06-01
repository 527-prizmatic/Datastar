#include "window_manager.h"
#include "savefile.h"

void w_Init(char* _title, sfVideoMode _mode, unsigned int _framerate) {
	window.title = calloc(strlen(_title), sizeof(char));
	if (!window.title) window.title = "Window";
	else {
		if (_title != '\0') strcpy(window.title, _title);
		else strcpy(window.title, "Window");
	}

	window.rspr = sfSprite_create();
	sfSprite_setPosition(window.rspr, Vector2f(0.f, _mode.height));

	window.rt = sfRenderTexture_create(_mode.width, _mode.height, sfFalse);
	window.mode = _mode;
	window.framerate = _framerate;
	window.isFullscreen = sfFalse;
	window.isPaused = sfFalse;
	log_LogStr(LOG_INFO, "Render window initialization complete", sfTrue, sfTrue);
	rq_Init();
}

sfBool w_IsClosed() { return !sfRenderWindow_isOpen(window.rw); }
sfBool w_IsFullscreen() { return window.isFullscreen; }
sfBool w_IsPaused() { return window.isPaused; }
sfBool w_HasFocus() { return sfRenderWindow_hasFocus(window.rw); }

void w_RenderStart() {
	sfRenderWindow_clear(window.rw, sfBlack);
	sfRenderTexture_clear(window.rt, sfTransparent);
}

void w_RenderEnd() {
	sfSprite_setTexture(window.rspr, sfRenderTexture_getTexture(window.rt), sfTrue);
	sfSprite_setScale(window.rspr, RQ_SCALE_FLIP_V);
	sfShader_setTextureUniform(shd_FetchShader("blur"), "u_TexBase", sfRenderTexture_getTexture(window.rt));
	sfShader_setVec2Uniform(shd_FetchShader("blur"), "u_Res", Vector2f(window.mode.width, window.mode.height));
	sfRenderWindow_drawSprite(window.rw, window.rspr, NULL);
	sfRenderWindow_display(window.rw);
}

void w_Create() {
	window.rw = sfRenderWindow_create(window.mode, window.title, window.isFullscreen ? sfFullscreen : sfDefaultStyle, NULL);

	if (window.rw == NULL) {
		log_LogStr(LOG_FATAL, "Game window creation error: insufficient memory", sfTrue, sfTrue);
		return;
	}
	sfRenderWindow_setFramerateLimit(window.rw, window.framerate);
	if (w_IsFullscreen()) sfRenderWindow_setMouseCursorVisible(window.rw, sfFalse);
	log_LogStr(LOG_INFO, "Successfully created new game window", sfTrue, sfTrue);
}

void w_Destroy() {
	sfRenderWindow_close(window.rw);
}

void w_ToggleFS() {
	window.isFullscreen = !window.isFullscreen;
	w_Destroy();
	w_Create();
}

void w_SetFS(sfBool _fs) {
	if (window.isFullscreen != _fs) w_ToggleFS();
}

void w_TogglePause() { window.isPaused = !window.isPaused; }

void w_SetView(sfView* _v) { sfRenderWindow_setView(window.rw, _v); }
void w_ResetView() { sfRenderWindow_setView(window.rw, sfRenderWindow_getDefaultView(window.rw)); }

void w_Update() {
	restartClock();
	while (sfRenderWindow_pollEvent(window.rw, &(window.e))) {
		if (window.e.type == sfEvtClosed) w_Destroy();
		if (window.e.type == sfEvtJoystickConnected) {
			log_LogStr(LOG_INFO, "Controller with ID", sfTrue, sfFalse);
			log_LogInt(LOG_INFO, window.e.joystickConnect.joystickId, sfFalse, sfFalse);
			log_LogStr(LOG_INFO, "connected", sfFalse, sfTrue);
		}
		if (window.e.type == sfEvtJoystickDisconnected) {
			log_LogStr(LOG_INFO, "Controller with ID", sfTrue, sfFalse);
			log_LogInt(LOG_INFO, window.e.joystickConnect.joystickId, sfFalse, sfFalse);
			log_LogStr(LOG_INFO, "disconnected", sfFalse, sfTrue);
		}
	}
	if (kb_TestPress(sfKeyF11)) {
		w_ToggleFS();
		sav_Save();
	}
	sfRenderWindow_setFramerateLimit(window.rw, window.framerate);

	if (kb_TestPress(sfKeyP)) window.framerate++;
}

sfVector2f w_GetMousePos() {
	if (!w_HasFocus()) return Vector2f(-65536.f, -65536.f);
	sfVector2i m = sfMouse_getPositionRenderWindow(window.rw);
	return Vector2f(m.x, m.y);
}

sfBool w_LeftClick() {
	static sfBool click = sfFalse;
	if (sfMouse_isButtonPressed(sfMouseLeft) && w_HasFocus()) {
		if (!click) {
			click = sfTrue;
			return sfTrue;
		}
	}
	else click = sfFalse;
	return sfFalse;
}


/// === RENDERING QUERY MANAGER === ///

sfSprite* rq_S;
sfCircleShape* rq_C;
sfRectangleShape* rq_R;
sfText* rq_T;

void rq_Init() {
	rq_S = sfSprite_create();
	rq_C = sfCircleShape_create();
	rq_R = sfRectangleShape_create();
	rq_T = sfText_create();
	if (!rq_S || !rq_C || !rq_R || !rq_T) {
		log_LogStr(LOG_FATAL, "Render query engine initialization error: insufficient memory", sfTrue, sfTrue);
		return;
	}
	log_LogStr(LOG_INFO, "Render query engine initialization complete", sfTrue, sfTrue);
}

void rq_Draw(RQType _type, sfRenderStates* _rs, ...) {
	va_list args;
	RQuery rq;
	rq.type = _type;
	rq.rState = _rs;

	va_start(args, _rs);
	if (_type == RQ_SPRITE) {
		rq.dataSp.pos = va_arg(args, sfVector2f);
		rq.dataSp.tex = tex_Fetch(va_arg(args, char*));
		rq.dataSp.texRect = va_arg(args, sfIntRect);
		rq.dataSp.origin = va_arg(args, sfVector2f);
		rq.dataSp.rot = va_arg(args, double);
		rq.dataSp.scale = va_arg(args, sfVector2f);
		rq.dataSp.clr = va_arg(args, sfColor);
	}
	else if (_type == RQ_CIRCLE) {
		rq.dataC.pos = va_arg(args, sfVector2f);
		rq.dataC.rds = va_arg(args, double);
		rq.dataC.origin = va_arg(args, sfVector2f);
		rq.dataC.fillClr = va_arg(args, sfColor);
		rq.dataC.scale = va_arg(args, sfVector2f);
	}
	else if (_type == RQ_RECTANGLE) {
		rq.dataR.pos = va_arg(args, sfVector2f);
		rq.dataR.dims = va_arg(args, sfVector2f);
		rq.dataR.origin = va_arg(args, sfVector2f);
		rq.dataR.fillClr = va_arg(args, sfColor);
		rq.dataR.rot = va_arg(args, double);
		rq.dataR.scale = va_arg(args, sfVector2f);
	}
	else if (_type == RQ_TEXT) {
		rq.dataT.pos = va_arg(args, sfVector2f);
		rq.dataT.font = va_arg(args, sfFont*);
		rq.dataT.size = va_arg(args, int);
		rq.dataT.clr = va_arg(args, sfColor);
		rq.dataT.msg = va_arg(args, char*);
		rq.dataT.align = va_arg(args, WTxtAlign);
	}
	else if (_type == RQ_VA) {
		sfRenderWindow_drawVertexArray(window.rw, va_arg(args, sfVertexArray*), _rs);
		va_end(args);
		return;
	}
	else {
		log_LogStr(LOG_ERROR, "Render query error - unknown query type", sfTrue, sfTrue);
		return;
	}

	va_end(args);
	rq_RenderQuery(rq);
}

void rq_RenderQuery(RQuery _query) {
	if (_query.type == RQ_SPRITE) {
		sfSprite_setPosition(rq_S, _query.dataSp.pos);
		sfSprite_setTexture(rq_S, _query.dataSp.tex, sfTrue);
		if (!(_query.dataSp.texRect.top == -1 && _query.dataSp.texRect.left == -1 && _query.dataSp.texRect.width == -1 && _query.dataSp.texRect.height == -1))
			sfSprite_setTextureRect(rq_S, _query.dataSp.texRect);
		sfSprite_setOrigin(rq_S, _query.dataSp.origin);
		sfSprite_setScale(rq_S, _query.dataSp.scale);
		sfSprite_setRotation(rq_S, _query.dataSp.rot);
		sfSprite_setColor(rq_S, _query.dataSp.clr);
		sfRenderWindow_drawSprite(window.rw, rq_S, _query.rState);
	}
	else if (_query.type == RQ_CIRCLE) {
		sfCircleShape_setPosition(rq_C, _query.dataC.pos);
		sfCircleShape_setRadius(rq_C, _query.dataC.rds);
		sfCircleShape_setOrigin(rq_C, _query.dataC.origin);
		sfCircleShape_setScale(rq_C, _query.dataC.scale);
		sfCircleShape_setFillColor(rq_C, _query.dataC.fillClr);
		sfRenderWindow_drawCircleShape(window.rw, rq_C, _query.rState);
	}
	else if (_query.type == RQ_RECTANGLE) {
		sfRectangleShape_setPosition(rq_R, _query.dataR.pos);
		sfRectangleShape_setSize(rq_R, _query.dataR.dims);
		sfRectangleShape_setOrigin(rq_R, _query.dataR.origin);
		sfRectangleShape_setScale(rq_R, _query.dataR.scale);
		sfRectangleShape_setRotation(rq_R, _query.dataR.rot);
		sfRectangleShape_setFillColor(rq_R, _query.dataR.fillClr);
		sfRenderWindow_drawRectangleShape(window.rw, rq_R, _query.rState);
	}
	else if (_query.type == RQ_TEXT) {
		sfText_setPosition(rq_T, _query.dataT.pos);
		sfText_setFont(rq_T, _query.dataT.font);
		sfText_setCharacterSize(rq_T, _query.dataT.size);
		sfText_setFillColor(rq_T, _query.dataT.clr);
		sfText_setString(rq_T, _query.dataT.msg);
		sfFloatRect bounds = sfText_getGlobalBounds(rq_T);
		if (_query.dataT.align == TXT_CENTER) sfText_setOrigin(rq_T, Vector2f(bounds.width / 2.f, 0.f));
		else if (_query.dataT.align == TXT_RIGHT) sfText_setOrigin(rq_T, Vector2f(bounds.width, 0.f));
		else sfText_setOrigin(rq_T, NULLVECTF);

		sfRenderWindow_drawText(window.rw, rq_T, _query.rState);
	}
	else log_LogStr(LOG_ERROR, "Render query error - malformed query", sfTrue, sfTrue);
}

sfFloatRect rq_GetBB(RQType _type) {
	if (_type == RQ_SPRITE) return sfSprite_getGlobalBounds(rq_S);
	else if (_type == RQ_CIRCLE) return sfCircleShape_getGlobalBounds(rq_C);
	else if (_type == RQ_RECTANGLE) return sfRectangleShape_getGlobalBounds(rq_R);
	else if (_type == RQ_TEXT) return sfText_getGlobalBounds(rq_T);
	else return FloatRect(-1.f, -1.f, -1.f, -1.f);
}