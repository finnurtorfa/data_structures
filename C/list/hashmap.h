#pragma once
/*
 * File: hashmap.h
 * Author: Finnur Smári Torfason
 * Compiler: GCC 4.8.2
 *
 * A basic implementation of a hashmap
 */

#include <string.h>

#include "linked_list.h"
#include "dynamic_array.h"

#define DEFAULT_NUM_BUCKETS 100

struct item_t {
  char *key;
  void *value;
  struct node_t node;
};

struct hashmap_t {
  struct item_t **buckets;
  struct d_array_t keys;
  int size;
  int num_buckets;
};

/**
 * Initialize the hashmap
 *
 * @map: A hashmap
 */
void hashmap_init(struct hashmap_t *map);

/**
 * Insert key/value pair to the hashmap
 *
 * @map: The hashmap to which the key/value pair will be inserted
 * @key: A key which can be mapped to a value
 * @val: The value to which the key is mapped to
 * @len: The length of the value in bytes.
 */
void hashmap_insert(struct hashmap_t *map, char *key, void *val , size_t len);

/**
 * Get a value, referenced by a key
 *
 * @map: The hashmap whose value to return
 * @key: The key to search for
 */
void * hashmap_get(struct hashmap_t *map, char *key);

/**
 * Remove item from the list 
 *
 * @map: A hashmap to remove an item from
 * @key: The key pointing to the item to remove
 */
void hashmap_remove(struct hashmap_t *map, char *key);

/**
 * A hashing function by Daniel J. Bernstein. A 'times 33' function with 
 * addition. It basically uses a function like
 *
 * hash(i) = hash(i-1)*33 + key[i]
 *
 * The function is not meant to be called directly
 *
 * @key: The key to hash
 */
static inline unsigned long __djb_hash(unsigned char *key) {
  unsigned long hash = 5381;
  int c;

  while ( (c = *key++) ) 
    hash = ((hash << 5) + hash) + c;

  return hash;
}

