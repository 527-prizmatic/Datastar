#include "logger.h"

FILE* log_File;
char log_Level;

void log_Init(int _lvl) {
	log_File = NULL;
	time_t t = time(NULL);
	struct tm time = *localtime(&t);
	char* filename = calloc(256, sizeof(char));
	if (filename == NULL) {
		printf("Error while creating log file: insufficient memory\n");
		return;
	}

	sprintf(filename, PATH_LOGS"log_%d-%02d-%02d_%02d-%02d-%02d.txt", time.tm_year + 1900, time.tm_mon + 1, time.tm_wday, time.tm_hour, time.tm_min, time.tm_sec);
	log_File = fopen(filename, "w+");
	if (log_File == NULL) {
		printf("Error while creating log file: file creation error\n");
		return;
	}

	log_Level = _lvl;
	//fprintf(log_File, "[INFO] Starting logging session.");
	log_LogStr(LOG_INFO, "Starting logging session", sfTrue, sfTrue);
}

void log_LogHeader(LogLevel _lvl) {
	time_t t = time(NULL);
	struct tm time = *localtime(&t);
	fprintf(log_File, "[%s] [%02d:%02d:%02d] ", log_GetLevel(_lvl), time.tm_hour, time.tm_min, time.tm_sec);
}

void log_LogStr(LogLevel _lvl, char* _msg, sfBool _header, sfBool _is_newline) {
	if (log_File == NULL) return;
	if ((log_Level & _lvl) == 0) return;
	if (_header) log_LogHeader(_lvl);
	
	fprintf(log_File, "%s ", _msg);
	if (_is_newline) fprintf(log_File, "\n");
}

void log_LogInt(LogLevel _lvl, int _msg, sfBool _header, sfBool _is_newline) {
	if (log_File == NULL) return;
	if ((log_Level & _lvl) == 0) return;
	if (_header) log_LogHeader(_lvl);

	fprintf(log_File, "%d ", _msg);
	if (_is_newline) fprintf(log_File, "\n");
}

void log_LogFloat(LogLevel _lvl, float _msg, sfBool _header, sfBool _is_newline) {
	if (log_File == NULL) return;
	if ((log_Level & _lvl) == 0) return;
	if (_header) log_LogHeader(_lvl);

	fprintf(log_File, "%.08f ", _msg);
	if (_is_newline) fprintf(log_File, "\n");
}

void log_Conclude() {
	log_LogStr(LOG_INFO, "Concluding logging session", sfTrue, sfTrue);
	fclose(log_File);
}

char* log_GetLevel(LogLevel _lvl) {
	switch (_lvl) {
		case LOG_INFO: return "INFO";
		case LOG_WARN: return "WARN";
		case LOG_ERROR: return "ERROR";
		case LOG_FATAL: return "FATAL";
		default: return "???";
	}
}