#include <stdio.h>
#include <string.h>
#include <iwlib.h>
#include <unistd.h>
// #include <stdbool.h> type bool
#include "ws_sock.h"
#include "request.h"
#include "slk.h"
#include "utils.h"
#include "config.h"

static void usage(char* bin) {
  printf("%s [ifname] [seconds]\n", bin);
  exit(0);
}

int main(int argc, char **argv) {
  if (argc < 3) {
    usage(argv[0]);
  }

  char* ifname = argv[1];
  char* seconds = argv[2];

  unsigned int uint_seconds = (unsigned int) atoi(seconds);
  if (uint_seconds == 0) {
    printf("Parameter [seconds](%s) is not a number\n", seconds);
    exit(1);
  }

  //Loading config
  cJSON* config = NULL;
  if (config_load(&config) == EXIT_FAILURE) exit(1);

  cJSON* slack_token_url = cJSON_GetObjectItemCaseSensitive(config, "slack_token_url");
  if (!cJSON_IsString(slack_token_url) || (slack_token_url->valuestring == NULL)) {
    fprintf(stderr, "Failed on load 'slack_token_url' value not is string or null");
  }

  cJSON* ssid = NULL;
  cJSON* ssids = cJSON_GetObjectItemCaseSensitive(config, "ssids");

  WSVector* ws_list = malloc(sizeof(WSVector));
  cJSON* message = NULL;

  for (;;) {
    //Initialize Message
    slk_wh_message_init(&message);

    //Initialize WSVector
    ws_vector_init(ws_list);

    // Scan wireless networks
    ws_sock_scan(ifname, ws_list);

    int finded = 0;
    wireless_scan* ws;

    cJSON_ArrayForEach(ssid, ssids) {
      for (int i = 0; i < ws_list->size; i++) {
        ws = ws_vector_get(ws_list, i);

        if (strcmp(ssid->valuestring, &ws->b.essid[0]) == 0) {
          finded = 1;
          break;
        }
      }

      if (!finded) {
        printf("SSID[%s] not found!\n", ssid->valuestring);

        cJSON* attachment = NULL;
        slk_wh_message_attachment_init(&attachment);

        cJSON* f_ssid = NULL;
        slk_wh_message_attachment_field_init(&f_ssid, "SSID", ssid->valuestring, 1);
        slk_wh_message_attachment_add_fields(&attachment, &f_ssid);

        cJSON* f_interval = NULL;
        slk_wh_message_attachment_field_init(&f_interval, "Interval", argv[2], 1);
        slk_wh_message_attachment_add_fields(&attachment, &f_interval);

        slk_wh_message_attachment_add_color(&attachment, "#F35A00");

        slk_wh_message_add_attachments(&message, &attachment);
      }

      finded = 0;
    }

    slk_wh_message_add_text(&message, "Listed below are all unavailable networks");
    slk_wh_message_add_username(&message, "WSFind");
    slk_wh_message_add_mrkdwn(&message, 1);

    slk_wh_message_send(message, slack_token_url->valuestring);

    //Destroy Message
    slk_wh_message_destroy(&message);
    //Destroy WSVector
    ws_vector_free(ws_list);

    printf("Waiting %ss for next check...\n", seconds);
    sleep(uint_seconds);
  }

  exit(0);
}