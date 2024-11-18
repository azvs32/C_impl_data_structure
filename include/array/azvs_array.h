//
// Created by azvs on 24-11-18.
//

#ifndef AZVS_ARRAY_H
#define AZVS_ARRAY_H
#include <stddef.h>

/**
 * @brief 线性表
 *
 * 浅拷贝存储，使用 void* 实现泛型的效果。
 */
typedef struct azvs_array {
    /**
     * @brief 存放数据的指针
     */
    void *data;
    /**
     * @brief 每个元素的大小
     */
    size_t size;
    /**
     * @brief 线性表最大容量
     */
    size_t total;
} AArray, *APArray;

/**
 * @brief 初始化线性表
 * @param size 单个元素占用的大小 sizeof(type)
 * @param total 线性表存储元素的总数量
 * @return
 */
APArray a_array_init(size_t size, size_t total);

void a_array_free(APArray * array);

/**
 * @brief 将数据存入指定下标，若下标内原本有元素，将会被覆盖
 * @param array 需要操作的线性表
 * @param data 需要插入的数据
 * @param index 指定下标
 */
void a_array_insert(APArray array, const void * data, size_t index);

/**
 * @brief 输出线性表的每个元素
 * @param array 需要操作的线性表
 * @param operate 回调函数，指定输出规则
 * @param end 结束输出，可指定为 NULL
 */
void a_array_print(APArray array, void (*operate)(void *), const char * end);

#endif //AZVS_ARRAY_H
