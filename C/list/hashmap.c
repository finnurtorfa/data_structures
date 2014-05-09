/*
 * File: hashmap.c
 * Author: Finnur Smári Torfason
 * Compiler: GCC 4.8.2
 */

#include "hashmap.h"

void init_hashmap(struct hashmap_t *map) {
  map->size = 0;
  map->num_buckets = DEFAULT_NUM_BUCKETS;
  map->buckets = (struct item_t **) malloc(sizeof(struct item_t *) * map->num_buckets);

  for ( int i = 0; i < map->num_buckets; i ++ ) {
    LIST_NODE_INIT(&(map->buckets[i])->node);
  }

  d_array_init(&map->items);
}
