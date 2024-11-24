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
#define NEW_ARRAY(type, count) ((type *)new_with_log(sizeof(type) * (count), __FILE__, __FUNCTION__, __LINE__))
#define REALLOC(ptr, size) remalloc_with_log(ptr, size, __FILE__, __FUNCTION__, __LINE__)
#define DELETE(ptr) delete_with_log(ptr, __FILE__, __FUNCTION__, __LINE__)


//////////////////////////////////////////////////
//     Linear 的实现
//////////////////////////////////////////////////
typedef struct azvs_linear {
    // 存放线性表数据的指针
    void *data;
    // 数据标记：flags[i]=='Y'时表示data[i]中存放了数据，'N'则表示未存放数据
    char *flags;
    // 线性表中元素的大小
    size_t data_size;
    // 线性表中元素的类型
    char *data_type;
    // 线性表中以存入的数据数量
    size_t count;
    // 线性表最大容量
    size_t total;
} ALinear, *APLinear;

/**
* @brief 初始化线性表，使用 #define 简化
* @param total 线性表存储元素的总数量
* @param data_size 单个元素占用的大小 sizeof(type)
* @param data_type 存入元素的数据类型 ElementType
*/
APLinear __a_linear_init(size_t total, size_t data_size, char *data_type);

#define a_linear_init(total, type) __a_linear_init(total, sizeof(type), #type)

/**
* @brief 释放线性表，使用 #define 简化
* 释放成功后，指针指向NULL。使用宏是为了释放时不需要 &
* @param linear 需要操作的线性表
*/
void __a_linear_free(APLinear *linear);

#define a_linear_free(linear) __a_linear_free(&(linear))

/**
* @brief 将数据存入指定下标。若原本有数据则覆盖
* @param linear 需要操作的线性表
* @param data 需要插入的数据
* @param index 指定下标
*/
void a_linear_set(APLinear linear, const void *data, size_t index);

/**
* @brief 返回线性表中指定下标元素的地址
* @param linear 需要操作的线性表
* @param index 指定下标
* @return 指定下标元素地址，若此处没有元素，将返回 NULL
*/
void *ap_linear_get(APLinear linear, size_t index);

// 使用 ap_linear_get 函数返回的线性表中元素的地址，如果在外部修改了，会影响到线性表中的元素。
// 使用 a_linear_get   函数会将线性表中的元素复制一份返回，外部元素修改不会影响到线性表中的元素。
#define a_linear_get(linear, index, type) (*((type *)ap_linear_get(linear, index)))
// note: 一个期盼：a_linear_get(linear, index) 已经将type类型存储到结构体中，但是不知道该如何动态的获取 type

/**
* @brief 删除线性表中指定下标的元素
* @param linear 需要操作的线性表
* @param index 指定下标
*/
void a_linear_del(APLinear linear, size_t index);

/**
* @brief 线性表排序，使用回调函数定义排序规则
* @param linear 需要操作的线性表
* @param operate 回调函数，指定排序规则
*/
void a_linear_sort(APLinear linear, int (*operate)(const void *, const void *));

/**
 * @brief 输出线性表的每个元素
 * @param linear 需要操作的线性表
 * @param operate 回调函数，指定输出规则
 * @param end 结束输出，可指定为 NULL
 */
void a_linear_print(APLinear linear, void (*operate)(void *), const char *end);

/**
* @brief 输出线性表的基本信息
* @param linear 需要操作的线性表
*/
void a_linear_print_info(APLinear linear);

const char *a_linear_get_type(APLinear linear);

size_t a_linear_get_count(APLinear linear);

size_t a_linear_get_total(APLinear linear);

#endif // !AZVS_BASE_H
