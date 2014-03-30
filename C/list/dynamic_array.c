/*
 * File: dynamic_array.c
 * Author: Finnur Smári Torfason
 * Compiler: GCC 4.8.2
 */
#include "dynamic_array.h"

int d_array_init(struct d_array_t *arr) {
  arr->size = INIT_SIZE;
  arr->used = 0;
  arr->data = (void *) calloc(arr->size, arr->size * sizeof(void *));
  
  if ( arr->data == NULL )
    return 0;

  return 1;
}

void d_array_add(struct d_array_t *arr, void *item, int pos) {
  d_array_check_resize(arr);

  if ( arr->data == NULL ) return;

  if ( pos >= arr->used ) {
    arr->data[arr->used++] = item;

    return;
  }

  for ( int i = arr->used-1; i >= pos; i-- ) {
    arr->data[i+1] = arr->data[i];
  }

  arr->used++;
  arr->data[pos] = item;
}

void d_array_append(struct d_array_t *arr, void *item) {
  d_array_add(arr, item, arr->used); 
}

void d_array_prepend(struct d_array_t *arr, void *item) {
  d_array_add(arr, item, 0); 
}

void d_array_check_resize(struct d_array_t *arr) {
  int size = arr->size;

  if ( arr->used < arr->size/4 ) 
    size /= 2;

  if ( arr->used == arr->size ) 
    size *= 2;

  if ( arr->size == size || arr->size > INIT_SIZE )
    return;

  arr->data = (void *) realloc(arr->data, size * sizeof(void *));
  arr->size = size;
}
