#ifndef AZVS_QUEUE_H
#define AZVS_QUEUE_H

#include <stddef.h>

typedef struct {
  void **data;  // 存储队列元素的数组
  size_t size;  // 当前队列的大小
  size_t total; // 总容量
} AQueue;

/**
 * 队列初始化操作
 * @param queue 指定队列
 * @param total 指定队列总容里
 * @return 成功创建返回 0
 */
int a_queue_init(AQueue *queue, size_t total);

#endif // !AZVS_QUEUE_H
