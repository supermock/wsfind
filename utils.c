#include "utils.h"

void utils_string_init(String* s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

void utils_string_free(String* s) {
  free(s->ptr);
}

void utils_string_set(String* dest, const char* src) {
  // Get source length
  size_t s_len = strlen(src);

  // Realloc size of dest
  dest->ptr = realloc(dest->ptr, s_len);

  // Verify if memory is allocated
  if (dest->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }

  // Copy variable content src to dest
  memcpy(dest->ptr, src, s_len);
  dest->len = s_len;
}

char* utils_string_get(String* s) {
  return s->ptr;
}

size_t utils_string_len(String* s) {
  return s->len;
}

void utils_itoa(char* s, int i) {
  int length = snprintf(NULL, 0, "%d", i);
  snprintf(s, length + 1, "%d", i);
}

char* utils_read_file(char *filename) {
  char *buffer = NULL;
  int string_size, read_size;
  FILE *handler = fopen(filename, "r");

  if (handler) {
    // Seek the last byte of the file
    fseek(handler, 0, SEEK_END);
    // Offset from the first to the last byte, or in other words, filesize
    string_size = ftell(handler);
    // go back to the start of the file
    rewind(handler);

    // Allocate a string that can hold it all
    buffer = (char*) malloc(sizeof(char) * (string_size + 1) );

    // Read it all in one operation
    read_size = fread(buffer, sizeof(char), string_size, handler);

    // fread doesn't set it so put a \0 in the last position
    // and buffer is now officially a string
    buffer[string_size] = '\0';

    if (string_size != read_size) {
      // Something went wrong, throw away the memory and set
      // the buffer to NULL
      free(buffer);
      buffer = NULL;
    }

    // Always remember to close the file.
    fclose(handler);
  }

  return buffer;
}