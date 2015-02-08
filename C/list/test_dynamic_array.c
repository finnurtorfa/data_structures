#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "dynamic_array.h"

int main(int argc, char **argv) {
  struct d_array_t array;

  d_array_init(&array);
  
  printf("Size: %d\n", array.size);
  printf("used: %d\n", array.used);

  for ( int i = 0; i < 200; i++ ) {
    d_array_append(&array, (void *)(intptr_t)i);
  }

  printf("\n");
  printf("Size: %d\n", array.size);
  printf("used: %d\n", array.used);

  for ( int i = 0; i < 200; i++ ) {
    if ( i % 2 ) 
      d_array_prepend(&array, (void *)(intptr_t)i);
    else
      d_array_append(&array, (void *)(intptr_t)i);
  }

  printf("\n");
  printf("Size: %d\n", array.size);
  printf("used: %d\n", array.used);

  for (int i = 0; i < 600; i++ ) {
    d_array_add(&array, (void *)(intptr_t)i, i);
  }

  printf("\n");
  printf("Head %d\n", (int)(intptr_t)array.data[0]);
  printf("100 %d\n", (int)(intptr_t)array.data[100]);
  printf("200 %d\n", (int)(intptr_t)array.data[200]);
  printf("300 %d\n", (int)(intptr_t)array.data[300]);
  printf("400 %d\n", (int)(intptr_t)array.data[400]);
  printf("500 %d\n", (int)(intptr_t)array.data[500]);
  printf("600 %d\n", (int)(intptr_t)array.data[600]);
  printf("700 %d\n", (int)(intptr_t)array.data[700]);
  printf("800 %d\n", (int)(intptr_t)array.data[800]);
  printf("900 %d\n", (int)(intptr_t)array.data[900]);
  printf("Tail %d\n", (int)(intptr_t)array.data[array.used-1]);


  int used = array.used;

  for (int i = 0; i < used; i++) {
    d_array_remove_head(&array);
  }

  printf("\n");
  printf("Size: %d\n", array.size);
  printf("used: %d\n", array.used);

  free(array.data);

  return 0;
}

