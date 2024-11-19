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
     * @brief 对应的标记
     * 当flag[i]=='Y'时，表示data[i]中存放了数据
     * 当flag[i]=='N'时，表示data[i]没有存放数据
     */
    char *flag;
    /**
     * @brief 线性表中已存入数据的总个数
     */
    size_t count;
    /**
     * @brief 线性表最大容量
     */
    size_t total;
} AArray, *APArray;

/**
 * @brief 初始化线性表
 * @param size 单个元素占用的大小 sizeof(type)
 * @param total 线性表存储元素的总数量
 * @return 线性表的首地址
 */
APArray a_array_init(size_t size, size_t total);

/**
* @brief 释放线性表，释放成功后，指针指向NULL
* @param array 需要操作的线性表
*/
void a_array_free(APArray * array);

/**
 * @brief 将数据存入指定下标，若下标内原本有元素，将会被覆盖
 * @param array 需要操作的线性表
 * @param data 需要插入的数据
 * @param index 指定下标
 */
void a_array_set(APArray array, const void * data, size_t index);

/**
* @brief 返回线性表中指定下标元素的地址
* @param array 需要操作的线性表
* @param index 指定下标
* @return 指定下标元素地址，若此处没有元素，将返回 NULL
*/
void *a_array_get_p(APArray array, size_t index);
// 使用 a_array_get_p 函数返回的线性表中元素的地址，如果在外部修改了，会影响到线性表中的元素。
// 使用 a_array_get   函数会将线性表中的元素复制一份返回，外部元素修改不会影响到线性表中的元素。
#define a_array_get(array, index, type) (*((type *)a_array_get_p(array, index)))

/**
* @brief 删除线性表中指定下标的元素
* @param array 需要操作的线性表
* @param index 指定下标
*/
void a_array_del(APArray array, size_t index);

/**
 * @brief 输出线性表的每个元素
 * @param array 需要操作的线性表
 * @param operate 回调函数，指定输出规则
 * @param end 结束输出，可指定为 NULL
 */
void a_array_print(APArray array, void (*operate)(void *), const char * end);

#endif //AZVS_ARRAY_H
