#include <stdio.h>
#include <stdlib.h>

#include "dynamic_array.h"

int main(int argc, char **argv) {
  struct d_array_t array;

  d_array_init(&array);
  
  printf("Size: %d\n", array.size);
  printf("used: %d\n", array.used);

  for ( int i = 0; i < 200; i++ ) {
    d_array_append(&array, (int *)i);
  }

  printf("\n");
  printf("Size: %d\n", array.size);
  printf("used: %d\n", array.used);

  for ( int i = 0; i < 200; i++ ) {
    if ( i % 2 ) 
      d_array_prepend(&array, (int *)i);
    else
      d_array_append(&array, (int *)i);
  }

  printf("\n");
  printf("Size: %d\n", array.size);
  printf("used: %d\n", array.used);

  for (int i = 0; i < 600; i++ ) {
    d_array_add(&array, (int *)i, i);
  }

  printf("\n");
  printf("Head %d\n", (int)array.data[0]);
  printf("100 %d\n", (int)array.data[100]);
  printf("200 %d\n", (int)array.data[200]);
  printf("300 %d\n", (int)array.data[300]);
  printf("400 %d\n", (int)array.data[400]);
  printf("500 %d\n", (int)array.data[500]);
  printf("600 %d\n", (int)array.data[600]);
  printf("700 %d\n", (int)array.data[700]);
  printf("800 %d\n", (int)array.data[800]);
  printf("900 %d\n", (int)array.data[900]);
  printf("Tail %d\n", (int)array.data[array.used-1]);


  int used = array.used;

  for (int i = 0; i < used; i++) {
    d_array_remove_head(&array);
  }

  printf("\n");
  printf("Size: %d\n", array.size);
  printf("used: %d\n", array.used);

  return 0;
}
