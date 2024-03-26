#include "sound_manager.h"

#define PATH_TYPE(x) (x == SND_SND) ? PATH_SOUNDS : PATH_MUSICS

float snd_VolMaster;
float snd_VolSnd;
float snd_VolMus;

SndWrapper* snd_NowPlaying;
sfSound* snd_Sound;
SndMusState snd_MusState;

float snd_VolMusFade;

/// Technical function to verify if the given ID corresponds to a valid music object.
SndWrapper* snd_IsValidMusic(char* _id);

void snd_Init() {
	snd_Sentinel = malloc(sizeof(SndWrapper));
	if (snd_Sentinel == NULL) {
		log_LogStr(LOG_FATAL, "Sound engine initialization error - insufficient memory", sfTrue, sfTrue);
		return;
	}
	snd_Sentinel->prev = NULL;
	snd_Sentinel->next = NULL;
	snd_Sentinel->type = SND_SENTINEL;
	snd_Sentinel->snd = NULL;
	snd_Sentinel->id = NULL;

	snd_NowPlaying = NULL;
	snd_Sound = sfSound_create();

	snd_StrSentinel = malloc(sizeof(SndStream));
	if (snd_StrSentinel == NULL) {
		log_LogStr(LOG_FATAL, "Sound engine initialization error - insufficient memory", sfTrue, sfTrue);
		return;
	}
	snd_StrSentinel->prev = NULL;
	snd_StrSentinel->next = NULL;
	snd_StrSentinel->snd = NULL;

	snd_VolMaster = 100.f;
	snd_VolSnd = 100.f;
	snd_VolMus = 100.f;

	snd_MusState = SND_STOPPED;
	snd_VolMusFade = 100.f;

	log_LogStr(LOG_INFO, "Sound engine initialization complete", sfTrue, sfTrue);
}

void snd_Preload(SndType _type, char* _path, char* _id) {
	if (_type == SND_SENTINEL) {
		log_LogStr(LOG_WARN, "Sound preloading error - attempted to create sound object as reserved type SND_SENTINEL, defaulting to SND_SND:", sfTrue, sfFalse);
		log_LogStr(LOG_WARN, _id, sfFalse, sfTrue);
		_type = SND_SND;
	}

	SndWrapper* itr = snd_Sentinel->next;
	while (itr != NULL) {
		if (!strcmp(itr->id, _id)) {
			log_LogStr(LOG_WARN, "Sound preloading error -", sfTrue, sfFalse);
			if (itr->type == SND_SND) log_LogStr(LOG_WARN, "sound with given ID already exists:", sfFalse, sfFalse);
			else log_LogStr(LOG_WARN, "music with given ID already exists:", sfFalse, sfFalse);
			log_LogStr(LOG_WARN, _id, sfFalse, sfTrue);
			return;
		}
		itr = itr->next;
	}

	SndWrapper* new = malloc(sizeof(SndWrapper));
	if (new == NULL) {
		log_LogStr(LOG_WARN, "Sound preloading error - insufficient memory:", sfTrue, sfFalse);
		log_LogStr(LOG_WARN, _id, sfFalse, sfTrue);
		return;
	}
	new->prev = NULL;
	new->next = NULL;
	new->type = _type;

	char* fullpath = calloc(strlen(_path) + strlen(PATH_TYPE(_type)) + 1, sizeof(char));
	if (fullpath == NULL) {
		log_LogStr(LOG_WARN, "Sound preloading error - insufficient memory:", sfTrue, sfFalse);
		log_LogStr(LOG_WARN, _id, sfFalse, sfTrue);
		free(new);
		return;
	}
	strcpy(fullpath, PATH_TYPE(_type));
	strcat(fullpath, _path);
	
	if (_type == SND_SND) new->snd = sfSoundBuffer_createFromFile(fullpath);
	else new->mus = sfMusic_createFromFile(fullpath);
	
	free(fullpath);

	new->id = calloc(strlen(_id) + 1, sizeof(char));
	if (new->id == NULL) {
		log_LogStr(LOG_WARN, "Sound preloading error - insufficient memory:", sfTrue, sfFalse);
		log_LogStr(LOG_WARN, _id, sfFalse, sfTrue);
		if (_type == SND_SND) sfSoundBuffer_destroy(new->snd);
		else sfMusic_destroy(new->mus);
		free(new);
		return;
	}
	strcpy(new->id, _id);
	snd_Add(new);
}

void snd_Add(SndWrapper* _snd) {
	SndWrapper* n = snd_Sentinel->next;
	snd_Sentinel->next = _snd;
	_snd->prev = snd_Sentinel;
	_snd->next = n;
	if (n != NULL) n->prev = _snd;
}

SndWrapper* snd_PopPtr(SndWrapper* _snd) {
	if (_snd->type == SND_SND) sfSoundBuffer_destroy(_snd->snd);
	else sfMusic_destroy(_snd->mus);
	free(_snd->id);

	SndWrapper* p = _snd->prev;
	SndWrapper* n = _snd->next;

	p->next = n;
	if (n != NULL) n->prev = p;
	free(_snd);
	return n;
}

void snd_Update() {
	if (snd_NowPlaying != NULL) sfMusic_setVolume(snd_NowPlaying->mus, snd_VolMaster * snd_VolMus * snd_VolMusFade * .0001f);

	SndStream* itr2 = snd_StrSentinel->next;
	while (itr2 != NULL) {
		sfSound_setVolume(itr2->snd, snd_VolMaster * snd_VolSnd * .01f);
		if (sfSound_getStatus(itr2->snd) == sfStopped) itr2 = snd_StrPopPtr(itr2);
		else itr2 = itr2->next;
	}

	switch (snd_MusState) {
		case SND_STOPPED:
			snd_VolMusFade = 0.f;
			snd_NowPlaying = NULL;
			break;

		case SND_PLAYING: snd_VolMusFade = 100.f; break;

		case SND_FADEIN:
			snd_VolMusFade += 50.f * getDeltaTime();
			if (snd_VolMusFade >= 100.f) {
				snd_VolMusFade = 100.f;
				snd_MusState = SND_PLAYING;
			}
			break;

		case SND_FADEOUT:
			snd_VolMusFade -= 50.f * getDeltaTime();
			if (snd_VolMusFade <= 0.f) {
				snd_VolMusFade = 0.f;
				snd_MusState = SND_STOPPED;
			}
			break;
	}
}

void mus_Play(char* _id) {
	SndWrapper* itr = snd_IsValidMusic(_id);
	if (itr == NULL) return;

	mus_Stop();

	sfMusic_play(itr->mus);
	snd_NowPlaying = itr;
	snd_MusState = SND_PLAYING;
}

void mus_FadeIn(char* _id) {
	SndWrapper* itr = snd_IsValidMusic(_id);
	if (itr == NULL) return;

	sfMusic_play(itr->mus);
	snd_NowPlaying = itr;
	snd_MusState = SND_FADEIN;
}

void mus_FadeOut() { snd_MusState = SND_FADEOUT; }

void mus_Stop() {
	SndWrapper* itr = snd_Sentinel->next;
	while (itr != NULL) {
		if (itr->type == SND_MUS) sfMusic_stop(itr->mus);
		itr = itr->next;
	}

	snd_MusState = SND_STOPPED;
}

void snd_Play(char* _id) {
	SndWrapper* itr = snd_Sentinel->next;
	while (itr != NULL) {
		if (!strcmp(itr->id, _id)) break;
		itr = itr->next;
	}

	if (itr == NULL) {
		printf("Error while playing sound: sound does not exist: \"%s\"\n", _id);
		return;
	}

	if (itr->type != SND_SND) {
		printf("Error while playing music: requested item is not sound: \"%s\"\n", _id);
		return;
	}

	snd_StrAdd(itr);
}

void snd_StrAdd(SndWrapper* _snd) {
	SndStream* s = malloc(sizeof(SndStream));
	if (s == NULL) {
		log_LogStr(LOG_ERROR, "Sound loading error - insufficient memory:", sfTrue, sfFalse);
		log_LogStr(LOG_ERROR, _snd->id, sfFalse, sfTrue);
		return;
	}

	s->snd = sfSound_create();
	if (s->snd == NULL) {
		log_LogStr(LOG_ERROR, "Sound loading error - insufficient memory:", sfTrue, sfFalse);
		log_LogStr(LOG_ERROR, _snd->id, sfFalse, sfTrue);
		return;
	}

	sfSound_setBuffer(s->snd, _snd->snd);
	SndStream* n = snd_StrSentinel->next;
	snd_StrSentinel->next = s;
	s->prev = snd_StrSentinel;
	s->next = n;
	if (n != NULL) n->prev = s;

	sfSound_play(s->snd);
}

SndStream* snd_StrPopPtr(SndStream* _snd) {
	sfSound_destroy(_snd->snd);

	SndStream* p = _snd->prev;
	SndStream* n = _snd->next;

	p->next = n;
	if (n != NULL) n->prev = p;
	free(_snd);
	return n;
}

void vol_SetMaster(float _vol) { snd_VolMaster = _vol; }
void vol_SetSnd(float _vol) { snd_VolSnd = _vol; }
void vol_SetMus(float _vol) { snd_VolMus = _vol; }
float vol_GetMaster() { return snd_VolMaster; }
float vol_GetSnd() { return snd_VolSnd; }
float vol_GetMus() { return snd_VolMus; }
SndMusState snd_GetMusicState() { return snd_MusState; }

void mus_SetPos(char* _id, float _time) {
	SndWrapper* mus = snd_IsValidMusic(_id);
	if (!mus) return;
	sfMusic_setPlayingOffset(mus->mus, (sfTime) { _time * 1e6f });
}

SndWrapper* snd_IsValidMusic(char* _id) {
	SndWrapper* itr = snd_Sentinel->next;
	while (itr != NULL) {
		if (!strcmp(itr->id, _id)) break;
		itr = itr->next;
	}

	if (itr == NULL) {
		log_LogStr(LOG_ERROR, "Music loading error - music does not exist:", sfTrue, sfFalse);
		log_LogStr(LOG_ERROR, _id, sfFalse, sfTrue);
		return NULL;
	}

	if (itr->type != SND_MUS) {
		log_LogStr(LOG_ERROR, "Music loading error - requested item is not music:", sfTrue, sfFalse);
		log_LogStr(LOG_ERROR, _id, sfFalse, sfTrue);
		return NULL;
	}

	return itr;
}

void snd_Unload(char* _id) {
	SndWrapper* itr = snd_Sentinel->next;
	while (itr != NULL) {
		if (!strcmp(itr->id, _id)) {
			if (snd_NowPlaying == itr) snd_NowPlaying = NULL;
			itr = snd_PopPtr(itr);
			log_LogStr(LOG_INFO, "Successfully unloaded sound:", sfTrue, sfFalse);
			log_LogStr(LOG_INFO, _id, sfFalse, sfTrue);
			return;
		}
	}

	log_LogStr(LOG_ERROR, "Sound unloading error - requested item does not exist:", sfTrue, sfFalse);
	log_LogStr(LOG_ERROR, _id, sfFalse, sfTrue);
	return;
}

void snd_ClearBuffer() {
	SndStream* str = snd_StrSentinel->next;
	while (str != NULL) str = snd_StrPopPtr(str);

	SndWrapper* itr = snd_Sentinel->next;
	while (itr != NULL) itr = snd_PopPtr(itr);
	snd_NowPlaying = NULL;

	log_LogStr(LOG_INFO, "Sound buffer cleared", sfTrue, sfTrue);
}