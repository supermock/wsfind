#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"
#include "utils.h"

int config_load(cJSON** config);

#endif

/*
=>config.json<=
{
  "slack_token_url": "https://hooks.slack.com/services/[TOKEN]",
  "ssids": [
    "SSID1",
    "SSID2",
    "SSID3"
  ]
}
*/