#ifndef __DYNAMIC_ARRAY_H__
#define __DYNAMIC_ARRAY_H__
/*
 * File: dynamic_array.h
 * Author: Finnur Smári Torfason
 * Compiler: GCC 4.8.2
 *
 * A basic implementation of a dynamic array
 */

#define INIT_SIZE 100

struct d_array_t { 
  void *data;       // void pointer for the data
  int size;         // Number of available data points
  int cnt;          // current data point were at
  size_t data_size; // Size of each data point. 
};

/**
 * Initialize a dynamic array
 *
 * @arr:  A struct d_array_t pointer to initialize
 */
void d_array_init(struct d_array_t *arr, size_t data_size);

/**
 * Add a new datapoint to the array
 *
 * @arr:  A struct d_array_t pointer 
 * @item: The item to add to the array
 * @pos:  The position in which to add the item
 */
void d_array_add(struct d_array_t *arr, void *item, int pos);

/**
 * Append a new datapoint to the array
 *
 * @arr:  A struct d_array_t pointer 
 * @item: The item to add to the array
 */
void d_array_append(struct d_array_t *arr, void *item);

/**
 * Prepend a new datapoint to the array
 *
 * @arr:  A struct d_array_t pointer 
 * @item: The item to add to the array
 */
void d_array_prepend(struct d_array_t *arr, void *item);

/**
 * Remove an item from an array
 *
 * @arr:  A struct d_array_t pointer 
 * @pos:  The position in which to add the item
 */
void d_array_remove(struct d_array_t *arr, int pos);

/**
 * Remove an item from an array's head
 *
 * @arr:  A struct d_array_t pointer 
 */
void  d_array_remove_head(struct d_array_t *arr);

/**
 * Remove an item from an array's tail
 *
 * @arr:  A struct d_array_t pointer 
 * @pos:  The position of the element to remove
 */
void  d_array_remove_tail(struct d_array_t *arr, int pos);
#endif
