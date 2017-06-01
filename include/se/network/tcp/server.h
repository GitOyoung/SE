//
// Created by 欧阳建华 on 2017/5/31.
//

#ifndef SE_SERVER_H
#define SE_SERVER_H

#include <se/network/tcp/socket.h>

namespace se {
    namespace network {
        namespace tcp {


            class Server
            {
            public:
                Server();

                Server& listen(unsigned short port);

            protected:
                virtual void onAcceptError(int error) {};
                virtual void onConnection(Socket& socket, const String& hostName, unsigned short port) {}
            private:
                Socket localSocket;
            };


        }
    }
}

#endif //SE_SERVER_H
