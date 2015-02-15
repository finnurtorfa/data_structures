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
  skip->head->level = 0;
  skip->head->data = NULL;

  init_list_node(&skip->head->node_v);
  init_list_node(&skip->head->node_h);

  tmp = (struct skip_node_t *)malloc(sizeof(struct skip_node_t));
  tmp->data = NULL;
  tmp->level = 1;

  list_append(&(tmp->node_v), &(skip->head->node_v));
  init_list_node(&(tmp->node_h));
}

int skip_insert(struct skip_list_t *skip, void *value) {
  struct skip_node_t *tmp, *head;
  struct skip_node_t *tmp_v = NULL, *tmp_h = NULL;
  struct node_t *pos_v, *q_v, *pos_h, *q_h;

  int insert = 0;
  int h = rand_height(MAX_HEIGHT);

  if ( h > skip->height ) {
    skip->height++;
    h = skip->height;

    tmp = (struct skip_node_t *)malloc(sizeof(struct skip_node_t));
    tmp->data = NULL;
    tmp->level = skip->height;

    list_append(&(tmp->node_v), &(skip->head->node_v));
    init_list_node(&(tmp->node_h));
  }

  head = skip->head;

  for_each(pos_v, q_v, &head->node_v) {
    tmp_v = get_list_node(pos_v, struct skip_node_t, node_v);

    if ( tmp_v->level <= h ) {
      for_each_reverse(pos_h, q_h, &tmp_v->node_h) {
        tmp_h = get_list_node(pos_h, struct skip_node_t, node_h);

        if ( tmp_h->data == NULL || value > tmp_h->data ) {
          continue;
        }

        insert = 1;

        break;
      }

      tmp = (struct skip_node_t *)malloc(sizeof(struct skip_node_t));
      tmp->level = tmp_v->level;
      tmp->data = value;

      init_list_node(&tmp->node_v);

      if ( !insert && tmp_v->level == 1 ) {
        list_append(&tmp->node_h, &head->node_h);
      } else if ( !insert ) {
        list_append(&tmp->node_h, &tmp_v->node_h);
      } else {
        list_append(&tmp->node_h, &tmp_h->node_h);
      }
    }
  }

  return 1;
}

