//
// Created by 欧阳建华 on 2017/5/26.
//

#ifndef SE_SOCKET_H
#define SE_SOCKET_H

#include <se/string.h>

namespace se {
    namespace network {
        namespace tcp {

            class SocketImpl;

            class Socket {
            public:
                Socket();

                //client
                bool  connect(const char *host, unsigned short port);
                void close();

                //server
                bool listen(unsigned short port);

                //common
                int write(const char *data, int length);
                int write(const String& content);

                int read(char *data, int length);

            private:
                SocketImpl *impl;

            };
        }
    }
}

#endif //SE_SOCKET_H
