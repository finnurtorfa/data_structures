#include <stdio.h>
#include <stdlib.h>

#include "skip_list.h"

int main(int argc, char **argv) {
  printf("Starting!\n");
  for ( int i = 0; i < 1000; i++) {
    int num = rand_height(16);
    printf("%d\n", num);
  }
}

