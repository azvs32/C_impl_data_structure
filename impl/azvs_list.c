#include "../include/azvs_list.h"
#include "../include/azvs_base.h"
#include <stdio.h>

void a_list_init(AList **list)
{
    if (list == NULL)
    {
        LOG_MSG(LOG_LEVEL_ERROR, "指针为空，无法初始化链表");
        return;
    }
    *list = NEW(AList);
    (*list)->head = NULL;
    (*list)->rear = NULL;
    (*list)->size = 0;
}

void a_list_free(AList **list)
{
    if (list == NULL || *list == NULL)
    {
        LOG_MSG(LOG_LEVEL_WARN, "指针为空，无需释放链表");
        return;
    }
    while ((*list)->head != (*list)->rear)
    {
        AListNode *tmp = (*list)->head;
        (*list)->head = (*list)->head->next;
        DELETE(tmp);
    }
    if ((*list)->head != NULL)
    {
        DELETE((*list)->head);
        (*list)->head = NULL;
    }
    DELETE(*list);
    *list = NULL;
}

int a_list_insert_head(AList *list, void *data)
{
    if (list == NULL)
    {
        LOG_MSG(LOG_LEVEL_ERROR, "传入的指针为空");
        return -1;
    }
    AListNode *new = NEW(AListNode);
    new->data = data;
    new->pre = NULL;
    new->next = NULL;
    if (list->head == NULL)
    {
        list->head = new;
        list->rear = new;
        list->size += 1;
        return 0;
    }
    new->next = list->head;
    list->head->pre = new;
    list->head = new;
    list->size += 1;
    return 0;
}

int a_list_insert_rear(AList *list, void *data)
{
    if (list == NULL)
    {
        LOG_MSG(LOG_LEVEL_ERROR, "传入的指针为空");
        return -1;
    }
    AListNode *new = NEW(AListNode);
    new->data = data;
    new->pre = NULL;
    new->next = NULL;
    if (list->rear == NULL)
    {
        list->head = new;
        list->rear = new;
        list->size += 1;
        return 0;
    }
    new->pre = list->rear;
    list->rear->next = new;
    list->rear = new;
    list->size += 1;
    return 0;
}

/* int a_list_remove_head(AList *list, void *data)
{
    if (list == NULL)
    {
        LOG_MSG(LOG_LEVEL_ERROR, "传入的指针为空");
        return -1;
    }
    if (list->head == NULL)
    {
        LOG_MSG(LOG_LEVEL_WARN, "传入的链表没有节点可删除");
        return -1;
    }

    if (list->head == list->rear)
    {
        DELETE(list->head);
        list->head = NULL;
        list->rear = NULL;
        list->size -= 1;
        return 0;
    }
    AListNode *del = list->head;
    list->head = list->head->next;
    *data = *(del->data);
    DELETE(del);
    list->size -= 1;
    return 0;
}

int a_list_remove_rear(AList *list, void *data)
{
    if (list == NULL)
    {
        LOG_MSG(LOG_LEVEL_ERROR, "传入的指针为空");
        return -1;
    }
    if (list->head == NULL)
    {
        LOG_MSG(LOG_LEVEL_WARN, "传入的链表没有节点可删除");
        return -1;
    }

    if (list->head == list->rear)
    {
        DELETE(list->rear);
        list->head = NULL;
        list->rear = NULL;
        list->size -= 1;
        return 0;
    }
    AListNode *del = list->rear;
    list->rear = list->rear->pre;
    // data = del->data;
    DELETE(del);
    list->size -= 1;
    return 0;
} */

int a_list_print(const AList *list, void (*operation)(void *), char *end)
{
    if (list == NULL)
    {
        return -1;
    }
    AListNode *cur = list->head;
    while (cur != NULL)
    {
        operation(cur->data);
        cur = cur->next;
    }
    printf("%s", end);
    return 0;
}
