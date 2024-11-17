#ifndef AZVS_STACK_H
#define AZVS_STACK_H

#include <stddef.h>

// 栈
typedef struct
{
    void **data;  // 存储栈元素的数组
    size_t size;  // 当前栈的大小
    size_t total; // 栈的预期总容量
} AStack;

/**
 * 栈初始化操作
 * @param stack 指定栈地址
 * @param total 指定栈的预期总容量，如果在压栈过程中发现总容量不足，会自动增大
 * @return 成功创建返回 0
 */
int a_stack_init(AStack *stack, size_t total);

/**
 * 清空栈操作
 * @param stack 指定栈地址
 */
void a_stack_free(AStack *stack);

/**
 * 入栈操作
 * @param stack 指定栈地址
 * @param e 指定需要压栈的元素地址
 * @return 成功入栈返回 0
 */
int a_stack_push(AStack *stack, void *e);

/**
 * 出栈操作
 * @param stack 指定栈地址
 * @param e 保存出栈的元素地址
 * @return 成功出栈返回 0
 */
int a_stack_pop(AStack *stack, void *e);

/**
 * 返回栈顶元素，该操作并不会使该元素出栈
 * @param stack 指定栈地址
 * @param e 保存栈定元素的地址
 * @return 成功则返回 0
 */
int a_stack_value(AStack *stack, void *e);

/**
 * 检查栈是否为空
 * @param stack 指定栈地址
 * @return 如果栈内没有存储，则返回真
 */
int a_stack_is_empty(AStack *stack);

/**
 * 打印栈中的所有元素，先出栈的元素排在后面
 * @param stack 指定栈地址
 * @param operation 指定输出规则
 * @param end 自定义结束符号，若为NULL，则不定义。通常可以指定为"\n"
 * @return 操作成功返回 0
 */
int a_stack_print(AStack *stack, void (*operation)(void *), char *end);

/**
 * 获取栈的大小
 * @param stack 指定栈地址
 * @return 获取栈当前已经存入数据的大小
 */
size_t a_stack_get_size(AStack *stack);

/**
 * 获取栈的最大容量
 * @param stack 指定栈地址
 * @return 获取栈当前总容量
 */
size_t a_stack_get_total(AStack *stack);

#endif // !AZVS_STACK_H
