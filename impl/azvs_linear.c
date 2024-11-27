//
// Created by azvs on 24-11-27.
//

#include "../include/azvs_base.h"
#include "../include/azvs_linear.h"
#include <stdio.h>
#include <string.h>

//////////////////////////////////////////////////
//     Linear 的实现
//////////////////////////////////////////////////

APLinear __a_linear_init(size_t total, const size_t data_size, char *data_type) {
    APLinear linear = NEW(ALinear);
    linear->data_size = data_size;
    linear->data_type = data_type;
    linear->count = 0;
    linear->total = total;
    linear->data = NEW_ARRAY(char, data_size*total);
    linear->flags = NEW_ARRAY(char, total);
    memset(linear->flags, 'N', total);
    return linear;
}

void __a_linear_free(APLinear *linear) {
    if (linear == NULL || *linear == NULL) {
        LOG_MSG(LOG_LEVEL_INFO, "尝试释放空线性表");
        return;
    }
    DELETE((*linear)->flags);
    DELETE((*linear)->data);
    DELETE(*linear);
    *linear = NULL;
}

void a_linear_set(APLinear linear, const void *data, size_t index) {
    if (linear == NULL) {
        LOG_MSG(LOG_LEVEL_ERROR, "线性表为空");
        return;
    }
    if (index >= linear->total) {
        LOG_MSG(LOG_LEVEL_ERROR, "线性表下标越界");
        return;
    }
    if (linear->flags[index] == 'Y') {
        LOG_MSG(LOG_LEVEL_INFO, "将覆盖线性表中原有的数据。");
        linear->count -= 1; // 后续还会加回来
    }
    if (data == NULL) {
        LOG_MSG(LOG_LEVEL_ERROR, "传入的数据为NULL，不允许插入");
        return;
    }
    memcpy(linear->data + index * linear->data_size, data, linear->data_size);
    linear->flags[index] = 'Y';
    linear->count += 1;
}

void *ap_linear_get(APLinear linear, size_t index) {
    if (linear == NULL) {
        LOG_MSG(LOG_LEVEL_ERROR, "线性表为空");
        return NULL;
    }
    if (index >= linear->total) {
        LOG_MSG(LOG_LEVEL_ERROR, "线性表下标越界");
        return NULL;
    }
    if (linear->flags[index] == 'N') {
        LOG_MSG(LOG_LEVEL_INFO, "线性表[%d]没有数据", index);
    }
    return linear->data + index * linear->data_size;
}

void a_linear_del(APLinear linear, size_t index) {
    if (linear == NULL) {
        LOG_MSG(LOG_LEVEL_ERROR, "线性表为空");
        return;
    }
    if (index >= linear->total) {
        LOG_MSG(LOG_LEVEL_ERROR, "线性表下标越界");
        return;
    }
    if (linear->flags[index] == 'N') {
        LOG_MSG(LOG_LEVEL_INFO, "线性表[%d]没有数据", index);
        return;
    }
    memset(linear->data + index * linear->data_size, 0, linear->data_size);
    linear->flags[index] = 'N';
    linear->count -= 1;
    LOG_MSG(LOG_LEVEL_INFO, "线性表[%d]数据已删除", index);
}

void a_linear_sort(APLinear linear, int (*operate)(const void *, const void *)) {
    // 使用 C 语言本身提供的排序函数 qsort()
    qsort(linear->data, linear->total, linear->data_size, operate);
}

void a_linear_print(APLinear linear, void (*operate)(void *), const char *end) {
    if (linear == NULL) {
        LOG_MSG(LOG_LEVEL_ERROR, "线性表为空");
        return;
    }
    for (int i = 0; i < linear->total; i++) {
        operate(linear->data + i * linear->data_size);
    }
    if (end) printf("%s", end);
}

void a_linear_print_info(APLinear linear) {
    if (linear == NULL) {
        LOG_MSG(LOG_LEVEL_ERROR, "线性表为空");
        return;
    }
    printf("\n");
    printf("ALinear Information:\n");
    printf("\tData size : %zu bytes\n", linear->data_size);
    printf("\tData type : %s\n", linear->data_type);
    printf("\tCount     : %zu\n", linear->count);
    printf("\tTotal     : %zu\n", linear->total);
    printf("\n");
}

const char *a_linear_get_type(APLinear linear) {
    if (linear == NULL) {
        LOG_MSG(LOG_LEVEL_ERROR, "线性表为空");
        return NULL;
    }
    return linear->data_type;
}

size_t a_linear_get_count(APLinear linear) {
    if (linear == NULL) {
        LOG_MSG(LOG_LEVEL_ERROR, "线性表为空");
        return -1;
    }
    return linear->count;
}

size_t a_linear_get_total(APLinear linear) {
    if (linear == NULL) {
        LOG_MSG(LOG_LEVEL_ERROR, "线性表为空");
        return -1;
    }
    return linear->total;
}
