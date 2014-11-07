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

struct skip_node_t {
  void *data;
  struct node_t node_vert;
  struct node_t node_horiz;
};

