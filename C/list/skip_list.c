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
  struct skip_node_t *tmp, *head, *save = NULL;
  struct skip_node_t *tmp_v = NULL, *tmp_h = NULL;
  struct node_t *pos_v, *q_v, *pos_h, *q_h;

  if ( skip_search(skip, value) == 1 ) {
    return -1;
  }

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

    for_each_reverse(pos_h, q_h, &tmp_v->node_h) {
      tmp_h = get_list_node(pos_h, struct skip_node_t, node_h);

      if ( value < tmp_h->data || &tmp_v->node_h == pos_h->prev ) {
        if ( tmp_v->level <= h ) {
          tmp = (struct skip_node_t *)malloc(sizeof(struct skip_node_t));
          tmp->level = tmp_h->level;
          tmp->data = value;

          init_list_node(&tmp->node_v);
          list_prepend(&tmp->node_h, &tmp_h->node_h);

          if ( save ) {
            list_append(&save->node_v, &tmp->node_v);
          }

          save = tmp;
        }

        if ( tmp_h->level == 1 ) {
          skip->length++;

          return 1;
        }

        q_h = (&tmp_h->node_v)->next;
        q_h++;
        pos_v = pos_v->next;
        tmp_v = get_list_node(pos_v, struct skip_node_t, node_v);
      }
    }

    if ( !tmp_h ) {
      tmp = (struct skip_node_t *)malloc(sizeof(struct skip_node_t));
      tmp->level = tmp_v->level;
      tmp->data = value;

      init_list_node(&tmp->node_v);
      list_prepend(&tmp->node_h, &tmp_v->node_h);

      if ( save ) {
        list_append(&save->node_v, &tmp->node_v);
      }

      save = tmp;
    }
  }

  skip->length++;

  return 1;
}

void skip_remove(struct skip_list_t *skip, void *value) {
  struct skip_node_t *tmp, *head, *save = NULL;
  struct skip_node_t *tmp_v = NULL, *tmp_h = NULL;
  struct node_t *pos_v, *q_v, *pos_h, *q_h;

  head = skip->head;

  for_each(pos_v, q_v, &head->node_v) {
    tmp_v = get_list_node(pos_v, struct skip_node_t, node_v);

    for_each(pos_h, q_h, &tmp_v->node_h) {
      tmp_h = get_list_node(pos_h, struct skip_node_t, node_h);
    }
  }
}

int skip_search(struct skip_list_t *skip, void *value) {
  struct skip_node_t *head;
  struct skip_node_t *tmp_v = NULL, *tmp_h = NULL;
  struct node_t *pos_v, *q_v, *pos_h, *q_h;

  head = skip->head;

  for_each(pos_v, q_v, &head->node_v) {
    tmp_v = get_list_node(pos_v, struct skip_node_t, node_v);

    for_each_reverse(pos_h, q_h, &tmp_v->node_h) {
      tmp_h = get_list_node(pos_h, struct skip_node_t, node_h);

      if ( tmp_h->data == value ) {
        return 1;
      }

      if ( &tmp_v->node_h == pos_h->prev ) {
        if ( tmp_v->level != 1 ) {
          q_h = (&tmp_h->node_v)->next;
          q_h++;
          pos_v = pos_v->next;
          tmp_v = get_list_node(pos_v, struct skip_node_t, node_v);
        }
      }
    }
  }

  return -1;
}

