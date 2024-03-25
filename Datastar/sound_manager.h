/// (C) 2024 The Prizmanager
/// Author - J.Sebastien Toussaint
/// 
/// Sound and music handler.
/// Function prefixes: snd_ (general and sounds), mus_ (musics), vol_ (volume)

#pragma once
#include "tools.h"
#include "logger.h"

typedef enum {
	SND_SENTINEL,
	SND_SND,
	SND_MUS
} SndType;

typedef enum {
	SND_STOPPED,
	SND_FADEIN,
	SND_PLAYING,
	SND_FADEOUT
} SndMusState;

typedef struct SndWrapper {
	struct SndWrapper* prev;
	struct SndWrapper* next;
	SndType type;
	union {
		sfSoundBuffer* snd;
		sfMusic* mus;
	};
	char* id;
} SndWrapper;
SndWrapper* snd_Sentinel;

typedef struct SndStream {
	struct SndStream* prev;
	struct SndStream* next;
	sfSound* snd;
} SndStream;
SndStream* snd_StrSentinel;

/// Initializes the sound manager.
void snd_Init();

/// Preloads a sound file into the sound buffer. Keep in mind no two sounds/musics can have the same ID - trying to do so will result in nothing being created.
void snd_Preload(SndType _type, char* _path, char* _id);

/// Appends a sound wrapper object to the buffer.
void snd_Add(SndWrapper* _snd);

/// Removes a sound wrapper object from the buffer via pointer.
SndWrapper* snd_PopPtr(SndWrapper* _snd);

/// Ticks the sound engine.
void snd_Update();

/// Plays the requested music, without any transition, stopping whatever music is currently playing in the process.
void mus_Play(char* _id);

/// Plays the requested music, smoothly fading in. Must be used if no other music is playing.
void mus_FadeIn(char* _id);

/// Fades out and eventually stops the currently playing music.
void mus_FadeOut();

/// Stops the curently playing music.
void mus_Stop();

/// Plays the requested sound.
void snd_Play(char* _id);

/// Creates a wrapper for streaming sounds. This buffer contains sound objects for what is currently playing and is dynamically updated as new sounds play and old sounds end.
void snd_StrAdd(SndWrapper* _snd);

/// Removes a sound stream object from the buffer via pointer.
SndStream* snd_StrPopPtr(SndStream* _snd);

void vol_SetMaster(float _vol);
void vol_SetSnd(float _vol);
void vol_SetMus(float _vol);
float vol_GetMaster();
float vol_GetSnd();
float vol_GetMus();
SndMusState snd_GetMusicState();

/// Unloads the requested sound from memory.
void snd_Unload(char* _id);

/// Empties the sound buffer.
void snd_ClearBuffer();