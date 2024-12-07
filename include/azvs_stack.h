#ifndef AZVS_STACK_H
#define AZVS_STACK_H

#include "./azvs_linear.h"
#include "./azvs_linked.h"
#include <stddef.h>

typedef enum azvs_stack_base_struct {
    // 底层使用线性表实现
    ASTACK_USE_ALINEAR,
    // 底层使用链表实现
    ASTACK_USE_ALINKED,
} ASTACK_BASE_T;

typedef union azvs_stack_data {
    APLinear linear;
    APLinked linked;
} ASTACK_DATA;

typedef struct azvs_stack {
    // 指定底层使用的结构
    ASTACK_BASE_T base_struct;
    // 存放数据
    ASTACK_DATA data;
} AStack, *APStack;

/**
* @brief 初始化栈
* @param base_struct 指定栈底层的数据结构
* @param total 若底层结构是线性表，则为栈的最大容量
* @param data_size 指定栈中存储的元素大小
* @param data_type 指定栈中存储的元素类型
*/
APStack __a_stack_init(ASTACK_BASE_T base_struct, size_t total, size_t data_size, char *data_type);

#define a_stack_init(...) \
    FUNCTION_OVERLOADING(__VA_ARGS__, _4, _3, a_stack_init_by_linear, a_stack_init_by_linked)(__VA_ARGS__)
#define a_stack_init_by_linked(type)  __a_stack_init(ASTACK_USE_ALINKED, 0, sizeof(type), #type)
#define a_stack_init_by_linear(total, type)  __a_stack_init(ASTACK_USE_ALINEAR, total, sizeof(type), #type)

/**
* @brief 释放栈
* 释放成功后，指针将指向NULL
* @param stack 需要操作的栈
*/
void __a_stack_free(APStack *stack);

#define a_stack_free(stack) __a_stack_free(&(stack))

/**
* @brief 入栈操作
* @param stack 需要操作的栈
* @param data 需要入栈的元素
*/
void a_stack_push(APStack stack, void *data);

/**
* @brief 出栈操作
* @param stack 需要操作的栈
*/
void *ap_stack_pop(APStack stack);

// #define a_stack_pop(stack, type) (*((type*)ap_stack_pop(stack)))
// #define a_stack_pop(stack) \
//     ({ \
//         const char *data_type = (stack)->data.linear->data_type; \
//         (typeof(*data_type) *)ap_stack_pop(stack); \
//     })

/**
* @brief 查看栈顶元素
* @param stack 需要操作的栈
*/
void *ap_stack_peek(APStack stack);

///**
// * 返回栈顶元素，该操作并不会使该元素出栈
// * @param stack 指定栈地址
// * @param e 保存栈定元素的地址
// * @return 成功则返回 0
// */
//int a_stack_value(AStack *stack, void *e);
//
///**
// * 检查栈是否为空
// * @param stack 指定栈地址
// * @return 如果栈内没有存储，则返回真
// */
//int a_stack_is_empty(AStack *stack);
//
///**
// * 打印栈中的所有元素，先出栈的元素排在后面
// * @param stack 指定栈地址
// * @param operation 指定输出规则
// * @param end 自定义结束符号，若为NULL，则不定义。通常可以指定为"\n"
// * @return 操作成功返回 0
// */
//int a_stack_print(AStack *stack, void (*operation)(void *), char *end);
//
///**
// * 获取栈的大小
// * @param stack 指定栈地址
// * @return 获取栈当前已经存入数据的大小
// */
//size_t a_stack_get_size(AStack *stack);
//
///**
// * 获取栈的最大容量
// * @param stack 指定栈地址
// * @return 获取栈当前总容量
// */
//size_t a_stack_get_total(AStack *stack);

#endif // !AZVS_STACK_H
