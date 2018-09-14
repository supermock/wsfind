#include "slk.h"

int slk_wh_message_init(cJSON** message) {
  *message = cJSON_CreateObject();
  if (*message == NULL) {
    printf("Failed on instance Message Object\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

void slk_wh_message_destroy(cJSON** message) {
  cJSON_Delete(*message);
}

int slk_wh_message_send(cJSON* message, char* token_url) {
  String data;
  utils_string_init(&data);

  char* raw_json_data = cJSON_Print(message);
  if (raw_json_data != NULL) {
    utils_string_set(&data, raw_json_data);

    struct curl_slist *headers_chunk = NULL;
    headers_chunk = curl_slist_append(headers_chunk, "Content-Type: application/json");
    headers_chunk = curl_slist_append(headers_chunk, "Content-Length: " + utils_string_len(&data));

    if (request_post(token_url, headers_chunk, &data, NULL, 0) == EXIT_SUCCESS) return EXIT_SUCCESS;
  } else {
    printf("Failed on cJSON_Print()\n");
  }

  utils_string_free(&data);
  
  return EXIT_FAILURE;
}

int slk_wh_message_add_text(cJSON** message, char* value) {
  if (cJSON_AddStringToObject(*message, "text", value) == NULL) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int slk_wh_message_add_username(cJSON** message, char* value) {
  if (cJSON_AddStringToObject(*message, "username", value) == NULL) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int slk_wh_message_add_mrkdwn(cJSON** message, int value) {
  cJSON_bool b_mrkdwn;

  if (value) {
    b_mrkdwn = cJSON_True;
  } else {
    b_mrkdwn = cJSON_False;
  }

  if (cJSON_AddBoolToObject(*message, "mrkdwn", b_mrkdwn) == NULL) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

void slk_wh_message_add_attachments(cJSON** message, cJSON** attachment) {
  cJSON* attachments;

  if (!cJSON_HasObjectItem(*message, "attachments")) {
    attachments = cJSON_AddArrayToObject(*message, "attachments");
  } else {
    attachments = cJSON_GetObjectItem(*message, "attachments");
  }

  cJSON_AddItemToArray(attachments, *attachment);
}

//Begin section Attachment
int slk_wh_message_attachment_init(cJSON** attachment) {
  *attachment = cJSON_CreateObject();
  if (*attachment == NULL) {
    printf("Failed on instance Attachment Object");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}

int slk_wh_message_attachment_add_fallback(cJSON** attachment, char* value) {
  if (cJSON_AddStringToObject(*attachment, "fallback", value) == NULL) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int slk_wh_message_attachment_add_color(cJSON** attachment, char* value) {
  if (cJSON_AddStringToObject(*attachment, "color", value) == NULL) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int slk_wh_message_attachment_add_pretext(cJSON** attachment, char* value) {
  if (cJSON_AddStringToObject(*attachment, "pretext", value) == NULL) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int slk_wh_message_attachment_add_author_name(cJSON** attachment, char* value) {
  if (cJSON_AddStringToObject(*attachment, "author_name", value) == NULL) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int slk_wh_message_attachment_add_author_link(cJSON** attachment, char* value) {
  if (cJSON_AddStringToObject(*attachment, "author_link", value) == NULL) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int slk_wh_message_attachment_add_author_icon(cJSON** attachment, char* value) {
  if (cJSON_AddStringToObject(*attachment, "author_icon", value) == NULL) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int slk_wh_message_attachment_add_title(cJSON** attachment, char* value) {
  if (cJSON_AddStringToObject(*attachment, "title", value) == NULL) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int slk_wh_message_attachment_add_title_link(cJSON** attachment, char* value) {
  if (cJSON_AddStringToObject(*attachment, "title_link", value) == NULL) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int slk_wh_message_attachment_add_text(cJSON** attachment, char* value) {
  if (cJSON_AddStringToObject(*attachment, "text", value) == NULL) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

//Begin section Fields
int slk_wh_message_attachment_field_init(cJSON** field, char* v_title, char* v_value, int v_short) {
  *field = cJSON_CreateObject();
  if (*field == NULL) {
    printf("Failed on instance Field Object");
    return EXIT_FAILURE;
  }

  if (v_title) {
    if (cJSON_AddStringToObject(*field, "title", v_title) == NULL) {
      printf("Failed on add Field title property");
      return EXIT_FAILURE;
    }
  }

  if (v_value) {
    if (cJSON_AddStringToObject(*field, "value", v_value) == NULL) {
      printf("Failed on add Field value property");
      return EXIT_FAILURE;
    }
  }

  if (v_short) {
    cJSON_bool b_short;

    if (v_short) {
      b_short = cJSON_True;
    } else {
      b_short = cJSON_False;
    }

    if (cJSON_AddBoolToObject(*field, "short", b_short) == NULL) {
      printf("Failed on add Field short property");
      return EXIT_FAILURE;
    }
  }

  return EXIT_SUCCESS;
}
//End section Fields

void slk_wh_message_attachment_add_fields(cJSON** attachment, cJSON** field) {
  cJSON* fields;

  if (!cJSON_HasObjectItem(*attachment, "fields")) {
    fields = cJSON_AddArrayToObject(*attachment, "fields");
  } else {
    fields = cJSON_GetObjectItem(*attachment, "fields");
  }

  cJSON_AddItemToArray(fields, *field);
}

int slk_wh_message_attachment_add_image_url(cJSON** attachment, char* value) {
  if (cJSON_AddStringToObject(*attachment, "image_url", value) == NULL) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int slk_wh_message_attachment_add_thumb_url(cJSON** attachment, char* value) {
  if (cJSON_AddStringToObject(*attachment, "thumb_url", value) == NULL) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int slk_wh_message_attachment_add_footer(cJSON** attachment, char* value) {
  if (cJSON_AddStringToObject(*attachment, "footer", value) == NULL) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int slk_wh_message_attachment_add_footer_icon(cJSON** attachment, char* value) {
  if (cJSON_AddStringToObject(*attachment, "footer_icon", value) == NULL) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}

int slk_wh_message_attachment_add_ts(cJSON** attachment, char* value) {
  int ts = (unsigned int) atoi(value);

  if (ts == 0) {
    printf("Property [ts](%s) is not a number\n", value);
  }

  if (cJSON_AddNumberToObject(*attachment, "ts", ts) == NULL) return EXIT_FAILURE;
  return EXIT_SUCCESS;
}
//End section Attachment