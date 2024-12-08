#ifndef AZVS_STACK_H
#define AZVS_STACK_H

#include "./azvs_linear.h"
#include "./azvs_linked.h"

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

#define a_stack_pop(stack, type) (*(type*)ap_stack_pop(stack))

/**
* @brief 查看栈顶元素
* @param stack 需要操作的栈
*/
void *ap_stack_peek(APStack stack);

#define a_stack_peek(stack, type) (*(type*)ap_stack_peek(stack))

/**
 * @brief 输出栈中的每个元素，栈顶元素在最后
 * @param stack 需要操作的栈
 * @param operate 回调函数，指定输出规则
 * @param end 结束输出，可指定为 NULL
 */
void a_stack_print(APStack stack, void (*operate)(void *), const char *end);

/**
* @brief 输出栈的基本信息
* @param stack 需要操作的栈
*/
void a_stack_print_info(APStack stack);

#endif // !AZVS_STACK_H
