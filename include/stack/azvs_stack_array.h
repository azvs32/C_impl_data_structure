//
// Created by azvs on 24-11-18.
//

#ifndef AZVS_STACK_ARRAY_H
#define AZVS_STACK_ARRAY_H
#include <stddef.h>

typedef struct azvs_stack_array {
    void **array;
    size_t size;
    size_t total;
} *AStackArray;

#endif //AZVS_STACK_ARRAY_H
