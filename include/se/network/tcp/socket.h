//
// Created by 欧阳建华 on 2017/5/26.
//

#ifndef SE_SOCKET_H
#define SE_SOCKET_H

#include <se/string.h>

namespace se {
    namespace network {
        namespace tcp {


            class Socket {

            public:
                static int errorCode;
            public:
                typedef int socket_t;

                Socket();
                Socket(const socket_t& s);
                Socket(const Socket& other);


                //server
                bool listen(const char *host, unsigned short port, int &error = errorCode, int backlog = 20) const ;

                int accept(String& remoteAddress, unsigned short &remotePort) const ;


                //client
                bool connect(const char *host, unsigned short port, int &error = errorCode) const ;

                //common
                int send(const void *data, int length, int flags = 0) const ;
                int recv(void *data, int length, unsigned int flags = 0) const ;
                void close();
                bool  shutdown(int how, int& error = errorCode);

                bool bad() const;
            private:
                socket_t socket;
            };
        }
    }
}

#endif //SE_SOCKET_H
