#pragma once
/*
 * File: queue.h
 * Author: Finnur Smári Torfason
 * Compiler: GCC 4.8.2
 *
 * A basic implementation of a queue
 */
#include <stdlib.h>
#include <string.h>

#include "linked_list.h"

struct queue_t {
  void *data;
  struct node_t node;
};

/**
 * Initialize the queue
 *
 * @q: A queue to initialize
 */
void queue_init(struct queue_t *q);

/**
 * Add data to the back of the queue
 *
 * @q: A queue to add the data to
 * @data: The data to add
 */
void queue_enqueue(struct queue_t *q, void *data);

/**
 * Remove and return data from the front of the queue
 *
 * @q; A queue to remove data from
 */
void * queue_dequeue(struct queue_t *q);
