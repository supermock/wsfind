#ifndef WS_SOCK_H_
#define WS_SOCK_H_

#include <stdio.h>
#include <stdlib.h>
#include <iwlib.h>
#include "ws_vector.h"

void ws_sock_scan(char* ifname, WSVector* ws_list);

#endif