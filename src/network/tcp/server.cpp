//
// Created by 欧阳建华 on 2017/5/31.
//

#include <se/network/tcp/server.h>
#include <future>

namespace se::network::tcp {

    Server::Server(): localSocket() {}


    Server& Server::listen(unsigned short port) {
        localSocket.listen("0.0.0.0", port);
        String hostName;
        unsigned short port;
        Socket accept = localSocket.accept(hostName, port);
        while(!accept.bad()) {
            std::async(std::launch::async, [=]() {
                onConnection(accept, hostName, port);
            });

            accept = localSocket.accept(hostName, port);
        }

    }
}