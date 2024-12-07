#include "../include/azvs_stack.h"

#include "../include/azvs_base.h"

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



// int a_stack_push(AStack *stack, void *e) {
//     if (stack->size >= stack->total) {
//         size_t new_total = stack->total * 2;
//         void **new_data = realloc(stack->data, new_total * sizeof(void *));
//         if (new_data == NULL) {
//             return -1; // 内存分配失败
//         }
//         stack->data = new_data;
//         stack->total = new_total;
//     }
//     stack->data[stack->size++] = e;
//     return 0;
// }
//
// int a_stack_pop(AStack *stack, void *e) {
//     if (a_stack_is_empty(stack)) {
//         return -1;
//     }
//     memcpy(e, stack->data[--stack->size], sizeof(e));
//     return 0;
// }
//
// int a_stack_value(AStack *stack, void *e) {
//     if (a_stack_is_empty(stack)) {
//         return -1;
//     }
//     memcpy(e, stack->data[stack->size - 1], sizeof(e));
//     return 0;
// }
//
// int a_stack_is_empty(AStack *stack) { return stack->size == 0; }
//
// int a_stack_print(AStack *stack, void (*operation)(void *), char *end) {
//     if (stack->data == NULL) {
//         return -1;
//     }
//     for (int i = 0; i < stack->size; i++) {
//         operation(stack->data[i]);
//     }
//     printf("%s", end);
//     return 0;
// }
//
// size_t a_stack_get_size(AStack *stack) { return stack->size; }
//
// size_t a_stack_get_total(AStack *stack) { return stack->total; }
