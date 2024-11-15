#include "../include/azvs_list.h"
#include <stdio.h>
#include <stdlib.h>

int a_list_init(AList *list) {
  if (list == NULL) {
    list = (AList *)malloc(sizeof(AList));
    if (list == NULL) {
      return -1;
    }
  }
  list->head = NULL;
  list->rear = NULL;
  list->size = 0;
  return 0;
}

void a_list_free(AList *list) {
  if (list == NULL) {
    return;
  }
  while (list->head != list->rear) {
    AListNode *t = list->head;
    list->head = list->head->next;
    free(t);
  }
  free(list->head);
  free(list);
}

int a_list_insert_head(AList *list, void *data) {
  if (list == NULL) {
    return -1;
  }
  AListNode *new = (AListNode *)malloc(sizeof(AListNode));
  if (new == NULL) {
    return -1;
  }
  new->data = data;
  new->pre = NULL;
  new->next = NULL;
  if (list->head == NULL) {
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

int a_list_insert_rear(AList *list, void *data) {
  if (list == NULL) {
    return -1;
  }
  AListNode *new = (AListNode *)malloc(sizeof(AListNode));
  if (new == NULL) {
    return -1;
  }
  new->data = data;
  new->pre = NULL;
  new->next = NULL;
  if (list->rear == NULL) {
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

int a_list_remove_head(AList *list, void *data) {
  if (list == NULL || list->head == NULL) {
    return -1;
  }
  if (list->head == list->rear) {
    free(list->head);
    list->head = NULL;
    list->rear = NULL;
    list->size -= 1;
    return 0;
  }
  AListNode *del = list->head;
  list->head = list->head->next;
  free(del);
  list->size -= 1;
  return 0;
}

int a_list_remove_rear(AList *list, void *data) {
  if (list == NULL || list->rear == NULL) {
    return -1;
  }
  if (list->head == list->rear) {
    free(list->rear);
    list->head = NULL;
    list->rear = NULL;
    list->size -= 1;
    return 0;
  }
  AListNode *del = list->rear;
  list->rear = list->rear->pre;
  free(del);
  list->size -= 1;
  return 0;
}

int a_list_print(AList *list, void (*operation)(void *), char *end) {
  if (list == NULL) {
    return -1;
  }
  AListNode *cur = list->head;
  while (cur != NULL) {
    operation(cur->data);
    cur = cur->next;
  }
  printf("%s", end);
  return 0;
}
