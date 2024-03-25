/// (C) 2024 The Prizmanager
/// Author - J.Sebastien Toussaint
/// 
/// Shader buffer handler.
/// Function prefix: shd_
 
#pragma once
#include "tools.h"
#include "logger.h"

typedef struct ShdWrapper {
	struct ShdWrapper* prev;
	struct ShdWrapper* next;
	sfRenderStates rs;
	char* id;
} ShdWrapper;
ShdWrapper* shd_Sentinel;

/// Initializes the shader buffer manager.
void shd_Init();

/// Preloads a shader into the shader buffer and stores it into a render state with default parameters. Keep in mind no two shaders can have the same ID - trying to do so will result in nothing being created.
void shd_Preload(char* _path_v, char* _path_f, char* _id);

/// Appends a shader wrapper object to the buffer.
void shd_Add(ShdWrapper* _shd);

/// Searches and returns a preloaded render state by ID.
/// Returns NULL if passed NULL.
sfRenderStates* shd_FetchState(char* _id);

/// Searches and returns a preloaded shader by ID.
/// Returns NULL if passed NULL.
const sfShader* shd_FetchShader(char* _id);

/// Removes a shader wrapper object from the buffer via pointer.
ShdWrapper* shd_PopPtr(ShdWrapper* _shd);

/// Empties the shader buffer.
void shd_ClearBuffer();