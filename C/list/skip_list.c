/*
 * File: skip_list.c
 * Author: Finnur Smári Torfason
 * Compiler: GCC 4.9.1
 */

#include <time.h>

#include "skip_list.h"

static int seed_set = 0;

int rand_height(int max) {
  if ( !seed_set ) {
    seed_set = 1;
    srand((unsigned int)time(NULL));
  }

  static int bits = 0;
  static int reset = 0;
  int h, found = 0;

  for ( h = 0; !found; h++ ) {
    if ( reset == 0 ) {
      bits = rand();
      reset = sizeof(int) * BYTE_LEN;
    }

    found = bits & 1;
    bits = bits >> 1;
    --reset;
  }

  if ( h >= max ) {
    h = max - 1;
  }

  return h;
}

void init_skip_list(struct skip_list_t *skip) {
  struct skip_node_t *tmp;

  skip->height = 1;
  skip->length = 0;

  skip->head = (struct skip_node_t *)malloc(sizeof(struct skip_node_t));

  init_list_node(&skip->head->node_vert);
  init_list_node(&skip->head->node_horiz);

  tmp = (struct skip_node_t *)malloc(sizeof(struct skip_node_t));
  tmp->data = NULL;
  tmp->level = 1;

  list_append(&(tmp->node_vert), &(skip->head->node_vert));
  list_append(&(tmp->node_horiz), &(skip->head->node_horiz));
}

int skip_insert(struct skip_list_t *skip, void *value) {
  struct skip_node_t *tmp, *save = NULL;

  int h = rand_height(MAX_HEIGHT);
  if ( h > skip->height ) {
    skip->height++;

    tmp = (struct skip_node_t *)malloc(sizeof(struct skip_node_t));
    tmp->data = NULL;
    tmp->level = skip->height;

    list_append(&(tmp->node_vert), &(skip->head->node_vert));
    init_list_node(&(tmp->node_horiz));
  }

  if ( skip->length == 0 ) {
    skip->length++;

    tmp = (struct skip_node_t *)malloc(sizeof(struct skip_node_t));
    tmp->data = value;

    list_append(&(tmp->node_horiz), &(skip->head->node_horiz));
    init_list_node(&(tmp->node_vert));

    for ( int i = 1; i < h; i++ ) {
      tmp = (struct skip_node_t *)malloc(sizeof(struct skip_node_t));
      tmp->data = value;

      list_append(&(tmp->node_vert), &(skip->head->node_horiz));
      init_list_node(&(tmp->node_vert));
    }
  } 

  return 1;
}

