/*
 * File: queue.c
 * Author: Finnur Smári Torfason
 * Compiler: GCC 4.8.2
 */
#include "queue.h"

void queue_init(struct queue_t *q) {
  init_list_node(&q->node);
}

void queue_enqueue(struct queue_t *q, void *data) {
  struct queue_t *tmp;

  tmp = (struct queue_t *)malloc(sizeof(struct queue_t));

  tmp->data = data;

  list_append(&(tmp->node), &(q->node));
}

void * queue_dequeue(struct queue_t *q) {
  struct queue_t *tmp;
  void * ret_val;

  tmp = get_list_node(q->node.next, struct queue_t, node);
  ret_val = tmp->data;

  list_remove(q->node.next);
  free(tmp);

  return ret_val;
}

