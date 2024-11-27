//
// Created by azvs on 24-11-27.
//
#include "../../include/azvs_base.h"
#include <stdio.h>
#include <stdarg.h>

LogLevel current_log_level = LOG_LEVEL_ERROR;

void set_log_level(LogLevel level) { current_log_level = level; }

char *get_log_level(LogLevel level) {
    switch (level) {
        case LOG_LEVEL_DEBUG:
            return "DEBUG";
        case LOG_LEVEL_INFO:
            return "INFO";
        case LOG_LEVEL_WARN:
            return "WARN";
        case LOG_LEVEL_ERROR:
            return "ERROR";
        default:
            return "UNKNOWN";
    }
}

void log_message(LogLevel level, const char *file, const char *function, int line, const char *format, ...) {
    // 判断日志级别操作。使用宏定义封装，在编译时优化。
    if (level < current_log_level) return;

    printf("[%s][%s][%s][%d] -> ", get_log_level(level), file, function, line);

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\n");
}
