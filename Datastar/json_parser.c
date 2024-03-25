#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json_parser.h"

#define LEN_KEY 64
#define LEN_STR 324

keyJSON* sentinel;

void json_Init() {
	sentinel = newNode(NULL);
	sentinel->key = NULL;
	sentinel->value = NULL;
	sentinel->next = NULL;
}

int json_LoadFile(char* _filename) {
	FILE* f = fopen(_filename, "r");
	if (f == NULL) {
		log_LogStr(LOG_FATAL, "JSON file reading error - insufficient memory:", sfTrue, sfFalse);
		log_LogStr(LOG_FATAL, _filename, sfFalse, sfTrue);
		return 1;
	}

	if (getc(f) != '{') {
		log_LogStr(LOG_FATAL, "JSON file reading error - malformed JSON:", sfTrue, sfFalse);
		log_LogStr(LOG_FATAL, _filename, sfFalse, sfTrue);
		return 2;
	}

	unsigned char c = 0;
	keyJSON* prev = sentinel;
	keyJSON* nodeNew;
	while (1) {
		c = getc(f);
		if (c == '\"') {
			nodeNew = newNode(prev);
			nodeNew->key = calloc(LEN_KEY, 1);
			if (nodeNew->key == NULL) {
				log_LogStr(LOG_FATAL, "JSON file reading error - insufficient memory:", sfTrue, sfFalse);
				log_LogStr(LOG_FATAL, _filename, sfFalse, sfTrue);
				return 3;
			}
			int i = 0;
			c = getc(f);
			do {
				nodeNew->key[i] = c;
				i++;
				c = getc(f);
			} while (c != '\"');

			do { c = getc(f); } while (c != ':');

			do { c = getc(f); } while (c == ' ' || c == '\t');
			if (c != '\"') {
				log_LogStr(LOG_FATAL, "JSON file reading error - malformed JSON:", sfTrue, sfFalse);
				log_LogStr(LOG_FATAL, _filename, sfFalse, sfTrue);
				return 2;
			}

			nodeNew->value = calloc(LEN_STR, 1);
			if (nodeNew->value == NULL) {
				log_LogStr(LOG_FATAL, "JSON file reading error - insufficient memory:", sfTrue, sfFalse);
				log_LogStr(LOG_FATAL, _filename, sfFalse, sfTrue);
				return 3;
			}
			i = 0;
			c = getc(f);
			do {
				nodeNew->value[i] = c;
				i++;
				c = getc(f);
			} while (c != '\"');
			do { c = getc(f); } while (c != ',' && c != '}' && c != EOF);
			if (c == '}' || c == EOF) break;

			prev = nodeNew;
			nodeNew = NULL;
		}
	}
	nodeNew->next = sentinel->next;
	fclose(f);

	log_LogStr(LOG_FATAL, "Successfully loaded JSON file", sfTrue, sfFalse);
	log_LogStr(LOG_FATAL, _filename, sfFalse, sfTrue);

	return 0;
}

char* json_Read(char* _property) {
	keyJSON* ptr = NULL;
	if (ptr == NULL) ptr = sentinel->next;
	keyJSON* start = ptr;

	do {
		if (strcmp(ptr->key, _property) == 0) return ptr->value;
		else ptr = ptr->next;
	} while (ptr != start);

	return NULL;
}

keyJSON* newNode(keyJSON* _prev) {
	keyJSON* node = malloc(sizeof(keyJSON));
	if (_prev != NULL) _prev->next = node;
	return node;
}

void json_ClearBuffer() {
	keyJSON* start = sentinel->next;
	keyJSON* ptr = sentinel->next;
	keyJSON* prev;
	while (1) {
		prev = ptr;
		ptr = ptr->next;
		free(prev->key);
		free(prev->value);
		free(prev);
		if (ptr == sentinel->next) break;
	}
	sentinel->next = NULL;
}

char* json_GetFilePath(Language _l) {
	switch (_l) {
		case ENGLISH: return PATH_LANGS"en_us.json";
		case FRENCH: return PATH_LANGS"fr_fr.json";
		default: return NULL;
	}
}

void json_SetLanguage(Language _l) {
	currentLang = _l;
	if (sentinel->next != NULL) json_ClearBuffer();
	json_LoadFile(json_GetFilePath(currentLang));
//	printf("%s\n", getDataJSON("lang_set"));
}

Language json_GetLanguage() {
	return currentLang;
}