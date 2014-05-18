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
    if ( strcmp(key, item->key) == 0 ) {
      /* Free the value if it is already taken */
      if ( item->value != NULL ) free(item->value);

      item->value = malloc(len);
      memcpy(item->value, val, len);

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

  struct node_t *pos, *q;

  for_each(pos, q, &item->node) {
    if ( strcmp(key, item->key) == 0 ) 
      return item->value;
  }

  return NULL;
}

void hashmap_remove(struct hashmap_t *map, char *key) {
  unsigned long hash = __djb_hash((unsigned char *)key) % map->num_buckets;
  char *tmp_key;

  struct item_t *item = map->buckets[hash];
  struct item_t *tmp;

  struct node_t *pos, *q;

  for_each(pos, q, &item->node) {
    if ( strcmp(key, item->key) == 0 ) {
      tmp = get_list_node(pos, struct item_t, node);
      list_remove(pos);
      
      for ( int i = 0; i < map->keys.used; i++ ) {
        if ( strcmp(key, (char *)&(map->keys).data[i]) ) {
          tmp_key = (char *)d_array_remove(&map->keys, i);
          break;
        }
      }

      free(tmp_key);
      free(tmp->key);
      free(tmp->value);
      free(tmp);

      map->size--;
    }
  }
}

void hashmap_delete(struct hashmap_t *map) {
  struct item_t *item, *tmp;
  struct node_t *pos, *q;
  char *tmp_key;

  for ( int i = 0; i < map->num_buckets; i++ ) {
    item = map->buckets[i];

    for_each(pos, q, &item->node) {
      tmp = get_list_node(pos, struct item_t, node);
      list_remove(pos);

      free(tmp->key);
      free(tmp->value);
      free(tmp);
    }

    tmp_key = (char *)d_array_remove(&map->keys, i);

    free(tmp_key);
  }

  free(&map->keys);
  free(&map->buckets);
  free(map);
}

void hashmap_resize(struct hashmap_t *map, int num_buckets) {
  map->buckets = (struct item_t **) 
                  malloc(sizeof(struct item_t *) * map->num_buckets);

  if ( num_buckets > map->num_buckets )
    for ( int i = map->num_buckets; i < num_buckets; i++ ) {
      LIST_NODE_INIT(&(map->buckets[i])->node);
    }

  for (int i = 0; i < map->size; i++ ) {
    char * key = (char *)&(map->keys).data[i];
    unsigned long hash = __djb_hash((unsigned char *)key) % map->num_buckets;
    
    struct item_t *item = map->buckets[hash];
    struct item_t *tmp;
    struct node_t *pos, *q;

    for_each(pos, q, &item->node) {
      if ( strcmp(item->key, key) == 0 ) {
        tmp = get_list_node(pos, struct item_t, node);
        list_remove(pos);

        break;
      }
    }

    hash = __djb_hash((unsigned char *)key) % num_buckets;

    list_append(&(tmp->node), &(map->buckets[hash]->node));
  }

  map->num_buckets = num_buckets;
}

