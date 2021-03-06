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
  
  memmove(&(arr->data[pos+1]), 
          &(arr->data[pos]), 
          (arr->used - pos)*sizeof(void *));

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

  if ( arr->used < INIT_SIZE/2  && arr->size != INIT_SIZE ) {
    void *tmp = (void *) realloc(arr->data, INIT_SIZE * sizeof(void *));

    if ( !tmp ) {
      printf("Reallocation of memory failed!\n");
      free(arr->data);
      exit(-1);
    }
    
    arr->data = tmp;
    arr->size = INIT_SIZE;
  }

  if (  arr->used < INIT_SIZE )
    return;

  if ( arr->used < arr->size/4 ) 
    size /= 2;

  if ( arr->used == arr->size )
    size *= 2;

  if ( arr->size == size ) 
    return;

  void *tmp = (void *) realloc(arr->data, size * sizeof(void *));

  if ( !tmp ) {
    printf("Reallocation of memory failed!\n");
    free(arr->data);
    exit(-1);
  }
  
  arr->data = tmp;
  arr->size = size;
}

void * d_array_remove(struct d_array_t *arr, int pos) {
  void *el;

  if ( pos >= arr->used ) {
    el = arr->data[arr->used--];
    
    d_array_check_resize(arr);

    return el;
  }

  el = arr->data[pos];

  memmove(&(arr->data[pos]), 
          &(arr->data[pos+1]), 
          (arr->used - pos)*sizeof(void *));

  arr->used--;

  d_array_check_resize(arr);

  return el;
}

void * d_array_remove_head(struct d_array_t *arr) {
  return d_array_remove(arr, 0);
}

void * d_array_remove_tail(struct d_array_t *arr) {
  return d_array_remove(arr, arr->used);
}

