#include "texture_manager.h"

void tex_Init() {
	tex_Sentinel = malloc(sizeof(TexWrapper));
	if (tex_Sentinel == NULL) {
		log_LogStr(LOG_FATAL, "Texture engine initialization error - insufficient memory", sfTrue, sfTrue);
		return;
	}
	tex_Sentinel->prev = NULL;
	tex_Sentinel->next = NULL;
	tex_Sentinel->tex  = NULL;
	tex_Sentinel->id   = NULL;

	log_LogStr(LOG_INFO, "Texture engine initialization complete", sfTrue, sfTrue);
}

void tex_Preload(char* _path, char* _id) {
	TexWrapper* itr = tex_Sentinel->next;
	while (itr != NULL) {
		if (!strcmp(itr->id, _id)) {
			log_LogStr(LOG_WARN, "Texture preloading error - texture with given ID already exists:", sfTrue, sfFalse);
			log_LogStr(LOG_WARN, _id, sfFalse, sfTrue);
			return;
		}
		itr = itr->next;
	}

	TexWrapper* new = malloc(sizeof(TexWrapper));
	if (new == NULL) {
		log_LogStr(LOG_ERROR, "Texture preloading error - insufficient memory:", sfTrue, sfFalse);
		log_LogStr(LOG_ERROR, _id, sfFalse, sfTrue);
		return;
	}
	new->prev = NULL;
	new->next = NULL;

	char* fullpath = calloc(strlen(_path) + strlen(PATH_TEXTURES) + 1, sizeof(char));
	if (fullpath == NULL) {
		log_LogStr(LOG_ERROR, "Texture preloading error - insufficient memory:", sfTrue, sfFalse);
		log_LogStr(LOG_ERROR, _id, sfFalse, sfTrue);
		return;
	}
	strcpy(fullpath, PATH_TEXTURES);
	strcat(fullpath, _path);
	new->tex = sfTexture_createFromFile(fullpath, NULL);
	free(fullpath);

	new->id = calloc(strlen(_id) + 1, sizeof(char));
	if (new->id == NULL) {
		log_LogStr(LOG_ERROR, "Texture preloading error - insufficient memory:", sfTrue, sfFalse);
		log_LogStr(LOG_ERROR, _id, sfFalse, sfTrue);
		return;
	}
	strcpy(new->id, _id);
	tex_Add(new);
}

void tex_Add(TexWrapper* _tex) {
	TexWrapper* n = tex_Sentinel->next;
	tex_Sentinel->next = _tex;
	_tex->prev = tex_Sentinel;
	_tex->next = n;
	if (n != NULL) n->prev = _tex;
}

sfTexture* tex_Fetch(char* _id) {
	TexWrapper* itr = tex_Sentinel->next;
	while (itr != NULL) {
		if (!strcmp(itr->id, _id)) return itr->tex;
		itr = itr->next;
	}
	log_LogStr(LOG_ERROR, "Texture loading error - unknown id:", sfTrue, sfFalse);
	log_LogStr(LOG_ERROR, _id, sfFalse, sfTrue);
	return NULL;
}

TexWrapper* tex_PopPtr(TexWrapper* _tex) {
	sfTexture_destroy(_tex->tex);
	free(_tex->id);

	TexWrapper* p = _tex->prev;
	TexWrapper* n = _tex->next;

	p->next = n;
	if (n != NULL) n->prev = p;
	free(_tex);
	return n;
}

void tex_Unload(char* _id) {
	TexWrapper* itr = tex_Sentinel->next;
	while (itr != NULL) {
		if (!strcmp(itr->id, _id)) {
			itr = tex_PopPtr(itr);
			return;
		}
		itr = itr->next;
	}
	log_LogStr(LOG_ERROR, "Texture unloading error - unknown id:", sfTrue, sfFalse);
	log_LogStr(LOG_ERROR, _id, sfFalse, sfTrue);
}

void tex_ClearBuffer() {
	TexWrapper* itr = tex_Sentinel->next;
	while (itr != NULL) itr = tex_PopPtr(itr);
	log_LogStr(LOG_INFO, "Texture buffer cleared", sfTrue, sfTrue);
}