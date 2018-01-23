//
//  WebSocket.h
//  运动会管理系统
//
//  Created by Aaron on 28/12/2017.
//  Copyright © 2017 Aaron. All rights reserved.
//

#ifndef WebSocket_h
#define WebSocket_h

#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void config(char * ipadd, int port);
void get(char * url, char * data);

/**
 *  
 */
void getResponseText(char * dest, char * src);

#endif /* WebSocket_h */
