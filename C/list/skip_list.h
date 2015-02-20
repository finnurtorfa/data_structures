#pragma once
/*
 * File: skip_list.h
 * Author: Finnur Smári Torfason
 * Compiler: GCC 4.9.1
 * 
 * An implementation of a skip list using linked lists.
 */
#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

#define BYTE_LEN 8
#define MAX_HEIGHT 24

struct skip_node_t {
  int level;
  void *data;
  struct node_t node_v;
  struct node_t node_h;
};

struct skip_list_t {
  struct skip_node_t *head;
  int height;
  int length;
};

/**
 * Returns a random number in the range [1, max). The value returned is a
 * weighted random number with a probability of 1/2.
 *
 * @max: An integer representing the maximum value of the random number
 *       generator.
 */
int rand_height(int max);

/** 
 * Initialize the skip list
 *
 * @skip: The skip list to initialize
 */
void init_skip_list(struct skip_list_t *skip);

/**
 * Insert a new value into the skip list
 */
int skip_insert(struct skip_list_t *skip, void *value);

/**
 * Search for a value in a skip list
 */
int skip_search(struct skip_list_t *skip, void *value);

