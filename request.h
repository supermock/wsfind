#ifndef REQUEST_H_
#define REQUEST_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h> // https://curl.haxx.se/libcurl/c/
#include "utils.h"

struct write_body {
  const char *read_ptr;
  size_t size_left;
};

int request_get(char* url, struct curl_slist *chunk,  String* response, int verbose);
int request_post(char* url, struct curl_slist *headers_chunk, String* body, String* response, int verbose);

#endif