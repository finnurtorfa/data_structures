#include <stdio.h>
#include <stdlib.h>

#include "dynamic_array.h"

int main(int argc, char **argv) {
  struct d_array_t array;

  d_array_init(&array);

  d_array_append(&array, (int *)1);
  d_array_append(&array, (int *)2);
  d_array_append(&array, (int *)3);
  d_array_prepend(&array, (int *)4);
  d_array_prepend(&array, (int *)5);
  d_array_prepend(&array, (int *)6);
  d_array_append(&array, (int *)7);

  for ( int i = 0; i < array.used; i++) {
    printf("%d, %d\n", i, (int)array.data[i]);
  }
  printf("\n");

  d_array_remove(&array, 3);
  d_array_remove_head(&array);
  d_array_remove_tail(&array);
  
  for ( int i = 0; i < array.used; i++) {
    printf("%d, %d\n", i, (int)array.data[i]);
  }

  return 0;
}
