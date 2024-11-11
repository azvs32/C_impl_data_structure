#include "../include/azvs_queue.h"
#include <stdlib.h>

int a_queue_init(AQueue *queue, size_t total) {
  queue->data = (void **)malloc(total * sizeof(void *));
  if (queue->data == NULL) {
    return -1; // 内存分配失败
  }
  queue->size = 0;
  queue->total = total;
  return 0;
}
