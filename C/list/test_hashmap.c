#include <stdio.h>
#include <stdlib.h>

#include "hashmap.h"

int main(int argc, char **argv) {
  struct hashmap_t *map = (struct hashmap_t *)malloc(sizeof(struct hashmap_t));

  char *res;

  printf("Starting!\n");

  hashmap_init(map);

  printf("Hashmap size: %d\n", map->size);

  hashmap_insert(map, "key", (void *)"value", 6);
  printf("Hashmap size: %d\n", map->size);

  hashmap_insert(map, "key2", (void *)"value2", 7);
  printf("Hashmap size: %d\n", map->size);

  hashmap_insert(map, "key2", (void *)"value3", 7);
  printf("Hashmap size: %d\n", map->size);

  hashmap_insert(map, "key3", (void *)"random_access_memory", 21);
  printf("Hashmap size: %d\n", map->size);

  res = (char *)hashmap_get(map, "key");
  printf("Key: key, value: %s\n", res);

  res = (char *)hashmap_get(map, "key2");
  printf("Key: key2, value: %s\n", res);

  res = (char *)hashmap_get(map, "key3");
  printf("Key: key3, value: %s\n", res);

  hashmap_remove(map, "key");
  printf("Hashmap size: %d\n", map->size);
  
  hashmap_remove(map, "key_not_in_map");
  printf("Hashmap size: %d\n", map->size);

  printf("Number of buckets before: %d\n", map->num_buckets);
  hashmap_resize(map, 2000);
  printf("Number of buckets after: %d\n", map->num_buckets);
  
  res = (char *)hashmap_get(map, "key2");
  printf("Key: key, value: %s\n", res);

  res = (char *)hashmap_get(map, "key3");
  printf("Key: key, value: %s\n", res);

  hashmap_delete(map);
  printf("Deleted the hashmap!\n");

  return 0;
}

