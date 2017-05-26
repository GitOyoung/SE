//
// Created by 欧阳建华 on 2017/5/26.
//

#include <se/network/tcp/socket.h>

#include "./socket_impl.h"

namespace se {
    namespace network {
        namespace tcp {


            Socket::Socket(): impl(new SocketImpl) {}

            bool Socket::connect(const char *host, unsigned short port) {
                return impl->connect(host, port);
            }

            bool Socket::listen(unsigned short port) {
                return impl->listen(port);
            }

            int Socket::write(const char *data, int length) {
                return  impl->write(data, length);
            }

            int Socket::write(const String &content) {
                return write(content.toStdString().c_str(), content.length());
            }

            int Socket::read(char *data, int length) {
                return impl->read(data, length);
            }




        }
    }
}
