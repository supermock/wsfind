#include "ws_sock.h"

void ws_sock_scan(char* ifname, WSVector* ws_list) {
  wireless_scan_head head;
  wireless_scan *result;
  iwrange range;
  int sock;

  /* Open socket to kernel */
  sock = iw_sockets_open();

  /* Get some metadata to use for scanning */
  if (iw_get_range_info(sock, ifname, &range) < 0) {
    printf("Error during iw_get_range_info. Aborting.\n");
    exit(1);
  }

  /* Perform the scan */
  if (iw_scan(sock, ifname, range.we_version_compiled, &head) < 0) {
    printf("Error during iw_scan. Aborting.\n");
    exit(1);
  }

  iw_sockets_close(sock);

  result = head.result;
  while (result != NULL) {
    ws_vector_append(ws_list, result);
    result = result->next;
  }
}