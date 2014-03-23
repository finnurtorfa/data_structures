#include <stdio.h>
#include <stdlib.h>

#include "linked_list.h"

struct linked_list_t {
  int item;
  struct node_t node;
};


int main(int argc, char **argv) {
  struct linked_list_t *tmp;
  struct node_t *pos, *q;

  /* Declare and initialize a list called "my_list" */
  struct linked_list_t my_list;
  LIST_NODE_INIT(&my_list.node);
  
  printf("Appending items to the linked list\n");
  for (int i = 0; i < 5; i++) {
    tmp = (struct linked_list_t *) 
           malloc(sizeof(struct linked_list_t));

    tmp->item = i;

    list_append(&(tmp->node), &(my_list.node));
  }

  printf("Prepending items to the linked list\n");
  for (int i = 4; i >= 0; i--) {
    tmp = (struct linked_list_t *) 
           malloc(sizeof(struct linked_list_t));

    tmp->item = i;

    list_prepend(&(tmp->node), &(my_list.node));
  }

  /* Traverse the list safely and delete every item in the list */
  printf("Looping through the list in forward order\n");
  for_each(pos, q, &my_list.node) {
    tmp = get_list_node(pos, struct linked_list_t, node);
    printf("item: %d\n", tmp->item);
  }
  
  printf("Looping through the list in reverse order and deleting the elements\n");
  for_each_reverse(pos, q, &my_list.node) {
    tmp = get_list_node(pos, struct linked_list_t, node);
    printf("item: %d\n", tmp->item);
    list_remove(pos);
    free(tmp);
  }

  return 0;
}
