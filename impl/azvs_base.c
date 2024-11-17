#include "../include/azvs_base.h"
#include <stdarg.h>
#include <stdio.h>

LogLevel current_log_level = LOG_LEVEL_ERROR;

void set_log_level(LogLevel level) { current_log_level = level; }

char *get_log_level(LogLevel level)
{
    switch (level)
    {
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

void log_message(LogLevel level, const char *file, const char *function,int line, const char *format, ...)
{
    if (level < current_log_level)
    {
        return;
    }

    printf("[%s][%s][%s][%d] -> ", get_log_level(level), file, function, line);

    va_list args;
    va_start(args, format);
    vprintf(format, args);
    va_end(args);
    printf("\n");
}

void *new_with_log(size_t size, const char *file, const char *function,int line)
{
    void *ptr = malloc(size);
    if (!ptr)
    {
        log_message(LOG_LEVEL_ERROR, file, function, line, "内存分配失败");
    }
    else
    {
        log_message(LOG_LEVEL_DEBUG, file, function, line, "地址 %p 分配 %u 字节 ",ptr, size);
    }
    return ptr;
}

void delete_with_log(void *ptr, const char *file, const char *function,int line)
{
    if (ptr)
    {
        free(ptr);
        log_message(LOG_LEVEL_DEBUG, file, function, line, "地址 %p 内存释放成功",ptr);
    }
    else
    {
        log_message(LOG_LEVEL_WARN, file, function, line, "试图释放空指针");
    }
}

void *realloc_with_log(void *ptr, size_t size, const char *file,const char *function, int line)
{
    if (size == 0)
    {
        free(ptr);
        log_message(LOG_LEVEL_INFO, file, function, line, "内存释放成功");
        return NULL;
    }
    void *new_ptr = realloc(ptr, size);
    if (!new_ptr)
    {
        log_message(LOG_LEVEL_ERROR, file, function, line, "内存分配失败");
    }
    else
    {
        log_message(LOG_LEVEL_DEBUG, file, function, line,"地址 %p 重新分配 %u 字节 ", ptr, size);
    }
    return new_ptr;
}
