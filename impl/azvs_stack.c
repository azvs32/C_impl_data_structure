#include "../include/azvs_stack.h"
#include "../include/azvs_base.h"
#include <stdio.h>

APStack __a_stack_init(ASTACK_BASE_T base_struct, size_t total, size_t data_size, char *data_type) {
    APStack stack = NEW(AStack);
    stack->base_struct = base_struct;
    switch (base_struct) {
        case ASTACK_USE_ALINEAR:
            stack->data.linear = __a_linear_init(total, data_size, data_type);
            break;
        case ASTACK_USE_ALINKED:
            stack->data.linked = __a_linked_init(data_size, data_type);
            break;
    }
    return stack;
}

void __a_stack_free(APStack *stack) {
    __CHECK_WARN(stack==NULL || *stack==NULL, "尝试释放空栈", return);
    switch ((*stack)->base_struct) {
        case ASTACK_USE_ALINEAR:
            a_linear_free((*stack)->data.linear);
            break;
        case ASTACK_USE_ALINKED:
            a_linked_free((*stack)->data.linked);
            break;
    }
    DELETE(*stack);
    *stack = NULL;
}

void a_stack_push(APStack stack, void *data) {
    __CHECK_ERROR(stack == NULL, "栈为空，无法压栈元素", return);
    __CHECK_ERROR(data == NULL, "栈中不允许插入NULL数据", return);
    __CHECK_ERROR(stack->base_struct == ASTACK_USE_ALINEAR && stack->data.linear->count == stack->data.linear->total,
                  "线性表实现的栈以满，无法继续压栈", return);
    switch (stack->base_struct) {
        case ASTACK_USE_ALINEAR:
            a_linear_set(stack->data.linear, data, stack->data.linear->count);
            break;
        case ASTACK_USE_ALINKED:
            a_linked_insert_tail(stack->data.linked, data);
            break;
    }
}

// 有问题，地址和值的问题 ***
// void *ap_stack_pop(APStack stack) {
//     __CHECK_ERROR(stack == NULL, "栈为空，无法出栈元素", return NULL);
//     __CHECK_ERROR(stack->base_struct == ASTACK_USE_ALINEAR && stack->data.linear->count <= 0 ||
//                   stack->base_struct == ASTACK_USE_ALINKED && stack->data.linked->count <= 0,
//                   "栈中无数据，无法出栈数据", return NULL);
//     void *result = NULL;
//     switch (stack->base_struct) {
//         case ASTACK_USE_ALINEAR:
//             result = ap_linear_get(stack->data.linear, stack->data.linear->count - 1);
//             // stack->data.linear->count -= 1;
//             a_linear_del(stack->data.linear, stack->data.linear->count - 1);
//             break;
//         case ASTACK_USE_ALINKED:
//             result = stack->data.linked->tail->data;
//             a_linked_remove_tail(stack->data.linked);
//             break;
//     }
//     return result;
// }
//
// void *ap_stack_peek(APStack stack) {
//     __CHECK_ERROR(stack == NULL, "栈为空，无法查看栈顶元素", return NULL);
//     __CHECK_ERROR(stack->base_struct == ASTACK_USE_ALINEAR && stack->data.linear->count <= 0 ||
//                   stack->base_struct == ASTACK_USE_ALINKED && stack->data.linked->count <= 0,
//                   "栈中无数据，无法查看栈顶元素", return NULL);
//     return NULL;
// }

void a_stack_print(APStack stack, void (*operate)(void *), const char *end) {
    __CHECK_ERROR(stack == NULL, "栈为空，无法输出栈元素", return);
    switch (stack->base_struct) {
        case ASTACK_USE_ALINEAR:
            a_linear_print(stack->data.linear, operate, end);
        break;
        case ASTACK_USE_ALINKED:
            a_linked_print(stack->data.linked, operate, end);
        break;
    }
}

void a_stack_print_info(APStack stack) {
    __CHECK_ERROR(stack == NULL, "栈为空，无法输出栈的基本信息", return);
    printf("\n");
    printf("AStack Information:\n");
    switch (stack->base_struct) {
        case ASTACK_USE_ALINEAR:
            printf("\tData size : %zu bytes\n", stack->data.linear->data_size);
            printf("\tData type : %s\n", stack->data.linear->data_type);
            printf("\tCount     : %zu\n", stack->data.linear->count);
            printf("\tTotal     : %zu\n", stack->data.linear->total);
            break;
        case ASTACK_USE_ALINKED:
            printf("\tData size : %zu bytes\n", stack->data.linked->data_size);
            printf("\tData type : %s\n", stack->data.linked->data_type);
            printf("\tCount     : %zu\n", stack->data.linked->count);
            break;
    }
    printf("\n");
}