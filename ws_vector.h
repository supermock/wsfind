#ifndef WS_VECTOR_H_
#define WS_VECTOR_H_

#define VECTOR_INITIAL_CAPACITY 20

#include <stdio.h>
#include <stdlib.h>
#include <iwlib.h>

// Define a vector type
typedef struct ws_vector {
  int size;      // slots used so far
  int capacity;  // total available slots
  wireless_scan** data;     // array of integers we're storing
} WSVector;

void ws_vector_init(WSVector *vector);

void ws_vector_append(WSVector *vector, wireless_scan* value);

wireless_scan* ws_vector_get(WSVector *vector, int index);

void ws_vector_double_capacity_if_full(WSVector *vector);

void ws_vector_free(WSVector *vector);

#endif