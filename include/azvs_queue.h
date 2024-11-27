#ifndef AZVS_QUEUE_H
#define AZVS_QUEUE_H

#include <stddef.h>

// 双向队列
typedef struct {
    void **data; // 存储双向队列元素的数组
    int front; // 记录队首位置
    int rear; // 记录队尾位置
    size_t size; // 当前元素数量
    size_t total; // 预期总容量
} AQueue;

/**
 * 双向队列初始化操作
 * @param queue 指定双向队列地址
 * @param total 指定队列的预期总容量
 * @return 成功创建返回 0
 */
int a_queue_init(AQueue *queue, size_t total);

/**
 * 清空双向队列操作
 * @param queue 指定双向队列地址
 */
void a_queue_free(AQueue *queue);

/**
 * 队列头部插入数据
 * @param queue 指定双向队列地址
 * @param e 指定需要插入的元素地址
 * @return 成功插入返回 0
 */
int a_queue_push_front(AQueue *queue, void *e);

/**
 * 队列尾部插入数据
 * @param queue 指定双向队列地址
 * @param e 指定需要插入的元素地址
 * @return 成功插入返回 0
 */
int a_queue_push_rear(AQueue *queue, void *e);

/**
 * 队列头部取出数据
 * @param queue 指定双向队列地址
 * @param e 保存取出的元素地址
 * @return 成功取出返回 0
 */
int a_queue_pop_front(AQueue *queue, void *e);

/**
 * 队列尾部取出数据
 * @param queue 指定双向队列地址
 * @param e 保存取出的元素地址
 * @return 成功取出返回 0
 */
int a_queue_pop_rear(AQueue *queue, void *e);

/**
 * 返回队列头部数据
 * @param queue 指定双向队列地址
 * @param e 保存获取的元素地址
 * @return 成功则返回 0
 */
int a_queue_value_front(AQueue *queue, void *e);

/**
 * 返回队列尾部数据
 * @param queue 指定双向队列地址
 * @param e 保存获取的元素地址
 * @return 成功则返回 0
 */
int a_queue_value_rear(AQueue *queue, void *e);

/**
 * 判断双向队列是否为空
 * @param queue 指定双向队列地址
 * @return 如果队列中没有元素，则返回真
 */
int a_queue_is_empty(AQueue *queue);

/**
 * 打印双向队列的所有元素
 * @param queue 指定双向队列地址
 * @param operation 指定输出规则
 * @param end 自定义结束符号，若为NULL，则不定义。通常可以指定为"\n"
 * @return 操作成功返回 0
 */
int a_queue_print(AQueue *queue, void (*operation)(void *), char *end);

/**
 * 获取双向队列的大小
 * @param queue 指定双向队列地址
 * @return 获取队列当前已经存入数据的大小
 */
size_t a_queue_get_size(AQueue *queue);

/**
 * 获取双向队列的最大容量
 * @param queue 指定双向队列地址
 * @return 获取队列当前总容量
 */
size_t a_queue_get_total(AQueue *queue);

#endif // !AZVS_QUEUE_H
