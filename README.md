# C_impl_data_structure
C语言版数据结构的实现
```c
// list的测试代码
#include "./include/azvs_data_structure.h"
#include <stdio.h>

typedef struct {
    int x;
    int y;
} Point;

Point p1 = {1, 2};
Point p2 = {2, 4};
Point p3 = {3, 6};
Point p4 = {4, 8};
Point p5 = {5, 10};

void operation_point_print(void *data) {
    Point *p = (Point *)data;
    printf("[x:%d,y:%d]", p->x, p->y);
}

int main(void)
{
    set_log_level(LOG_LEVEL_DEBUG);
    AList *list;
    a_list_init(&list);
    // a_list_insert_head(list, &p1);
    // a_list_insert_head(list, &p2);
    // a_list_insert_head(list, &p3);
    // a_list_insert_head(list, &p4);
    // a_list_insert_head(list, &p5);
    a_list_insert_rear(list, &p1);
    a_list_insert_rear(list, &p2);
    a_list_insert_rear(list, &p3);
    a_list_insert_rear(list, &p4);
    a_list_insert_rear(list, &p5);
    a_list_remove_head(list, NULL);
    a_list_remove_head(list, NULL);
    a_list_remove_head(list, NULL);
    a_list_remove_head(list, NULL);
    a_list_remove_head(list, NULL);
    a_list_remove_head(list, NULL);
    a_list_print(list, operation_point_print, "\n");
    a_list_free(&list);
    return 0;
}
```