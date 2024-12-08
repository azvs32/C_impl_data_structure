//
// Created by azvs on 24-11-29.
//

#ifndef AZVS_LINKED_H
#define AZVS_LINKED_H

//////////////////////////////////////////////////
//     Linked 的实现
//////////////////////////////////////////////////

typedef struct azvs_linked_node {
    // 存放链表数据
    void *data;
    // 指向上一个节点
    struct azvs_linked_node *prev;
    // 指向下一个节点
    struct azvs_linked_node *next;
} ALinkedNode, *APLinkedNode;

typedef struct azvs_linked {
    // 链表的头部节点
    APLinkedNode head;
    // 链表的尾部节点
    APLinkedNode tail;
    // 链表中元素的大小
    size_t data_size;
    // 链表中元素的类型
    char *data_type;
    // 链表的节点个数
    size_t count;
} ALinked, *APLinked;

/**
* @brief 初始化链表，使用 #define 简化
* @param data_size 单个元素占用的大小 sizeof(type)
* @param data_type 存入元素的数据类型 ElementType
*/
APLinked __a_linked_init(size_t data_size, char *data_type);

#define a_linked_init(type) __a_linked_init(sizeof(type), #type)

/**
* @brief 释放链表，使用 #define 简化
* 释放成功后，指针指向 NULL。使用宏是为了释放时不需要 &
* @param linked 需要释放的链表
*/
void __a_linked_free(APLinked *linked);

#define a_linked_free(linked) __a_linked_free(&(linked))

/**
* @brief 创建链表节点，拷贝操作
* @param data 需要创建的数据
* @param data_size 数据大小
*/
APLinkedNode __a_linked_node_init(void *data, size_t data_size);

/**
* @brief 释放链表节点
* @param node 需要释放的链表节点
*/
void __a_linked_node_free(APLinkedNode *node);

/**
* @brief 在链表头部插入数据
* @param linked 需要操作的链表
* @param data 需要插入的数据
*/
void a_linked_insert_head(APLinked linked, void *data);

/**
* @brief 在链表尾部插入数据
* @param linked 需要操作的链表
* @param data 需要插入的数据
*/
void a_linked_insert_tail(APLinked linked, void *data);

/**
* @brief 删除链表头部数据
* @param linked 需要操作的链表
*/
void a_linked_remove_head(APLinked linked);

/**
* @brief 删除链表尾部数据
* @param linked 需要操作的链表
*/
void a_linked_remove_tail(APLinked linked);

/**
 * @brief 输出链表的每个元素
 * @param linked 需要操作的线性表
 * @param operate 回调函数，指定输出规则
 * @param end 结束输出，可指定为 NULL
 */
void a_linked_print(APLinked linked, void (*operate)(void *), const char *end);

/**
* @brief 输出链表的基本信息
* @param linked 需要操作的链表
*/
void a_linked_print_info(APLinked linked);

const char *a_linked_get_type(APLinked linked);

size_t a_linked_get_count(APLinked linked);
#endif //AZVS_LINKED_H
