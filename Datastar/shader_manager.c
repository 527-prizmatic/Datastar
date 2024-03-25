#include "shader_manager.h"

void shd_Init() {
	shd_Sentinel = malloc(sizeof(ShdWrapper));
	if (shd_Sentinel == NULL) {
		log_LogStr(LOG_FATAL, "Shader engine initialization error - insufficient memory", sfTrue, sfTrue);
		return;
	}
	shd_Sentinel->prev = NULL;
	shd_Sentinel->next = NULL;
	memset(&(shd_Sentinel->rs), 0, sizeof(sfRenderStates));
	shd_Sentinel->id = NULL;

	log_LogStr(LOG_INFO, "Shader engine initialization complete", sfTrue, sfTrue);
}

void shd_Preload(char* _path_v, char* _path_f, char* _id) {
	ShdWrapper* itr = shd_Sentinel->next;
	while (itr != NULL) {
		if (!strcmp(itr->id, _id)) {
			log_LogStr(LOG_WARN, "Shader preloading error - shader with given ID already exists:", sfTrue, sfFalse);
			log_LogStr(LOG_WARN, _id, sfFalse, sfTrue);
			return;
		}
		itr = itr->next;
	}

	ShdWrapper* new = malloc(sizeof(ShdWrapper));
	if (new == NULL) {
		log_LogStr(LOG_ERROR, "Shader preloading error - insufficient memory:", sfTrue, sfFalse);
		log_LogStr(LOG_ERROR, _id, sfFalse, sfTrue);
		return;
	}
	new->prev = NULL;
	new->next = NULL;

	char* fullpathV;
	if (_path_v == NULL) fullpathV = NULL;
	else {
		fullpathV = calloc(strlen(_path_v) + strlen(PATH_SHADERS) + 1, sizeof(char));
		if (fullpathV == NULL) {
			log_LogStr(LOG_ERROR, "Shader preloading error - insufficient memory:", sfTrue, sfFalse);
			log_LogStr(LOG_ERROR, _id, sfFalse, sfTrue);
			return;
		}
		strcpy(fullpathV, PATH_SHADERS);
		strcat(fullpathV, _path_v);
	}

	char* fullpathF;
	if (_path_f == NULL) fullpathF = NULL;
	else {
		fullpathF = calloc(strlen(_path_f) + strlen(PATH_SHADERS) + 1, sizeof(char));
		if (fullpathF == NULL) {
			log_LogStr(LOG_ERROR, "Shader preloading error - insufficient memory:", sfTrue, sfFalse);
			log_LogStr(LOG_ERROR, _id, sfFalse, sfTrue);
			return;
		}
		strcpy(fullpathF, PATH_SHADERS);
		strcat(fullpathF, _path_f);
	}

	new->rs.shader = sfShader_createFromFile(fullpathV, NULL, fullpathF);
	new->rs.blendMode = sfBlendAlpha;
	new->rs.transform = sfTransform_Identity;
	new->rs.texture = NULL;

	free(fullpathV);
	free(fullpathF);

	new->id = calloc(strlen(_id) + 1, sizeof(char));
	if (new->id == NULL) {
		log_LogStr(LOG_ERROR, "Shader preloading error - insufficient memory:", sfTrue, sfFalse);
		log_LogStr(LOG_ERROR, _id, sfFalse, sfTrue);
		return;
	}
	strcpy(new->id, _id);
	shd_Add(new);
}

void shd_Add(ShdWrapper* _shd) {
	ShdWrapper* n = shd_Sentinel->next;
	shd_Sentinel->next = _shd;
	_shd->prev = shd_Sentinel;
	_shd->next = n;
	if (n != NULL) n->prev = _shd;
}

sfRenderStates* shd_FetchState(char* _id) {
	if (_id == NULL) return NULL;
	ShdWrapper* itr = shd_Sentinel->next;
	while (itr != NULL) {
		if (!strcmp(itr->id, _id)) return &(itr->rs);
		itr = itr->next;
	}
	log_LogStr(LOG_ERROR, "Shader loading error - unknown id:", sfTrue, sfFalse);
	log_LogStr(LOG_ERROR, _id, sfFalse, sfTrue);
	return NULL;
}

const sfShader* shd_FetchShader(char* _id) { return _id ? shd_FetchState(_id)->shader : NULL; }

ShdWrapper* shd_PopPtr(ShdWrapper* _shd) {
	sfShader_destroy(_shd->rs.shader);
	free(_shd->id);

	ShdWrapper* p = _shd->prev;
	ShdWrapper* n = _shd->next;

	p->next = n;
	if (n != NULL) n->prev = p;
	free(_shd);
	return n;
}

void shd_ClearBuffer() {
	ShdWrapper* itr = shd_Sentinel->next;
	while (itr != NULL) itr = shd_PopPtr(itr);
	log_LogStr(LOG_INFO, "Shader buffer cleared", sfTrue, sfTrue);
}