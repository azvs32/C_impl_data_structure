//
// Created by azvs on 24-11-18.
//

#include "../../include/array/azvs_array.h"

#include <stdio.h>
#include <string.h>

#include "../../include/azvs_base.h"

APArray a_array_init(const size_t size, const size_t total) {
    APArray array = NEW(AArray);
    array->size = size;
    array->total = total;
    array->data = NEW_ARRAY(char, size*total);
    return array;
}

void a_array_free(APArray * array) {
    if (*array == NULL) {
        LOG_MSG(LOG_LEVEL_INFO, "尝试释放空线性表");
        return;
    }
    if (*array!=NULL) {
        DELETE((*array)->data);
        DELETE(*array);
        *array = NULL;
    }
}

void a_array_insert(APArray array, const void * data, const size_t index) {
    if (!array) {
        LOG_MSG(LOG_LEVEL_ERROR, "数组为空");
        return;
    }
    if (index >= array->total) {
        LOG_MSG(LOG_LEVEL_ERROR, "数组下标越界");
        return;
    }
    memcpy(array->data+index*array->size, data, array->size);
}

void a_array_print(APArray array, void (*operate)(void *), const char * end) {
    if (!array) {
        LOG_MSG(LOG_LEVEL_ERROR, "数组为空");
        return;
    }
    for (int i = 0; i < array->total; i++) {
        operate(array->data+i*array->size);
    }
    if (!end) printf(end);
}