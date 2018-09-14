#include "ws_vector.h"

void ws_vector_init(WSVector *vector) {
  // initialize size and capacity
  vector->size = 0;
  vector->capacity = VECTOR_INITIAL_CAPACITY;

  // allocate memory for vector->data
  vector->data = malloc(sizeof(wireless_scan*)* vector->capacity);
}

void ws_vector_append(WSVector *vector, wireless_scan* value) {
  // make sure there's room to expand into
  ws_vector_double_capacity_if_full(vector);

  // append the value and increment vector->size
  vector->data[vector->size++] = value;
}

wireless_scan* ws_vector_get(WSVector *vector, int index) {
  if (index >= vector->size || index < 0) {
    printf("Index %d out of bounds for vector of size %d\n", index, vector->size);
    exit(1);
  }
  return vector->data[index];
}

void ws_vector_double_capacity_if_full(WSVector *vector) {
  if (vector->size >= vector->capacity) {
    // double vector->capacity and resize the allocated memory accordingly
    vector->capacity *= 2;
    vector->data = realloc(vector->data, sizeof(wireless_scan*)* vector->capacity);
  }
}

void ws_vector_free(WSVector *vector) {
  free(vector->data);
}