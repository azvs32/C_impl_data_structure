#ifndef AZVS_BASE_H
#define AZVS_BASE_H

#include <stdlib.h>

//////////////////////////////////////////////////
//     日志系统
//////////////////////////////////////////////////
/*
 * 一些设想：
 *  + [简单]添加时间模块
 *  + [简单]用户自定义日志输出格式
 *  + 定义日志输出模式：console\file\both\...
 */

// 定义了日志有哪些级别，危险级别依次递增。
// 若修改了该枚举，请同步修改 get_log_level 函数。
typedef enum log_level {
    LOG_LEVEL_DEBUG,
    LOG_LEVEL_INFO,
    LOG_LEVEL_WARN,
    LOG_LEVEL_ERROR
} LogLevel;

// 定义了当前日志输入的级别，高于该级别的日志将全部输出。
extern LogLevel current_log_level;

/**
 * @brief 修改当前日志输出级别
 * @param level 日志级别
 */
void set_log_level(LogLevel level);

/**
 * @brief 获取日志级别对应的字符串
 * @param level 日志级别
 */
char *get_log_level(LogLevel level);

/**
 * @brief 输入日志信息
 * @param level 日志级别
 * @param file 文件名，为日志服务 __FILE__
 * @param function 函数名，为日志服务 __FUNCTION__
 * @param line 行号，为日志服务 __LINE__
 * @param format
 * @param ...
 */
void log_message(LogLevel level, const char *file, const char *function, int line, const char *format, ...);

// 给外界简化日志打印操作
#define LOG_MSG(level, format, ...) log_message(level, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__)
// note: 不知道哪里错了，if不生效
// #define LOG_MSG(level, format, ...) \
//   do { if (level >= current_log_level) \
//     log_message(level, __FILE__, __FUNCTION__, __LINE__, format, ##__VA_ARGS__); \
//   } while(0)

#define __CHECK(judgment, level, message, result) \
  do { \
    if (judgment) { \
      LOG_MSG(level, "%s", (message)); \
      result; \
    } \
  } while(0)

#define __CHECK_WARN(judgment, message, result) \
  __CHECK(judgment, LOG_LEVEL_WARN, message, result)
#define __CHECK_ERROR(judgment, message, result) \
  __CHECK(judgment, LOG_LEVEL_ERROR, message, result)

//////////////////////////////////////////////////
//     内存申请与释放
//////////////////////////////////////////////////

/**
 * @brief 宏定义 NEW 函数，用于申请内存
 * @param size 内存大小
 * @param file 文件名，为日志服务
 * @param function 函数名，为日志服务
 * @param line 行号，为日志服务
 */
void *new_with_log(size_t size, const char *file, const char *function, int line);

/**
 * @brief 宏定义 DELETE 函数，用于释放内存
 * @param ptr 内存指针
 * @param file 文件名，为日志服务
 * @param function 函数名，为日志服务
 * @param line 行号，为日志服务
 */
void delete_with_log(void *ptr, const char *file, const char *function, int line);

/**
 * @brief 宏定义 REALLOC 函数，用于重新申请内存
 * @param ptr 内存指针
 * @param size 新申请的内存大小
 * @param file 文件名，为日志服务
 * @param function 函数名，为日志服务
 * @param line 行号，为日志服务
 */
void *realloc_with_log(void *ptr, size_t size, const char *file, const char *function, int line);

// 将 malloc、free、realloc 包装成带日志的版本
#define NEW(type) ((type *)new_with_log(sizeof(type), __FILE__, __FUNCTION__, __LINE__))
#define NEW_SIZE(size) new_with_log(size, __FILE__, __FUNCTION__, __LINE__)
#define NEW_ARRAY(type, count) ((type *)new_with_log(sizeof(type) * (count), __FILE__, __FUNCTION__, __LINE__))
#define REALLOC(ptr, size) remalloc_with_log(ptr, size, __FILE__, __FUNCTION__, __LINE__)
#define DELETE(ptr) delete_with_log(ptr, __FILE__, __FUNCTION__, __LINE__)

#endif // !AZVS_BASE_H
