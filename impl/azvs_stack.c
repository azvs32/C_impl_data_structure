#include "../include/azvs_stack.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int a_stack_init(AStack *stack, size_t total)
{
    stack->data = (void **)malloc(total * sizeof(void *));
    if (stack->data == NULL)
    {
        return -1; // 内存分配失败
    }
    stack->size = 0;
    stack->total = total;
    return 0;
}

void a_stack_free(AStack *stack)
{
    free(stack->data);
    stack->size = 0;
    stack->total = 0;
}

int a_stack_push(AStack *stack, void *e)
{
    if (stack->size >= stack->total)
    {
        size_t new_total = stack->total * 2;
        void **new_data = realloc(stack->data, new_total * sizeof(void *));
        if (new_data == NULL)
        {
            return -1; // 内存分配失败
        }
        stack->data = new_data;
        stack->total = new_total;
    }
    stack->data[stack->size++] = e;
    return 0;
}

int a_stack_pop(AStack *stack, void *e)
{
    if (a_stack_is_empty(stack))
    {
        return -1;
    }
    memcpy(e, stack->data[--stack->size], sizeof(e));
    return 0;
}

int a_stack_value(AStack *stack, void *e)
{
    if (a_stack_is_empty(stack))
    {
        return -1;
    }
    memcpy(e, stack->data[stack->size - 1], sizeof(e));
    return 0;
}

int a_stack_is_empty(AStack *stack) { return stack->size == 0; }

int a_stack_print(AStack *stack, void (*operation)(void *), char *end)
{
    if (stack->data == NULL)
    {
        return -1;
    }
    for (int i = 0; i < stack->size; i++)
    {
        operation(stack->data[i]);
    }
    printf("%s", end);
    return 0;
}

size_t a_stack_get_size(AStack *stack) { return stack->size; }

size_t a_stack_get_total(AStack *stack) { return stack->total; }
