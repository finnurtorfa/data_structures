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
  
  printf("Adding items to the linked list\n");
  for (int i = 0; i < 5; i++) {
    tmp = (struct linked_list_t *) 
           malloc(sizeof(struct linked_list_t));

    tmp->item = i;

    list_append(&(tmp->node), &(my_list.node));
  }

  /* Traverse the list safely and delete every item in the list */
  for (pos = (&my_list.node)->next, q = pos->next; 
       pos != (&my_list.node); 
       pos = q, q = pos->next) {
    tmp = get_list_node(pos, struct linked_list_t, node);
    printf("item: %d\n", tmp->item);
    printf("Deleting item: %d\n", tmp->item);
    list_remove(pos);
    free(tmp);
  }

  return 0;
}
