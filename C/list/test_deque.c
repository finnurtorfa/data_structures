#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "deque.h"

int main(int argc, char **argv) {
  printf("Initializing deque!\n");

  struct deque_t my_deque;
  deque_init(&my_deque);

  printf("Push-ing 1,2,3\n");

  deque_push(&my_deque, (void *)1);
  deque_push(&my_deque, (void *)2);
  deque_push(&my_deque, (void *)3);

  int *a = (int *)deque_peek(&my_deque);
  printf("Taking a peek at the front of the deque: %d\n", (int)(intptr_t)a);

  a = (int *)deque_peek_left(&my_deque);
  printf("Taking a peek at the back of the deque: %d\n", (int)(intptr_t)a);

  printf("Push-ing left 1,2,3\n");

  deque_push_left(&my_deque, (void *)1);
  deque_push_left(&my_deque, (void *)2);
  deque_push_left(&my_deque, (void *)3);

  deque_pop(&my_deque);
  printf("Pop-ing!\n"); 

  a = (int *)deque_peek(&my_deque);
  printf("Taking a head at the front of the deque: %d\n", (int)(intptr_t)a);

  a = (int *)deque_peek_left(&my_deque);
  printf("Taking a peek at the back of the deque: %d\n", (int)(intptr_t)a);

  deque_pop_left(&my_deque);
  printf("Pop-ing left!\n"); 

  a = (int *)deque_peek(&my_deque);
  printf("Taking a head at the front of the deque: %d\n", (int)(intptr_t)a);

  a = (int *)deque_peek_left(&my_deque);
  printf("Taking a peek at the back of the deque: %d\n", (int)(intptr_t)a);

  deque_pop(&my_deque);
  printf("Pop-ing!\n"); 

  a = (int *)deque_peek(&my_deque);
  printf("Taking a head at the front of the deque: %d\n", (int)(intptr_t)a);

  a = (int *)deque_peek_left(&my_deque);
  printf("Taking a peek at the back of the deque: %d\n", (int)(intptr_t)a);

  deque_pop_left(&my_deque);
  printf("Pop-ing left!\n"); 

  a = (int *)deque_peek(&my_deque);
  printf("Taking a head at the front of the deque: %d\n", (int)(intptr_t)a);

  a = (int *)deque_peek_left(&my_deque);
  printf("Taking a peek at the back of the deque: %d\n", (int)(intptr_t)a);

  deque_pop(&my_deque);
  printf("Pop-ing!\n"); 

  a = (int *)deque_peek(&my_deque);
  printf("Taking a head at the front of the deque: %d\n", (int)(intptr_t)a);

  a = (int *)deque_peek_left(&my_deque);
  printf("Taking a peek at the back of the deque: %d\n", (int)(intptr_t)a);

  deque_pop_left(&my_deque);
  printf("Pop-ing left!\n"); 

  a = (int *)deque_peek(&my_deque);
  printf("Taking a head at the front of the deque: %d\n", (int)(intptr_t)a);

  a = (int *)deque_peek_left(&my_deque);
  printf("Taking a peek at the back of the deque: %d\n", (int)(intptr_t)a);

  deque_pop(&my_deque);

  printf("Done!\n");

  return 0;
}

