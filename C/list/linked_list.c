/*
 * File: linked_list.c
 * Author: Finnur Smári Torfason
 * Compiler: GCC 4.8.2
 */

#include "list/linked_list.h"

static void init_list_node(struct node_t *list) {
  list->next = list;
  list->prev = list;
}

static void list_append(struct node_t *new, struct node_t *old) {
  __list_add(new, old, old->next);
}

static void list_prepend(struct node_t *new, struct node_t *old) {
  __list_add(new, old->prev, old);
}
