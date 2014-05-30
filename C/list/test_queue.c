#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

int main(int argc, char **argv) {
  printf("Initializing queue!\n");

  struct queue_t my_queue;
  queue_init(&my_queue);

  printf("Enqueue-ing 1,2,3\n");

  queue_enqueue(&my_queue, (void *)1);
  queue_enqueue(&my_queue, (void *)2);
  queue_enqueue(&my_queue, (void *)3);

  int *a = (int *)queue_peek(&my_queue);
  printf("Taking a head at the front of the queue: %d\n", (int)a);

  queue_dequeue(&my_queue);
  printf("Dequeue-ing!\n"); 

  a = (int *)queue_peek(&my_queue);
  printf("Taking a head at the front of the queue: %d\n", (int)a);

  queue_dequeue(&my_queue);
  printf("Dequeue-ing!\n"); 

  a = (int *)queue_peek(&my_queue);
  printf("Taking a head at the front of the queue: %d\n", (int)a);

  queue_dequeue(&my_queue);
  printf("Dequeue-ing!\n"); 

  printf("Done!\n");

  return 0;
}

