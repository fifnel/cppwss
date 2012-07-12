//
//  main.cpp
//  CppWebSocket
//
//  Created by fifnel on 2012/04/18.
//  Copyright (c) 2012年 fifnel. All rights reserved.
//
#include <iostream>
#include "Server.h"
#include <vector>

using namespace std;

int main(int argc, const char * argv[])
{
    wss::Server server("localhost", "9000");
    server.run();

    return 0;
}

