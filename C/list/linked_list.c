/*
 * File: linked_list.c
 * Author: Finnur Smári Torfason
 * Compiler: GCC 4.8.2
 */

#include "linked_list.h"

void init_list_node(struct node_t *list) {
  list->next = list;
  list->prev = list;
}

void list_append(struct node_t *new, struct node_t *old) {
  __list_add(new, old, old->next);
}

void list_prepend(struct node_t *new, struct node_t *old) {
  __list_add(new, old->prev, old);
}

void list_remove(struct node_t *node) {
  __list_remove(node->prev, node->next);
  node->prev = (void *)0;
  node->next = (void *)0;
}

