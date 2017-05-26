//
// Created by 欧阳建华 on 2017/5/26.
//

#include "socket_impl.h"

namespace se {
    namespace network {
        namespace tcp {
            SocketImpl::SocketImpl() {}

            bool SocketImpl::connect(const char *host, unsigned short port) {
                return false;
            }

            bool SocketImpl::listen(unsigned short port) {
                return false;
            }

            int SocketImpl::write(const char *data, int length) {
                return 0;
            }

            int SocketImpl::read(char *data, int length) {
                return 0;
            }
        }
    }
}
