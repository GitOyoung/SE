//
// Created by 欧阳建华 on 2017/5/26.
//

#include <se/network/tcp/socket.h>


//darwin
#ifdef __DARWIN_UNIX03
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <sys/errno.h>
    #include <unistd.h>
#endif

namespace se {
    namespace network {
        namespace tcp {

            int Socket::defaultInt = 0;

            Socket::Socket() {
               socket = ::socket(AF_INET, SOCK_STREAM, 0);
            }

            Socket::Socket(const socket_t& s): socket(s) {}

            Socket::Socket(const Socket &other): socket(other.socket) {}

            bool Socket::listen(const char *host, unsigned short port, int &error, int backlog) {
                sockaddr_in sa;
                sa.sin_family = AF_INET;
                sa.sin_addr.s_addr = ::inet_addr(host);
                sa.sin_port = htons(port);
                if(::bind(socket, (const sockaddr *)&sa, sizeof(sa)) < 0 || ::listen(socket, backlog) < 0) {
                    error = errno;
                    return false;
                }
                return true;
            }

            Socket Socket::accept(String &remoteAddress, unsigned short &remotePort) {
                sockaddr_in sa;
                socklen_t saLen = sizeof(sa);
                socket_t newSocket = ::accept(socket, (sockaddr *)&sa, &saLen);
                if(newSocket < 0) {
                    return Socket(0);
                }
                remoteAddress = ::inet_ntoa(sa.sin_addr);
                remotePort = ntohs(sa.sin_port);
                return Socket(newSocket);
            }

            bool Socket::connect(const char *host, unsigned short port, int &error) {
                sockaddr_in sa;
                sa.sin_family = AF_INET;
                sa.sin_addr.s_addr = ::inet_addr(host);
                sa.sin_port = htons(port);
                if(::connect(socket, (const sockaddr *)&sa, sizeof(sa)) <  0) {
                    error = errno;
                    return false;
                }
                return true;
            }

            int Socket::send(const void *data, int length, int flags) {
                return (int) ::send(socket, data, length, flags);
            }

            int Socket::recv(void *data, int length, unsigned int flags) {
                return (int) ::recv(socket, data, length, flags);
            }

            void Socket::close() {
                ::close(socket);
            }
            bool Socket::shutdown(int how, int &error) {
                if(::shutdown(socket, how) < 0 ) {
                    error = errno;
                    return false;
                }
                return true;
            }

            bool Socket::bad() const {
                return socket == 0;
            }

        }
    }
}

