#ifndef __LINKED_LIST_H__
#define __LINKED_LIST_H__
/*
 * File: linked_list.h
 * Author: Finnur Smári Torfason
 * Compiler: GCC 4.8.2
 * 
 * Simple linked list implementation
 */
#include <stdio.h>
#include <stdlib.h>

struct node_t {
  struct node_t *next, *prev;
};

#endif
