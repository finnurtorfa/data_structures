#pragma once
/*
 * File: deque.h
 * Author: Finnur Smári Torfason
 * Compiler: GCC 4.8.2
 *
 * A basic implementation of a deque
 */
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "linked_list.h"

struct deque_t {
  void *data;
  struct node_t node;
};

/**
 * Initialize the deque
 *
 * @q: A deque to initialize
 */
void deque_init(struct deque_t *q);

/**
 * Add data to the back of the deque
 *
 * @q: A deque to add the data to
 * @data: The data to add
 */
void deque_push(struct deque_t *q, void *data);

/**
 * Add data to the front of the deque
 *
 * @q: A deque to add the data to
 * @data: The data to add
 */
void deque_push_left(struct deque_t *q, void *data);

/**
 * Remove data from the front of the deque
 *
 * @q; A deque to remove data from
 */
void deque_pop(struct deque_t *q);

/**
 * Remove data from the back of the deque
 *
 * @q; A deque to remove data from
 */
void deque_pop_left(struct deque_t *q);

/**
 * Return the first element in the deque, without removing it
 *
 * @q: The deque to peek at
 */
void * deque_peek(struct deque_t *q);

/**
 * Return the last element in the deque, without removing it
 *
 * @q: The deque to peek at
 */
void * deque_peek_left(struct deque_t *q);

/**
 * Returns wether or not the deque is empty
 *
 * @q: The deque to test
 */
bool deque_is_empty(struct deque_t *q);

