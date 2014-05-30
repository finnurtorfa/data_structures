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

  list_prepend(&(tmp->node), &(q->node));
}

void queue_dequeue(struct queue_t *q) {
  struct queue_t *tmp;

  if ( queue_is_empty(q) ) {
    return;
  }

  tmp = get_list_node(q->node.next, struct queue_t, node);

  list_remove(q->node.next);
  free(tmp);
}

void * queue_peek(struct queue_t *q) {
  struct queue_t *tmp;

  if ( queue_is_empty(q) ) {
    return NULL;
  }

  tmp = get_list_node(q->node.next, struct queue_t, node);

  return tmp->data;
}

bool queue_is_empty(struct queue_t *q) {
  return q == get_list_node(q->node.next, struct queue_t, node);
}

