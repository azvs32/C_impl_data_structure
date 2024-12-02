//
// Created by azvs on 24-11-29.
//

#include "../include/azvs_base.h"
#include "../include/azvs_linked.h"

#include <stdio.h>
#include <string.h>

//////////////////////////////////////////////////
//     Linked 的实现
//////////////////////////////////////////////////

APLinked __a_linked_init(const size_t data_size, char *data_type) {
    APLinked linked = NEW(ALinked);
    linked->data_size = data_size;
    linked->data_type = data_type;
    linked->head = NULL;
    linked->tail = NULL;
    linked->count = 0;
    return linked;
}

void __a_linked_free(APLinked *linked) {
    __CHECK_WARN(linked==NULL || *linked==NULL, "尝试释放空链表", return);
    while ((*linked)->head != NULL) {
        APLinkedNode del = (*linked)->head;
        (*linked)->head = (*linked)->head->next;
        DELETE(del);
    }
    DELETE(*linked);
    *linked = NULL;
}

APLinkedNode __a_linked_node_init(void *data, const size_t data_size) {
    APLinkedNode new_node = NEW(ALinkedNode);
    new_node->data = NEW_SIZE(data_size);
    memcpy(new_node->data, data, data_size);
    new_node->prev = NULL;
    new_node->next = NULL;
    return new_node;
}

void a_linked_insert_head(APLinked linked, void *data) {
    __CHECK_ERROR(linked == NULL, "链表为空，无法插入链表元素", return);
    APLinkedNode new_node = __a_linked_node_init(data, linked->data_size);
    if (linked->count == 0) {
        linked->head = new_node;
        linked->tail = new_node;
        linked->count += 1;
        return;
    }
    new_node->next = linked->head;
    new_node->next->prev = new_node;
    linked->head = new_node;
    linked->count += 1;
}

void a_linked_insert_tail(APLinked linked, void *data) {
    __CHECK_ERROR(linked == NULL, "链表为空，无法插入链表元素", return);
    APLinkedNode new_node = __a_linked_node_init(data, linked->data_size);
    if (linked->count == 0) {
        linked->head = new_node;
        linked->tail = new_node;
        linked->count += 1;
        return;
    }
    new_node->prev = linked->tail;
    new_node->prev->next = new_node;
    linked->tail = new_node;
    linked->count += 1;
}

void a_linked_remove_head(APLinked linked) {
    __CHECK_ERROR(linked == NULL, "链表为空，无法删除链表元素", return);
    __CHECK_WARN(linked->count == 0, "链表中没有数据，无法删除数据", return);
    if (linked->count == 1) {
        DELETE(linked->head);
        linked->head = NULL;
        linked->tail = NULL;
        linked->count -= 1;
        return;
    }
    APLinkedNode del = linked->head;
    linked->head = del->next;
    linked->head->prev = NULL;
    DELETE(del);
    linked->count -= 1;
}

void a_linked_remove_tail(APLinked linked) {
    __CHECK_ERROR(linked == NULL, "链表为空，无法删除链表元素", return);
    __CHECK_WARN(linked->count == 0, "链表中没有数据，无法删除数据", return);
    if (linked->count == 1) {
        DELETE(linked->head);
        linked->head = NULL;
        linked->tail = NULL;
        linked->count -= 1;
        return;
    }
    APLinkedNode del = linked->tail;
    linked->tail = del->prev;
    linked->tail->next = NULL;
    DELETE(del);
    linked->count -= 1;
}

void a_linked_print(APLinked linked, void (*operate)(void *), const char *end) {
    __CHECK_ERROR(linked == NULL, "链表为空，无法输出链表元素", return);
    APLinkedNode node = linked->head;
    while (node != NULL) {
        operate(node->data);
        node = node->next;
    }
    if (end) printf("%s", end);
}

void a_linked_print_info(APLinked linked) {
    __CHECK_ERROR(linked == NULL, "链表为空，无法输出链表基本信息", return);
    printf("\n");
    printf("ALinked Information:\n");
    printf("\tData size : %zu bytes\n", linked->data_size);
    printf("\tData type : %s\n", linked->data_type);
    printf("\tCount     : %zu\n", linked->count);
    printf("\n");
}
