//
// Created by 欧阳建华 on 2017/5/26.
//

#ifndef SE_SOCKET_IMPL_H
#define SE_SOCKET_IMPL_H

namespace se {
    namespace network {
        namespace tcp {

            class SocketImpl {
            public:
                SocketImpl();

                bool connect(const char *host, unsigned short port);

                bool listen(unsigned short port);

                int write(const char *data, int length);

                int read(char *data, int length);

            private:
            };


        }
    }
}


#endif //SE_SOCKET_IMPL_H
