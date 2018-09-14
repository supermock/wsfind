#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string {
  char* ptr;
  size_t len;
} String;

void utils_string_init(String* s);
void utils_string_free(String* s);
void utils_string_set(String* dest, const char* src);
char* utils_string_get(String* s);
size_t utils_string_len(String* s);

void utils_itoa(char* s, int i);
char* utils_read_file(char *filename);

#endif