/*
 * File: deque.c
 * Author: Finnur Smári Torfason
 * Compiler: GCC 4.8.2
 */
#include "deque.h"

void deque_init(struct deque_t *q) {
  init_list_node(&q->node);
}

void deque_push(struct deque_t *q, void *data) {
  struct deque_t *tmp;

  tmp = (struct deque_t *)malloc(sizeof(struct deque_t));

  tmp->data = data;

  list_prepend(&(tmp->node), &(q->node));
}

void deque_push_left(struct deque_t *q, void *data) {
  struct deque_t *tmp;

  tmp = (struct deque_t *)malloc(sizeof(struct deque_t));

  tmp->data = data;

  list_append(&(tmp->node), &(q->node));
}


void deque_pop(struct deque_t *q) {
  struct deque_t *tmp;

  if ( deque_is_empty(q) ) {
    return;
  }

  tmp = get_list_node(q->node.next, struct deque_t, node);

  list_remove(q->node.next);
  free(tmp);
}

void deque_pop_left(struct deque_t *q) {
  struct deque_t *tmp;

  if ( deque_is_empty(q) ) {
    return;
  }

  tmp = get_list_node(q->node.prev, struct deque_t, node);

  list_remove(q->node.prev);
  free(tmp);
}

void * deque_peek(struct deque_t *q) {
  struct deque_t *tmp;

  if ( deque_is_empty(q) ) {
    return NULL;
  }

  tmp = get_list_node(q->node.next, struct deque_t, node);

  return tmp->data;
}

void * deque_peek_left(struct deque_t *q) {
  struct deque_t *tmp;

  if ( deque_is_empty(q) ) {
    return NULL;
  }

  tmp = get_list_node(q->node.prev, struct deque_t, node);

  return tmp->data;
}

bool deque_is_empty(struct deque_t *q) {
  return q == get_list_node(q->node.next, struct deque_t, node);
}

