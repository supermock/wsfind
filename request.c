#include "request.h"

size_t read_memory_callback(void *dest, size_t size, size_t nmemb, struct write_body *wt) {
  size_t buffer_size = size * nmemb;
 
  if(wt->size_left) {
    /* copy as much as possible from the source to the destination */ 
    size_t copy_this_much = wt->size_left;
    if(copy_this_much > buffer_size) copy_this_much = buffer_size;
    memcpy(dest, wt->read_ptr, copy_this_much);
 
    wt->read_ptr += copy_this_much;
    wt->size_left -= copy_this_much;
    return copy_this_much; /* we copied this many bytes */ 
  }
 
  return 0; /* no more data left to deliver */ 
}

size_t write_memory_callback(void *contents, size_t size, size_t nmemb, struct string *s) {
  size_t realsize = size * nmemb;

  if (s) {
    s->ptr = realloc(s->ptr, s->len + realsize + 1);
    if(s->ptr == NULL) {
      /* out of memory! */ 
      printf("not enough memory (realloc returned NULL)\n");
      return 0;
    }
  
    memcpy(&(s->ptr[s->len]), contents, realsize);
    // memcpy(s->ptr+s->len, contents, realsize); //Equivalent to this
    s->len += realsize;
    s->ptr[s->len] = '\0';
  }
 
  return realsize;
}

/* Example:
String body;
utils_string_init(&body);

struct curl_slist *chunk = NULL;
 
Remove a header curl would otherwise add by itself
chunk = curl_slist_append(chunk, "Accept:");
 
Add a custom header
chunk = curl_slist_append(chunk, "Another: yes");

Modify a header curl otherwise adds differently
chunk = curl_slist_append(chunk, "Host: example.com");

Add a header with "blank" contents to the right of the colon. Note that we're then using a semicolon in the string we pass to curl!
chunk = curl_slist_append(chunk, "X-silly-header;");

int err = request_get("https://jsonplaceholder.typicode.com/todos/1", headers_chunk, &body);

if (err == EXIT_FAILURE) {
  printf("Failed on request_get()");
}

printf("Body: %s\n", utils_string_get(&body));
utils_string_free(&body);
*/
int request_get(char* url, struct curl_slist *headers_chunk,  String* response, int verbose) {
  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  if(curl) {
    if (headers_chunk != NULL)  curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers_chunk);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
    if (verbose) curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

    res = curl_easy_perform(curl);

    /* always cleanup */
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  }

  fprintf(stderr, "curl_easy_init() failed\n");
  return EXIT_FAILURE;
}

int request_post(char* url, struct curl_slist *headers_chunk, String* body, String* response, int verbose) {
  CURL *curl;
  CURLcode res;
 
  curl = curl_easy_init();
  if(curl) {
    headers_chunk = curl_slist_append(headers_chunk, "Expect:");
    headers_chunk = curl_slist_append(headers_chunk, "Transfer-Encoding: chunked");

    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers_chunk);
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(curl, CURLOPT_POST, 1L);
    if (body) {
      struct write_body wt;
      wt.read_ptr = body->ptr;
      wt.size_left = body->len;

      curl_easy_setopt(curl, CURLOPT_READFUNCTION, read_memory_callback);
      curl_easy_setopt(curl, CURLOPT_READDATA, &wt);
    }
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_memory_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, response);
    if (verbose) curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);
    // curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "name=daniel&project=curl");
    // curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, strlen("name=daniel&project=curl"));

    res = curl_easy_perform(curl);

    /* always cleanup */ 
    curl_easy_cleanup(curl);

    if(res != CURLE_OK) {
      fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
  }

  fprintf(stderr, "curl_easy_init() failed\n");
  return EXIT_FAILURE;
}