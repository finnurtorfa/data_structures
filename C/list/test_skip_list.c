#include <stdio.h>
#include <stdlib.h>

#include "skip_list.h"

int main(int argc, char **argv) {
  printf("Starting!\n");
  struct skip_list_t *skip = (struct skip_list_t *)malloc(sizeof(struct skip_list_t));
  init_skip_list(skip);

  for ( int i = 0; i < 1000; i++) {
    skip->length++;
    skip_insert(skip, (void *)i);
    printf("height: %d\n", skip->height);
  }
}

