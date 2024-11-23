//
// Created by azvs on 24-11-18.
//

#include "../../include/array/azvs_array.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

#include "../../include/azvs_base.h"

APArray a_array_init(const size_t size, const size_t total) {
    APArray array = NEW(AArray);
    array->size = size;
    array->total = total;
    array->count = 0;
    array->data = NEW_ARRAY(char, size*total);
    array->flag = NEW_ARRAY(char, total);
    memset(array->flag, 'N', total);
    return array;
}

APArray a_array_init2_(size_t total, size_t size, char * type) {
    APArray array = a_array_init(size, total);
    array->type = type;
    return array;
}

void a_array_free_p(APArray * array) {
    if (array==NULL || *array==NULL) {
        LOG_MSG(LOG_LEVEL_INFO, "尝试释放空线性表");
        return;
    }
    DELETE((*array)->flag);
    DELETE((*array)->data);
    DELETE(*array);
    *array = NULL;
}

void a_array_set(APArray array, const void * data, const size_t index) {
    if (!array) {
        LOG_MSG(LOG_LEVEL_ERROR, "线性表为空");
        return;
    }
    if (index >= array->total) {
        LOG_MSG(LOG_LEVEL_ERROR, "线性表下标越界");
        return;
    }
    if (array->flag[index] == 'Y') {
        LOG_MSG(LOG_LEVEL_INFO, "将覆盖线性表中原有的数据。");
        array->count-=1; // 后续还会加回来
    }
    memcpy(array->data+index*array->size, data, array->size);
    array->flag[index] = 'Y';
    array->count+=1;
}

void *a_array_get_p(APArray array, const size_t index) {
    if (!array) {
        LOG_MSG(LOG_LEVEL_ERROR, "线性表为空");
        return NULL;
    }
    if (index >= array->total) {
        LOG_MSG(LOG_LEVEL_ERROR, "线性表下标越界");
        return NULL;
    }
    if (array->flag[index] == 'N') {
        LOG_MSG(LOG_LEVEL_INFO, "线性表[%d]没有数据", index);
    }
    return array->data+index*array->size;
}

void a_array_del(APArray array, const size_t index) {
    if (!array) {
        LOG_MSG(LOG_LEVEL_ERROR, "线性表为空");
        return;
    }
    if (index >= array->total) {
        LOG_MSG(LOG_LEVEL_ERROR, "线性表下标越界");
        return;
    }
    if (array->flag[index] == 'N') {
        LOG_MSG(LOG_LEVEL_INFO, "线性表[%d]没有数据，无需删除", index);
        return;
    }
    memset(array->data+index*array->size, 0, array->size);
    array->flag[index] = 'N';
    LOG_MSG(LOG_LEVEL_INFO, "线性表[%d]数据已删除", index);
}

void a_array_sqrt(APArray array, int (*operate)(const void *, const void *)) {
    qsort(array->data, array->total, array->size, operate); // C 语言提供的排序函数
}

void a_array_print(APArray array, void (*operate)(void *), const char * end) {
    if (!array) {
        LOG_MSG(LOG_LEVEL_ERROR, "线性表为空");
        return;
    }
    for (int i = 0; i < array->total; i++) {
        operate(array->data+i*array->size);
    }
    if (end) printf("%s", end);
}

char*a_array_get_type(APArray array) {
    return array->type;
}