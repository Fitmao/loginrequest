//
//  WebSocket.c
//  运动会管理系统
//
//  Created by Aaron on 28/12/2017.
//  Copyright © 2017 Aaron. All rights reserved.
//

#include "WebSocket.h"
#include <string.h>

char * IPSTR = "";
int PORT = 80;
#define BUFSIZE 1024

void config(char * ipadd, int port) {
    IPSTR = ipadd;
    PORT = port;
}

void getResponseText(char * dest, char * src) {
    char * text = strstr(src, "\r\n\r\n");
    strcpy(dest, text+4);
}

void get(char * url, char * data) {
    int sockfd, ret, i, h;
    struct sockaddr_in servaddr;
    char str1[4096], str2[4096], *str;
    char * buf = (char *)malloc(sizeof(char)*BUFSIZ);
    socklen_t len;
    fd_set   t_set1;
    struct timeval tv;
    
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        printf("网络连接失败，请检查网络连接\n");
        exit(0);
    };
    
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, IPSTR, &servaddr.sin_addr) <= 0 ){
        printf("网络连接失败，请检查网络连接。ErrorType: inet_pton error.\n");
        exit(0);
    };
    
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        printf("连接到服务器失败。ErrorType: connect error.\n");
        exit(0);
    }
    printf("服务器连接成功。\n");
    
    memset(str2, 0, 4096);
    strcat(str2, "");
    str = (char *)malloc(128);
    len = strlen(str2);
    sprintf(str, "%d", len);
    
    memset(str1, 0, 4096);
    strcat(str1, "GET ");
    strcat(str1, url);
    strcat(str1, " HTTP/1.1\r\n");
    strcat(str1, "Host: www.hostname.cn\r\n");
    strcat(str1, "Content-Type: text/html\r\n");
    strcat(str1, "\r\n\r\n");
    
    ret = (int)write(sockfd, str1, strlen(str1));
    if (ret < 0) {
        printf("请求发送失败，ErrorType: %d, %s\n", errno, strerror(errno));
        exit(0);
    }
    
    FD_ZERO(&t_set1);
    FD_SET(sockfd, &t_set1);
    
    while(1){
        sleep(1);
        tv.tv_sec = 0;
        tv.tv_usec = 0;
        h = 0;
        
        h = select(sockfd + 1, &t_set1, NULL, NULL, &tv);
        
        if (h == 0) break;
        if (h < 0) {
            close(sockfd);
            printf("Socket 异常，即将终止线程。\n");
            return;
        }
        
        if (h > 0) {
            i = (int)read(sockfd, buf, 4095);
            if (i == 0){
                close(sockfd);
                printf("服务器中断了连接。\n");
                return;
            }
            
            strcpy(data, buf);
        }
    }
    
    close(sockfd);
}
