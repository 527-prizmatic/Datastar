/// (C) 2024 The Prizmanager
/// Author - J.Sebastien Toussaint
/// 
/// Texture buffer handler.
/// Function prefix: tex_

#pragma once
#include "tools.h"
#include "logger.h"

typedef struct TexWrapper {
	struct TexWrapper* prev;
	struct TexWrapper* next;
	sfTexture* tex;
	char* id;
} TexWrapper;
TexWrapper* tex_Sentinel;

/// Initializes the texture buffer manager.
void tex_Init();

/// Preloads a texture file into the texture buffer. Keep in mind no two textures can have the same ID - trying to do so will result in nothing being created.
void tex_Preload(char* _path, char* _id);

/// Searches and returns a preloaded texture resource by ID.
sfTexture* tex_Fetch(char* _id);

/// Appends a texture wrapper object to the buffer.
void tex_Add(TexWrapper* _tex);

/// Removes a texture wrapper object from the buffer via pointer.
TexWrapper* tex_PopPtr(TexWrapper* _tex);

/// Unloads the given texture and frees up allocated memory.
void tex_Unload(char* _id);

/// Empties the texture buffer.
void tex_ClearBuffer();