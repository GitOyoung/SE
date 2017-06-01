//
// Created by 欧阳建华 on 2017/4/25.
//

#include <se/string.h>
#include <se/network/tcp/socket.h>
#include <iostream>

int main(int argc, char **argv)
{
    se::network::tcp::Socket socket;

    socket.listen("0.0.0.0", 8989);


    se::String host;
    unsigned  short port;

    se::network::tcp::Socket acsocket(0);

    while(!(acsocket = socket.accept(host, port)).bad()) {
        std::cout<< host.toStdString() << ":" << port << std::endl;
        acsocket.send("Hahaha", 6);
    }

    return 0;
}