/// (C) 2024 The Prizmanager
/// Author - J.Sebastien Toussaint
/// 
/// Various functions for logging program behavior and possible bugs to .txt.
/// Function prefix: log_

#pragma once
#include "tools.h"

typedef enum {
	LOG_NONE = 0,
	LOG_INFO = 1, /// Just info messages to ensure everything is running smoothly
	LOG_WARN = 2, /// Warnings and heads-ups to indicate something might be wrong
	LOG_ERROR = 4, /// Indications that something went wrong
	LOG_FATAL = 8 /// Critical errors and crashes
} LogLevel;

/// Initializes the logger. Should only be called once at the program's very beginning.
void log_Init(int _lvl);

/// Writes a quick info header to the log, comprising logging level and current time.
void log_LogHeader(LogLevel _lvl);

/// Writes a string to the log.
/// \param _lvl - Logging level, indicating whether this is an info message, a warn or an error
/// \param _msg - The message to be logged
/// \param _is_newline - Should a newline be printed at the end of this entry?
void log_LogStr(LogLevel _lvl, char* _msg, sfBool _header, sfBool _is_newline);

/// Writes an integer to the log.
/// \param _lvl - Logging level, indicating whether this is an info message, a warn or an error
/// \param _msg - The integer to be logged
/// \param _is_newline - Should a newline be printed at the end of this entry?
void log_LogInt(LogLevel _lvl, int _msg, sfBool _header, sfBool _is_newline);

/// Writes a float to the log.
/// \param _lvl - Logging level, indicating whether this is an info message, a warn or an error
/// \param _msg - The number to be logged
/// \param _is_newline - Should a newline be printed at the end of this entry?
void log_LogFloat(LogLevel _lvl, float _msg, sfBool _header, sfBool _is_newline);

/// Ends the logging session. Should only be called once at the program's very end.
void log_Conclude();

char* log_GetLevel(LogLevel _lvl);