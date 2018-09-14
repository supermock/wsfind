#include "config.h"

int config_load(cJSON** config) {
  char* raw_json = utils_read_file("./wsfind-config.json");

  if (raw_json) {
    *config = cJSON_Parse(raw_json);
    if (*config == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) fprintf(stderr, "Error before: %s\n", error_ptr);
    }

    free(raw_json);
    return EXIT_SUCCESS;
  }

  fprintf(stderr, "Failed on read 'config.json'\n");
  return EXIT_FAILURE;
}