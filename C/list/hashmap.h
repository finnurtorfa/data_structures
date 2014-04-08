#pragma once
/*
 * File: hashmap.h
 * Author: Finnur Smári Torfason
 * Compiler: GCC 4.8.2
 *
 * A basic implementation of a hashmap
 */

#include "linked_list.h"
#include "dynamic_array.h"

struct item_t {
  char *key;
  void *item;
  struct node_t node;
}

struct hashmap_t {
  struct item_t **buckets;
  struct d_array_t items;
  int size;
  int num_buckets;
}
