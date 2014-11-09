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
  struct node_t node_vert;
  struct node_t node_horiz;
  void *data;
};

struct skip_list_t {
  struct skip_node_t *head;
  struct skip_node_t *bottom;
  int height;
};

int rand_height(int max);
