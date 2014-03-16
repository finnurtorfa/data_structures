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

/**
 * A macro that will initialize a list node
 *
 * @ptr: Pointer to the node
 */
#define LIST_NODE_INIT(ptr) \
  (ptr)->next = (ptr); (ptr)->prev = (ptr)

/**
 * A macro for getting a node within the list
 *
 * @ptr:    The &struct node_t pointer
 * @type:   The type of the struct the "ptr" is embedded in
 * @member: The name of the node_t within the struct.
 */
#define get_list_node(ptr, type, member) ({               \
    const typeof( ((type *)0)->member ) *__mptr = (ptr);  \
    (type *)( (char *)__mptr - offsetof(type, member) );  \
    })

/**
 * A macro that returns the offset(in bytes) of a member within a struct
 *
 * @type:   A struct of a specified type
 * @member: A member within a struct of a specified type. 
 */
#define offsetof(type, member) ((size_t) &((type *)0)->member)

struct node_t {
  struct node_t *next, *prev;
};

/**
 * Initialize the list
 *
 * @list: A node, which will be initialized
 */
void init_list_node(struct node_t *list);

/**
 * Add a new node between two known consecutive nodes in the list.
 * This function is only used internally.
 *
 * @new:  The new node to insert
 * @prev: The new node goes after this one
 * @next: The new node goes before this one 
 */
static inline void __list_add(struct node_t *new, 
                              struct node_t *prev,
                              struct node_t *next) {
  next->prev = new;
  new->next  = next;
  new->prev  = prev;
  prev->next = new;
}

/**
 * Add a new node after an old node. Good for implementing stacks.
 *
 * @new: The new node to insert
 * @old: The old node, which the new node will be appended to
 */ 
void list_append(struct node_t *new, struct node_t *old);

/**
 * Add a new node before an old node. Good for implementing queues.
 *
 * @new: The new node to insert
 * @old: The old node to prepend the new one to.
 */
void list_prepend(struct node_t *new, struct node_t *old);

/**
 * Remove node from a list. This function is only used internally.
 *
 * @prev: The previous node to the one being removed
 * @next: The next node to the one being removed
 */
static inline void __list_remove(struct node_t *prev, struct node_t *next) {
  next->prev = prev;
  prev->next = next;
}

/**
 * Remove a node from a list
 *
 * @node: The node which will be removed from the list
 */
void list_remove(struct node_t *node);

#endif
