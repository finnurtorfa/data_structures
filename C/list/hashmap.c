/*
 * File: hashmap.c
 * Author: Finnur Smári Torfason
 * Compiler: GCC 4.8.2
 */

#include "hashmap.h"

void hashmap_init(struct hashmap_t *map) {
  map->size = 0;
  map->num_buckets = DEFAULT_NUM_BUCKETS;
  map->buckets = (struct item_t **) 
                  malloc(sizeof(struct item_t *) * map->num_buckets);

  for ( int i = 0; i < map->num_buckets; i++ ) {
    struct item_t *tmp = (struct item_t *)malloc(sizeof(struct item_t));

    LIST_NODE_INIT(&tmp->node);
    map->buckets[i] = tmp;
  }

  d_array_init(&map->keys);
}

void hashmap_insert(struct hashmap_t *map, char *key, void *val , size_t len) {
  int keylen = strlen(key);
  unsigned long hash = __djb_hash((unsigned char *)key) % map->num_buckets;

  struct item_t *item = map->buckets[hash];
  struct item_t *tmp;

  struct node_t *pos, *q;

  for_each(pos, q, &item->node) {
    /* If key already exists */
    tmp = get_list_node(pos, struct item_t, node);
    if ( strcmp(key, tmp->key) == 0 ) {
      tmp->value = realloc(tmp->value, len);
      memcpy(tmp->value, val, len);

      return;
    }
  }

  tmp = (struct item_t *)malloc(sizeof(struct item_t));
  tmp->key = malloc(keylen + 1);
  tmp->value = malloc(len);

  memcpy(tmp->key, key, keylen + 1);
  memcpy(tmp->value, val, len);

  list_append(&(tmp->node), &(map->buckets[hash]->node));
  d_array_append(&map->keys, (char *)tmp->key);

  map->size++;
}

void * hashmap_get(struct hashmap_t *map, char *key) {
  if ( key == NULL ) return NULL;

  unsigned long hash = __djb_hash((unsigned char *)key) % map->num_buckets;

  struct item_t *item = map->buckets[hash];
  struct item_t *tmp;

  struct node_t *pos, *q;

  for_each(pos, q, &item->node) {
    tmp = get_list_node(pos, struct item_t, node);
    if ( strcmp(key, tmp->key) == 0 ) 
      return tmp->value;
  }

  return NULL;
}

void hashmap_remove(struct hashmap_t *map, char *key) {
  unsigned long hash = __djb_hash((unsigned char *)key) % map->num_buckets;
  struct item_t *item = map->buckets[hash];
  struct item_t *tmp;

  struct node_t *pos, *q;

  for_each(pos, q, &item->node) {
    tmp = get_list_node(pos, struct item_t, node);

    if ( strcmp(key, tmp->key) == 0 ) {
      list_remove(pos);
      
      for ( int i = 0; i < map->keys.used; i++ ) {
        if ( strcmp(key, (char *)&(map->keys).data[i]) ) {
          free((char *)d_array_remove(&map->keys, i));
          break;
        }
      }

      free(tmp->value);
      free(tmp);

      map->size--;
    }
  }
}

void hashmap_delete(struct hashmap_t *map) {
  struct item_t *item, *tmp;
  struct node_t *pos, *q;

  for ( int i = 0; i < map->size; i++ ) {
    int hash = __djb_hash((unsigned char *)map->keys.data[0]) % map->num_buckets;
    item = map->buckets[hash];

    for_each(pos, q, &item->node) {
      tmp = get_list_node(pos, struct item_t, node);
      list_remove(pos);

      free(tmp->key);
      free(tmp->value);
      free(tmp);
    }

    (char *)d_array_remove_head(&map->keys);
  }

  for ( int i = 0; i < map->num_buckets; i++ ) {
    item = map->buckets[i];

    free(item);
  }

  free(map->keys.data);
  free(map->buckets);
  free(&map->buckets);
}

void hashmap_resize(struct hashmap_t *map, int num_buckets) {
  map->buckets = (struct item_t **) 
                  realloc(map->buckets, 
                          sizeof(struct item_t *) * num_buckets);

  if ( num_buckets > map->num_buckets )
    for ( int i = map->num_buckets; i < num_buckets; i++ ) {
      struct item_t *tmp = (struct item_t *)malloc(sizeof(struct item_t));

      LIST_NODE_INIT(&tmp->node);
      map->buckets[i] = tmp;
    }

  for (int i = 0; i < map->size; i++ ) {
    char * key = (char *)map->keys.data[i];
    unsigned long hash = __djb_hash((unsigned char *)key) % map->num_buckets;
    
    struct item_t *item = map->buckets[hash];
    struct item_t *tmp;
    struct node_t *pos, *q;

    for_each(pos, q, &item->node) {
      tmp = get_list_node(pos, struct item_t, node);
      
      if ( strcmp(tmp->key, key) == 0 ) {
        list_remove(pos);

        break;
      }
    }

    hash = __djb_hash((unsigned char *)key) % num_buckets;

    list_append(&(tmp->node), &(map->buckets[hash]->node));
  }

  map->num_buckets = num_buckets;
}

