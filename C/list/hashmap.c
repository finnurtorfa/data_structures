/*
 * File: hashmap.c
 * Author: Finnur Smári Torfason
 * Compiler: GCC 4.8.2
 */

#include "hashmap.h"

void hashmap_init(struct hashmap_t *map) {
  map->size = 0;
  map->num_buckets = DEFAULT_NUM_BUCKETS;
  map->buckets = (struct item_t **) malloc(sizeof(struct item_t *) * map->num_buckets);

  for ( int i = 0; i < map->num_buckets; i ++ ) {
    LIST_NODE_INIT(&(map->buckets[i])->node);
  }

  d_array_init(&map->items);
}

void hashmap_insert(struct hashmap_t *map, char *key, void *val , size_t len) {
  int keylen = strlen(key);
  unsigned long hash = __djb_hash((unsigned char *)key) % map->num_buckets;

  struct item_t *item = map->buckets[hash];
  struct item_t *tmp;

  struct node_t *pos, *q;

  for_each(pos, q, &item->node) {
    /* If key already exists */
    if ( strcmp(key, item->key) == 0 ) {
      /* Free the value if it is already taken */
      if ( item->item != NULL ) free(item->item);

      item->item = malloc(len);
      memcpy(item->item, val, len);

      return;
    }
  }

  tmp = (struct item_t *)malloc(sizeof(struct item_t));
  tmp->key = malloc(keylen + 1);
  tmp->item = malloc(len);

  memcpy(tmp->key, key, keylen + 1);
  memcpy(tmp->item, val, len);

  list_append(&(tmp->node), &(map->buckets[hash]->node));
  d_array_append(&map->items, (char *)tmp->key);

  map->size++;
}

