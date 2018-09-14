#ifndef SLK_H_
#define SLK_H_

#include <stdlib.h>
#include "cJSON.h"
#include "request.h"
#include "utils.h"

int slk_wh_message_init(cJSON** message);
void slk_wh_message_destroy(cJSON** message);
int slk_wh_message_send(cJSON* message, char* token_url);

int slk_wh_message_add_text(cJSON** message, char* value);
int slk_wh_message_add_username(cJSON** message, char* value);
int slk_wh_message_add_mrkdwn(cJSON** message, int value);

void slk_wh_message_add_attachments(cJSON** message, cJSON** attachment);
int slk_wh_message_attachment_init(cJSON** attachment);
int slk_wh_message_attachment_add_fallback(cJSON** attachment, char* value);
int slk_wh_message_attachment_add_color(cJSON** attachment, char* value);
int slk_wh_message_attachment_add_pretext(cJSON** attachment, char* value);
int slk_wh_message_attachment_add_author_name(cJSON** attachment, char* value);
int slk_wh_message_attachment_add_author_link(cJSON** attachment, char* value);
int slk_wh_message_attachment_add_author_icon(cJSON** attachment, char* value);
int slk_wh_message_attachment_add_title(cJSON** attachment, char* value);
int slk_wh_message_attachment_add_title_link(cJSON** attachment, char* value);
int slk_wh_message_attachment_add_text(cJSON** attachment, char* value);
int slk_wh_message_attachment_field_init(cJSON** field, char* v_title, char* v_value, int v_short);
void slk_wh_message_attachment_add_fields(cJSON** attachment, cJSON** field);
int slk_wh_message_attachment_add_image_url(cJSON** attachment, char* value);
int slk_wh_message_attachment_add_thumb_url(cJSON** attachment, char* value);
int slk_wh_message_attachment_add_footer(cJSON** attachment, char* value);
int slk_wh_message_attachment_add_footer_icon(cJSON** attachment, char* value);
int slk_wh_message_attachment_add_ts(cJSON** attachment, char* value);

#endif

// static void test_slk_message() {
//   cJSON* message = NULL;
//   slk_wh_message_init(&message);

//   cJSON* attachment = NULL;
//   slk_wh_message_attachment_init(&attachment);
//   slk_wh_message_attachment_add_color(&attachment, "#F35A00");

//   cJSON* f_ssid = NULL;
//   slk_wh_message_attachment_field_init(&f_ssid, "SSID", "Mock", 1);
//   slk_wh_message_attachment_add_fields(&attachment, &f_ssid);

//   cJSON* f_interval = NULL;
//   slk_wh_message_attachment_field_init(&f_interval, "Interval", "10", 1);
//   slk_wh_message_attachment_add_fields(&attachment, &f_interval);

//   slk_wh_message_add_attachments(&message, &attachment);

//   slk_wh_message_add_text(&message, "Abaixo estão listadas todas as redes indisponíveis");
//   slk_wh_message_add_username(&message, "WSFind");
//   slk_wh_message_add_mrkdwn(&message, 1);

//   slk_wh_message_send(message, "[TOKEN]");

//   slk_wh_message_destroy(&message);
// }