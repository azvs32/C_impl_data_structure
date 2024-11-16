#ifndef AZVS_LIST_H
#define AZVS_LIST_H

#include <stddef.h>

// 双向链表结构体
typedef struct azvs_list_node {
  void *data;                  // 元素数据
  struct azvs_list_node *pre;  // 指向上一个节点
  struct azvs_list_node *next; // 指向下一个节点
} AListNode;

typedef struct {
  AListNode *head; // 链表的头节点
  AListNode *rear; // 链表的尾节点
  size_t size;     // 链表节点中元素的数量
} AList;

/////////////////////////

/**
 * 链表初始化操作
 * @param list 链表地址，需要改变所以使用二级指针
 */
void a_list_init(AList **list);

/**
 * 清空指定链表
 * @param list 链表地址，需要改变所以使用二级指针
 */
void a_list_free(AList **list);

/**
 * 采用头插法插入元素
 * @param list 指定链表地址
 * @param data 元素数据
 */
int a_list_insert_head(AList *list, void *data);

/**
 * 采用尾法插入元素
 * @param list 指定链表地址
 * @param data 元素数据
 */
int a_list_insert_rear(AList *list, void *data);

// /**
//  * 删除头部数据
//  * @param list 指定链表地址
//  * @param data 被删除元素数据，若不需要该数据则使用NULL
//  */
// int a_list_remove_head(AList *list, void *data);
//
// /**
//  * 删除尾部数据
//  * @param list 指定链表地址
//  * @param data 被删除元素数据，若不需要该数据则使用NULL
//  */
// int a_list_remove_rear(AList *list, void *data);

/**
* 删除链表中所有满足条件的元素
* @param list 指定链表地址
* @param operation 自定义查找规则：找到满足条件的元素需返回 0
* @return 返回成功删除的个数
*/
int a_list_remove(AList *list, int (*operation)(void *, void *));

/**
 * 判断指定链表是否为空
 * @param list 指定链表地址
 * @return 若链表中没有元素则返回真
 */
int a_list_is_empty(AList *list);

/**
 * 查找元素，查找规则由用户提供
 * @param list 指定链表地址
 * @param operation 自定义查找规则：找到满足条件的元素需返回 0
 * 返回查找到的元素地址
 *
 */
AListNode *a_list_find(AList *list, int (*operation)(void *, void *));

/**
 * 排序链表，排序规则由用户提供
 * @param list 指定链表地址
 * @param operation 自定义排序规则：使用正负来决定升序和降序
 * @return 成功返回 0
 */
int a_list_sort(AList *list, int (*operation)(void *, void *));

/**
 * 打印队列中的所有元素
 * @param list 指定链表地址
 * @param operation 指定输出规则
 * @param end 自定义结束符号，若为NULL，则不定义。通常可以指定为"\n"
 * @return 操作成功返回 0
 */
int a_list_print(const AList *list, void (*operation)(void *), char *end);

/**
 * 获取链表的大小
 * @param stack 指定链表地址
 * @return 获取链表当前已经存入数据的大小
 */
size_t a_list_get_size(AList *list);

/**
 * 获取链表的头节点地址
 * @param stack 指定链表地址
 * @return 头节点地址
 */
AListNode *a_list_get_head(AList *list);

/**
 * 获取链表的尾节点地址
 * @param stack 指定链表地址
 * @return 尾节点地址
 */
AListNode *a_list_get_rear(AList *list);

#endif // !AZVS_LIST_H
