//
//  main.c
//  运动会管理系统
//
//  Created by Aaron on 28/12/2017.
//  Copyright © 2017 Aaron. All rights reserved.
//

#include <stdio.h>
#include "WebSocket.h"
#include "Login.h"

int main(int argc, char **argv) {
    
    if (loginWith("root", "") == LOGIN_SUCCESSFUL) {
        printf("登录成功！");
    }
    
    return 0;
} 
