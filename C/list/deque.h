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

