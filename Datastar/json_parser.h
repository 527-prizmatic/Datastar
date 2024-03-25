/// (C) 2024 The Prizmanager
/// Author - J.Sebastien Toussaint
/// 
/// JSON-based language API.
/// Function prefix: json_

#pragma once
#include <stdio.h>
#include <stdlib.h>

#include "tools.h"
#include "logger.h"

typedef enum {
	ENGLISH = 0,
	FRENCH,
	LANGUAGES_TOTAL
} Language;
static Language currentLang = ENGLISH;

/// Crude ass and largely incomplete implementation of a one-way interpreter from JSON to C.
/// So far all it can really do is read root-level string literals and stuff them into pointers, but not as if we needed anything more advanced than that for the Feel! project.

/// Language buffer node
typedef struct keyJSON {
	char* key;
	char* value;
	struct keyJSON* next;
} keyJSON;

/// Initializes the JSON parser by creating and allocating a sentinel node from which to "grow" data trees.
void json_Init();

/// Reads the contents of the JSON file passed as argument and creates a circular linked list to store its contents.
/// \return 0 - Successful execution
/// \return 1 - File opening error
/// \return 2 - Malformed JSON error
/// \return 3 - Out of memory
int json_LoadFile(char* _filename);

/// Searches a JSON file for a given property and returns a pointer to its associated value.
/// Returns NULL if the given file is invalid, a reading error occured (e.g. due to a JSON formatting error), or the property does not exist.
char* json_Read(char* _property);

/// Creates a new node in the language buffer and links it to the node passed as argument.
keyJSON* newNode(keyJSON* _prev);

/// Destroys contents of the language buffer.
void json_ClearBuffer();

/// Returns the path to the language file associated with the given language.
char* json_GetFilePath(Language _l);

/// Sets game language. This function also handles destroying the language buffer and loading a new file into memory, so no need to bother with that.
void json_SetLanguage(Language _l);

/// Returns the currently selected language.
Language json_GetLanguage();