//
//  Login.c
//  运动会管理系统
//
//  Created by Aaron on 28/12/2017.
//  Copyright © 2017 Aaron. All rights reserved.
//

#include "Login.h"
#include "WebSocket.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

/**
 *  在 Apple macOS 10.11 环境下，Xcode 抛弃了 OpenSSL 库，取而代之的是
 *  CommonCrypto 库，MD5 校验算法的用法无异，基本只有命名规则有一定变化
 *  使用 MD5 函数需要导入 CommonDigest.h 头文件。
 *
 *  在 Linux 或 Windows Visual Studio 环境下可能需要单独安装 OpenSSL
 *  才能使用 OpenSSL/md5.h，具体安装方法请见论文附录一
 */

//#include <openssl/md5.h> —— Deprecated on macOS 10.11
#include <CommonCrypto/CommonDigest.h>

#define MD5_DIGEST_LENGTH 16

void hexMD5(char * dest, unsigned char * src) {
    int i;
    char * hex = (char *)malloc(sizeof(char)*MD5_DIGEST_LENGTH);
    for (i = 0;i < MD5_DIGEST_LENGTH;i++) {
        char * str = (char *)malloc(sizeof(char)*2);
        sprintf(str, "%02x", *(src+i));
        strcat(hex, str);
    }
    strcpy(dest, hex);
}

int getTime() {
    return (int)time(0);
}

int validLogin(char * str) {
    if (strcmp(str, "login success") == 0) {
        return LOGIN_SUCCESSFUL;
    } else {
        return LOGIN_FAILED;
    }
}

int loginWith(char * username, char * password) {
    printf("正在登录系统，请稍后...\n");
    
    char timeinterval[11];
    size_t dataLength = strlen(username) + strlen(password);
    const char * userData = (const char *)malloc(sizeof(const char)*dataLength);
    const char * data = (const char *)malloc(sizeof(const char)*11);
    unsigned char md[MD5_DIGEST_LENGTH];
    unsigned char md2[MD5_DIGEST_LENGTH];
    char * md5Str = (char *)malloc(sizeof(char)*MD5_DIGEST_LENGTH);
    char * md5StrWithTimecamp = (char *)malloc(sizeof(char)*MD5_DIGEST_LENGTH);
    char final[1024];
    char responseData[4096];
    char responseText[1024];
    
    sprintf(timeinterval, "%d", getTime());
    strcat((char *)userData, username);
    strcat((char *)userData, password);
    CC_MD5(userData, (CC_LONG)strlen(userData), md);
    hexMD5(md5Str, md);
    
    strcat((char *)data, md5Str);
    strcat((char *)data, timeinterval);

    CC_MD5(data, (CC_LONG)strlen(data), md2);
    hexMD5(md5StrWithTimecamp, md2);
    
    strcat(final, "/test.php?usercode=");
    strcat(final, md5StrWithTimecamp);
    strcat(final, "&timecamp=");
    strcat(final, timeinterval);

    config("127.0.0.1", 8080);
    get(final, responseData);
    getResponseText(responseText, responseData);
    
    return validLogin(responseText);
}





